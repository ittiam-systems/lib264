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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef X86_MINGW
#include <signal.h>
#endif

#include "../common/ih264_typedefs.h"
#include "../decoder/api/iv.h"
#include "../decoder/api/ivd.h"
#include "../decoder/api/ih264d.h"
#include "../libthread/include/ithread.h"

#include "decode-avc-priv.h"

#ifdef WINDOWS_TIMER
// #include <windows.h>
#else
#include <sys/time.h>
#endif

#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE

#define ALIGN8(x) ((((x) + 7) >> 3) << 3)

#define ENABLE_DEGRADE 0
#define MAX_DISP_BUFFERS 64
#define EXTRA_DISP_BUFFERS 8
#define STRLENGTH 1000

#define MAX_FRAME_WIDTH 3840
#define MAX_FRAME_HEIGHT 2160
#define MAX_LEVEL_SUPPORTED 50
#define MAX_REF_FRAMES 16
#define MAX_REORDER_FRAMES 16
#define STRIDE 0

UWORD32 file_pos = 0;
UWORD32 total_bytes_comsumed = 0;

struct AVC_Video_Frame
{
    float avf_TimeStamp; /**< Time for this frame            */
    void *avf_Buffer;    /**< Pointer to the decoded frame   */

    void *y_Buffer;
    void *u_Buffer;
    void *v_Buffer;

    iv_yuv_buf_t disp_stats;

    size_t avf_BufferSize; /**< Bytes for the stored frame     */
};

struct AVC_Video_Init_Params
{
    int avi_fgs_enable;
    int avi_fgs_blk_size;
    int avi_fgs_transform;
    int avi_fgs_chroma;
    int avi_num_cores;
    int avi_playback_fps;
};

/*****************************************************************************/
/*                                                                           */
/*  Function Name : codec_exit                                               */
/*                                                                           */
/*  Description   : handles unrecoverable errors                             */
/*  Inputs        : Error message                                            */
/*  Globals       : None                                                     */
/*  Processing    : Prints error message to console and exits.               */
/*  Outputs       : Error mesage to the console                              */
/*  Returns       : None                                                     */
/*                                                                           */
/*  Issues        :                                                          */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*                                                                           */
/*****************************************************************************/
void codec_exit(CHAR *pc_err_message)
{
    printf("%s\n", pc_err_message);
    exit(-1);
}

/*
 *  The externally visible API starts here
 */
AVC_Decoder *AVC_Decoder_new(void)
{
    AVC_Decoder *ad;

    if((ad = malloc(sizeof *ad)) != NULL)
    {
        memset(ad, 0, sizeof *ad);
    }
    return ad;
}

AVC_Video_Init_Params *AVC_Decoder_get_init_params(void)
{
    AVC_Video_Init_Params *avip;

    if((avip = malloc(sizeof *avip)) != NULL)
    {
        memset(avip, 0, sizeof *avip);
    }
    return avip;
}

void AVC_Decoder_destroy(AVC_Decoder *ad, AVC_Video_Init_Params *avip)
{
    if(avip)
    {
        free(avip);
    }
    if(ad)
    {
        int i;
        WORD32 ret;
        iv_obj_t *codec_obj;
        UWORD32 u4_num_mem_recs;

        Buffer_Handler_close(ad->ad_Buffer);
        if(ad->ad_LastFrame != NULL)
        {
            free(ad->ad_LastFrame);
        }
        for(i = 0; i < ad->ad_NumBuffered; i++)
        {
            free(ad->ad_Frames[i]);
        }

        if(ad->codec_obj)
        {
            iv_retrieve_mem_rec_ip_t s_retrieve_dec_ip;
            iv_retrieve_mem_rec_op_t s_retrieve_dec_op;
            s_retrieve_dec_ip.pv_mem_rec_location = (iv_mem_rec_t *) ad->pv_mem_rec_location;

            s_retrieve_dec_ip.e_cmd = IV_CMD_RETRIEVE_MEMREC;
            s_retrieve_dec_ip.u4_size = sizeof(iv_retrieve_mem_rec_ip_t);
            s_retrieve_dec_op.u4_size = sizeof(iv_retrieve_mem_rec_op_t);

            ret = ih264d_api_function((iv_obj_t *) ad->codec_obj, (void *) &s_retrieve_dec_ip,
                                      (void *) &s_retrieve_dec_op);

            if(IV_SUCCESS != ret)
            {
                printf("Error in Retrieve Memrec %x\n", s_retrieve_dec_op.u4_error_code);
                return;
            }
        }

        if(ad->ad_InputBuffer != NULL)
        {
            free(ad->ad_InputBuffer);
        }

        if(ad->pBuf != NULL)
        {
            free(ad->pBuf);
        }
        free(ad);
    }
}

static void *ih264a_aligned_malloc(WORD32 alignment, WORD32 size)
{
    return memalign(alignment, size);
}

static void ih264a_aligned_free(void *ctxt, void *buf)
{
    UNUSED(ctxt);
    free(buf);
    return;
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : get_version                                              */
/*                                                                           */
/*  Description   : Control call to get codec version                        */
/*                                                                           */
/*                                                                           */
/*  Inputs        : codec_obj : Codec handle                                 */
/*  Globals       :                                                          */
/*  Processing    : Calls enable skip B frames control                       */
/*                                                                           */
/*  Outputs       :                                                          */
/*  Returns       : Control call return i4_status                            */
/*                                                                           */
/*  Issues        :                                                          */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes                              */
/*                                                                           */
/*****************************************************************************/

void get_version(AVC_Decoder *ad)
{
    ivd_ctl_getversioninfo_ip_t ps_ctl_ip;
    ivd_ctl_getversioninfo_op_t ps_ctl_op;
    UWORD8 au1_buf[512];
    IV_API_CALL_STATUS_T i4_status;
    ps_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
    ps_ctl_ip.e_sub_cmd = IVD_CMD_CTL_GETVERSION;
    ps_ctl_ip.u4_size = sizeof(ivd_ctl_getversioninfo_ip_t);
    ps_ctl_op.u4_size = sizeof(ivd_ctl_getversioninfo_op_t);
    ps_ctl_ip.pv_version_buffer = au1_buf;
    ps_ctl_ip.u4_version_buffer_size = sizeof(au1_buf);

    i4_status = ih264d_api_function((iv_obj_t *) ad->codec_obj, (void *) &(ps_ctl_ip),
                                    (void *) &(ps_ctl_op));

    if(i4_status != IV_SUCCESS)
    {
        printf("\nError in Getting Version number e_dec_status = %d u4_error_code = %x\n",
               i4_status, ps_ctl_op.u4_error_code);
    }
    else
    {
        printf("Ittiam Decoder Version number: %s\n", (char *) ps_ctl_ip.pv_version_buffer);
    }
    return;
}

UWORD32 default_get_stride(void) { return 0; }

IV_COLOR_FORMAT_T default_get_color_fmt(void) { return IV_YUV_420P; }

int release_disp_frame(AVC_Decoder *ad, UWORD32 buf_id)
{
    ivd_rel_display_frame_ip_t s_video_rel_disp_ip;
    ivd_rel_display_frame_op_t s_video_rel_disp_op;
    IV_API_CALL_STATUS_T e_dec_status;

    s_video_rel_disp_ip.e_cmd = IVD_CMD_REL_DISPLAY_FRAME;
    s_video_rel_disp_ip.u4_size = sizeof(ivd_rel_display_frame_ip_t);
    s_video_rel_disp_op.u4_size = sizeof(ivd_rel_display_frame_op_t);
    s_video_rel_disp_ip.u4_disp_buf_id = buf_id;

    e_dec_status = ih264d_api_function((iv_obj_t *) ad->codec_obj, (void *) &s_video_rel_disp_ip,
                                       (void *) &s_video_rel_disp_op);
    if(IV_SUCCESS != e_dec_status)
    {
        printf("Error in Release Disp frame\n");
    }

    return (e_dec_status);
}

int setFlushMode(AVC_Decoder *ad)
{
    IV_API_CALL_STATUS_T status;
    ivd_ctl_flush_ip_t s_video_flush_ip;
    ivd_ctl_flush_op_t s_video_flush_op;
    s_video_flush_ip.e_cmd = IVD_CMD_VIDEO_CTL;
    s_video_flush_ip.e_sub_cmd = IVD_CMD_CTL_FLUSH;
    s_video_flush_ip.u4_size = sizeof(ivd_ctl_flush_ip_t);
    s_video_flush_op.u4_size = sizeof(ivd_ctl_flush_op_t);

    /* Set the decoder in Flush mode, subsequent decode() calls will flush */
    status = ih264d_api_function((iv_obj_t *) ad->codec_obj, (void *) &s_video_flush_ip,
                                 (void *) &s_video_flush_op);

    if(status != IV_SUCCESS)
    {
        printf("Error in setting the decoder in flush mode: (%d) 0x%x", status,
               s_video_flush_op.u4_error_code);
        return -1;
    }

    ad->mIsInFlush = true;

    return 0;
}

int AVC_deInitDecoder(AVC_Decoder *ad)
{
    WORD32 ret;
    void *pv_mem_rec_location;
    int i;
    if(ad->codec_obj)
    {
        iv_retrieve_mem_rec_ip_t s_retrieve_dec_ip;
        iv_retrieve_mem_rec_op_t s_retrieve_dec_op;
        s_retrieve_dec_ip.pv_mem_rec_location = (iv_mem_rec_t *) pv_mem_rec_location;

        s_retrieve_dec_ip.e_cmd = IV_CMD_RETRIEVE_MEMREC;
        s_retrieve_dec_ip.u4_size = sizeof(iv_retrieve_mem_rec_ip_t);
        s_retrieve_dec_op.u4_size = sizeof(iv_retrieve_mem_rec_op_t);

        ret = ih264d_api_function((iv_obj_t *) ad->codec_obj, (void *) &s_retrieve_dec_ip,
                                  (void *) &s_retrieve_dec_op);

        if(IV_SUCCESS != ret)
        {
            printf("Error in Codec delete\n");
            return -1;
        }
    }

    return 0;
}

int setParams(AVC_Decoder *ad, size_t stride)
{
    WORD32 ret;
    ivd_ctl_set_config_ip_t s_ctl_ip;
    ivd_ctl_set_config_op_t s_ctl_op;

    s_ctl_ip.u4_disp_wd = stride;
    s_ctl_ip.e_frm_skip_mode = IVD_SKIP_NONE;
    s_ctl_ip.e_frm_out_mode = IVD_DISPLAY_FRAME_OUT;
    s_ctl_ip.e_vid_dec_mode = IVD_DECODE_FRAME;
    s_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
    s_ctl_ip.e_sub_cmd = IVD_CMD_CTL_SETPARAMS;
    s_ctl_ip.u4_size = sizeof(ivd_ctl_set_config_ip_t);
    s_ctl_op.u4_size = sizeof(ivd_ctl_set_config_op_t);

    ret = ih264d_api_function((iv_obj_t *) ad->codec_obj, (void *) &s_ctl_ip, (void *) &s_ctl_op);
    if(ret != IV_SUCCESS)
    {
        printf("\nError in setting the stride");
        return -1;
    }

    return 0;
}

int resetDecoder(AVC_Decoder *ad)
{
    WORD32 ret;
    ivd_ctl_reset_ip_t s_ctl_ip;
    ivd_ctl_reset_op_t s_ctl_op;

    s_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
    s_ctl_ip.e_sub_cmd = IVD_CMD_CTL_RESET;
    s_ctl_ip.u4_size = sizeof(ivd_ctl_reset_ip_t);
    s_ctl_op.u4_size = sizeof(ivd_ctl_reset_op_t);

    ret = ih264d_api_function((iv_obj_t *) ad->codec_obj, (void *) &s_ctl_ip, (void *) &s_ctl_op);
    if(IV_SUCCESS != ret)
    {
        printf("Error in Reset");
        return -1;
    }

    return 0;
}

int resetPlugin(AVC_Decoder *ad)
{
    ad->mIsInFlush = false;
    ad->mReceivedEOS = false;
    return 0;
}

int setNumCores(AVC_Decoder *ad)
{
    WORD32 ret;
    ih264d_ctl_set_num_cores_ip_t s_ctl_set_cores_ip;
    ih264d_ctl_set_num_cores_op_t s_ctl_set_cores_op;

    s_ctl_set_cores_ip.e_cmd = IVD_CMD_VIDEO_CTL;
    s_ctl_set_cores_ip.e_sub_cmd = (IVD_CONTROL_API_COMMAND_TYPE_T) IH264D_CMD_CTL_SET_NUM_CORES;
    s_ctl_set_cores_ip.u4_num_cores = 1;
    s_ctl_set_cores_ip.u4_size = sizeof(ih264d_ctl_set_num_cores_ip_t);
    s_ctl_set_cores_op.u4_size = sizeof(ih264d_ctl_set_num_cores_op_t);

    ret = ih264d_api_function((iv_obj_t *) ad->codec_obj, (void *) &s_ctl_set_cores_ip,
                              (void *) &s_ctl_set_cores_op);
    if(ret != IV_SUCCESS)
    {
        printf("\nError in setting number of cores");
        return -1;
    }
    return 0;
}

int setProcessor(AVC_Decoder *ad)
{
    WORD32 ret;
    ih264d_ctl_set_processor_ip_t s_ctl_set_num_processor_ip;
    ih264d_ctl_set_processor_op_t s_ctl_set_num_processor_op;

    s_ctl_set_num_processor_ip.e_cmd = IVD_CMD_VIDEO_CTL;
    s_ctl_set_num_processor_ip.e_sub_cmd =
        (IVD_CONTROL_API_COMMAND_TYPE_T) IH264D_CMD_CTL_SET_PROCESSOR;
    s_ctl_set_num_processor_ip.u4_arch = ARCH_X86_SSE42;
    s_ctl_set_num_processor_ip.u4_soc = SOC_GENERIC;
    s_ctl_set_num_processor_ip.u4_size = sizeof(ih264d_ctl_set_processor_ip_t);
    s_ctl_set_num_processor_op.u4_size = sizeof(ih264d_ctl_set_processor_op_t);

    ret = ih264d_api_function((iv_obj_t *) ad->codec_obj, (void *) &s_ctl_set_num_processor_ip,
                              (void *) &s_ctl_set_num_processor_op);
    if(ret != IV_SUCCESS)
    {
        printf("\nError in setting Processor type%x", s_ctl_set_num_processor_op.u4_error_code);
        return -1;
    }

    return 0;
}

int AVC_initDecoder(AVC_Decoder *ad, AVC_Video_Init_Params *avip)
{
    WORD32 width = 0, height = 0;
    iv_obj_t *codec_obj;
    IV_API_CALL_STATUS_T e_dec_status;
    CHAR ac_error_str[STRLENGTH];

    UWORD32 u4_num_mem_recs;
    UWORD32 i;
    WORD32 ret;
    UWORD32 u4_ip_buf_len;
    UWORD8 *pu1_bs_buf = NULL;
    ivd_out_bufdesc_t *ps_out_buf = NULL;
    void *pv_mem_rec_location;

    /***********************************************************************/
    /*                      Create decoder instance                        */
    /***********************************************************************/
    {
        ps_out_buf = (ivd_out_bufdesc_t *) malloc(sizeof(ivd_out_bufdesc_t));

        {
            iv_num_mem_rec_ip_t s_no_of_mem_rec_query_ip;
            iv_num_mem_rec_op_t s_no_of_mem_rec_query_op;

            s_no_of_mem_rec_query_ip.u4_size = sizeof(s_no_of_mem_rec_query_ip);
            s_no_of_mem_rec_query_op.u4_size = sizeof(s_no_of_mem_rec_query_op);
            s_no_of_mem_rec_query_ip.e_cmd = IV_CMD_GET_NUM_MEM_REC;

            /*****************************************************************************/
            /*   API Call: Get Number of Mem Records */
            /*****************************************************************************/
            e_dec_status = ih264d_api_function(NULL, (void *) &s_no_of_mem_rec_query_ip,
                                               (void *) &s_no_of_mem_rec_query_op);
            if(IV_SUCCESS != e_dec_status)
            {
                sprintf(ac_error_str, "Error in get mem records");
                codec_exit(ac_error_str);
            }

            u4_num_mem_recs = s_no_of_mem_rec_query_op.u4_num_mem_rec;
        }

        pv_mem_rec_location = malloc(u4_num_mem_recs * sizeof(iv_mem_rec_t));
        if(pv_mem_rec_location == NULL)
        {
            sprintf(ac_error_str, "Allocation failure for mem_rec_location");
            codec_exit(ac_error_str);
        }

        ad->pv_mem_rec_location = pv_mem_rec_location;

        {
            ih264d_fill_mem_rec_ip_t s_fill_mem_rec_ip;
            ih264d_fill_mem_rec_op_t s_fill_mem_rec_op;
            iv_mem_rec_t *ps_mem_rec;
            UWORD32 total_size;

            s_fill_mem_rec_ip.s_ivd_fill_mem_rec_ip_t.e_cmd = IV_CMD_FILL_NUM_MEM_REC;
            s_fill_mem_rec_ip.s_ivd_fill_mem_rec_ip_t.pv_mem_rec_location =
                (iv_mem_rec_t *) pv_mem_rec_location;
            s_fill_mem_rec_ip.s_ivd_fill_mem_rec_ip_t.u4_max_frm_wd = MAX_FRAME_WIDTH;
            s_fill_mem_rec_ip.s_ivd_fill_mem_rec_ip_t.u4_max_frm_ht = MAX_FRAME_HEIGHT;
            s_fill_mem_rec_ip.i4_level = MAX_LEVEL_SUPPORTED;
            s_fill_mem_rec_ip.u4_num_ref_frames = MAX_REF_FRAMES;
            s_fill_mem_rec_ip.u4_num_reorder_frames = MAX_REORDER_FRAMES;
            s_fill_mem_rec_ip.u4_share_disp_buf = 0;
            s_fill_mem_rec_ip.e_output_format = IV_YUV_420P;
            s_fill_mem_rec_ip.u4_num_extra_disp_buf = EXTRA_DISP_BUFFERS;

            s_fill_mem_rec_ip.s_ivd_fill_mem_rec_ip_t.u4_size = sizeof(ih264d_fill_mem_rec_ip_t);
            s_fill_mem_rec_op.s_ivd_fill_mem_rec_op_t.u4_size = sizeof(ih264d_fill_mem_rec_op_t);

            ps_mem_rec = (iv_mem_rec_t *) pv_mem_rec_location;

            for(i = 0; i < u4_num_mem_recs; i++)
            {
                ps_mem_rec[i].u4_size = sizeof(iv_mem_rec_t);
            }

            /*****************************************************************************/
            /*   API Call: Fill Mem Records                                              */
            /*****************************************************************************/

            e_dec_status =
                ih264d_api_function(NULL, (void *) &s_fill_mem_rec_ip, (void *) &s_fill_mem_rec_op);

            u4_num_mem_recs = s_fill_mem_rec_op.s_ivd_fill_mem_rec_op_t.u4_num_mem_rec_filled;

            if(IV_SUCCESS != e_dec_status)
            {
                sprintf(ac_error_str, "Error in fill mem records: %x",
                        s_fill_mem_rec_op.s_ivd_fill_mem_rec_op_t.u4_error_code);
                codec_exit(ac_error_str);
            }

            ps_mem_rec = (iv_mem_rec_t *) pv_mem_rec_location;
            total_size = 0;
            for(i = 0; i < u4_num_mem_recs; i++)
            {
                ps_mem_rec->pv_base =
                    ih264a_aligned_malloc(ps_mem_rec->u4_mem_alignment, ps_mem_rec->u4_mem_size);
                if(ps_mem_rec->pv_base == NULL)
                {
                    sprintf(ac_error_str, "\nAllocation failure for mem record id %d i4_size %d\n",
                            i, ps_mem_rec->u4_mem_size);
                    codec_exit(ac_error_str);
                }
                total_size += ps_mem_rec->u4_mem_size;
                ps_mem_rec++;
            }
        }

        /*****************************************************************************/
        /*   API Call: Initialize the Decoder                                        */
        /*****************************************************************************/
        {
            ih264d_init_ip_t s_init_ip;
            ih264d_init_op_t s_init_op;
            void *fxns = &ih264d_api_function;
            iv_mem_rec_t *mem_tab;

            mem_tab = (iv_mem_rec_t *) pv_mem_rec_location;
            s_init_ip.s_ivd_init_ip_t.e_cmd = (IVD_API_COMMAND_TYPE_T) IV_CMD_INIT;
            s_init_ip.s_ivd_init_ip_t.pv_mem_rec_location = mem_tab;
            s_init_ip.s_ivd_init_ip_t.u4_frm_max_wd = MAX_FRAME_WIDTH;
            s_init_ip.s_ivd_init_ip_t.u4_frm_max_ht = MAX_FRAME_HEIGHT;
            s_init_ip.i4_level = MAX_LEVEL_SUPPORTED;
            s_init_ip.u4_num_ref_frames = MAX_REF_FRAMES;
            s_init_ip.u4_num_reorder_frames = MAX_REORDER_FRAMES;
            s_init_ip.u4_share_disp_buf = 0;
            s_init_ip.u4_num_extra_disp_buf = EXTRA_DISP_BUFFERS;
            s_init_ip.s_ivd_init_ip_t.u4_num_mem_rec = u4_num_mem_recs;
            s_init_ip.s_ivd_init_ip_t.e_output_format = IV_YUV_420P;
            s_init_ip.s_ivd_init_ip_t.u4_size = sizeof(ih264d_init_ip_t);
            s_init_op.s_ivd_init_op_t.u4_size = sizeof(ih264d_init_op_t);

            codec_obj = (iv_obj_t *) mem_tab[0].pv_base;
            codec_obj->pv_fxns = (void *) fxns;
            codec_obj->u4_size = sizeof(iv_obj_t);

            ret = ih264d_api_function((iv_obj_t *) codec_obj, (void *) &s_init_ip,
                                      (void *) &s_init_op);
            if(ret != IV_SUCCESS)
            {
                printf("\nError in Init");
                return -1;
            }

            /*****************************************************************************/
            /*  Input and output buffer allocation */
            /*****************************************************************************/
            {
                ivd_ctl_getbufinfo_ip_t s_ctl_ip;
                ivd_ctl_getbufinfo_op_t s_ctl_op;

                s_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
                s_ctl_ip.e_sub_cmd = IVD_CMD_CTL_GETBUFINFO;
                s_ctl_ip.u4_size = sizeof(ivd_ctl_getbufinfo_ip_t);
                s_ctl_op.u4_size = sizeof(ivd_ctl_getbufinfo_op_t);

                ret = ih264d_api_function((iv_obj_t *) codec_obj, (void *) &s_ctl_ip,
                                          (void *) &s_ctl_op);
                if(ret != IV_SUCCESS)
                {
                    printf("\nError in Get Buf Info");
                    return -1;
                }

                /* Allocate input buffer */
                u4_ip_buf_len = s_ctl_op.u4_min_in_buf_size[0];
                pu1_bs_buf = (UWORD8 *) malloc(u4_ip_buf_len);

                if(pu1_bs_buf == NULL)
                {
                    printf("\nAllocation failure for input buffer of i4_size");
                    return -1;
                }
                /* Allocate output buffer only if display buffers are not shared */
                /* Or if shared and output is 420P */
                {
                    UWORD32 outlen;
                    ps_out_buf->u4_min_out_buf_size[0] = s_ctl_op.u4_min_out_buf_size[0];
                    ps_out_buf->u4_min_out_buf_size[1] = s_ctl_op.u4_min_out_buf_size[1];
                    ps_out_buf->u4_min_out_buf_size[2] = s_ctl_op.u4_min_out_buf_size[2];

                    outlen = s_ctl_op.u4_min_out_buf_size[0];
                    if(s_ctl_op.u4_min_num_out_bufs > 1) outlen += s_ctl_op.u4_min_out_buf_size[1];

                    if(s_ctl_op.u4_min_num_out_bufs > 2) outlen += s_ctl_op.u4_min_out_buf_size[2];

                    ps_out_buf->pu1_bufs[0] = (UWORD8 *) malloc(outlen);

                    if(ps_out_buf->pu1_bufs[0] == NULL)
                    {
                        printf("\nAllocation failure for output buffer of i4_size");
                        return -1;
                    }

                    if(s_ctl_op.u4_min_num_out_bufs > 1)
                    {
                        ps_out_buf->pu1_bufs[1] =
                            ps_out_buf->pu1_bufs[0] + (s_ctl_op.u4_min_out_buf_size[0]);
                    }

                    if(s_ctl_op.u4_min_num_out_bufs > 2)
                    {
                        ps_out_buf->pu1_bufs[2] =
                            ps_out_buf->pu1_bufs[1] + (s_ctl_op.u4_min_out_buf_size[1]);
                    }

                    ps_out_buf->u4_num_bufs = s_ctl_op.u4_min_num_out_bufs;
                }
            }
        }
    }

    /*************************************************************************/
    /* set num of cores                                                      */
    /*************************************************************************/
    {
        ih264d_ctl_set_num_cores_ip_t s_ctl_set_cores_ip;
        ih264d_ctl_set_num_cores_op_t s_ctl_set_cores_op;

        s_ctl_set_cores_ip.e_cmd = IVD_CMD_VIDEO_CTL;
        s_ctl_set_cores_ip.e_sub_cmd =
            (IVD_CONTROL_API_COMMAND_TYPE_T) IH264D_CMD_CTL_SET_NUM_CORES;
        s_ctl_set_cores_ip.u4_num_cores = avip->avi_num_cores;
        s_ctl_set_cores_ip.u4_size = sizeof(ih264d_ctl_set_num_cores_ip_t);
        s_ctl_set_cores_op.u4_size = sizeof(ih264d_ctl_set_num_cores_op_t);

        ret = ih264d_api_function((iv_obj_t *) codec_obj, (void *) &s_ctl_set_cores_ip,
                                  (void *) &s_ctl_set_cores_op);
        if(ret != IV_SUCCESS)
        {
            printf("\nError in setting number of cores");
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
        s_ctl_set_num_processor_ip.e_sub_cmd =
            (IVD_CONTROL_API_COMMAND_TYPE_T) IH264D_CMD_CTL_SET_PROCESSOR;
        s_ctl_set_num_processor_ip.u4_arch = ARCH_X86_GENERIC;
        s_ctl_set_num_processor_ip.u4_soc = SOC_GENERIC;
        s_ctl_set_num_processor_ip.u4_size = sizeof(ih264d_ctl_set_processor_ip_t);
        s_ctl_set_num_processor_op.u4_size = sizeof(ih264d_ctl_set_processor_op_t);

        ret = ih264d_api_function((iv_obj_t *) codec_obj, (void *) &s_ctl_set_num_processor_ip,
                                  (void *) &s_ctl_set_num_processor_op);
        if(ret != IV_SUCCESS)
        {
            printf("\nError in setting Processor type %x",
                   s_ctl_set_num_processor_op.u4_error_code);
            return -1;
        }
    }

    ad->codec_obj = codec_obj;

    /* Reset the plugin state */
    resetPlugin(ad);

    /* Set the Processor type to be used by the codec */
    setProcessor(ad);

    /* Get codec version */
    get_version(ad);

    return 0;
}

void AVC_Decoder_set_source(AVC_Decoder *ad, Buffer_Handler *handle) { ad->ad_Buffer = handle; }

void AVC_Decoder_set_fgs(AVC_Video_Init_Params *avip, int fgs_enable)
{
    avip->avi_fgs_enable = fgs_enable;
}

void AVC_Decoder_set_fgs_transform(AVC_Video_Init_Params *avip, int fgs_transform)
{
    avip->avi_fgs_transform = fgs_transform;
}

void AVC_Decoder_set_fgs_blk_size(AVC_Video_Init_Params *avip, int fgs_blk_size)
{
    avip->avi_fgs_blk_size = fgs_blk_size;
}

void AVC_Decoder_set_fgs_chroma(AVC_Video_Init_Params *avip, int fgs_chroma)
{
    avip->avi_fgs_chroma = fgs_chroma;
}

void AVC_Decoder_set_num_cores(AVC_Video_Init_Params *avip, int num_cores)
{
    avip->avi_num_cores = num_cores;
}

void AVC_Decoder_set_fps(AVC_Video_Init_Params *avip, int playback_fps)
{
    avip->avi_playback_fps = playback_fps;
}

int decodeHeader(AVC_Decoder *ad, size_t timeStampIx)
{
    int status;
    /* Allocate input buffer for header */
    UWORD32 u4_ip_buf_len = 256 * 1024;
    UWORD8 *pu1_bs_buf = NULL;
    pu1_bs_buf = (UWORD8 *) malloc(u4_ip_buf_len);
    WORD32 ret;

    UWORD32 u4_num_bytes_dec = 0;

    UWORD64 u8_ip_frm_ts = 0, u8_op_frm_ts = 0;

    WORD32 u4_bytes_remaining = 0;
    UWORD32 i;
    UWORD32 frm_cnt = 0;
    UWORD32 max_op_frm_ts;
    FILE *ps_ip_file = NULL;

    if(pu1_bs_buf == NULL)
    {
        printf("\nAllocation failure for input buffer of i4_size %d", u4_ip_buf_len);
        return -1;
    }
    ivd_ctl_set_config_ip_t s_ctl_ip;
    ivd_ctl_set_config_op_t s_ctl_op;

    ivd_video_decode_ip_t s_video_decode_ip;
    ivd_video_decode_op_t s_video_decode_op;

    s_ctl_ip.u4_disp_wd = STRIDE;

    s_ctl_ip.e_frm_skip_mode = IVD_SKIP_NONE;
    s_ctl_ip.e_frm_out_mode = IVD_DISPLAY_FRAME_OUT;
    s_ctl_ip.e_vid_dec_mode = IVD_DECODE_HEADER;
    s_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
    s_ctl_ip.e_sub_cmd = IVD_CMD_CTL_SETPARAMS;
    s_ctl_ip.u4_size = sizeof(ivd_ctl_set_config_ip_t);
    s_ctl_op.u4_size = sizeof(ivd_ctl_set_config_op_t);

    ret = ih264d_api_function((iv_obj_t *) ad->codec_obj, (void *) &s_ctl_ip, (void *) &s_ctl_op);
    if(ret != IV_SUCCESS)
    {
        printf("\nError in setting the codec in header decode mode");
        return -1;
    }

    WORD32 numbytes;
    numbytes = u4_ip_buf_len;

    u4_bytes_remaining = Buffer_Handler_read(ad->ad_Buffer, pu1_bs_buf, numbytes);
    if(0 == u4_bytes_remaining)
    {
        printf("\nUnable to read from input file");
        return -1;
    }
    s_video_decode_ip.e_cmd = IVD_CMD_VIDEO_DECODE;
    s_video_decode_ip.u4_ts = 0.0;
    s_video_decode_ip.pv_stream_buffer = pu1_bs_buf;
    s_video_decode_ip.u4_num_Bytes = u4_bytes_remaining;
    s_video_decode_ip.u4_size = sizeof(ivd_video_decode_ip_t);
    s_video_decode_op.u4_size = sizeof(ivd_video_decode_op_t);

    /*****************************************************************************/
    /*   API Call: Header Decode                                                  */
    /*****************************************************************************/

    ret = ih264d_api_function((iv_obj_t *) ad->codec_obj, (void *) &s_video_decode_ip,
                              (void *) &s_video_decode_op);

    if(ret != IV_SUCCESS)
    {
        printf("Error in header decode 0x%x\n", s_video_decode_op.u4_error_code);
        return -1;
    }

    u4_num_bytes_dec = s_video_decode_op.u4_num_bytes_consumed;

    file_pos += u4_num_bytes_dec;
    total_bytes_comsumed += u4_num_bytes_dec;
    Buffer_Handler_update_pos(ad->ad_Buffer, file_pos);

    /* copy pic_wd and pic_ht to initialize buffers */
    ad->frame_width = s_video_decode_op.u4_pic_wd;
    ad->frame_height = s_video_decode_op.u4_pic_ht;
    free(pu1_bs_buf);

    /*************************************************************************/
    /* Set the decoder in frame decode mode. It was set in header decode     */
    /* mode earlier                                                          */
    /*************************************************************************/
    {
        ivd_ctl_set_config_ip_t s_ctl_ip;
        ivd_ctl_set_config_op_t s_ctl_op;

        s_ctl_ip.u4_disp_wd = ad->frame_width;
        s_ctl_ip.e_frm_skip_mode = IVD_SKIP_NONE;

        s_ctl_ip.e_frm_out_mode = IVD_DISPLAY_FRAME_OUT;
        s_ctl_ip.e_vid_dec_mode = IVD_DECODE_FRAME;
        s_ctl_ip.e_cmd = IVD_CMD_VIDEO_CTL;
        s_ctl_ip.e_sub_cmd = IVD_CMD_CTL_SETPARAMS;
        s_ctl_ip.u4_size = sizeof(ivd_ctl_set_config_ip_t);

        s_ctl_op.u4_size = sizeof(ivd_ctl_set_config_op_t);

        ret =
            ih264d_api_function((iv_obj_t *) ad->codec_obj, (void *) &s_ctl_ip, (void *) &s_ctl_op);

        if(IV_SUCCESS != ret)
        {
            printf("Error in Set Parameters");
            return -1;
        }
    }

    return 0;
}

void AVC_Decoder_run(AVC_Decoder *ad, int multi_frame)
{
    size_t timeStampIx = 0;
    int status;
    UWORD32 u4_num_bytes_dec = 0;
    UWORD64 u8_ip_frm_ts = 0, u8_op_frm_ts = 0;
    WORD32 u4_bytes_remaining = 0;
    UWORD32 i;
    UWORD32 u4_ip_buf_len = (1920 * 1080 * 3) / 2;
    UWORD32 frm_cnt = 0;
    UWORD32 max_op_frm_ts;

    if(NULL == ad->codec_obj)
    {
        status = AVC_initDecoder(ad, NULL);
        if(0 != status)
        {
            return;
        }
    }

    if(ad->ad_NumBuffered >= NUM_FRAMES_BUFFERED)
    {
        return;
    }

    /*Block for decoding the header and getting the color format*/
    /*bit depth information for configuring the dispaly*/
    if(0 == ad->is_header_decoded)
    {
        status = decodeHeader(ad, timeStampIx);
        if(0 != status)
        {
            printf("failed to decode header, return error");
            return;
        }
        ad->is_header_decoded = 1;
        setParams(ad, ad->frame_width);
    }

    if(NULL == ad->ad_InputBuffer)
    {
        ad->ad_InputBuffer =
            (unsigned char *) malloc((ad->frame_width * ad->frame_height * 3) >> 1);
    }

    if(NULL == ad->pBuf)
    {
        ad->pBuf = (uint8_t *) malloc((ad->frame_width * ad->frame_height * 3) >> 1);
    }

    if(NULL == ad->yBuf)
    {
        ad->yBuf = (uint8_t *) malloc(ad->frame_width * ad->frame_height);
    }

    if(NULL == ad->uBuf)
    {
        ad->uBuf = (uint8_t *) malloc((ad->frame_width * ad->frame_height) >> 2);
    }

    if(NULL == ad->vBuf)
    {
        ad->vBuf = (uint8_t *) malloc((ad->frame_width * ad->frame_height) >> 2);
    }

    size_t frame_size = 0;
    size_t got;

    WORD32 numbytes;

    numbytes = u4_ip_buf_len;

    u4_bytes_remaining = Buffer_Handler_read(ad->ad_Buffer, ad->ad_InputBuffer, numbytes);
    if(0 == u4_bytes_remaining)
    {
        printf("\nUnable to read from input file");
        return;
    }

    {
        ivd_video_decode_ip_t s_video_decode_ip;
        ivd_video_decode_op_t s_video_decode_op;
        WORD32 timeDelay, timeTaken;
        size_t timeStampIx;

        size_t sizeY = ad->frame_width * ad->frame_height;
        size_t sizeUV;

        sizeUV = sizeY / 4;

        s_video_decode_ip.e_cmd = IVD_CMD_VIDEO_DECODE;
        s_video_decode_ip.u4_ts = ad->u8_ip_frm_ts;
        s_video_decode_ip.pv_stream_buffer = ad->ad_InputBuffer;
        s_video_decode_ip.u4_num_Bytes = u4_bytes_remaining;
        s_video_decode_ip.u4_size = sizeof(ivd_video_decode_ip_t);
        s_video_decode_ip.s_out_buffer.u4_min_out_buf_size[0] = sizeY;
        s_video_decode_ip.s_out_buffer.u4_min_out_buf_size[1] = sizeUV;
        s_video_decode_ip.s_out_buffer.u4_min_out_buf_size[2] = sizeUV;
        s_video_decode_ip.s_out_buffer.pu1_bufs[0] = ad->yBuf;
        s_video_decode_ip.s_out_buffer.pu1_bufs[1] = ad->uBuf;
        s_video_decode_ip.s_out_buffer.pu1_bufs[2] = ad->vBuf;
        s_video_decode_ip.s_out_buffer.u4_num_bufs = 3;
        s_video_decode_op.u4_size = sizeof(ivd_video_decode_op_t);

        IV_API_CALL_STATUS_T status;
        status = ih264d_api_function((iv_obj_t *) ad->codec_obj, (void *) &s_video_decode_ip,
                                     (void *) &s_video_decode_op);

        u4_num_bytes_dec = s_video_decode_op.u4_num_bytes_consumed;

        file_pos += u4_num_bytes_dec;
        total_bytes_comsumed += u4_num_bytes_dec;
        Buffer_Handler_update_pos(ad->ad_Buffer, file_pos);

        ad->u8_ip_frm_ts++;

        ad->output_present = s_video_decode_op.u4_output_present;

        ad->sei_fgc_params_present_flag = s_video_decode_op.s_sei_decode_op.u1_sei_fgc_params_present_flag;
        if(s_video_decode_op.u4_output_present)
        {
            if(1 == s_video_decode_op.s_sei_decode_op.u1_sei_fgc_params_present_flag)
            {
                ih264d_ctl_get_sei_fgc_params_ip_t s_ctl_get_sei_fgc_params_ip;
                ih264d_ctl_get_sei_fgc_params_op_t s_ctl_get_sei_fgc_params_op;

                memset(&s_ctl_get_sei_fgc_params_ip, 0, sizeof(ih264d_ctl_get_sei_fgc_params_ip_t));
                memset(&s_ctl_get_sei_fgc_params_op, 0, sizeof(ih264d_ctl_get_sei_fgc_params_op_t));

                s_ctl_get_sei_fgc_params_ip.e_cmd = IVD_CMD_VIDEO_CTL;
                s_ctl_get_sei_fgc_params_ip.e_sub_cmd =
                    (IVD_CONTROL_API_COMMAND_TYPE_T) IH264D_CMD_CTL_GET_SEI_FGC_PARAMS;
                s_ctl_get_sei_fgc_params_ip.u4_size = sizeof(ih264d_ctl_get_sei_fgc_params_ip_t);
                s_ctl_get_sei_fgc_params_op.u4_size = sizeof(ih264d_ctl_get_sei_fgc_params_op_t);

                status = ih264d_api_function((iv_obj_t *) ad->codec_obj,
                                             (void *) &s_ctl_get_sei_fgc_params_ip,
                                             (void *) &s_ctl_get_sei_fgc_params_op);

                if(status != IV_SUCCESS)
                {
                    printf("\nError in setting FGS enable flag %x",
                           s_ctl_get_sei_fgc_params_op.u4_error_code);
                    return;
                }
            }

            AVC_Video_Frame *avf;
            avf = (AVC_Video_Frame *) malloc(sizeof(AVC_Video_Frame));
            avf->y_Buffer = (unsigned char *) ad->yBuf;
            avf->u_Buffer = (unsigned char *) ad->uBuf;
            avf->v_Buffer = (unsigned char *) ad->vBuf;

            avf->avf_TimeStamp = 0.0;  // TODO
            avf->avf_BufferSize = ((ad->frame_width * ad->frame_height * 3) >> 1);
            avf->disp_stats = s_video_decode_op.s_disp_frm_buf;
            // Append the buffered frame
            ad->ad_Frames[ad->ad_NumBuffered] = avf;
            ad->ad_NumBuffered++;
        }
    }
}

void AVC_Decoder_video_reset(AVC_Decoder *ad)
{
    Buffer_Handler_update_pos(ad->ad_Buffer, 0);
    ad->file_pos = 0;
    ad->total_bytes_comsumed = 0;
    return;
}

int AVC_Decoder_video_finished(AVC_Decoder *ad) { return Buffer_Handler_empty(ad->ad_Buffer); }

int AVC_Decoder_get_width(AVC_Decoder *ad)
{
    if(ad == NULL)
    {
        return 0;
    }
    return ad->frame_width;
}

int AVC_Decoder_get_height(AVC_Decoder *ad)
{
    if(ad == NULL)
    {
        return 0;
    }
    return ad->frame_height;
}

float AVC_Video_Frame_get_time(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return 0.0;
    }
    return avf->avf_TimeStamp;
}

unsigned int AVC_Decoder_get_y_strd(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return 0;
    }
    return avf->disp_stats.u4_y_strd;
}

unsigned int AVC_Decoder_get_y_wd(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return 0;
    }
    return avf->disp_stats.u4_y_wd;
}

unsigned int AVC_Decoder_get_y_ht(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return 0;
    }
    return avf->disp_stats.u4_y_ht;
}

unsigned int AVC_Decoder_get_u_strd(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return 0;
    }
    return avf->disp_stats.u4_u_strd;
}

unsigned int AVC_Decoder_get_u_wd(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return 0;
    }
    return avf->disp_stats.u4_u_wd;
}

unsigned int AVC_Decoder_get_u_ht(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return 0;
    }
    return avf->disp_stats.u4_u_ht;
}

unsigned int AVC_Decoder_get_v_strd(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return 0;
    }
    return avf->disp_stats.u4_v_strd;
}

unsigned int AVC_Decoder_get_v_wd(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return 0;
    }
    return avf->disp_stats.u4_v_wd;
}

unsigned int AVC_Decoder_get_v_ht(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return 0;
    }
    return avf->disp_stats.u4_v_ht;
}

void *AVC_Video_Frame_get_buffer(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return NULL;
    }
    return avf->avf_Buffer;
}

void *AVC_Video_Frame_get_y_buffer(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return NULL;
    }
    return avf->y_Buffer;
}
void *AVC_Video_Frame_get_u_buffer(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return NULL;
    }
    return avf->u_Buffer;
}
void *AVC_Video_Frame_get_v_buffer(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return NULL;
    }
    return avf->v_Buffer;
}

size_t AVC_Video_Frame_get_size(AVC_Video_Frame *avf)
{
    if(avf == NULL)
    {
        return 0;
    }
    return avf->avf_BufferSize;
}

AVC_Video_Frame *AVC_Decoder_get_frame(AVC_Decoder *ad)
{
    // free up the memory from any previous frame returned
    if(ad->ad_LastFrame != NULL)
    {
        free(ad->ad_LastFrame);
        ad->ad_LastFrame = NULL;
    }
    if(ad->ad_NumBuffered > 0)
    {
        AVC_Video_Frame *frame;

        frame = ad->ad_Frames[0];
        ad->ad_NumBuffered--;
        if(ad->ad_NumBuffered > 0)
        {
            memmove(ad->ad_Frames, &ad->ad_Frames[1],
                    ad->ad_NumBuffered * sizeof(AVC_Video_Frame *));
        }
        // Hang on to this refernce so we can free the memory
        ad->ad_LastFrame = frame;
        return frame;
    }
    return NULL;
}
