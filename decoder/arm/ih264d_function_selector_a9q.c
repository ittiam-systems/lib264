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
/**
*******************************************************************************
* @file
*  ih264e_function_selector_a9q.c
*
* @brief
*  Contains functions to initialize function pointers of codec context
*
* @author
*  Ittiam
*
* @par List of Functions:
*  - ih264e_init_function_ptr_a9q
*
* @remarks
*  None
*
*******************************************************************************
*/

/*****************************************************************************/
/* File Includes                                                             */
/*****************************************************************************/

/* System Include files */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* User Include files */
#include "ih264_typedefs.h"
#include "iv.h"
#include "ivd.h"
#include "ih264_defs.h"
#include "ih264_size_defs.h"
#include "ih264_error.h"
#include "ih264_trans_quant_itrans_iquant.h"
#include "ih264_inter_pred_filters.h"

#include "ih264d_structs.h"

/**
*******************************************************************************
*
* @brief Initialize the intra/inter/transform/deblk function pointers of
* codec context
*
* @par Description: the current routine initializes the function pointers of
* codec context basing on the architecture in use
*
* @param[in] ps_codec
*  Codec context pointer
*
* @returns  none
*
* @remarks none
*
*******************************************************************************
*/
void ih264d_init_function_ptr_a9q(dec_struct_t *ps_codec) {
  /* Init function pointers for intra pred leaf level functions luma
   * Intra 16x16 */
  ps_codec->apf_intra_pred_luma_16x16[0] =
      ih264_intra_pred_luma_16x16_mode_vert_a9q;
  ps_codec->apf_intra_pred_luma_16x16[1] =
      ih264_intra_pred_luma_16x16_mode_horz_a9q;
  ps_codec->apf_intra_pred_luma_16x16[2] =
      ih264_intra_pred_luma_16x16_mode_dc_a9q;
  ps_codec->apf_intra_pred_luma_16x16[3] =
      ih264_intra_pred_luma_16x16_mode_plane_a9q;

  /* Init function pointers for intra pred leaf level functions luma
   * Intra 4x4 */
  ps_codec->apf_intra_pred_luma_4x4[0] =
      ih264_intra_pred_luma_4x4_mode_vert_a9q;
  ps_codec->apf_intra_pred_luma_4x4[1] =
      ih264_intra_pred_luma_4x4_mode_horz_a9q;
  ps_codec->apf_intra_pred_luma_4x4[2] = ih264_intra_pred_luma_4x4_mode_dc_a9q;
  ps_codec->apf_intra_pred_luma_4x4[3] =
      ih264_intra_pred_luma_4x4_mode_diag_dl_a9q;
  ps_codec->apf_intra_pred_luma_4x4[4] =
      ih264_intra_pred_luma_4x4_mode_diag_dr_a9q;
  ps_codec->apf_intra_pred_luma_4x4[5] =
      ih264_intra_pred_luma_4x4_mode_vert_r_a9q;
  ps_codec->apf_intra_pred_luma_4x4[6] =
      ih264_intra_pred_luma_4x4_mode_horz_d_a9q;
  ps_codec->apf_intra_pred_luma_4x4[7] =
      ih264_intra_pred_luma_4x4_mode_vert_l_a9q;
  ps_codec->apf_intra_pred_luma_4x4[8] =
      ih264_intra_pred_luma_4x4_mode_horz_u_a9q;

  /* Init function pointers for intra pred leaf level functions luma
   * Intra 8x8 */
  ps_codec->apf_intra_pred_luma_8x8[0] =
      ih264_intra_pred_luma_8x8_mode_vert_a9q;
  ps_codec->apf_intra_pred_luma_8x8[1] =
      ih264_intra_pred_luma_8x8_mode_horz_a9q;
  ps_codec->apf_intra_pred_luma_8x8[2] = ih264_intra_pred_luma_8x8_mode_dc_a9q;
  ps_codec->apf_intra_pred_luma_8x8[3] =
      ih264_intra_pred_luma_8x8_mode_diag_dl_a9q;
  ps_codec->apf_intra_pred_luma_8x8[4] =
      ih264_intra_pred_luma_8x8_mode_diag_dr_a9q;
  ps_codec->apf_intra_pred_luma_8x8[5] =
      ih264_intra_pred_luma_8x8_mode_vert_r_a9q;
  ps_codec->apf_intra_pred_luma_8x8[6] =
      ih264_intra_pred_luma_8x8_mode_horz_d_a9q;
  ps_codec->apf_intra_pred_luma_8x8[7] =
      ih264_intra_pred_luma_8x8_mode_vert_l_a9q;
  ps_codec->apf_intra_pred_luma_8x8[8] =
      ih264_intra_pred_luma_8x8_mode_horz_u_a9q;

  /* ih264_intra_pred_luma_8x8_mode_ref_filtering_a9q does not handle all
   * availibilities */
  ps_codec->pf_intra_pred_ref_filtering =
      ih264_intra_pred_luma_8x8_mode_ref_filtering;

  /* Init function pointers for intra pred leaf level functions chroma
   * Intra 8x8 */
  ps_codec->apf_intra_pred_chroma[0] =
      ih264_intra_pred_chroma_8x8_mode_vert_a9q;
  ps_codec->apf_intra_pred_chroma[1] =
      ih264_intra_pred_chroma_8x8_mode_horz_a9q;
  /* ih264_intra_pred_chroma_8x8_mode_dc_a9q does not support interlaced clips,
   * hence using C */
  ps_codec->apf_intra_pred_chroma[2] = ih264_intra_pred_chroma_8x8_mode_dc;
  ps_codec->apf_intra_pred_chroma[3] =
      ih264_intra_pred_chroma_8x8_mode_plane_a9q;

  ps_codec->pf_default_weighted_pred_luma =
      ih264_default_weighted_pred_luma_a9q;
  ps_codec->pf_default_weighted_pred_chroma =
      ih264_default_weighted_pred_chroma_a9q;
  ps_codec->pf_weighted_pred_luma = ih264_weighted_pred_luma_a9q;
  ps_codec->pf_weighted_pred_chroma = ih264_weighted_pred_chroma_a9q;
  ps_codec->pf_weighted_bi_pred_luma = ih264_weighted_bi_pred_luma_a9q;
  ps_codec->pf_weighted_bi_pred_chroma = ih264_weighted_bi_pred_chroma_a9q;

  /* Padding Functions */
  ps_codec->pf_pad_top = ih264_pad_top_a9q;
  ps_codec->pf_pad_bottom = ih264_pad_bottom;

  ps_codec->pf_pad_left_luma = ih264_pad_left_luma_a9q;
  ps_codec->pf_pad_right_luma = ih264_pad_right_luma_a9q;
  ps_codec->pf_pad_left_chroma = ih264_pad_left_chroma_a9q;
  ps_codec->pf_pad_right_chroma = ih264_pad_right_chroma_a9q;

  ps_codec->pf_iquant_itrans_recon_luma_4x4 = ih264_iquant_itrans_recon_4x4_a9;
  ps_codec->pf_iquant_itrans_recon_luma_4x4_dc =
      ih264_iquant_itrans_recon_4x4_dc_a9;
  ps_codec->pf_iquant_itrans_recon_luma_8x8 = ih264_iquant_itrans_recon_8x8_a9;
  ps_codec->pf_iquant_itrans_recon_luma_8x8_dc =
      ih264_iquant_itrans_recon_8x8_dc_a9;
  ps_codec->pf_ihadamard_scaling_4x4 = ih264_ihadamard_scaling_4x4_a9;

  ps_codec->pf_iquant_itrans_recon_chroma_4x4 =
      ih264_iquant_itrans_recon_chroma_4x4_a9;
  ps_codec->pf_iquant_itrans_recon_chroma_4x4_dc =
      ih264_iquant_itrans_recon_chroma_4x4_dc_a9;

  /* Init fn ptr luma deblocking */
  ps_codec->pf_deblk_luma_vert_bs4 = ih264_deblk_luma_vert_bs4_a9;
  ps_codec->pf_deblk_luma_vert_bslt4 = ih264_deblk_luma_vert_bslt4_a9;
  ps_codec->pf_deblk_luma_vert_bs4_mbaff = ih264_deblk_luma_vert_bs4_mbaff_a9;
  ps_codec->pf_deblk_luma_vert_bslt4_mbaff =
      ih264_deblk_luma_vert_bslt4_mbaff_a9;

  ps_codec->pf_deblk_luma_horz_bs4 = ih264_deblk_luma_horz_bs4_a9;
  ps_codec->pf_deblk_luma_horz_bslt4 = ih264_deblk_luma_horz_bslt4_a9;

  /* Init fn ptr chroma deblocking */
  ps_codec->pf_deblk_chroma_vert_bs4 = ih264_deblk_chroma_vert_bs4_a9;
  ps_codec->pf_deblk_chroma_vert_bslt4 = ih264_deblk_chroma_vert_bslt4_a9;
  ps_codec->pf_deblk_chroma_vert_bs4_mbaff =
      ih264_deblk_chroma_vert_bs4_mbaff_a9;
  ps_codec->pf_deblk_chroma_vert_bslt4_mbaff =
      ih264_deblk_chroma_vert_bslt4_mbaff_a9;

  ps_codec->pf_deblk_chroma_horz_bs4 = ih264_deblk_chroma_horz_bs4_a9;
  ps_codec->pf_deblk_chroma_horz_bslt4 = ih264_deblk_chroma_horz_bslt4_a9;

  /* Inter pred leaf level functions */
  ps_codec->apf_inter_pred_luma[0] = ih264_inter_pred_luma_copy_a9q;

  ps_codec->apf_inter_pred_luma[1] = ih264_inter_pred_luma_horz_qpel_a9q;
  ps_codec->apf_inter_pred_luma[2] = ih264_inter_pred_luma_horz_a9q;
  ps_codec->apf_inter_pred_luma[3] = ih264_inter_pred_luma_horz_qpel_a9q;
  ps_codec->apf_inter_pred_luma[4] = ih264_inter_pred_luma_vert_qpel_a9q;

  ps_codec->apf_inter_pred_luma[5] =
      ih264_inter_pred_luma_horz_qpel_vert_qpel_a9q;

  ps_codec->apf_inter_pred_luma[6] =
      ih264_inter_pred_luma_horz_hpel_vert_qpel_a9q;

  ps_codec->apf_inter_pred_luma[7] =
      ih264_inter_pred_luma_horz_qpel_vert_qpel_a9q;

  ps_codec->apf_inter_pred_luma[8] = ih264_inter_pred_luma_vert_a9q;
  ps_codec->apf_inter_pred_luma[9] =
      ih264_inter_pred_luma_horz_qpel_vert_hpel_a9q;
  ps_codec->apf_inter_pred_luma[10] =
      ih264_inter_pred_luma_horz_hpel_vert_hpel_a9q;
  ps_codec->apf_inter_pred_luma[11] =
      ih264_inter_pred_luma_horz_qpel_vert_hpel_a9q;
  ps_codec->apf_inter_pred_luma[12] = ih264_inter_pred_luma_vert_qpel_a9q;
  ps_codec->apf_inter_pred_luma[13] =
      ih264_inter_pred_luma_horz_qpel_vert_qpel_a9q;
  ps_codec->apf_inter_pred_luma[14] =
      ih264_inter_pred_luma_horz_hpel_vert_qpel_a9q;
  ps_codec->apf_inter_pred_luma[15] =
      ih264_inter_pred_luma_horz_qpel_vert_qpel_a9q;

  ps_codec->pf_inter_pred_chroma = ih264_inter_pred_chroma_a9q;

  return;
}
