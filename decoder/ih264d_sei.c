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
/*  File Name         : ih264d_sei.c */
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
#include <string.h>

#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264d_sei.h"
#include "ih264d_bitstrm.h"
#include "ih264d_structs.h"
#include "ih264d_error_handler.h"
#include "ih264d_vui.h"
#include "ih264d_parse_cavlc.h"
#include "ih264d_defs.h"

/*****************************************************************************/
/*                                                                           */
/*  Function Name : ih264d_parse_buffering_period */
/*                                                                           */
/*  Description   : This function parses SEI message buffering_period        */
/*  Inputs        : ps_buf_prd pointer to struct buf_period_t */
/*                  ps_bitstrm    Bitstream                                */
/*  Globals       : None                                                     */
/*  Processing    : Parses SEI payload buffering period.                     */
/*  Outputs       : None                                                     */
/*  Returns       : None                                                     */
/*                                                                           */
/*  Issues        : Not implemented fully                                    */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         06 05 2002   NS              Draft                                */
/*                                                                           */
/*****************************************************************************/

WORD32 ih264d_parse_buffering_period(buf_period_t *ps_buf_prd,
                                     dec_bit_stream_t *ps_bitstrm,
                                     dec_struct_t *ps_dec) {
  UWORD8 u1_seq_parameter_set_id;
  dec_seq_params_t *ps_seq;
  UWORD8 u1_nal_hrd_present, u1_vcl_hrd_present;
  UWORD32 i;
  UWORD32 *pu4_bitstrm_ofst = &ps_bitstrm->u4_ofst;
  UWORD32 *pu4_bitstrm_buf = ps_bitstrm->pu4_buffer;
  UNUSED(ps_buf_prd);
  u1_seq_parameter_set_id = ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
  if (u1_seq_parameter_set_id > MAX_NUM_SEQ_PARAMS)
    return ERROR_INVALID_SEQ_PARAM;
  ps_seq = &ps_dec->ps_sps[u1_seq_parameter_set_id];
  if (TRUE != ps_seq->u1_is_valid) return (-1);

  ps_dec->ps_sei->u1_seq_param_set_id = u1_seq_parameter_set_id;
  ps_dec->ps_cur_sps = ps_seq;
  if (FALSE == ps_seq->u1_is_valid) return ERROR_INVALID_SEQ_PARAM;
  if (1 == ps_seq->u1_vui_parameters_present_flag) {
    u1_nal_hrd_present = ps_seq->s_vui.u1_nal_hrd_params_present;
    if (u1_nal_hrd_present) {
      for (i = 0; i < ps_seq->s_vui.s_nal_hrd.u4_cpb_cnt; i++) {
        ih264d_get_bits_h264(
            ps_bitstrm, ps_seq->s_vui.s_nal_hrd.u1_initial_cpb_removal_delay);
        ih264d_get_bits_h264(
            ps_bitstrm, ps_seq->s_vui.s_nal_hrd.u1_initial_cpb_removal_delay);
      }
    }

    u1_vcl_hrd_present = ps_seq->s_vui.u1_vcl_hrd_params_present;
    if (u1_vcl_hrd_present) {
      for (i = 0; i < ps_seq->s_vui.s_vcl_hrd.u4_cpb_cnt; i++) {
        ih264d_get_bits_h264(
            ps_bitstrm, ps_seq->s_vui.s_vcl_hrd.u1_initial_cpb_removal_delay);
        ih264d_get_bits_h264(
            ps_bitstrm, ps_seq->s_vui.s_vcl_hrd.u1_initial_cpb_removal_delay);
      }
    }
  }
  return OK;
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : ih264d_parse_pic_timing */
/*                                                                           */
/*  Description   : This function parses SEI message pic_timing              */
/*  Inputs        : ps_bitstrm    Bitstream                                */
/*                  ps_dec          Poniter decoder context                  */
/*                  ui4_payload_size pay load i4_size */
/*  Globals       : None                                                     */
/*  Processing    : Parses SEI payload picture timing                        */
/*  Outputs       : None                                                     */
/*  Returns       : None                                                     */
/*                                                                           */
/*  Issues        : Not implemented fully                                    */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         06 05 2002   NS              Draft                                */
/*                                                                           */
/*****************************************************************************/
WORD32 ih264d_parse_pic_timing(dec_bit_stream_t *ps_bitstrm,
                               dec_struct_t *ps_dec, UWORD32 ui4_payload_size) {
  sei *ps_sei;
  vui_t *ps_vu4;
  UWORD8 u1_cpb_dpb_present;
  UWORD8 u1_pic_struct_present_flag;
  UWORD32 u4_start_offset, u4_bits_consumed;
  UWORD8 u1_cpb_removal_delay_length, u1_dpb_output_delay_length;

  ps_sei = (sei *) ps_dec->ps_sei;
  ps_vu4 = &ps_dec->ps_cur_sps->s_vui;

  u1_cpb_dpb_present =
      ps_vu4->u1_vcl_hrd_params_present + ps_vu4->u1_nal_hrd_params_present;

  if (ps_vu4->u1_vcl_hrd_params_present) {
    u1_cpb_removal_delay_length = ps_vu4->s_vcl_hrd.u1_cpb_removal_delay_length;
    u1_dpb_output_delay_length = ps_vu4->s_vcl_hrd.u1_dpb_output_delay_length;
  } else if (ps_vu4->u1_nal_hrd_params_present) {
    u1_cpb_removal_delay_length = ps_vu4->s_nal_hrd.u1_cpb_removal_delay_length;
    u1_dpb_output_delay_length = ps_vu4->s_nal_hrd.u1_dpb_output_delay_length;
  } else {
    u1_cpb_removal_delay_length = 24;
    u1_dpb_output_delay_length = 24;
  }

  u4_start_offset = ps_bitstrm->u4_ofst;
  if (u1_cpb_dpb_present) {
    ih264d_get_bits_h264(ps_bitstrm, u1_cpb_removal_delay_length);
    ih264d_get_bits_h264(ps_bitstrm, u1_dpb_output_delay_length);
  }

  u1_pic_struct_present_flag = ps_vu4->u1_pic_struct_present_flag;
  if (u1_pic_struct_present_flag) {
    ps_sei->u1_pic_struct = ih264d_get_bits_h264(ps_bitstrm, 4);
    ps_dec->u1_pic_struct_copy = ps_sei->u1_pic_struct;
    ps_sei->u1_is_valid = 1;
  }
  u4_bits_consumed = ps_bitstrm->u4_ofst - u4_start_offset;
  ih264d_flush_bits_h264(ps_bitstrm,
                         (ui4_payload_size << 3) - u4_bits_consumed);

  return (0);
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : ih264d_parse_recovery_point */
/*                                                                           */
/*  Description   : This function parses SEI message recovery point          */
/*  Inputs        : ps_bitstrm    Bitstream                                */
/*                  ps_dec          Poniter decoder context                  */
/*                  ui4_payload_size pay load i4_size */
/*  Globals       : None                                                     */
/*  Processing    : Parses SEI payload picture timing                        */
/*  Outputs       : None                                                     */
/*  Returns       : None                                                     */
/*                                                                           */
/*  Issues        : Not implemented fully                                    */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         06 05 2002   NS              Draft                                */
/*                                                                           */
/*****************************************************************************/
WORD32 ih264d_parse_recovery_point(dec_bit_stream_t *ps_bitstrm,
                                   dec_struct_t *ps_dec,
                                   UWORD32 ui4_payload_size) {
  sei *ps_sei = ps_dec->ps_sei;
  dec_err_status_t *ps_err = ps_dec->ps_dec_err_status;
  UWORD32 *pu4_bitstrm_ofst = &ps_bitstrm->u4_ofst;
  UWORD32 *pu4_bitstrm_buf = ps_bitstrm->pu4_buffer;
  UNUSED(ui4_payload_size);
  ps_sei->u2_recovery_frame_cnt = ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
  ps_err->u4_frm_sei_sync = ps_err->u4_cur_frm + ps_sei->u2_recovery_frame_cnt;
  ps_sei->u1_exact_match_flag = ih264d_get_bit_h264(ps_bitstrm);
  ps_sei->u1_broken_link_flag = ih264d_get_bit_h264(ps_bitstrm);
  ps_sei->u1_changing_slice_grp_idc = ih264d_get_bits_h264(ps_bitstrm, 2);

  return (0);
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : ih264d_parse_mdcv                                        */
/*                                                                           */
/*  Description   : This function parses SEI message mdcv                    */
/*  Inputs        : ps_bitstrm    Bitstream                                  */
/*                  ps_dec          Poniter decoder context                  */
/*                  ui4_payload_size pay load i4_size                        */
/*  Globals       : None                                                     */
/*  Processing    :                                                          */
/*  Outputs       : None                                                     */
/*  Return        : 0 for successfull parsing, else -1                       */
/*                                                                           */
/*  Issues        :                                                          */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*                                         Draft                             */
/*                                                                           */
/*****************************************************************************/
WORD32 ih264d_parse_mdcv(dec_bit_stream_t *ps_bitstrm, dec_struct_t *ps_dec,
                         UWORD32 ui4_payload_size) {
  sei *ps_sei;
  UWORD32 u4_count;
  UNUSED(ui4_payload_size);

  if (ps_dec == NULL) {
    return NOT_OK;
  }

  ps_sei = (sei *) ps_dec->ps_sei_parse;

  if (ps_sei == NULL) {
    return NOT_OK;
  }

  ps_sei->u1_sei_mdcv_params_present_flag = 0;
  memset(&ps_sei->s_sei_mdcv_params, 0, sizeof(sei));

  /* display primaries x */
  for (u4_count = 0; u4_count < NUM_SEI_MDCV_PRIMARIES; u4_count++) {
    ps_sei->s_sei_mdcv_params.au2_display_primaries_x[u4_count] =
        (UWORD16) ih264d_get_bits_h264(ps_bitstrm, 16);

    if ((ps_sei->s_sei_mdcv_params.au2_display_primaries_x[u4_count] >
         DISPLAY_PRIMARIES_X_UPPER_LIMIT) ||
        (ps_sei->s_sei_mdcv_params.au2_display_primaries_x[u4_count] <
         DISPLAY_PRIMARIES_X_LOWER_LIMIT) ||
        ((ps_sei->s_sei_mdcv_params.au2_display_primaries_x[u4_count] %
          DISPLAY_PRIMARIES_X_DIVISION_FACTOR) != 0)) {
      ps_sei->u1_sei_mdcv_params_present_flag = 0;
      return ERROR_INV_SEI_MDCV_PARAMS;
    }

    ps_sei->s_sei_mdcv_params.au2_display_primaries_y[u4_count] =
        (UWORD16) ih264d_get_bits_h264(ps_bitstrm, 16);

    if ((ps_sei->s_sei_mdcv_params.au2_display_primaries_y[u4_count] >
         DISPLAY_PRIMARIES_Y_UPPER_LIMIT) ||
        (ps_sei->s_sei_mdcv_params.au2_display_primaries_y[u4_count] <
         DISPLAY_PRIMARIES_Y_LOWER_LIMIT) ||
        ((ps_sei->s_sei_mdcv_params.au2_display_primaries_y[u4_count] %
          DISPLAY_PRIMARIES_Y_DIVISION_FACTOR) != 0)) {
      ps_sei->u1_sei_mdcv_params_present_flag = 0;
      return ERROR_INV_SEI_MDCV_PARAMS;
    }
  }

  /* white point x */
  ps_sei->s_sei_mdcv_params.u2_white_point_x =
      (UWORD16) ih264d_get_bits_h264(ps_bitstrm, 16);

  if ((ps_sei->s_sei_mdcv_params.u2_white_point_x >
       WHITE_POINT_X_UPPER_LIMIT) ||
      (ps_sei->s_sei_mdcv_params.u2_white_point_x <
       WHITE_POINT_X_LOWER_LIMIT) ||
      ((ps_sei->s_sei_mdcv_params.u2_white_point_x %
        WHITE_POINT_X_DIVISION_FACTOR) != 0)) {
    ps_sei->u1_sei_mdcv_params_present_flag = 0;
    return ERROR_INV_SEI_MDCV_PARAMS;
  }
  /* white point y */
  ps_sei->s_sei_mdcv_params.u2_white_point_y =
      (UWORD16) ih264d_get_bits_h264(ps_bitstrm, 16);

  if ((ps_sei->s_sei_mdcv_params.u2_white_point_y >
       WHITE_POINT_Y_UPPER_LIMIT) ||
      (ps_sei->s_sei_mdcv_params.u2_white_point_y <
       WHITE_POINT_Y_LOWER_LIMIT) ||
      ((ps_sei->s_sei_mdcv_params.u2_white_point_y %
        WHITE_POINT_Y_DIVISION_FACTOR) != 0)) {
    ps_sei->u1_sei_mdcv_params_present_flag = 0;
    return ERROR_INV_SEI_MDCV_PARAMS;
  }
  /* max display mastering luminance */
  ps_sei->s_sei_mdcv_params.u4_max_display_mastering_luminance =
      (UWORD32) ih264d_get_bits_h264(ps_bitstrm, 32);

  if ((ps_sei->s_sei_mdcv_params.u4_max_display_mastering_luminance >
       MAX_DISPLAY_MASTERING_LUMINANCE_UPPER_LIMIT) ||
      (ps_sei->s_sei_mdcv_params.u4_max_display_mastering_luminance <
       MAX_DISPLAY_MASTERING_LUMINANCE_LOWER_LIMIT) ||
      ((ps_sei->s_sei_mdcv_params.u4_max_display_mastering_luminance %
        MAX_DISPLAY_MASTERING_LUMINANCE_DIVISION_FACTOR) != 0)) {
    ps_sei->u1_sei_mdcv_params_present_flag = 0;
    return ERROR_INV_SEI_MDCV_PARAMS;
  }
  /* min display mastering luminance */
  ps_sei->s_sei_mdcv_params.u4_min_display_mastering_luminance =
      (UWORD32) ih264d_get_bits_h264(ps_bitstrm, 32);

  if ((ps_sei->s_sei_mdcv_params.u4_min_display_mastering_luminance >
       MIN_DISPLAY_MASTERING_LUMINANCE_UPPER_LIMIT) ||
      (ps_sei->s_sei_mdcv_params.u4_min_display_mastering_luminance <
       MIN_DISPLAY_MASTERING_LUMINANCE_LOWER_LIMIT)) {
    ps_sei->u1_sei_mdcv_params_present_flag = 0;
    return ERROR_INV_SEI_MDCV_PARAMS;
  }
  if (ps_sei->s_sei_mdcv_params.u4_max_display_mastering_luminance <=
      ps_sei->s_sei_mdcv_params.u4_min_display_mastering_luminance) {
    ps_sei->u1_sei_mdcv_params_present_flag = 0;
    return ERROR_INV_SEI_MDCV_PARAMS;
  }

  ps_sei->u1_sei_mdcv_params_present_flag = 1;
  return (OK);
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : ih264d_parse_clli                                         */
/*                                                                           */
/*  Description   : This function parses SEI CLLI message                     */
/*  Inputs        : ps_bitstrm    Bitstream                                  */
/*                  ps_dec          Poniter decoder context                  */
/*                  ui4_payload_size pay load i4_size                        */
/*  Globals       : None                                                     */
/*  Processing    :                                                          */
/*  Outputs       : None                                                     */
/*  Return        : 0 for successfull parsing, else -1                       */
/*                                                                           */
/*  Issues        :                                                          */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*                                         Draft                             */
/*                                                                           */
/*****************************************************************************/
WORD32 ih264d_parse_clli(dec_bit_stream_t *ps_bitstrm, dec_struct_t *ps_dec,
                        UWORD32 ui4_payload_size) {
  sei *ps_sei;
  UNUSED(ui4_payload_size);

  if (ps_dec == NULL) {
    return NOT_OK;
  }
  ps_sei = (sei *) ps_dec->ps_sei_parse;

  if (ps_sei == NULL) {
    return NOT_OK;
  }

  ps_sei->u1_sei_clli_params_present_flag = 1;
  memset(&ps_sei->s_sei_clli_params, 0, sizeof(sei));

  ps_sei->s_sei_clli_params.u2_max_content_light_level =
      (UWORD16) ih264d_get_bits_h264(ps_bitstrm, 16);
  ps_sei->s_sei_clli_params.u2_max_pic_average_light_level =
      (UWORD16) ih264d_get_bits_h264(ps_bitstrm, 16);

  return (OK);
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : ih264d_parse_fgc                                         */
/*                                                                           */
/*  Description   : This function parses SEI message film grain charcaristics*/
/*  Inputs        : ps_bitstrm    Bitstream                                  */
/*                  ps_dec          Poniter decoder context                  */
/*                  ui4_payload_size pay load i4_size                        */
/*  Globals       : None                                                     */
/*  Processing    :                                                          */
/*  Outputs       : None                                                     */
/*  Return        : 0 for successfull parsing, else -1                       */
/*                                                                           */
/*  Issues        :                                                          */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*                         Draft                                             */
/*                                                                           */
/*****************************************************************************/
WORD32 ih264d_parse_fgc(dec_bit_stream_t *ps_bitstrm, dec_struct_t *ps_dec,
                        UWORD32 ui4_payload_size)
{
  sei *ps_sei = ps_dec->ps_sei_parse;
  dec_err_status_t *ps_err = ps_dec->ps_dec_err_status;
  UWORD32 *pu4_bitstrm_ofst = &ps_bitstrm->u4_ofst;
  UWORD32 *pu4_bitstrm_buf = ps_bitstrm->pu4_buffer;
  UWORD32 u4_count;
  WORD32 i4_luma_bitdepth, i4_chroma_bitdepth;
  UWORD32 c, i, j;
  UNUSED(ui4_payload_size);

  if((ps_dec == NULL) || (ps_sei == NULL))
  {
    return NOT_OK;
  }

  ps_sei->u1_sei_fgc_params_present_flag = 0;

  ps_sei->s_sei_fgc_params.u1_film_grain_characteristics_cancel_flag =
      (UWORD8) ih264d_get_bit_h264(ps_bitstrm);

  if(0 == ps_sei->s_sei_fgc_params.u1_film_grain_characteristics_cancel_flag)
  {
    ps_sei->s_sei_fgc_params.u1_film_grain_model_id = (UWORD8) ih264d_get_bits_h264(ps_bitstrm, 2);
    if(ps_sei->s_sei_fgc_params.u1_film_grain_model_id > 1)
    {
      return ERROR_INV_SEI_FGC_PARAMS;
    }
    ps_sei->s_sei_fgc_params.u1_separate_colour_description_present_flag =
        (UWORD8) ih264d_get_bit_h264(ps_bitstrm);

    if(ps_sei->s_sei_fgc_params.u1_separate_colour_description_present_flag)
    {
      ps_sei->s_sei_fgc_params.u1_film_grain_bit_depth_luma_minus8 =
          (UWORD8) ih264d_get_bits_h264(ps_bitstrm, 3);

      i4_luma_bitdepth = ps_sei->s_sei_fgc_params.u1_film_grain_bit_depth_luma_minus8 + 8;

      ps_sei->s_sei_fgc_params.u1_film_grain_bit_depth_chroma_minus8 =
          (UWORD8) ih264d_get_bits_h264(ps_bitstrm, 3);

      i4_chroma_bitdepth = ps_sei->s_sei_fgc_params.u1_film_grain_bit_depth_chroma_minus8 + 8;

      ps_sei->s_sei_fgc_params.u1_film_grain_full_range_flag =
          (UWORD8) ih264d_get_bit_h264(ps_bitstrm);

      ps_sei->s_sei_fgc_params.u1_film_grain_colour_primaries =
          (UWORD8) ih264d_get_bits_h264(ps_bitstrm, 8);

      ps_sei->s_sei_fgc_params.u1_film_grain_transfer_characteristics =
          (UWORD8) ih264d_get_bits_h264(ps_bitstrm, 8);

      ps_sei->s_sei_fgc_params.u1_film_grain_matrix_coefficients =
          (UWORD8) ih264d_get_bits_h264(ps_bitstrm, 8);
    }
    else
    {
      if(ps_dec->ps_cur_sps == NULL)
      {
        return NOT_OK;
      }
      i4_luma_bitdepth = ps_dec->ps_cur_sps->i4_bit_depth_luma_minus8 + 8;
      i4_chroma_bitdepth = ps_dec->ps_cur_sps->i4_bit_depth_chroma_minus8 + 8;
    }
    ps_sei->s_sei_fgc_params.u1_blending_mode_id = (UWORD8) ih264d_get_bits_h264(ps_bitstrm, 2);

    if(ps_sei->s_sei_fgc_params.u1_blending_mode_id > 1)
    {
      return ERROR_INV_SEI_FGC_PARAMS;
    }

    ps_sei->s_sei_fgc_params.u1_log2_scale_factor = (UWORD8) ih264d_get_bits_h264(ps_bitstrm, 4);

    for(c = 0; c < SEI_FGC_NUM_COLOUR_COMPONENTS; c++)
    {
      ps_sei->s_sei_fgc_params.au1_comp_model_present_flag[c] =
          (UWORD8) ih264d_get_bit_h264(ps_bitstrm);
    }

    for(c = 0; c < SEI_FGC_NUM_COLOUR_COMPONENTS; c++)
    {
      if(ps_sei->s_sei_fgc_params.au1_comp_model_present_flag[c])
      {
        ps_sei->s_sei_fgc_params.au1_num_intensity_intervals_minus1[c] =
            (UWORD8) ih264d_get_bits_h264(ps_bitstrm, 8);

        ps_sei->s_sei_fgc_params.au1_num_model_values_minus1[c] =
            (UWORD8) ih264d_get_bits_h264(ps_bitstrm, 3);

        if(ps_sei->s_sei_fgc_params.au1_num_model_values_minus1[c] >
           (SEI_FGC_MAX_NUM_MODEL_VALUES - 1))
        {
            return ERROR_INV_SEI_FGC_PARAMS;
        }

        for(i = 0; i <= ps_sei->s_sei_fgc_params.au1_num_intensity_intervals_minus1[c]; i++)
        {
            ps_sei->s_sei_fgc_params.au1_intensity_interval_lower_bound[c][i] =
                (UWORD8) ih264d_get_bits_h264(ps_bitstrm, 8);

            ps_sei->s_sei_fgc_params.au1_intensity_interval_upper_bound[c][i] =
                (UWORD8) ih264d_get_bits_h264(ps_bitstrm, 8);

            for(j = 0; j <= ps_sei->s_sei_fgc_params.au1_num_model_values_minus1[c]; j++)
            {
                ps_sei->s_sei_fgc_params.ai4_comp_model_value[c][i][j] =
                    (WORD32) ih264d_sev(pu4_bitstrm_ofst, pu4_bitstrm_buf);
                if(0 == ps_sei->s_sei_fgc_params.u1_film_grain_model_id)
                {
                    if((1 == j) || (2 == j))
                    {
                        if((ps_sei->s_sei_fgc_params.ai4_comp_model_value[c][i][j] < 0) ||
                           (ps_sei->s_sei_fgc_params.ai4_comp_model_value[c][i][j] > 16))
                            return ERROR_INV_SEI_FGC_PARAMS;
                    }
                    else if((3 == j) || (4 == j))
                    {
                        if((ps_sei->s_sei_fgc_params.ai4_comp_model_value[c][i][j] < 0) ||
                           (ps_sei->s_sei_fgc_params.ai4_comp_model_value[c][i][j] >
                            ps_sei->s_sei_fgc_params.ai4_comp_model_value[c][i][j - 2]))
                            return ERROR_INV_SEI_FGC_PARAMS;
                    }
                    else
                    {
                        WORD32 max_lim =
                            (c == 0) ? (1 << i4_luma_bitdepth) - 1 : (1 << i4_chroma_bitdepth) - 1;

                        if((ps_sei->s_sei_fgc_params.ai4_comp_model_value[c][i][j] < 0) ||
                           (ps_sei->s_sei_fgc_params.ai4_comp_model_value[c][i][j] > max_lim))
                        {
                            return ERROR_INV_SEI_FGC_PARAMS;
                        }
                    }
                }
                else
                {
                    WORD32 max_lim =
                        (c == 0) ? (1 << (i4_luma_bitdepth - 1)) : (1 << (i4_chroma_bitdepth - 1));

                    if((ps_sei->s_sei_fgc_params.ai4_comp_model_value[c][i][j] < -max_lim) ||
                       (ps_sei->s_sei_fgc_params.ai4_comp_model_value[c][i][j] >= max_lim))
                    {
                        return ERROR_INV_SEI_FGC_PARAMS;
                    }
                }
            }
        }
      }
    }

    ps_sei->s_sei_fgc_params.u4_film_grain_characteristics_repetition_period =
        (UWORD32) ih264d_uev(pu4_bitstrm_ofst, pu4_bitstrm_buf);

    if(ps_sei->s_sei_fgc_params.u4_film_grain_characteristics_repetition_period < 0 ||
       ps_sei->s_sei_fgc_params.u4_film_grain_characteristics_repetition_period > 16384)
    {
      return ERROR_INV_SEI_FGC_PARAMS;
    }

    ps_sei->u1_sei_fgc_params_present_flag = 1;
  }

  return (OK);
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : ih264d_parse_sei_payload */
/*                                                                           */
/*  Description   : This function parses SEI pay loads. Currently it's       */
/*                  implemented partially.                                   */
/*  Inputs        : ps_bitstrm    Bitstream                                */
/*                  ui4_payload_type  SEI payload type                       */
/*                  ui4_payload_size  SEI payload i4_size */
/*  Globals       : None                                                     */
/*  Processing    : Parses SEI payloads units and stores the info            */
/*  Outputs       : None                                                     */
/*  Returns       : None                                                     */
/*                                                                           */
/*  Issues        : Not implemented fully                                    */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         06 05 2002   NS              Draft                                */
/*                                                                           */
/*****************************************************************************/

WORD32 ih264d_parse_sei_payload(dec_bit_stream_t *ps_bitstrm,
                                UWORD32 ui4_payload_type,
                                UWORD32 ui4_payload_size,
                                dec_struct_t *ps_dec) {
  sei *ps_sei;
  WORD32 i4_status = 0;
  ps_sei = (sei *) ps_dec->ps_sei_parse;

  if (NULL == ps_bitstrm) {
    return NOT_OK;
  }

  switch (ui4_payload_type) {
    case SEI_BUF_PERIOD:

      i4_status = ih264d_parse_buffering_period(&ps_sei->s_buf_period,
                                                ps_bitstrm, ps_dec);
      /*if(i4_status != OK)
          return i4_status;*/
      break;
    case SEI_PIC_TIMING:
      if (NULL == ps_dec->ps_cur_sps)
        ih264d_flush_bits_h264(ps_bitstrm, (ui4_payload_size << 3));
      else
        ih264d_parse_pic_timing(ps_bitstrm, ps_dec, ui4_payload_size);
      break;
    case SEI_RECOVERY_PT:
      ih264d_parse_recovery_point(ps_bitstrm, ps_dec, ui4_payload_size);
      break;
    case SEI_MASTERING_DISP_COL_VOL:
      i4_status = ih264d_parse_mdcv(ps_bitstrm, ps_dec, ui4_payload_size);
      break;
    case SEI_CONTENT_LIGHT_LEVEL_INFORMATION_DATA:
      i4_status = ih264d_parse_clli(ps_bitstrm, ps_dec, ui4_payload_size);
      break;
    case SEI_FILM_GRAIN_CHARACTERISTICS:
      i4_status = ih264d_parse_fgc(ps_bitstrm, ps_dec, ui4_payload_size);
       break;

    default:
      ih264d_flush_bits_h264(ps_bitstrm, (ui4_payload_size << 3));
      break;
  }
  return (i4_status);
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : ih264d_parse_sei_message */
/*                                                                           */
/*  Description   : This function is parses and decode SEI. Currently it's   */
/*                  not implemented fully.                                   */
/*  Inputs        : ps_dec    Decoder parameters                       */
/*                  ps_bitstrm    Bitstream                                */
/*  Globals       : None                                                     */
/*  Processing    : Parses SEI NAL units and stores the info                 */
/*  Outputs       : None                                                     */
/*  Returns       : None                                                     */
/*                                                                           */
/*  Issues        : Not implemented fully                                    */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         06 05 2002   NS              Draft                                */
/*                                                                           */
/*****************************************************************************/

WORD32 ih264d_parse_sei_message(dec_struct_t *ps_dec,
                                dec_bit_stream_t *ps_bitstrm) {
  UWORD32 ui4_payload_type, ui4_payload_size;
  UWORD32 u4_bits;
  WORD32 i4_status = 0;

  do {
    ui4_payload_type = 0;

    u4_bits = ih264d_get_bits_h264(ps_bitstrm, 8);
    while (0xff == u4_bits) {
      u4_bits = ih264d_get_bits_h264(ps_bitstrm, 8);
      ui4_payload_type += 255;
    }
    ui4_payload_type += u4_bits;

    ui4_payload_size = 0;
    u4_bits = ih264d_get_bits_h264(ps_bitstrm, 8);
    while (0xff == u4_bits) {
      u4_bits = ih264d_get_bits_h264(ps_bitstrm, 8);
      ui4_payload_size += 255;
    }
    ui4_payload_size += u4_bits;

    i4_status = ih264d_parse_sei_payload(ps_bitstrm, ui4_payload_type,
                                         ui4_payload_size, ps_dec);
    if (i4_status == -1) {
      i4_status = 0;
      break;
    }

    if (i4_status != OK) return i4_status;

    if (ih264d_check_byte_aligned(ps_bitstrm) == 0) {
      u4_bits = ih264d_get_bit_h264(ps_bitstrm);
      if (0 == u4_bits) {
        H264_DEC_DEBUG_PRINT("\nError in parsing SEI message");
      }
      while (0 == ih264d_check_byte_aligned(ps_bitstrm)) {
        u4_bits = ih264d_get_bit_h264(ps_bitstrm);
        if (u4_bits) {
          H264_DEC_DEBUG_PRINT("\nError in parsing SEI message");
        }
      }
    }
  } while (ps_bitstrm->u4_ofst < ps_bitstrm->u4_max_ofst);
  return (i4_status);
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : ih264d_export_sei_mdcv_params                            */
/*                                                                           */
/*  Description   : This function populates SEI mdcv message in              */
/*                     output structure                                      */
/*  Inputs        : ps_sei_mdcv_op pointer to sei mdcv o\p struct            */
/*                : ps_sei pointer to decoded sei params                     */
/*  Outputs       :                                                          */
/*  Returns       : returns 0 for success; -1 for failure                    */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
WORD32 ih264d_export_sei_mdcv_params(ivd_sei_decode_op_t *ps_sei_decode_op,
                                     sei *ps_sei, sei *ps_sei_export) {
  if ((ps_sei_export == NULL) || (ps_sei == NULL)) {
    return NOT_OK;
  }

  ps_sei_export->u1_sei_mdcv_params_present_flag =
      ps_sei->u1_sei_mdcv_params_present_flag;
  ps_sei_decode_op->u1_sei_mdcv_params_present_flag =
      ps_sei->u1_sei_mdcv_params_present_flag;

  if (0 == ps_sei_export->u1_sei_mdcv_params_present_flag) {
    memset(&ps_sei_export->s_sei_mdcv_params, 0, sizeof(sei_mdcv_params_t));
  } else {
    memcpy(&ps_sei_export->s_sei_mdcv_params, &ps_sei->s_sei_mdcv_params,
           sizeof(sei_mdcv_params_t));
  }

  return (OK);
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : ih264d_export_sei_clli_params                             */
/*                                                                           */
/*  Description   : This function populates SEI CLLI message in               */
/*                     output structure                                      */
/*  Inputs        : ps_sei_clli_op pointer to SEI CLLI o\p struct              */
/*                : ps_sei pointer to decoded sei params                     */
/*  Outputs       :                                                          */
/*  Returns       : returns 0 for success; -1 for failure                    */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
WORD32 ih264d_export_sei_clli_params(ivd_sei_decode_op_t *ps_sei_decode_op,
                                    sei *ps_sei, sei *ps_sei_export) {
  if ((ps_sei_export == NULL) || (ps_sei == NULL)) {
    return NOT_OK;
  }

  ps_sei_export->u1_sei_clli_params_present_flag =
      ps_sei->u1_sei_clli_params_present_flag;
  ps_sei_decode_op->u1_sei_clli_params_present_flag =
      ps_sei->u1_sei_clli_params_present_flag;

  if (0 == ps_sei_export->u1_sei_clli_params_present_flag) {
    memset(&ps_sei_export->s_sei_clli_params, 0, sizeof(sei_clli_params_t));
  } else {
    memcpy(&ps_sei_export->s_sei_clli_params, &ps_sei->s_sei_clli_params,
           sizeof(sei_clli_params_t));
  }
  return (OK);
}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : ih264d_export_sei_fgc_params                             */
/*                                                                           */
/*  Description   : This function populates SEI film grain params in         */
/*                     output structure                                      */
/*  Inputs        : ps_sei_fgc_op pointer to sei fgc o\p struct              */
/*                : ps_sei pointer to decoded sei params                     */
/*  Outputs       :                                                          */
/*  Returns       : returns 0 for success; -1 for failure                    */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision History:                                                        */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
WORD32 ih264d_export_sei_fgc_params(ivd_sei_decode_op_t *ps_sei_decode_op, sei *ps_sei,
                                    sei *ps_sei_export)
{
    if((ps_sei_export == NULL) || (ps_sei == NULL))
    {
        return NOT_OK;
    }

    ps_sei_export->u1_sei_fgc_params_present_flag = ps_sei->u1_sei_fgc_params_present_flag;
    ps_sei_decode_op->u1_sei_fgc_params_present_flag = ps_sei->u1_sei_fgc_params_present_flag;

    if(0 == ps_sei_export->u1_sei_fgc_params_present_flag)
    {
        memset(&ps_sei_export->s_sei_fgc_params, 0, sizeof(sei_fgc_params_t));
    }
    else
    {
        memcpy(&ps_sei_export->s_sei_fgc_params, &ps_sei->s_sei_fgc_params,
               sizeof(sei_fgc_params_t));
    }

    return (OK);
}
