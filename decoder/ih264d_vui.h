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
/*  File Name         : ih264d_vui.h */
/*                                                                           */
/*  Description       : This file contains routines to parse SEI NAL's       */
/*                                                                           */
/*  List of Functions : <List the functions defined in this file>            */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         25 05 2005   NS              Draft                                */
/*                                                                           */
/*****************************************************************************/

#ifndef _IH264D_VUI_H_
#define _IH264D_VUI_H_

#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264d_bitstrm.h"

#define VUI_EXTENDED_SAR 255

typedef struct {
  UWORD32 u4_cpb_cnt;
  UWORD8 u1_bit_rate_scale;
  UWORD8 u1_cpb_size_scale;
  UWORD32 u4_bit_rate[32];
  UWORD32 u4_cpb_size[32];
  UWORD8 u1_cbr_flag[32];
  UWORD8 u1_initial_cpb_removal_delay;
  UWORD8 u1_cpb_removal_delay_length;
  UWORD8 u1_dpb_output_delay_length;
  UWORD8 u1_time_offset_length;
} hrd_t;

typedef struct {
  UWORD8 u1_aspect_ratio_idc;
  UWORD16 u2_sar_width;
  UWORD16 u2_sar_height;
  UWORD8 u1_overscan_appropriate_flag;
  UWORD8 u1_video_format;
  UWORD8 u1_video_full_range_flag;
  UWORD8 u1_colour_primaries;
  UWORD8 u1_tfr_chars;
  UWORD8 u1_matrix_coeffs;
  UWORD8 u1_cr_top_field;
  UWORD8 u1_cr_bottom_field;
  UWORD32 u4_num_units_in_tick;
  UWORD32 u4_time_scale;
  UWORD8 u1_fixed_frame_rate_flag;
  UWORD8 u1_nal_hrd_params_present;
  hrd_t s_nal_hrd;
  UWORD8 u1_vcl_hrd_params_present;
  hrd_t s_vcl_hrd;
  UWORD8 u1_low_delay_hrd_flag;
  UWORD8 u1_pic_struct_present_flag;
  UWORD8 u1_mv_over_pic_boundaries_flag;
  UWORD32 u4_max_bytes_per_pic_denom;
  UWORD32 u4_max_bits_per_mb_denom;
  UWORD32 u4_log2_max_mv_length_horz;
  UWORD32 u4_log2_max_mv_length_vert;
  UWORD32 u4_num_reorder_frames;
  UWORD32 u4_max_dec_frame_buffering;
} vui_t;

WORD32 ih264d_parse_vui_parametres(vui_t *ps_vu4, dec_bit_stream_t *ps_bitstrm);
#endif /* _SEI_H_ */
