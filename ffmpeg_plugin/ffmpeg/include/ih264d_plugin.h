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
/*****************************************************************************/
/*                                                                           */
/*  File Name         : ih264d_plugin.h                                      */
/*                                                                           */
/*  Description       : This file contains all the necessary structure and   */
/*                      enumeration definitions needed for the Application   */
/*                      Program Interface(API) of the Ittiam H264 ASP       */
/*                      Decoder on Cortex A8 - Neon platform                 */
/*                                                                           */
/*  List of Functions : ih264d_api_function                              */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         26 08 2010   100239(RCY)     Draft                                */
/*                                                                           */
/*****************************************************************************/

#ifndef _IH264D_PLUGIN_H_
#define _IH264D_PLUGIN_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "iv.h"
#include "ivd.h"

#define PLAYER  0
#define ANDROID 0
#define UNUSED(x) (void)x

#define PROFILE_ENABLE 1
/*****************************************************************************/
/* Constant Macros                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Function Macros                                                           */
/*****************************************************************************/
#define MIN_PRINT_LEVEL 100


#define MAX_TIMESTAMP_CNT 64
#define MAX_DISP_BUFFERS    64

#define MAX_BITS_SIZE               2 * 1024 * 1024

#define LOG_ENABLE 1
#define THREAD_ENABLE   0
#define SPS_NAL_TYPE    33
#define MAIN422_PROFILE  4
#define MAIN10_PROFILE   2
#define MAIN_PROFILE     1

#define ALIGN16(x)  ((((x) + 15) >> 4) << 4)
#define ALIGN64(x)  ((((x) + 63) >> 6) << 6)

#define CLIP3(x, min, max) (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))
#define MIN(a, b)   ((a) < (b)) ? (a) : (b)
#define MAX(a, b)   ((a) > (b)) ? (a) : (b)

#define PEAK_WINDOW_SIZE            8
// #define MAX_FRAME_WIDTH             3840
// #define MAX_FRAME_HEIGHT            2160
#define MAX_LEVEL_SUPPORTED         50
#define MAX_REF_FRAMES              16
#define MAX_REORDER_FRAMES          16
#define DEFAULT_SHARE_DISPLAY_BUF   0
#define STRIDE                      0
#define DEFAULT_NUM_CORES           1
#define MAX_NUM_CORES               8
#define MAX_NUM_FRAME_PARSE         2
// #define DEFAULT_FPS                 24

#ifdef LOG_ENABLE
#if ANDROID
#include <android/log.h>
#define LOG_TAG "IVCODEC"
#define LOGI(ps_ctxt, level, ...)                   \
{                                                   \
    if(level >= MIN_PRINT_LEVEL)                    \
    {                                               \
        __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__);      \
    }                                               \
}

#define LOGE(ps_ctxt, level, ...)                   \
{                                                   \
    __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__);      \
}
#else
#define LOGI(ps_ctxt, level, ...)                   \
{                                                   \
    AVCodecContext *avctxt = ps_ctxt->avctx;        \
    if(level >= MIN_PRINT_LEVEL)                    \
    {                                               \
        av_log(avctxt, AV_LOG_INFO, __VA_ARGS__);   \
        av_log(avctxt, AV_LOG_INFO, "\n");          \
    }                                               \
}

#define LOGE(ps_ctxt, level, ...)                   \
{                                                   \
    AVCodecContext *avctxt = ps_ctxt->avctx;        \
    av_log(avctxt, AV_LOG_ERROR, __VA_ARGS__);      \
    av_log(avctxt, AV_LOG_ERROR, "\n");             \
}
#endif
#else
#define LOGI(ps_ctxt, level, ...)
#define LOGE(ps_ctxt, level, ...)
#endif

#if PLAYER
#define ENABLE_DYNAMIC_DEGRADE      1
#else
#define ENABLE_DYNAMIC_DEGRADE      0
#endif

#define DEFAULT_CHROMA_FMT  IV_YUV_420P
#define DUMP_INPUT 0
#define DUMP_INPUT_PATH "inp.raw"
#define DUMP_INPUT_UNPARSED_PATH  "inp_unparsed.raw"

#if DUMP_INPUT
#define DEBUG_DUMP (fname, mode, buf, size)     \
{                                               \
    FILE *fp = fopen(fname, mode);              \
    if(fp)                                      \
    {                                           \
        fwrite(buf, 1, size, fp);               \
        fclose(fp);                             \
    }                                           \
}
#else
#define DEBUG_DUMP(fname, mode, buf, size)
#endif


/*****************************************************************************/
/* API Function Prototype                                                    */
/*****************************************************************************/
void * ih264a_aligned_malloc(WORD32 alignment, WORD32 size);

void ih264a_aligned_free(void *pv_buf);

// #ifndef _TIMEVAL_DEFINED
// #define _TIMEVAL_DEFINED

// struct timeval
// {
// 	long tv_sec;
// 	long tv_usec;
// };


#ifdef PROFILE_ENABLE
    #ifdef X86_MSVC
        typedef  LARGE_INTEGER TIMER;
    #else
        typedef struct timeval TIMER;
    #endif
#else
    typedef int TIMER;
#endif

#ifdef PROFILE_ENABLE
    #ifdef X86_MSVC
        #define GETTIME(timer) QueryPerformanceCounter(timer);
    #else
        #define GETTIME(timer) gettimeofday(timer,NULL);
    #endif

    #ifdef X86_MSVC
        #define ELAPSEDTIME(s_start_timer,s_end_timer, s_elapsed_time, frequency) \
                { \
                   TIMER s_temp_time;   \
                   s_temp_time.LowPart = s_end_timer.LowPart - s_start_timer.LowPart ; \
                   s_elapsed_time = (UWORD32) ( ((DOUBLE)s_temp_time.LowPart / (DOUBLE)frequency.LowPart )  * 1000000); \
                }
    #else
        #define ELAPSEDTIME(s_start_timer,s_end_timer, s_elapsed_time, frequency) \
                   s_elapsed_time = ((s_end_timer.tv_sec - s_start_timer.tv_sec) * 1000000) + (s_end_timer.tv_usec - s_start_timer.tv_usec);
    #endif
#else
    #define GETTIME(timer)
    #define ELAPSEDTIME(s_start_timer,s_end_timer, s_elapsed_time, frequency)
#endif

/*****************************************************************************/
/* Extended Structures                                                       */
/*****************************************************************************/


typedef int64_t  mtime_t;
typedef struct ctxt_t
{
	const AVClass               *class;
    AVCodecContext 				*avctx;
    WORD32 						i4_num_cores;
    IV_COLOR_FORMAT_T 			e_output_chroma_format;
    IV_COLOR_FORMAT_T 			e_output_format;
    IVD_ARCH_T 					e_arch;
    IVD_SOC_T 					e_soc;
    UWORD32 					share_disp_buf;
    UWORD32 					num_disp_buf;
    UWORD32 					max_wd;
    UWORD32 					max_ht;
    UWORD32 					max_level;
    WORD32  					i4_pic_wd;
    WORD32  					i4_pic_ht;
    UWORD32 					u4_strd;
    UWORD32 					u4_bit_depth;
    iv_obj_t 					*ps_codec_obj;
    WORD32  					i4_pic_cnt;
    mtime_t 					ai8_timestamp[MAX_TIMESTAMP_CNT];
    WORD32  					ai4_timestamp_valid[MAX_TIMESTAMP_CNT];
    UWORD8						*pu1_bits_base;
    WORD32  					i4_bits_size;
    WORD32 					 	i4_is_annexb;
    WORD32 					 	i4_annexb_ts;
    WORD32 					 	i4_profile_detected;
    void   					 	*pv_mem_rec_location;
    UWORD32					 	u4_num_mem_rec;
    WORD32 					 	i4_pic_duration;
    WORD32 					 	i4_fps;
    WORD32  					i4_header_done;
    UWORD8  					*pu1_inp;
    UWORD32 					u4_num_bytes;
    UWORD32 					e_profile;
    WORD32  					i4_num_disp_bufs;
    WORD32  					i4_cur_disp_buf;
    AVFrame 					*ps_disp_buf[MAX_DISP_BUFFERS];
    // TIMER   					first_pic_display_time;
    WORD32  					i4_first_pic_display_time_set;
    WORD32  					i4_expected_time;
    WORD32  					i4_lateness;
    WORD32  					i4_degrade_type;
    WORD32  					i4_skipb_enabled;
    UWORD32 					u4_max_num_frm_parse;
    WORD32  					i4_output_present;
    AVPacket 					avpkt;
    AVFrame  					*disp_pic;
    WORD32  					i4_disp_strd;
    void    					*pv_disp_buf[3];
    mtime_t 					in_pts;
    mtime_t 					out_pts;
    void    					*pv_thread_handle;
    WORD32  					i4_thread_created;
    WORD32  					i4_thread_enable;
#ifdef PROFILE_ENABLE
    // TIMER   					s_last_end_timer;
    UWORD32 					u4_tot_cycles;
    UWORD32 					u4_tot_fmt_cycles;
    UWORD32 					peak_window[PEAK_WINDOW_SIZE];
    UWORD32 					peak_window_idx;
    UWORD32 					peak_avg_max;
#endif
	UWORD8						*apu1_metadata_buf[1];

}ctxt_t;

/*****************************************************************************/
/* Enums                                                                     */
/*****************************************************************************/


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif
#endif /* _IH264D_PLUGIN_H_ */
