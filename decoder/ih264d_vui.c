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
/*  File Name         : ih264d_vui.c */
/*                                                                           */
/*  Description       : This file contains routines to parse VUI NAL's       */
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

#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264d_vui.h"
#include "ih264d_bitstrm.h"
#include "ih264d_parse_cavlc.h"
#include "ih264d_structs.h"
#include "ih264d_error_handler.h"

/*****************************************************************************/
/*                                                                           */
/*  Function Name : ih264d_parse_hrd_parametres */
/*                                                                           */
/*  Description   : This function parses hrd_t parametres */
/*  Inputs        : ps_hrd          pointer to HRD params                    */
/*                  ps_bitstrm   Bitstream                                */
/*  Globals       : None                                                     */
/*  Processing    : Parses HRD params                                        */
/*  Outputs       : None                                                     */
/*  Returns       : None                                                     */
/*                                                                           */
/*  Issues        : None                                                     */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         06 05 2002   NS              Draft                                */
/*                                                                           */
/*****************************************************************************/

WORD32 ih264d_parse_hrd_parametres(hrd_t *ps_hrd,
                                   dec_bit_stream_t *ps_bitstrm) {
  UWORD8 u1_index;
  UWORD32 *pu4_bitstrm_ofst = &ps_bitstrm->u4_ofst;
  UWORD32 *pu4_bitstrm_buf = ps_bitstrm->pu4_buffer;

  ps_hrd->u4_cpb_cnt = 1 + ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
  if (ps_hrd->u4_cpb_cnt > 31) return ERROR_INV_SPS_PPS_T;
  ps_hrd->u1_bit_rate_scale = ih264d_get_bits_h264(ps_bitstrm, 4);
  ps_hrd->u1_cpb_size_scale = ih264d_get_bits_h264(ps_bitstrm, 4);

  for (u1_index = 0; u1_index < (UWORD8) ps_hrd->u4_cpb_cnt; u1_index++) {
    ps_hrd->u4_bit_rate[u1_index] =
        1 + ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
    ps_hrd->u4_cpb_size[u1_index] =
        1 + ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
    ps_hrd->u1_cbr_flag[u1_index] = ih264d_get_bits_h264(ps_bitstrm, 1);
  }

  ps_hrd->u1_initial_cpb_removal_delay =
      1 + ih264d_get_bits_h264(ps_bitstrm, 5);
  ps_hrd->u1_cpb_removal_delay_length = 1 + ih264d_get_bits_h264(ps_bitstrm, 5);
  ps_hrd->u1_dpb_output_delay_length = 1 + ih264d_get_bits_h264(ps_bitstrm, 5);
  ps_hrd->u1_time_offset_length = ih264d_get_bits_h264(ps_bitstrm, 5);

  return OK;
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : ih264d_parse_vui_parametres */
/*                                                                           */
/*  Description   : This function parses VUI NALs.                           */
/*  Inputs        : ps_vu4          pointer to VUI params                    */
/*                  ps_bitstrm   Bitstream                                */
/*  Globals       : None                                                     */
/*  Processing    : Parses VUI NAL's units and stores the info               */
/*  Outputs       : None                                                     */
/*  Returns       : None                                                     */
/*                                                                           */
/*  Issues        : None                                                     */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         06 05 2002   NS              Draft                                */
/*                                                                           */
/*****************************************************************************/

WORD32 ih264d_parse_vui_parametres(vui_t *ps_vu4,
                                   dec_bit_stream_t *ps_bitstrm) {
  UWORD8 u4_bits;
  UWORD32 *pu4_bitstrm_ofst = &ps_bitstrm->u4_ofst;
  UWORD32 *pu4_bitstrm_buf = ps_bitstrm->pu4_buffer;
  WORD32 ret;

  u4_bits = ih264d_get_bits_h264(ps_bitstrm, 1);
  if (u4_bits) {
    u4_bits = ih264d_get_bits_h264(ps_bitstrm, 8);
    ps_vu4->u1_aspect_ratio_idc = (UWORD8) u4_bits;
    if (VUI_EXTENDED_SAR == u4_bits) {
      ps_vu4->u2_sar_width = ih264d_get_bits_h264(ps_bitstrm, 16);
      ps_vu4->u2_sar_height = ih264d_get_bits_h264(ps_bitstrm, 16);
    }
  }

  u4_bits = ih264d_get_bits_h264(ps_bitstrm, 1);
  if (u4_bits) {
    ps_vu4->u1_overscan_appropriate_flag = ih264d_get_bits_h264(ps_bitstrm, 1);
  }
  u4_bits = ih264d_get_bits_h264(ps_bitstrm, 1);
  if (u4_bits) {
    ps_vu4->u1_video_format = ih264d_get_bits_h264(ps_bitstrm, 3);
    ps_vu4->u1_video_full_range_flag = ih264d_get_bits_h264(ps_bitstrm, 1);
    u4_bits = ih264d_get_bits_h264(ps_bitstrm, 1);
    if (u4_bits) {
      ps_vu4->u1_colour_primaries = ih264d_get_bits_h264(ps_bitstrm, 8);
      ps_vu4->u1_tfr_chars = ih264d_get_bits_h264(ps_bitstrm, 8);
      ps_vu4->u1_matrix_coeffs = ih264d_get_bits_h264(ps_bitstrm, 8);
    }
  }

  u4_bits = ih264d_get_bits_h264(ps_bitstrm, 1);
  if (u4_bits) {
    ps_vu4->u1_cr_top_field = ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
    ps_vu4->u1_cr_bottom_field = ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
  }

  u4_bits = ih264d_get_bits_h264(ps_bitstrm, 1);
  if (u4_bits) {
    ps_vu4->u4_num_units_in_tick = ih264d_get_bits_h264(ps_bitstrm, 32);
    ps_vu4->u4_time_scale = ih264d_get_bits_h264(ps_bitstrm, 32);
    ps_vu4->u1_fixed_frame_rate_flag = ih264d_get_bits_h264(ps_bitstrm, 1);
  }

  u4_bits = ih264d_get_bits_h264(ps_bitstrm, 1);
  ps_vu4->u1_nal_hrd_params_present = u4_bits;
  if (u4_bits) {
    ret = ih264d_parse_hrd_parametres(&ps_vu4->s_nal_hrd, ps_bitstrm);
    if (ret != OK) return ret;
  }
  u4_bits = ih264d_get_bits_h264(ps_bitstrm, 1);
  ps_vu4->u1_vcl_hrd_params_present = u4_bits;
  if (u4_bits) {
    ret = ih264d_parse_hrd_parametres(&ps_vu4->s_vcl_hrd, ps_bitstrm);
    if (ret != OK) return ret;
  }

  if (ps_vu4->u1_nal_hrd_params_present || u4_bits) {
    ps_vu4->u1_low_delay_hrd_flag = ih264d_get_bits_h264(ps_bitstrm, 1);
  }
  ps_vu4->u1_pic_struct_present_flag = ih264d_get_bits_h264(ps_bitstrm, 1);

  u4_bits = ih264d_get_bits_h264(ps_bitstrm, 1);
  if (u4_bits) {
    ps_vu4->u1_mv_over_pic_boundaries_flag =
        ih264d_get_bits_h264(ps_bitstrm, 1);
    ps_vu4->u4_max_bytes_per_pic_denom =
        ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
    ps_vu4->u4_max_bits_per_mb_denom =
        ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
    ps_vu4->u4_log2_max_mv_length_horz =
        ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
    ps_vu4->u4_log2_max_mv_length_vert =
        ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
    ps_vu4->u4_num_reorder_frames =
        ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
    ps_vu4->u4_max_dec_frame_buffering =
        ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
  } else {
    /* Setting this to a large value if not present */
    ps_vu4->u4_num_reorder_frames = 64;
  }

  return OK;
}
