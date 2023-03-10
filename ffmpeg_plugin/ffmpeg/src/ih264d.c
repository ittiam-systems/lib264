/* Copyright (c) [2020]-[2023] Ittiam Systems Pvt. Ltd.
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted (subject to the limitations in the
   disclaimer below) provided that the following conditions are met:
   •    Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
   •    Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
   •    None of the names of Ittiam Systems Pvt. Ltd., its affiliates,
   investors, business partners, nor the names of its contributors may be
   used to endorse or promote products derived from this software without
   specific prior written permission.

   NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED
   BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
   BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
   OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
   EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   This Software is an implementation of the AVC/H.264
   standard by Ittiam Systems Pvt. Ltd. (“Ittiam”).
   Additional patent licenses may be required for this Software,
   including, but not limited to, a license from MPEG LA’s AVC/H.264
   licensing program (see https://www.mpegla.com/programs/avc-h-264/).

   NOTWITHSTANDING ANYTHING TO THE CONTRARY, THIS DOES NOT GRANT ANY
   EXPRESS OR IMPLIED LICENSES TO ANY PATENT CLAIMS OF ANY AFFILIATE
   (TO THE EXTENT NOT IN THE LEGAL ENTITY), INVESTOR, OR OTHER
   BUSINESS PARTNER OF ITTIAM. You may only use this software or
   modifications thereto for purposes that are authorized by
   appropriate patent licenses. You should seek legal advice based
   upon your implementation details.

---------------------------------------------------------------
*/


#include <malloc.h>

#include "libavutil/attributes.h"
#include "libavutil/common.h"
#include "libavutil/internal.h"
#include "libavutil/md5.h"
#include "libavutil/opt.h"
#include "libavutil/pixdesc.h"
#include "libavutil/mastering_display_metadata.h"
#include "libavcodec/avcodec.h"
#include "libavcodec/internal.h"
#include "codec_internal.h"
#include "itypedefs.h"
#include "config.h"


#include "iv.h"
#include "ivd.h"
#include "ih264d.h"
#include "ih264d_plugin.h"
#include "ithread.h"

#ifdef WINDOWS_TIMER
#include <windows.h>
#else
#include <sys/time.h>
#endif

#if ARCH_ARM
#include "libavutil/arm/cpu.h"
#else
#include "libavutil/x86/cpu.h"
#endif

#define PEAK_WINDOW_SIZE            8
#define MAX_FRAME_WIDTH             1920
#define MAX_FRAME_HEIGHT            1080
#define MAX_LEVEL_SUPPORTED         50
#define MAX_REF_FRAMES              16
#define MAX_REORDER_FRAMES          16
#define DEFAULT_SHARE_DISPLAY_BUF   0
#define STRIDE                      0
#define DEFAULT_NUM_CORES           1

#define ALIGN8(x) ((((x) + 7) >> 3) << 3)
#define NUM_DISPLAY_BUFFERS 4
#define DEFAULT_FPS         30

#define ENABLE_DEGRADE 0
#define MAX_DISP_BUFFERS    64
#define EXTRA_DISP_BUFFERS  8
#define STRLENGTH 1000

#define DUMP_SINGLE_BUF 0
#define IV_ISFATALERROR(x)         (((x) >> IVD_FATALERROR) & 0x1)

#define ivd_api_function        ih264d_api_function


CHAR ac_cfg_fname[STRLENGTH];
FILE *fp_cfg_file = NULL;
FILE *ps_piclen_file = NULL;
FILE *ps_ip_file = NULL;
FILE *ps_op_file = NULL;
FILE *ps_op_chksum_file = NULL;
WORD32 ret;
CHAR ac_error_str[STRLENGTH];
UWORD8 *pu1_bs_buf;

ivd_out_bufdesc_t *ps_out_buf;
UWORD32 file_pos = 0;
IV_API_CALL_STATUS_T e_dec_status;
UWORD32 u4_ip_frm_ts = 0, u4_op_frm_ts = 0;

UWORD32 i;
UWORD32 u4_ip_buf_len;
UWORD32 frm_cnt = 0;
WORD32 total_bytes_comsumed;
UWORD32 max_op_frm_ts;

WORD32 width = 0, height = 0;


void * ih264a_aligned_malloc(WORD32 alignment, WORD32 size)
{
    return memalign(alignment, size);    
}

void ih264a_aligned_free(void *pv_buf)
{
    free(pv_buf);
    return;
}


/**
*******************************************************************************
*
* @brief
*  Get Architecture details of the platform
*
* @par   Description
* Using ffmpeg macros, get the architecture runtime
*
* @param[in] void
*
* @returns Architecture: supported, SSS3, SSE42 and ARM neon
*
* @remarks
*  Does not check for no-neon currently
*******************************************************************************
*/
static int ivd_ff_get_arch(void)
{

#if ARCH_ARM
    //TODO Check for no-neon
    return ARCH_ARM_A9Q;
#endif
#if ARCH_X86
    int cpu_flags = av_get_cpu_flags();
    if(EXTERNAL_AVX2(cpu_flags))
        return ARCH_X86_AVX2;
    if(EXTERNAL_SSE42(cpu_flags))
        return ARCH_X86_SSE42;
    else if(EXTERNAL_SSSE3(cpu_flags))
        return ARCH_X86_SSSE3;
    else
        return ARCH_X86_GENERIC;
#endif
}

/**
*******************************************************************************
*
* @brief
*  Get number of cores
* @par   Description
*  Using ffmpeg function get number of cores present on the target platform
*  and limit it to thread_count from ffmpeg arguments
*
* @param[in] ps_ctxt
*  Plugin context
*
* @returns Number of cores to be used
*
* @remarks
*
*******************************************************************************
*/
static int ivd_ff_get_num_cores(ctxt_t *ps_ctxt)
{
    AVCodecContext *avctx = ps_ctxt->avctx;
    int num_cores = av_cpu_count();
    num_cores = CLIP3(num_cores, 1, avctx->thread_count);
    num_cores = CLIP3(num_cores, 1, MAX_NUM_CORES);
    return 4;//num_cores;
    //TODO: Get number of cores from parameters
}

/**
*******************************************************************************
*
* @brief
* Deinit decoder by freeing all the allocated memory
*
* @par   Description
* Frees all the memory records allocated and also frees buffers allocated
*
* @param[in] ps_ctxt
* Plugin context
*
* @returns None
*
* @remarks
*
*******************************************************************************
*/
static void ivd_plugin_free(ctxt_t *ps_ctxt)
{
    iv_mem_rec_t *ps_mem_rec;
    UWORD32 i;

    ps_mem_rec = (iv_mem_rec_t*)ps_ctxt->pv_mem_rec_location;

    for(i = 0; i < ps_ctxt->u4_num_mem_rec; i++)
    {
        LOGI(ps_ctxt, 10,  "Freeing Memory cnt %d Base %p", i, ps_mem_rec->pv_base);
        ih264a_aligned_free(ps_mem_rec->pv_base);
        ps_mem_rec->pv_base = NULL;
        ps_mem_rec++;
    }
    
    if(ps_ctxt->pv_mem_rec_location)
    {
        free(ps_ctxt->pv_mem_rec_location);
        ps_ctxt->pv_mem_rec_location = NULL;
    }
    /* Free internal state */

    if(ps_ctxt->pu1_bits_base)
    {
        ih264a_aligned_free(ps_ctxt->pu1_bits_base);
        ps_ctxt->pu1_bits_base = NULL;
    }
    if(ps_ctxt->pv_thread_handle)
    {
        ih264a_aligned_free(ps_ctxt->pv_thread_handle);
        ps_ctxt->pv_thread_handle = NULL;
    }


    return;
}
/**
*******************************************************************************
*
* @brief
* Deinit function for the plugin
*
* @par   Description
* Free all the memory allocated
*
* @param[in] avctx
* AVContext
*
* @returns 0 on success
*
* @remarks
*
*******************************************************************************
*/
static av_cold int ih264_decode_free(AVCodecContext *avctx)
{

    ctxt_t *ps_ctxt = avctx->priv_data;
    ivd_plugin_free(ps_ctxt);

    LOGI(ps_ctxt, 0, "ih264_decode_free done");
    return 0;
}

/**
*******************************************************************************
*
* @brief
* Get Codec version
*
* @par   Description
* Get codec version using GETVERSION api
*
* @param[in] ps_ctxt
* Plugin context
*
* @returns Error status
*
* @remarks
*
*******************************************************************************
*/
static IV_API_CALL_STATUS_T ivd_get_version(ctxt_t *ps_ctxt)
{

    ivd_ctl_getversioninfo_ip_t s_ctl_dec_ip;
    ivd_ctl_getversioninfo_op_t s_ctl_dec_op;
    UWORD8 au1_buf[512];

    void *ps_codec_obj = ps_ctxt->ps_codec_obj;

    IV_API_CALL_STATUS_T i4_status;
    s_ctl_dec_ip.e_cmd = IVD_CMD_VIDEO_CTL;
    s_ctl_dec_ip.e_sub_cmd = IVD_CMD_CTL_GETVERSION;
    s_ctl_dec_ip.u4_size = sizeof(ivd_ctl_getversioninfo_ip_t);
    s_ctl_dec_op.u4_size = sizeof(ivd_ctl_getversioninfo_op_t);
    s_ctl_dec_ip.pv_version_buffer = au1_buf;
    s_ctl_dec_ip.u4_version_buffer_size = sizeof(au1_buf);

    i4_status = ivd_api_function((iv_obj_t *) ps_codec_obj,
        (void *)&(s_ctl_dec_ip),
        (void *)&(s_ctl_dec_op));


    if(i4_status != IV_SUCCESS)
    {
        LOGI(ps_ctxt, 99,
            "Error in Getting Version number e_dec_status = %d u4_error_code = 0x%x",
            i4_status, s_ctl_dec_op.u4_error_code);

    }
    else
    {
        LOGI(ps_ctxt, 99, "Ittiam Decoder Version number: %s",
            (char *)s_ctl_dec_ip.pv_version_buffer);
    }

    return i4_status;
}

#if ENABLE_DYNAMIC_DEGRADE

/**
*******************************************************************************
*
* @brief
* Set degrade params for HEVC decoder
*
* @par   Description
* Set degrade params for HEVC decoder using DEGRADE api
*
* @param[in] ps_ctxt
* Plugin context
*
* @param[in] type
* Type of degrade (Refer to ihevcd_cxa_ctl_degrade_ip_t for details)
*
* @param[in] pics
* Pictures to be degraded (Refer to ihevcd_cxa_ctl_degrade_ip_t for details)
*
* @returns Error status
*
* @remarks
*
*******************************************************************************
*/
static IV_API_CALL_STATUS_T ih264d_set_degrade(ctxt_t *ps_ctxt, UWORD32 type, WORD32 pics)
{
    ih264d_ctl_degrade_ip_t s_ctl_ip;
    ih264d_ctl_degrade_op_t s_ctl_op;
    void *pv_api_ip, *pv_api_op;
    void *ps_codec_obj = ps_ctxt->ps_codec_obj;
    IV_API_CALL_STATUS_T e_dec_status;

    s_ctl_ip.u4_size = sizeof(ih264d_ctl_degrade_ip_t);
    s_ctl_ip.i4_degrade_type = type;
    s_ctl_ip.i4_nondegrade_interval = 4;
    s_ctl_ip.i4_degrade_pics = pics;

    s_ctl_op.u4_size = sizeof(ih264d_ctl_degrade_ip_t);

    pv_api_ip = (void *)&s_ctl_ip;
    pv_api_op = (void *)&s_ctl_op;

    s_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
    s_ctl_ip.e_sub_cmd = (IVD_CONTROL_API_COMMAND_TYPE_T) IH264D_CMD_CTL_DEGRADE;

    e_dec_status = ivd_api_function((iv_obj_t *)ps_codec_obj, pv_api_ip, pv_api_op);

    if(IV_SUCCESS != e_dec_status)
    {
        LOGE(ps_ctxt, 10, "Error in setting degrade level \n");
    }
    return (e_dec_status);

}

/**
*******************************************************************************
*
* @brief
* Enable SKIP non-reference B pictures
*
* @par   Description
* Enable SKIP non-reference B pictures
*
* @param[in] ps_ctxt
* Plugin context
*
* @returns Error status
*
* @remarks
*
*******************************************************************************
*/
static IV_API_CALL_STATUS_T ivd_enable_skipb_frames(ctxt_t *ps_ctxt)
{
    ivd_ctl_set_config_ip_t s_ctl_ip;
    ivd_ctl_set_config_op_t s_ctl_op;
    IV_API_CALL_STATUS_T e_dec_status;
    void *ps_codec_obj = ps_ctxt->ps_codec_obj;

    s_ctl_ip.u4_disp_wd = ps_ctxt->u4_strd;
    s_ctl_ip.e_frm_skip_mode = IVD_SKIP_B;

    s_ctl_ip.e_frm_out_mode = IVD_DISPLAY_FRAME_OUT;
    s_ctl_ip.e_vid_dec_mode = IVD_DECODE_FRAME;
    s_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
    s_ctl_ip.e_sub_cmd = IVD_CMD_CTL_SETPARAMS;
    s_ctl_ip.u4_size = sizeof(ivd_ctl_set_config_ip_t);
    s_ctl_op.u4_size = sizeof(ivd_ctl_set_config_op_t);

    LOGI(ps_ctxt, 0, "Enable SkipB frames \n");
    e_dec_status = ivd_api_function((iv_obj_t *)ps_codec_obj, (void *)&s_ctl_ip,
        (void *)&s_ctl_op);

    if(IV_SUCCESS != e_dec_status)
    {
        LOGI(ps_ctxt, 10, "Error in Enable SkipB frames \n");
    }

    return e_dec_status;
}

/**
*******************************************************************************
*
* @brief
* Disable SKIP non-reference B pictures
*
* @par   Description
* Disable SKIP non-reference B pictures
*
* @param[in] ps_ctxt
* Plugin context
*
* @returns Error status
*
* @remarks
*
*******************************************************************************
*/
static IV_API_CALL_STATUS_T ivd_disable_skip_frames(ctxt_t *ps_ctxt)
{
    ivd_ctl_set_config_ip_t s_ctl_ip;
    ivd_ctl_set_config_op_t s_ctl_op;
    IV_API_CALL_STATUS_T e_dec_status;
    void *ps_codec_obj = ps_ctxt->ps_codec_obj;

    s_ctl_ip.u4_disp_wd = ps_ctxt->u4_strd;
    s_ctl_ip.e_frm_skip_mode = IVD_SKIP_NONE;

    s_ctl_ip.e_frm_out_mode = IVD_DISPLAY_FRAME_OUT;
    s_ctl_ip.e_vid_dec_mode = IVD_DECODE_FRAME;
    s_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
    s_ctl_ip.e_sub_cmd = IVD_CMD_CTL_SETPARAMS;
    s_ctl_ip.u4_size = sizeof(ivd_ctl_set_config_ip_t);
    s_ctl_op.u4_size = sizeof(ivd_ctl_set_config_op_t);
    LOGI(ps_ctxt, 0, "Disable SkipB frames \n");
    e_dec_status = ivd_api_function((iv_obj_t *)ps_codec_obj, (void *)&s_ctl_ip,
        (void *)&s_ctl_op);

    if(IV_SUCCESS != e_dec_status)
    {
        LOGI(ps_ctxt, 10, "Error in Disable Skip frames\n");
    }

    return e_dec_status;
}

/**
*******************************************************************************
*
* @brief
* Compute lateness for the picture being given for display
*
* @par   Description
* Compute lateness based on current time and expected display time
*
* @param[in] ps_ctxt
* Plugin context
*
* @returns None
*
* @remarks
*
*******************************************************************************
*/
static void ivd_set_lateness(ctxt_t *ps_ctxt, mtime_t pts)
{
    if(0 == ps_ctxt->i4_first_pic_display_time_set)
    {
        ps_ctxt->i4_first_pic_display_time_set = 1;
        GETTIME(&ps_ctxt->first_pic_display_time);
    }
    else
    {
        TIMER curtime;
        double pts_us;
        WORD32 actual_time;
        GETTIME(&curtime);
        ELAPSEDTIME(ps_ctxt->first_pic_display_time, curtime, actual_time,frequency);

        /* pts is in ms, convert to us */
        pts_us = pts * 1000;

        if(pts_us && ((pts_us + LATENESS_TIME_THRESHOLD) < actual_time ))
        {
            ps_ctxt->i4_lateness += actual_time - (pts_us + LATENESS_TIME_THRESHOLD);
        }
        else
        {
            ps_ctxt->i4_lateness = 0;
        }
    }
    return;
}

/**
*******************************************************************************
*
* @brief
* Set dynamic degrade based on lateness
*
* @par   Description
* Based on lateness enable/disable dynamic degradation
*
* @param[in] ps_ctxt
* Plugin context
*
* @returns None
*
* @remarks
*
*******************************************************************************
*/
#if 0
static void ivd_set_dynamic_degrade(ctxt_t *ps_ctxt)
{
    if(ps_ctxt->i4_lateness > LATENESS_DEGRADE_THRESH3)
    {
        if(0 == ps_ctxt->i4_skipb_enabled)
        {
            LOGI(ps_ctxt, 99, "Skipping non-ref pictures Lateness %d", ps_ctxt->i4_lateness);
            ivd_enable_skipb_frames(ps_ctxt);
            ps_ctxt->i4_skipb_enabled = 1;
        }
    }
    else if(ps_ctxt->i4_lateness > LATENESS_DEGRADE_THRESH2)
    {
        if(1 == ps_ctxt->i4_skipb_enabled)
        {
            LOGI(ps_ctxt, 99, "Disabling skipping non-ref pictures Lateness %d", ps_ctxt->i4_lateness);
            ivd_disable_skip_frames(ps_ctxt);
            ps_ctxt->i4_skipb_enabled = 0;
        }

        if(ps_ctxt->i4_degrade_type != 15)
        {
            LOGI(ps_ctxt, 99, "Degrade enabled type 15 for non-ref pictures Lateness %d", ps_ctxt->i4_lateness);
            /* Set degrade type for non-ref pictures */
            ih264d_set_degrade(ps_ctxt, 15, 1);
            ps_ctxt->i4_degrade_type = 15;
        }
    }
    else if(ps_ctxt->i4_lateness > LATENESS_DEGRADE_THRESH1)
    {
        if(1 == ps_ctxt->i4_skipb_enabled)
        {
            LOGI(ps_ctxt, 99, "Disabling skipping non-ref pictures Lateness %d", ps_ctxt->i4_lateness);
            ivd_disable_skip_frames(ps_ctxt);
            ps_ctxt->i4_skipb_enabled = 0;
        }
        if(ps_ctxt->i4_degrade_type != 3)
        {
            LOGI(ps_ctxt, 99, "Degrade enabled type 3 for non-ref pictures Lateness %d", ps_ctxt->i4_lateness);
            /* Set degrade type for non-ref pictures */
            ih264d_set_degrade(ps_ctxt, 3, 1);
            ps_ctxt->i4_degrade_type = 3;
        }

    }
    else
    {
        if(ps_ctxt->i4_degrade_type)
        {
            LOGI(ps_ctxt, 99, "Disabling degrade Lateness %d", ps_ctxt->i4_lateness);
            ih264d_set_degrade(ps_ctxt, 0, 0);
            ps_ctxt->i4_degrade_type = 0;
        }
        if(1 == ps_ctxt->i4_skipb_enabled)
        {
            LOGI(ps_ctxt, 99, "Disabling skipping non-ref pictures Lateness %d", ps_ctxt->i4_lateness);
            ivd_disable_skip_frames(ps_ctxt);
            ps_ctxt->i4_skipb_enabled = 0;
        }

    }
    return;
}
#endif

#else
static void ivd_set_lateness(ctxt_t *ps_ctxt, mtime_t pts)
{
    UNUSED(ps_ctxt);
    UNUSED(pts);
    return;
}
#if 0
static void ivd_set_dynamic_degrade(ctxt_t *ps_ctxt)
{
    UNUSED(ps_ctxt);
    return;
}
#endif

#endif

/**
*******************************************************************************
*
* @brief
* Create HEVC decoder
*
* @par   Description
* Create HEVC decoder, set architecture and number of cores
*
* @param[in] ps_ctxt
* Plugin context
*
* @returns
*
* @remarks
*
*******************************************************************************
*/
static WORD32 ih264d_create(ctxt_t *ps_ctxt)
{
    WORD32 ret = 0;
    IV_API_CALL_STATUS_T e_dec_status;
    iv_obj_t *ps_codec_obj;
    /***********************************************************************/
    /*                      Create decoder instance                        */
    /***********************************************************************/
    {

        ps_out_buf = (ivd_out_bufdesc_t *)malloc(sizeof(ivd_out_bufdesc_t));

        {
            iv_num_mem_rec_ip_t s_no_of_mem_rec_query_ip;
            iv_num_mem_rec_op_t s_no_of_mem_rec_query_op;

            s_no_of_mem_rec_query_ip.u4_size = sizeof(s_no_of_mem_rec_query_ip);
            s_no_of_mem_rec_query_op.u4_size = sizeof(s_no_of_mem_rec_query_op);
            s_no_of_mem_rec_query_ip.e_cmd = IV_CMD_GET_NUM_MEM_REC;

            /*****************************************************************************/
            /*   API Call: Get Number of Mem Records                                     */
            /*****************************************************************************/

            
            e_dec_status = ivd_api_function(
                            NULL, (void*)&s_no_of_mem_rec_query_ip,
                            (void*)&s_no_of_mem_rec_query_op);
            if(IV_SUCCESS != e_dec_status)
            {
                LOGE(ps_ctxt,0, "Error in get mem records");
            }

            ps_ctxt->u4_num_mem_rec = s_no_of_mem_rec_query_op.u4_num_mem_rec;

        }

        ps_ctxt->pv_mem_rec_location = malloc(ps_ctxt->u4_num_mem_rec * sizeof(iv_mem_rec_t));
        if(ps_ctxt->pv_mem_rec_location == NULL)
        {
            LOGE(ps_ctxt,0, "Allocation failure for mem_rec_location");

        }

        {
            ih264d_fill_mem_rec_ip_t s_fill_mem_rec_ip;
            ih264d_fill_mem_rec_op_t s_fill_mem_rec_op;
            iv_mem_rec_t *ps_mem_rec;
            UWORD32 total_size;

            s_fill_mem_rec_ip.s_ivd_fill_mem_rec_ip_t.e_cmd =
                            IV_CMD_FILL_NUM_MEM_REC;
            s_fill_mem_rec_ip.s_ivd_fill_mem_rec_ip_t.pv_mem_rec_location =
                            (iv_mem_rec_t *)ps_ctxt->pv_mem_rec_location;
            s_fill_mem_rec_ip.s_ivd_fill_mem_rec_ip_t.u4_max_frm_wd = ps_ctxt->max_wd;
            s_fill_mem_rec_ip.s_ivd_fill_mem_rec_ip_t.u4_max_frm_ht = ps_ctxt->max_ht;
            s_fill_mem_rec_ip.i4_level = ps_ctxt->max_level ;
            s_fill_mem_rec_ip.u4_num_ref_frames = MAX_REF_FRAMES;
            s_fill_mem_rec_ip.u4_num_reorder_frames = MAX_REORDER_FRAMES;
            s_fill_mem_rec_ip.u4_share_disp_buf = ps_ctxt->share_disp_buf;
            s_fill_mem_rec_ip.e_output_format =
                            (IV_COLOR_FORMAT_T)ps_ctxt->e_output_chroma_format;
            s_fill_mem_rec_ip.u4_num_extra_disp_buf = EXTRA_DISP_BUFFERS;

            s_fill_mem_rec_ip.s_ivd_fill_mem_rec_ip_t.u4_size =
                            sizeof(ih264d_fill_mem_rec_ip_t);
            s_fill_mem_rec_op.s_ivd_fill_mem_rec_op_t.u4_size =
                            sizeof(ih264d_fill_mem_rec_op_t);

            ps_mem_rec = (iv_mem_rec_t *)ps_ctxt->pv_mem_rec_location;
            for(i = 0; i < ps_ctxt->u4_num_mem_rec; i++)
                ps_mem_rec[i].u4_size = sizeof(iv_mem_rec_t);

            /*****************************************************************************/
            /*   API Call: Fill Mem Records                                     */
            /*****************************************************************************/

            e_dec_status = ivd_api_function(NULL,
                                                (void *)&s_fill_mem_rec_ip,
                                                (void *)&s_fill_mem_rec_op);

            ps_ctxt->u4_num_mem_rec =
                            s_fill_mem_rec_op.s_ivd_fill_mem_rec_op_t.u4_num_mem_rec_filled;


            if(IV_SUCCESS != e_dec_status)
            {
                LOGE(ps_ctxt,0, "Error in fill mem records: %x",s_fill_mem_rec_op.s_ivd_fill_mem_rec_op_t.u4_error_code);
            }

            ps_mem_rec = (iv_mem_rec_t *)ps_ctxt->pv_mem_rec_location;

            total_size = 0;
            for(i = 0; i < ps_ctxt->u4_num_mem_rec; i++)
            {
                ps_mem_rec->pv_base = ih264a_aligned_malloc(ps_mem_rec->u4_mem_alignment,
                                               ps_mem_rec->u4_mem_size);

                if(ps_mem_rec->pv_base == NULL)
                {
                    LOGE(ps_ctxt,0,
                            "\nAllocation failure for mem record id %d i4_size %d\n",
                            i, ps_mem_rec->u4_mem_size);

                }
                total_size += ps_mem_rec->u4_mem_size;
                ps_mem_rec++;
            }
            LOGI(ps_ctxt,0, "\nTotal memory for codec %d\n", total_size);
        }
    }
        /*****************************************************************************/
        /*   API Call: Initialize the Decoder                                        */
        /*****************************************************************************/
        {
            ih264d_init_ip_t s_init_ip;
            ih264d_init_op_t s_init_op;
            void *fxns = &ivd_api_function;
            iv_mem_rec_t *mem_tab;

            mem_tab = (iv_mem_rec_t*)ps_ctxt->pv_mem_rec_location;
            s_init_ip.s_ivd_init_ip_t.e_cmd = (IVD_API_COMMAND_TYPE_T)IV_CMD_INIT;
            s_init_ip.s_ivd_init_ip_t.pv_mem_rec_location = mem_tab;
            s_init_ip.s_ivd_init_ip_t.u4_frm_max_wd = ps_ctxt->max_wd;
            s_init_ip.s_ivd_init_ip_t.u4_frm_max_ht = ps_ctxt->max_ht;
            s_init_ip.i4_level = ps_ctxt->max_level ;
            s_init_ip.u4_num_ref_frames = MAX_REF_FRAMES;
            s_init_ip.u4_num_reorder_frames = MAX_REORDER_FRAMES;
            s_init_ip.u4_share_disp_buf = ps_ctxt->share_disp_buf;
            s_init_ip.u4_num_extra_disp_buf = EXTRA_DISP_BUFFERS;
            s_init_ip.s_ivd_init_ip_t.u4_num_mem_rec = ps_ctxt->u4_num_mem_rec;

            s_init_ip.s_ivd_init_ip_t.e_output_format =
                            (IV_COLOR_FORMAT_T)ps_ctxt->e_output_chroma_format;
            s_init_ip.s_ivd_init_ip_t.u4_size = sizeof(ih264d_init_ip_t);

            s_init_op.s_ivd_init_op_t.u4_size = sizeof(ih264d_init_op_t);


            ps_codec_obj = (iv_obj_t*)mem_tab[0].pv_base;
            ps_codec_obj->pv_fxns = fxns;
            ps_codec_obj->u4_size = sizeof(iv_obj_t);

            ps_ctxt->ps_codec_obj = ps_codec_obj;

            ret = ivd_api_function((iv_obj_t*)ps_codec_obj, (void *)&s_init_ip,
                                       (void *)&s_init_op);
            if(ret != IV_SUCCESS)
            {
            LOGE(ps_ctxt, 100, "Error in Init %8x",
                s_init_op.s_ivd_init_op_t.u4_error_code);
            return -1;
            }
            LOGI(ps_ctxt, 0, "Codec Initialized");
        }
        /*****************************************************************************/
        /*  Input and output buffer allocation                                       */
        /*****************************************************************************/
            {

                ivd_ctl_getbufinfo_ip_t s_ctl_ip;
                ivd_ctl_getbufinfo_op_t s_ctl_op;

                s_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
                s_ctl_ip.e_sub_cmd = IVD_CMD_CTL_GETBUFINFO;
                s_ctl_ip.u4_size = sizeof(ivd_ctl_getbufinfo_ip_t);
                s_ctl_op.u4_size = sizeof(ivd_ctl_getbufinfo_op_t);
                ret = ivd_api_function((iv_obj_t*)ps_ctxt->ps_codec_obj, (void *)&s_ctl_ip,
                                           (void *)&s_ctl_op);
                if(ret != IV_SUCCESS)
                {
                    LOGE(ps_ctxt,0, "Error in Get Buf Info %x", s_ctl_op.u4_error_code);
                }

                /* Allocate input buffer */
                u4_ip_buf_len = s_ctl_op.u4_min_in_buf_size[0];
                pu1_bs_buf = (UWORD8 *)malloc(u4_ip_buf_len);

                if(pu1_bs_buf == NULL)
                {
                    LOGE(ps_ctxt,0,
                            "\nAllocation failure for input buffer of i4_size %d",
                            u4_ip_buf_len);
                }
                ps_ctxt->num_disp_buf = s_ctl_op.u4_num_disp_bufs;
                /* Allocate output buffer only if display buffers are not shared */
                /* Or if shared and output is 420P */
                if((0 == ps_ctxt->share_disp_buf) || (IV_YUV_420P == ps_ctxt->e_output_chroma_format))
                {
                    UWORD32 outlen;
                    ps_out_buf->u4_min_out_buf_size[0] =
                                    s_ctl_op.u4_min_out_buf_size[0];
                    ps_out_buf->u4_min_out_buf_size[1] =
                                    s_ctl_op.u4_min_out_buf_size[1];
                    ps_out_buf->u4_min_out_buf_size[2] =
                                    s_ctl_op.u4_min_out_buf_size[2];

                    outlen = s_ctl_op.u4_min_out_buf_size[0];
                    if(s_ctl_op.u4_min_num_out_bufs > 1)
                        outlen += s_ctl_op.u4_min_out_buf_size[1];

                    if(s_ctl_op.u4_min_num_out_bufs > 2)
                        outlen += s_ctl_op.u4_min_out_buf_size[2];

                    ps_out_buf->pu1_bufs[0] = (UWORD8 *)malloc(outlen);
                    if(ps_out_buf->pu1_bufs[0] == NULL)
                    {
                        LOGE(ps_ctxt,0,
                                "\nAllocation failure for output buffer of i4_size %d",
                                outlen);
                    }

                    if(s_ctl_op.u4_min_num_out_bufs > 1)
                        ps_out_buf->pu1_bufs[1] = ps_out_buf->pu1_bufs[0]
                                        + (s_ctl_op.u4_min_out_buf_size[0]);

                    if(s_ctl_op.u4_min_num_out_bufs > 2)
                        ps_out_buf->pu1_bufs[2] = ps_out_buf->pu1_bufs[1]
                                        + (s_ctl_op.u4_min_out_buf_size[1]);

                    ps_out_buf->u4_num_bufs = s_ctl_op.u4_min_num_out_bufs;

                }

            }

    
        /*************************************************************************/
        /* set num of cores                                                      */
        /*************************************************************************/
        {

        ih264d_ctl_set_num_cores_ip_t s_ctl_set_cores_ip;
        ih264d_ctl_set_num_cores_op_t s_ctl_set_cores_op;

        s_ctl_set_cores_ip.e_cmd = IVD_CMD_VIDEO_CTL;
        s_ctl_set_cores_ip.e_sub_cmd =(IVD_CONTROL_API_COMMAND_TYPE_T) IH264D_CMD_CTL_SET_NUM_CORES;
        s_ctl_set_cores_ip.u4_num_cores = ps_ctxt->i4_num_cores;
        s_ctl_set_cores_ip.u4_size = sizeof(ih264d_ctl_set_num_cores_ip_t);
        s_ctl_set_cores_op.u4_size = sizeof(ih264d_ctl_set_num_cores_op_t);


        ret = ivd_api_function((iv_obj_t*)ps_codec_obj, (void *)&s_ctl_set_cores_ip,
                                   (void *)&s_ctl_set_cores_op);
        if(ret != IV_SUCCESS)
        {
            LOGE(ps_ctxt, 100,
                    "\nError in setting number of cores 0x%x",
                    s_ctl_set_cores_op.u4_error_code);
                return -1;
        }

        }
        /*************************************************************************/
        /* set processsor                                                        */
        /*************************************************************************/
        {

        ih264d_ctl_set_processor_ip_t s_ctl_set_num_processor_ip;
        ih264d_ctl_set_processor_op_t s_ctl_set_num_processor_op;

        s_ctl_set_num_processor_ip.e_cmd = IVD_CMD_VIDEO_CTL;
        s_ctl_set_num_processor_ip.e_sub_cmd =(IVD_CONTROL_API_COMMAND_TYPE_T) IH264D_CMD_CTL_SET_PROCESSOR;
        s_ctl_set_num_processor_ip.u4_arch = ps_ctxt->e_arch;
        s_ctl_set_num_processor_ip.u4_soc = ps_ctxt->e_soc;
        s_ctl_set_num_processor_ip.u4_size = sizeof(ih264d_ctl_set_processor_ip_t);
        s_ctl_set_num_processor_op.u4_size = sizeof(ih264d_ctl_set_processor_op_t);

        ret = ivd_api_function((iv_obj_t*)ps_codec_obj, (void *)&s_ctl_set_num_processor_ip,
                                   (void *)&s_ctl_set_num_processor_op);
        if(ret != IV_SUCCESS)
        {
            LOGE(ps_ctxt, 100, "\nError in setting Processor type 0x%x",
                    s_ctl_set_num_processor_op.u4_error_code);
                return -1;
        }

        }
    
    return ret;

}

static void set_app_params(ctxt_t *ps_ctxt)
{
    ps_ctxt->avctx->width = ps_ctxt->i4_pic_wd;
    ps_ctxt->avctx->height = ps_ctxt->i4_pic_ht;
    //TODO Change to handle frame cropping
    //Better initialize from hvcC box

    if(0 == ps_ctxt->avctx->coded_width)
        ps_ctxt->avctx->coded_width = ALIGN64(ps_ctxt->avctx->width);
    if(0 == ps_ctxt->avctx->coded_height)
        ps_ctxt->avctx->coded_height = ps_ctxt->avctx->height;
    return;
}

/**
*******************************************************************************
*
* @brief
* Header decode
*
* @par   Description
* Search for SPS/PPS and detect profile, call codec create, and decode header
*
* @param[in] ps_ctxt
* Plugin context
*
* @param[in] pu1_bits_base
* Input bitstream
*
* @param[in] i4_bits_size
* Number of bytes in the input bitstream
*
* @returns 0 on success, -1 on error
*
* @remarks
*
*******************************************************************************
*/
static int ivd_h264_header_decode(ctxt_t *ps_ctxt,
    UWORD8 *pu1_bits_base,
    WORD32 i4_bits_size)
{
    WORD32 ret = 0;

    LOGI(ps_ctxt, 0, "Setting the decoder in header decode mode");
    /*****************************************************************************/
    /*   Decode header to get width and height and buffer sizes                  */
    /*****************************************************************************/
    {

        ivd_ctl_set_config_ip_t s_ctl_ip;
        ivd_ctl_set_config_op_t s_ctl_op;

        s_ctl_ip.u4_disp_wd = STRIDE;
        if(NULL != ps_ctxt->disp_pic) s_ctl_ip.u4_disp_wd = ps_ctxt->u4_strd;
        
        s_ctl_ip.e_frm_skip_mode = IVD_SKIP_NONE;
        s_ctl_ip.e_frm_out_mode = IVD_DISPLAY_FRAME_OUT;
        s_ctl_ip.e_vid_dec_mode = IVD_DECODE_HEADER;
        s_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
        s_ctl_ip.e_sub_cmd = IVD_CMD_CTL_SETPARAMS;
        s_ctl_ip.u4_size = sizeof(ivd_ctl_set_config_ip_t);
        s_ctl_op.u4_size = sizeof(ivd_ctl_set_config_op_t);


        ret = ivd_api_function((iv_obj_t*)ps_ctxt->ps_codec_obj, (void *)&s_ctl_ip,
                                   (void *)&s_ctl_op);
        if(ret != IV_SUCCESS)
        {
            LOGE(ps_ctxt, 100,
                "\nError in setting the codec in header decode mode 0x%x",
                s_ctl_op.u4_error_code);
            return -1;
        }
    }
    

        LOGI(ps_ctxt, 0, "Calling the decoder to decode header");
        {
            ivd_video_decode_ip_t s_video_decode_ip;
            ivd_video_decode_op_t s_video_decode_op;
            
            s_video_decode_ip.e_cmd = IVD_CMD_VIDEO_DECODE;
            s_video_decode_ip.u4_ts = 0;
            s_video_decode_ip.pv_stream_buffer = pu1_bits_base;
            s_video_decode_ip.u4_num_Bytes = i4_bits_size;
            s_video_decode_ip.u4_size = sizeof(ivd_video_decode_ip_t);
            s_video_decode_op.u4_size = sizeof(ivd_video_decode_op_t);

            /*****************************************************************************/
            /*   API Call: Header Decode                                                  */
            /*****************************************************************************/
    
            ret = ivd_api_function((iv_obj_t *)ps_ctxt->ps_codec_obj, (void *)&s_video_decode_ip,
                                       (void *)&s_video_decode_op);
            

            if(ret != IV_SUCCESS)
            {
                LOGE(ps_ctxt, 50, "Error in Header decode : ret %x Error %x\n",
                    ret, s_video_decode_op.u4_error_code);

                //TODO Handle change in resolution by flushing the decoder output and calling reset
            }
            LOGI(ps_ctxt, 50, "After header decode Width %d Height %d",
                s_video_decode_op.u4_pic_wd, s_video_decode_op.u4_pic_ht);
            ps_ctxt->i4_pic_wd = s_video_decode_op.u4_pic_wd;
            ps_ctxt->i4_pic_ht = s_video_decode_op.u4_pic_ht;

            ps_ctxt->avctx->pix_fmt = AV_PIX_FMT_YUV420P;

            ps_ctxt->e_output_format = s_video_decode_op.e_output_format;

            if(ps_ctxt->i4_pic_wd &&  ps_ctxt->i4_pic_ht)
            {
                ps_ctxt->i4_header_done = 1;
                set_app_params(ps_ctxt);
            }

    {
        ivd_ctl_set_config_ip_t s_ctl_ip;
        ivd_ctl_set_config_op_t s_ctl_op;

        s_ctl_ip.u4_disp_wd = STRIDE;
        if(NULL != ps_ctxt->disp_pic) s_ctl_ip.u4_disp_wd = ps_ctxt->u4_strd;

        s_ctl_ip.e_frm_skip_mode = IVD_SKIP_NONE;
        s_ctl_ip.e_frm_out_mode = IVD_DISPLAY_FRAME_OUT;
        s_ctl_ip.e_vid_dec_mode = IVD_DECODE_FRAME;
        s_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
        s_ctl_ip.e_sub_cmd = IVD_CMD_CTL_SETPARAMS;
        s_ctl_ip.u4_size = sizeof(ivd_ctl_set_config_ip_t);
        s_ctl_op.u4_size = sizeof(ivd_ctl_set_config_op_t);

        ret = ivd_api_function((iv_obj_t *)ps_ctxt->ps_codec_obj,
            (void *)&s_ctl_ip, (void *)&s_ctl_op);

        if(ret != IV_SUCCESS)
        {
            LOGE(ps_ctxt, 100,
                "\nError in setting the codec in frame decode mode 0x%x",
                s_ctl_op.u4_error_code);
            return -1;
        }
    }

    ivd_get_version(ps_ctxt);
    }
    return(0);
}


/**
*******************************************************************************
*
* @brief
* Get buffer to be sent to decoder to get the display picture
*
* @par   Description
* Allocate/get a display buffer to be sent to decoder
* Initialize buffer pointers and stride
*
* @param[in] ps_ctxt
* Plugin context

* @returns display picture structure
*
* @remarks
*
*******************************************************************************
*/
static AVFrame *ivd_ff_get_disp_pic(ctxt_t *ps_ctxt)
{
    AVCodecContext *avctx = ps_ctxt->avctx;
    AVFrame *disp_pic;
    WORD32 luma_size;
    WORD32 chroma_size;

    disp_pic = av_frame_alloc();

    LOGI(ps_ctxt, 0, "Allocating av_frame_alloc %p", ps_ctxt->disp_pic);
    ff_get_buffer(avctx, disp_pic, 0);
    av_frame_make_writable(disp_pic);


    ps_ctxt->i4_disp_strd = disp_pic->linesize[0];

    if(IV_RGBA_8888 == ps_ctxt->e_output_chroma_format)
    {
        ps_ctxt->i4_disp_strd /= 4;
    }
    else if(10 == ps_ctxt->u4_bit_depth)
    {
        ps_ctxt->i4_disp_strd /= 2;
    }

    luma_size = ps_ctxt->i4_disp_strd * (ps_ctxt->i4_pic_ht);

    if(IV_YUV_422P == ps_ctxt->e_output_format)
    {
        chroma_size = ps_ctxt->i4_disp_strd * ps_ctxt->i4_pic_ht / 2;
    }
    else
    {
        chroma_size = ps_ctxt->i4_disp_strd * ps_ctxt->i4_pic_ht / 4;
    }



    ps_ctxt->pv_disp_buf[0] = &disp_pic->data[0][0];
    ps_ctxt->pv_disp_buf[1] = &disp_pic->data[1][0];
    ps_ctxt->pv_disp_buf[2] = &disp_pic->data[2][0];

    {
        UWORD8 *pu1_buf = (UWORD8 *)ps_ctxt->pv_disp_buf[0];

        pu1_buf += luma_size;
        if(NULL == ps_ctxt->pv_disp_buf[1])
            ps_ctxt->pv_disp_buf[1] = pu1_buf;

        pu1_buf += chroma_size;
        if(NULL == ps_ctxt->pv_disp_buf[2])
            ps_ctxt->pv_disp_buf[2] = pu1_buf;
    }

    return disp_pic;

}

/**
*******************************************************************************
*
* @brief
* Decode a picture
*
* @par   Description
* Decode a picture
* If header decode is not done, try decoding header till SPS is done
*
* @param[in] ps_ctxt
* Plugin context

* @returns
*
* @remarks
*
*******************************************************************************
*/
static int ivd_h264_decode_frame(ctxt_t *ps_ctxt)
{
    IV_API_CALL_STATUS_T ret;
    WORD32 timestamp_id = 0;

    ps_ctxt->i4_output_present = 0;
    /* If input is zero bytes, then set the decoder in flush mode */
    if(0 == ps_ctxt->u4_num_bytes)
    {
        ivd_ctl_flush_ip_t s_ctl_ip;
        ivd_ctl_flush_op_t s_ctl_op;

        s_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
        s_ctl_ip.e_sub_cmd = IVD_CMD_CTL_FLUSH;
        s_ctl_ip.u4_size = sizeof(ivd_ctl_flush_ip_t);
        s_ctl_op.u4_size = sizeof(ivd_ctl_flush_op_t);
        ret = ivd_api_function((iv_obj_t *)ps_ctxt->ps_codec_obj,
            (void *)&s_ctl_ip, (void *)&s_ctl_op);

        if(ret != IV_SUCCESS)
        {
            LOGI(ps_ctxt, 10, "Error in Setting the decoder in flush mode\n");
        }
    }

    if(0 == ps_ctxt->i4_header_done)
    {
        ret = ivd_h264_header_decode(ps_ctxt, ps_ctxt->pu1_inp, ps_ctxt->u4_num_bytes);
        if(ret != IV_SUCCESS)
        {
            return AVERROR_INVALIDDATA;
        }

        /* If header was not successfully decoded, release input buffer and return */
        /* ALso return if all the bytes were consumed in header decode itself */

        if((0 == ps_ctxt->i4_header_done) || (4 > ps_ctxt->u4_num_bytes))
        {
            LOGE(ps_ctxt, 0, "Header decode failed");
            if(ps_ctxt->i4_thread_created)
                ithread_exit(0);

            return AVERROR_INVALIDDATA;
        }
    }

    {
        WORD32 i;
        timestamp_id = 0;
        for(i = 0; i < MAX_TIMESTAMP_CNT;i++)
        {
            if(0 == ps_ctxt->ai4_timestamp_valid[i])
            {
                timestamp_id = i;
                break;
            }
        }
        LOGI(ps_ctxt, 0, "timestamp_id %d", timestamp_id);
        ps_ctxt->ai8_timestamp[timestamp_id] = ps_ctxt->in_pts;
        ps_ctxt->ai4_timestamp_valid[timestamp_id] = 1;
    }

    ps_ctxt->disp_pic = ivd_ff_get_disp_pic(ps_ctxt);

    {
        ivd_ctl_set_config_ip_t s_ctl_ip;
        ivd_ctl_set_config_op_t s_ctl_op;

        s_ctl_ip.u4_disp_wd = STRIDE;
        if(NULL != ps_ctxt->disp_pic) s_ctl_ip.u4_disp_wd = ps_ctxt->u4_strd;

        s_ctl_ip.e_frm_skip_mode = IVD_SKIP_NONE;
        s_ctl_ip.e_frm_out_mode = IVD_DISPLAY_FRAME_OUT;
        s_ctl_ip.e_vid_dec_mode = IVD_DECODE_FRAME;
        s_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
        s_ctl_ip.e_sub_cmd = IVD_CMD_CTL_SETPARAMS;
        s_ctl_ip.u4_size = sizeof(ivd_ctl_set_config_ip_t);
        s_ctl_op.u4_size = sizeof(ivd_ctl_set_config_op_t);


        ret = ivd_api_function((iv_obj_t *)ps_ctxt->ps_codec_obj,
            (void *)&s_ctl_ip, (void *)&s_ctl_op);

        if(ret != IV_SUCCESS)
        {
            LOGE(ps_ctxt, 100,
                "\nError in setting the codec in frame decode mode 0x%x",
                s_ctl_op.u4_error_code);
            if(ps_ctxt->i4_thread_created)
            {
                ithread_exit(0);
            }

            return ps_ctxt->u4_num_bytes;
        }
    }

    {
        ivd_video_decode_ip_t s_video_decode_ip;
        ivd_video_decode_op_t s_video_decode_op;


        WORD32 luma_size;
        WORD32 chroma_size;
        WORD32 bit_depth;

        UWORD32 i4_time_diff;
        UWORD32 i4_delay;
        TIMER s_start_timer;
        TIMER s_end_timer;

        s_video_decode_ip.e_cmd = IVD_CMD_VIDEO_DECODE;
        s_video_decode_ip.u4_ts = timestamp_id;
        s_video_decode_ip.pv_stream_buffer = ps_ctxt->pu1_inp;
        s_video_decode_ip.u4_num_Bytes = ps_ctxt->u4_num_bytes;
        s_video_decode_ip.u4_size = sizeof(ivd_video_decode_ip_t);

        luma_size = ps_ctxt->i4_disp_strd * (ps_ctxt->i4_pic_ht);
        if(IV_YUV_422P == ps_ctxt->e_output_format)
        {
            chroma_size = ps_ctxt->i4_disp_strd * ps_ctxt->i4_pic_ht / 2;
        }
        else
        {
            chroma_size = ps_ctxt->i4_disp_strd * ps_ctxt->i4_pic_ht / 4;
        }

        if((IV_YUV_420SP_UV == ps_ctxt->e_output_chroma_format)
            || (IV_YUV_420SP_VU == ps_ctxt->e_output_chroma_format))
            chroma_size *= 2;

        if(10 == ps_ctxt->u4_bit_depth)
        {
            bit_depth = 2;
        }
        else
        {
            bit_depth = 1;
        }

        s_video_decode_ip.s_out_buffer.u4_min_out_buf_size[0] = luma_size
            * bit_depth;
        s_video_decode_ip.s_out_buffer.u4_min_out_buf_size[1] = chroma_size
            * bit_depth;
        s_video_decode_ip.s_out_buffer.u4_min_out_buf_size[2] = chroma_size
            * bit_depth;

        s_video_decode_ip.s_out_buffer.pu1_bufs[0] = ps_ctxt->pv_disp_buf[0];
        s_video_decode_ip.s_out_buffer.pu1_bufs[1] = ps_ctxt->pv_disp_buf[1];
        s_video_decode_ip.s_out_buffer.pu1_bufs[2] = ps_ctxt->pv_disp_buf[2];
        s_video_decode_ip.s_out_buffer.u4_num_bufs = 3;

        s_video_decode_op.u4_size = sizeof(ivd_video_decode_op_t);
        s_video_decode_op.s_sei_decode_op.u1_sei_mdcv_params_present_flag = 0;
        s_video_decode_op.s_sei_decode_op.u1_sei_cll_params_present_flag = 0;


      /*****************************************************************************/
      /*   API Call: Video Decode */
      /*****************************************************************************/        
        GETTIME(&s_start_timer);

        ret = ivd_api_function((iv_obj_t *)ps_ctxt->ps_codec_obj, (void *)&s_video_decode_ip,
                                       (void *)&s_video_decode_op);

        ps_ctxt->e_output_format = s_video_decode_op.e_output_format;


        GETTIME(&s_end_timer);
        ELAPSEDTIME(s_start_timer,s_end_timer,i4_time_diff,frequency);
        
        {
            UWORD32 peak_avg, id;
            ps_ctxt->u4_tot_cycles += i4_time_diff;
            ps_ctxt->peak_window[ps_ctxt->peak_window_idx++] = i4_time_diff;
            if(ps_ctxt->peak_window_idx == PEAK_WINDOW_SIZE)
                ps_ctxt->peak_window_idx = 0;
            peak_avg = 0;
            for(id = 0; id < PEAK_WINDOW_SIZE; id++)
            {
                peak_avg += ps_ctxt->peak_window[id];
            }
            peak_avg /= PEAK_WINDOW_SIZE;
            if(peak_avg > ps_ctxt->peak_avg_max) ps_ctxt->peak_avg_max = peak_avg;
            ps_ctxt->i4_pic_cnt++;

            LOGI(ps_ctxt,
                99,
                "\n FrameNum: %4d TimeTaken(microsec): %6d AvgTime: %6d Delay: %6d, PeakAvgTimeMax: %6d NumBytes: %6d \n",
                ps_ctxt->i4_pic_cnt, i4_time_diff,
                ps_ctxt->u4_tot_cycles / ps_ctxt->i4_pic_cnt, i4_delay,
                ps_ctxt->peak_avg_max,
                s_video_decode_op.u4_num_bytes_consumed);
            
        }

        if(ret != IV_SUCCESS)
        {
            LOGI(ps_ctxt, 0, "Error in video Frame decode : ret %x Error %x\n",
                ret, s_video_decode_op.u4_error_code);

            //TODO Handle change in resolution by flushing the decoder output and calling reset
        }

      /*************************************************************************/
      /* Get SEI MDCV parameters */
      /*************************************************************************/
      if (1 == s_video_decode_op.s_sei_decode_op.u1_sei_mdcv_params_present_flag) {

        AVMasteringDisplayMetadata *metadata = av_mastering_display_metadata_create_side_data(ps_ctxt->disp_pic);

        ih264d_ctl_get_sei_mdcv_params_ip_t s_ctl_get_sei_mdcv_params_ip = {0};
        ih264d_ctl_get_sei_mdcv_params_op_t s_ctl_get_sei_mdcv_params_op = {0};

        s_ctl_get_sei_mdcv_params_ip.e_cmd = IVD_CMD_VIDEO_CTL;
        s_ctl_get_sei_mdcv_params_ip.e_sub_cmd =
            (IVD_CONTROL_API_COMMAND_TYPE_T) IH264D_CMD_CTL_GET_SEI_MDCV_PARAMS;
        s_ctl_get_sei_mdcv_params_ip.u4_size =
            sizeof(ih264d_ctl_get_sei_mdcv_params_ip_t);
        s_ctl_get_sei_mdcv_params_op.u4_size =
            sizeof(ih264d_ctl_get_sei_mdcv_params_op_t);

        ret = ivd_api_function((iv_obj_t *) ps_ctxt->ps_codec_obj,
                               (void *) &s_ctl_get_sei_mdcv_params_ip,
                               (void *) &s_ctl_get_sei_mdcv_params_op);


        /* Fill MDCV data */
        /** H264 uses a g,b,r ordering, which we convert to a more natural r,g,b */
	{
        const int mapping[3] = {2, 0, 1};

        const int chroma_den = 50000;
        const int luma_den = 10000;
        int i;

       
        if (!metadata)
            return AVERROR(ENOMEM);
        
        for (i = 0; i < 3; i++) {
            const int j = mapping[i];
            metadata->display_primaries[i][0].num = s_ctl_get_sei_mdcv_params_op.au2_display_primaries_x[j];
            metadata->display_primaries[i][0].den = chroma_den;
            metadata->display_primaries[i][1].num = s_ctl_get_sei_mdcv_params_op.au2_display_primaries_y[j];
            metadata->display_primaries[i][1].den = chroma_den;

       }
        metadata->white_point[0].num = s_ctl_get_sei_mdcv_params_op.u2_white_point_x;
        metadata->white_point[0].den = chroma_den;
        metadata->white_point[1].num = s_ctl_get_sei_mdcv_params_op.u2_white_point_y;
        metadata->white_point[1].den = chroma_den;

        metadata->max_luminance.num = s_ctl_get_sei_mdcv_params_op.u4_max_display_mastering_luminance;
        metadata->max_luminance.den = luma_den;
        metadata->min_luminance.num = s_ctl_get_sei_mdcv_params_op.u4_min_display_mastering_luminance;
        metadata->min_luminance.den = luma_den;
        metadata->has_luminance = 1;
        metadata->has_primaries = 1;

        
        if (IV_SUCCESS != ret) {
          LOGE(ps_ctxt,0,"MDCV SEI params not present : Error %x\n",
                 s_ctl_get_sei_mdcv_params_op.u4_error_code);
        }
	}
      }

      /*************************************************************************/
      /* Get SEI CLL parameters */
      /*************************************************************************/
      if (1 == s_video_decode_op.s_sei_decode_op.u1_sei_cll_params_present_flag) {
        
        AVContentLightMetadata *metadata =
            av_content_light_metadata_create_side_data(ps_ctxt->disp_pic);

        ih264d_ctl_get_sei_cll_params_ip_t s_ctl_get_sei_cll_params_ip = {0};
        ih264d_ctl_get_sei_cll_params_op_t s_ctl_get_sei_cll_params_op = {0};

        s_ctl_get_sei_cll_params_ip.e_cmd = IVD_CMD_VIDEO_CTL;
        s_ctl_get_sei_cll_params_ip.e_sub_cmd =
            (IVD_CONTROL_API_COMMAND_TYPE_T) IH264D_CMD_CTL_GET_SEI_CLL_PARAMS;
        s_ctl_get_sei_cll_params_ip.u4_size =
            sizeof(ih264d_ctl_get_sei_cll_params_ip_t);
        s_ctl_get_sei_cll_params_op.u4_size =
            sizeof(ih264d_ctl_get_sei_cll_params_op_t);

        ret = ivd_api_function((iv_obj_t *) ps_ctxt->ps_codec_obj,
                               (void *) &s_ctl_get_sei_cll_params_ip,
                               (void *) &s_ctl_get_sei_cll_params_op);

        if (!metadata)
            return AVERROR(ENOMEM);
        metadata->MaxCLL  = s_ctl_get_sei_cll_params_op.u2_max_content_light_level;
        metadata->MaxFALL = s_ctl_get_sei_cll_params_op.u2_max_pic_average_light_level;


        if (IV_SUCCESS != ret) {
          LOGE(ps_ctxt,0,"CLL SEI params not present : Error %x\n",
                 s_ctl_get_sei_cll_params_op.u4_error_code);
        }
      }

        /* If frame was not decoded, then free the timestamp */
        if(0 == s_video_decode_op.u4_frame_decoded_flag)
        {
            ps_ctxt->ai4_timestamp_valid[s_video_decode_ip.u4_ts] = 0;
        }
        if(1 == s_video_decode_op.u4_output_present)
        {


            if(ps_ctxt->ai4_timestamp_valid[s_video_decode_op.u4_ts])
            {
                ps_ctxt->out_pts = ps_ctxt->ai8_timestamp[s_video_decode_op.u4_ts];
                ps_ctxt->ai4_timestamp_valid[s_video_decode_op.u4_ts] = 0;
            }

            /* If annex B and ps_block->i_pts is zero, then use fps configured from command line */
            if((1 == ps_ctxt->i4_is_annexb) && (0 == ps_ctxt->in_pts))
            {
                ps_ctxt->out_pts = ps_ctxt->i4_annexb_ts;
                ps_ctxt->i4_annexb_ts += ps_ctxt->i4_pic_duration;
            }
            ps_ctxt->i4_output_present = 1;
            ivd_set_lateness(ps_ctxt, ps_ctxt->out_pts);
        }
    }

    if(ps_ctxt->i4_thread_created)
        ithread_exit(0);
    return ps_ctxt->u4_num_bytes;
}

                
/**
*******************************************************************************
*
* @brief
* Get input bitstream
*
* @par   Description
* Get input bitstream, in case of mp4 convert to Annex B format, in case of
* elementary streams just copy. Elementary stream case instead of copying
* a pointer can be set, but if the decode is to be done in a different
* thread, then it has to be copied and input can be released
*
* @param[in] ps_ctxt
* Plugin context
*
* @param[in] pu1_buf
* Input bitstream buffer
*
* @param[in] i4_size
* Size of input bitstream buffer

* @returns None
*
* @remarks
*
*******************************************************************************
*/
static void ih264_get_input(ctxt_t *ps_ctxt, UWORD8 *pu1_buf, WORD32 i4_size)
{

    
    DEBUG_DUMP(DUMP_INPUT_UNPARSED_PATH, "ab", pu1_buf, i4_size);

    ps_ctxt->pu1_inp = ps_ctxt->pu1_bits_base;
    /* If during header parse in create it is detected as mp4, then
    do not mark it as annex b. In case of mp4 first 4 bytes may emulate a start code,
    hence ensure the check is done only if during create annex b was not initialized */
    if((i4_size) && (-1 == ps_ctxt->i4_is_annexb))
    {

        if((0x0 == ps_ctxt->pu1_inp[0]) &&
            (0x0 == ps_ctxt->pu1_inp[1]) &&
            (0x0 == ps_ctxt->pu1_inp[2]) &&
            (0x1 == ps_ctxt->pu1_inp[3]))
        {
            ps_ctxt->i4_is_annexb = 1;
        }

        if((0x0 == ps_ctxt->pu1_inp[0]) &&
            (0x0 == ps_ctxt->pu1_inp[1]) &&
            (0x1 == ps_ctxt->pu1_inp[2]))
        {
            ps_ctxt->i4_is_annexb = 1;
        }
    }

    LOGI(ps_ctxt, 0, "ps_ctxt->i4_is_annexb %d", ps_ctxt->i4_is_annexb);
    /* If not in annex B format, add start code */
    ps_ctxt->u4_num_bytes = 0;

    if(0 == ps_ctxt->i4_is_annexb)
    {

        UWORD32 size;
        WORD32 bytes_remaining;

        switch(ps_ctxt->avctx->codec_id)
        {
        case AV_CODEC_ID_H264:

            bytes_remaining = i4_size;
            while(bytes_remaining > 4)
            {
                //TODO: Following assumes first four bytes in the input buffer give length. This is mp4 container specific
                size = (pu1_buf[0] << 24) | (pu1_buf[1] << 16)
                    | (pu1_buf[2] << 8) | (pu1_buf[3] << 0);
                pu1_buf += 4;
                bytes_remaining -= 4;
                /* Set the first four bytes as start code */
                ps_ctxt->pu1_inp[ps_ctxt->u4_num_bytes] = 0;
                ps_ctxt->pu1_inp[ps_ctxt->u4_num_bytes + 1] = 0;
                ps_ctxt->pu1_inp[ps_ctxt->u4_num_bytes + 2] = 0;
                ps_ctxt->pu1_inp[ps_ctxt->u4_num_bytes + 3] = 1;
                ps_ctxt->u4_num_bytes += 4;

                /* Limit size to remaining number of bytes */
                size = MIN(size, bytes_remaining);
                LOGI(ps_ctxt, 10, "Copying %d bytes", size);
                memcpy(&ps_ctxt->pu1_inp[ps_ctxt->u4_num_bytes], pu1_buf,
                    size);
                ps_ctxt->u4_num_bytes += size;
                pu1_buf += size;
                bytes_remaining -= size;
            }
            break;
        default:
            break;
        }
    }
    else
    {
        LOGI(ps_ctxt, 10, "Copying %d bytes", i4_size);
        memcpy(&ps_ctxt->pu1_inp[ps_ctxt->u4_num_bytes], pu1_buf, i4_size);
        ps_ctxt->u4_num_bytes += i4_size;

    }

    DEBUG_DUMP(DUMP_INPUT_PATH, "ab", ps_ctxt->pu1_inp, ps_ctxt->u4_num_bytes);

    return;
}

/**
*******************************************************************************
*
* @brief
*  Plugin's entry point for Decode picture
*
* @par   Description
* Get input and call decode frame. If threading is enabled call decode in a different thread
*
* @param[in] avctx
* Framework context
*
* @param[in] data
* Output pointer
*
* @param[in] got_output
* Flag to signal if output is present
*
* @param[in] avpkt
* Input buffer structure
*
* @returns Number of bytes consumed
*
* @remarks
*
*******************************************************************************
*/
static int ih264_decode_frame_wrapper(AVCodecContext *avctx,
    AVFrame *data,
    int *got_output,
    AVPacket *avpkt)
{
    ctxt_t *ps_ctxt = avctx->priv_data;
    int ret;

    *got_output = 0;
    if(ps_ctxt->i4_thread_created)
    {
        ithread_join(ps_ctxt->pv_thread_handle, NULL);
        ps_ctxt->i4_thread_created = 0;

        if(ps_ctxt->i4_output_present)
        {
            av_frame_move_ref(data, ps_ctxt->disp_pic);
            *got_output = 1;
        }

    }
    ps_ctxt->avpkt = *avpkt;

    ps_ctxt->in_pts = avpkt->pts;
    ih264_get_input(ps_ctxt, avpkt->data, avpkt->size);

    if(ps_ctxt->i4_thread_enable && ps_ctxt->i4_num_cores > 1)
    {

        ithread_create(ps_ctxt->pv_thread_handle, NULL,
            (void *)&ivd_h264_decode_frame, (void *)ps_ctxt);
        ps_ctxt->i4_thread_created = 1;

    }
    else
    {
        ret = ivd_h264_decode_frame(ps_ctxt);

        if(ps_ctxt->i4_output_present)
        {
            ps_ctxt->disp_pic->pts = ps_ctxt->out_pts;
            av_frame_move_ref(data, ps_ctxt->disp_pic);

            *got_output = 1;
        }
        if(ret < 0)
        {
            return AVERROR_INVALIDDATA;
        }
    }

    return avpkt->size;

}

/**
*******************************************************************************
*
* @brief
* Init plugin context
*
* @par   Description
* Init plugin context
*
* @param[in] avctx
*

* @returns
*
* @remarks
*
*******************************************************************************
*/
static int ih264d_init_context(AVCodecContext *avctx)
{

    ctxt_t *ps_ctxt;

    int i;

    ps_ctxt = avctx->priv_data;
    ps_ctxt->pv_thread_handle = ih264a_aligned_malloc(16, ithread_get_handle_size());
    ps_ctxt->i4_thread_created = 0;
    ps_ctxt->i4_thread_enable = THREAD_ENABLE;
    ps_ctxt->avctx = avctx;
    ps_ctxt->i4_num_cores = ivd_ff_get_num_cores(ps_ctxt);
    ps_ctxt->disp_pic = NULL;

    ps_ctxt->e_arch = ivd_ff_get_arch();
    ps_ctxt->e_soc                   = SOC_GENERIC;
    ps_ctxt->share_disp_buf          = DEFAULT_SHARE_DISPLAY_BUF;
    ps_ctxt->num_disp_buf            = EXTRA_DISP_BUFFERS;

    ps_ctxt->max_wd                  = ALIGN64(avctx->width);
    ps_ctxt->max_ht                  = ALIGN64(avctx->height);

    ps_ctxt->e_output_chroma_format = DEFAULT_CHROMA_FMT;

    if(0 == ps_ctxt->max_wd)
        ps_ctxt->max_wd = MAX_FRAME_WIDTH;

    if(0 == ps_ctxt->max_ht)
        ps_ctxt->max_ht = MAX_FRAME_HEIGHT;

    ps_ctxt->max_level               = MAX_LEVEL_SUPPORTED;
    if(ps_ctxt->max_wd * ps_ctxt->max_ht > 1920 * 1080)
        ps_ctxt->max_level = 50;

    ps_ctxt->u4_strd                 = 0;
    ps_ctxt->i4_pic_cnt              = 0;

    ps_ctxt->u4_tot_cycles           = 0;
    ps_ctxt->u4_tot_fmt_cycles       = 0;
    ps_ctxt->peak_window_idx         = 0;
    ps_ctxt->peak_avg_max            = 0;
    ps_ctxt->i4_is_annexb            = -1;
    ps_ctxt->i4_fps                  = DEFAULT_FPS;
    ps_ctxt->i4_pic_duration         = 1000000 / ps_ctxt->i4_fps;

    ps_ctxt->pv_mem_rec_location     = NULL;
    ps_ctxt->u4_num_mem_rec          = 0;
    ps_ctxt->i4_annexb_ts            = 0;
    ps_ctxt->i4_header_done          = 0;
    ps_ctxt->i4_pic_ht               = 0;
    ps_ctxt->i4_pic_wd               = 0;
    ps_ctxt->i4_num_disp_bufs        = EXTRA_DISP_BUFFERS;
    ps_ctxt->i4_cur_disp_buf         = 0;
    ps_ctxt->i4_first_pic_display_time_set = 0;
    ps_ctxt->i4_expected_time        = 0;
    ps_ctxt->i4_lateness          = 0;
    ps_ctxt->i4_degrade_type        = 0;
    ps_ctxt->i4_skipb_enabled        = 0;

    memset(&ps_ctxt->peak_window[0], 0, sizeof(WORD32) *PEAK_WINDOW_SIZE) ;

    for(i = 0; i < MAX_TIMESTAMP_CNT;i++)
    {
        ps_ctxt->ai8_timestamp[i] = 0;
        ps_ctxt->ai4_timestamp_valid[i]  = 0;
    }
    return 0;


}

/**
*******************************************************************************
*
* @brief
* Extract SPS & PPS from hvcC box for mp4 files
*
* @par   Description
* Extract SPS & PPS from hvcC box for mp4 files
*
* @param[in] ps_ctxt
* Plugin context
*
* @param[in] pu1_hdr_buf
* Input buffer
*
* @param[in] i4_hdr_size
* Number of bytes in input buffer
*
* @returns 0 on success
*
* @remarks
*
*******************************************************************************
*/
static int hvcC_parse_sps_pps(ctxt_t *ps_ctxt,
    UWORD8 *pu1_hdr_buf,
    WORD32 i4_hdr_size)
{

    WORD32 cnt, size;
    WORD32 hdr_cnt;
    WORD32 i, j;

    pu1_hdr_buf += 22;
    i4_hdr_size -= 22;
    hdr_cnt = *pu1_hdr_buf++;
    i4_hdr_size--;
    LOGI(ps_ctxt, 0, "Number of headers %d", hdr_cnt);
    for(i = 0; i < hdr_cnt; i++)
    {
        pu1_hdr_buf++;
        i4_hdr_size--;
        /* Get number of header NALs sps/pps/vps that follow */
        cnt = *pu1_hdr_buf++ << 8;
        i4_hdr_size--;
        cnt |= *pu1_hdr_buf++;
        i4_hdr_size--;
        if(i4_hdr_size <= 0)
        {
            return -1;
        }
        LOGI(ps_ctxt, 0, "Number of headers %d", cnt);

        for(j = 0; j < cnt;j++)
        {
            /* Size of NALs */
            size = *pu1_hdr_buf++ << 8;
            i4_hdr_size--;
            size|= *pu1_hdr_buf++;
            i4_hdr_size--;
            LOGI(ps_ctxt, 0, "Size of header %d", size);

            ps_ctxt->pu1_bits_base[ps_ctxt->i4_bits_size] = 0;
            ps_ctxt->i4_bits_size++;
            ps_ctxt->pu1_bits_base[ps_ctxt->i4_bits_size] = 0;
            ps_ctxt->i4_bits_size++;
            ps_ctxt->pu1_bits_base[ps_ctxt->i4_bits_size] = 0;
            ps_ctxt->i4_bits_size++;
            ps_ctxt->pu1_bits_base[ps_ctxt->i4_bits_size] = 1;
            ps_ctxt->i4_bits_size++;

            memcpy(&ps_ctxt->pu1_bits_base[ps_ctxt->i4_bits_size], pu1_hdr_buf,
                size);
            ps_ctxt->i4_bits_size += size;
            pu1_hdr_buf+=size;
            i4_hdr_size -= size;

        }
    }
    return 0;
}

/**
*******************************************************************************
*
* @brief
* Plugin's entry point for HEVC decoder
*
* @par   Description
* Allocate plugin context, extract SPS/PPS from extra data for mp4 containers
*
* @param[in] avctx
* Framework context
*
* @returns AVERROR(ENOMEM) on failure else 0
*
* @remarks
*
*******************************************************************************
*/
static int ih264_decode_init(AVCodecContext *avctx)
{

    ctxt_t *ps_ctxt = avctx->priv_data;
    int ret;

    ret = ih264d_init_context(avctx);
    if (ret < 0)
        return AVERROR(ENOMEM);

    ps_ctxt->pu1_bits_base = ih264a_aligned_malloc(16, MAX_BITS_SIZE);
    if(NULL == ps_ctxt->pu1_bits_base)
        return AVERROR(ENOMEM);

    ps_ctxt->i4_bits_size = 0;

    if (avctx->extradata_size > 0 && avctx->extradata)
    {
        UWORD8 *pu1_hdr_buf = avctx->extradata;
        DEBUG_DUMP(DUMP_INPUT_UNPARSED_PATH, "wb", avctx->extradata, avctx->extradata_size);

        /* If start code is present, treat it as elementary stream */
        if((0x0 == pu1_hdr_buf[0]) && (0x0 == pu1_hdr_buf[1])
            && (0x0 == pu1_hdr_buf[2]) && (0x1 == pu1_hdr_buf[3]))
            ps_ctxt->i4_is_annexb = 1;

        if((0x0 == pu1_hdr_buf[0]) && (0x0 == pu1_hdr_buf[1])
            && (0x1 == pu1_hdr_buf[2]))
            ps_ctxt->i4_is_annexb = 1;

        if(1 == ps_ctxt->i4_is_annexb)
        {
            WORD32 size = avctx->extradata_size;
            LOGI(ps_ctxt, 10, "Elementary stream found");
            memcpy(ps_ctxt->pu1_bits_base, pu1_hdr_buf,
                size);
            ps_ctxt->i4_bits_size += size;
            pu1_hdr_buf+=size;

        }
        /* Check if extra data is hvcC */
        else if((avctx->extradata_size > 3)
            && (avctx->extradata[0] || avctx->extradata[1]
        || avctx->extradata[2] > 1))
        {
            LOGI(ps_ctxt, 10, "hvcC header found");
            ps_ctxt->i4_is_annexb = 0;
            ret = hvcC_parse_sps_pps(ps_ctxt, avctx->extradata,
                avctx->extradata_size);
            if (ret < 0)
            {
                ih264_decode_free(ps_ctxt->avctx);
                return AVERROR(ENOMEM);
            }

        }
        DEBUG_DUMP(DUMP_INPUT_PATH, "wb", ps_ctxt->pu1_bits_base, ps_ctxt->i4_bits_size);
    }

    LOGI(ps_ctxt, 99, "Architecture     :%d", ps_ctxt->e_arch);
    LOGI(ps_ctxt, 99, "NumCores         :%d", ps_ctxt->i4_num_cores);
    LOGI(ps_ctxt, 99, "MaxWidth         :%d", ps_ctxt->max_wd);
    LOGI(ps_ctxt, 99, "MaxHeight        :%d", ps_ctxt->max_ht);
    LOGI(ps_ctxt, 99, "FPS (for ES)     :%d", ps_ctxt->i4_fps);

    /* Initialize the codec */
    LOGI(ps_ctxt, 0, "ivd_vlc_open: Create HEVC decoder instance\n");

    ret = ih264d_create(ps_ctxt);
    if (ret < 0)
    {
        ih264_decode_free(ps_ctxt->avctx);
        return -1;
    }

    {
        IV_API_CALL_STATUS_T ret;

        if(0 == ps_ctxt->i4_header_done && avctx->extradata_size > 0 && avctx->extradata)
        {
            ret = ivd_h264_header_decode(ps_ctxt, ps_ctxt->pu1_bits_base, ps_ctxt->i4_bits_size);
            if(ret != IV_SUCCESS)
            {
                return AVERROR_INVALIDDATA;
            }

            /* If header was not successfully decoded, release input buffer and return */
            /* ALso return if all the bytes were consumed in header decode itself */

            if((0 == ps_ctxt->i4_header_done) || (4 > ps_ctxt->i4_bits_size))
            {
                LOGE(ps_ctxt, 0, "Header decode failed");
                if(ps_ctxt->i4_thread_created)
                    ithread_exit(0);

                return AVERROR_INVALIDDATA;
            }
        }

    }

    return 0;
}

/**
*******************************************************************************
*
* @brief
* Plugin's entry point for flushing
*
* @par   Description
* Since decoder flush is hanlded as part of decode, nothign to be done here
*
* @param[in] avctx
* Framework context
*
* @returns None
*
* @remarks
*
*******************************************************************************
*/
static void ih264_decode_flush(AVCodecContext *avctx)
{
    UNUSED(avctx);
    return;
}

#define OFFSET(x) offsetof(ctxt_t, x)
#define PAR (AV_OPT_FLAG_DECODING_PARAM | AV_OPT_FLAG_VIDEO_PARAM)
static const AVProfile profiles[] = {
    { FF_PROFILE_H264_BASELINE,             "Baseline"              },
    { FF_PROFILE_H264_CONSTRAINED_BASELINE, "Constrained Baseline"  },
    { FF_PROFILE_H264_MAIN,                 "Main"                  },
    { FF_PROFILE_H264_EXTENDED,             "Extended"              },
    { FF_PROFILE_H264_HIGH,                 "High"                  },
    { FF_PROFILE_H264_HIGH_10,              "High 10"               },
    { FF_PROFILE_H264_HIGH_10_INTRA,        "High 10 Intra"         },
    { FF_PROFILE_H264_HIGH_422,             "High 4:2:2"            },
    { FF_PROFILE_H264_HIGH_422_INTRA,       "High 4:2:2 Intra"      },
    { FF_PROFILE_H264_HIGH_444,             "High 4:4:4"            },
    { FF_PROFILE_H264_HIGH_444_PREDICTIVE,  "High 4:4:4 Predictive" },
    { FF_PROFILE_H264_HIGH_444_INTRA,       "High 4:4:4 Intra"      },
    { FF_PROFILE_H264_CAVLC_444,            "CAVLC 4:4:4"           },
    { FF_PROFILE_UNKNOWN },
};


const FFCodec ff_ih264_decoder = {
    .p.name           = "ih264d",
    .p.long_name      = NULL_IF_CONFIG_SMALL("Ittiam H264 Decoder"),
    .p.type           = AVMEDIA_TYPE_VIDEO,
    .p.id             = AV_CODEC_ID_H264,
    .priv_data_size = sizeof(ctxt_t),
    .init           = ih264_decode_init,
    .close          = ih264_decode_free,
    FF_CODEC_DECODE_CB(ih264_decode_frame_wrapper),
    .p.capabilities   = AV_CODEC_CAP_DR1 | AV_CODEC_CAP_DELAY,
    .flush          = ih264_decode_flush,
    .p.pix_fmts       = (const enum AVPixelFormat[]) { AV_PIX_FMT_VDPAU,
                                                     AV_PIX_FMT_NONE},
    .p.profiles       = NULL_IF_CONFIG_SMALL(profiles),
};

