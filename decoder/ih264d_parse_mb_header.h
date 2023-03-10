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
/*!
 ***************************************************************************
 * \file ih264d_parse_mb_header.h
 *
 * \brief
 *    This file contains context identifier decoding routines.
 *
 * \date
 *    04/02/2003
 *
 * \author  NS
 ***************************************************************************
 */
#ifndef _IH264D_PARSE_MB_HEADER_H_
#define _IH264D_PARSE_MB_HEADER_H_

#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264d_structs.h"
#include "ih264d_cabac.h"

WORD32 ih264d_read_intra_pred_modes_cabac(
    dec_struct_t *ps_dec, UWORD8 *pu1_prev_intra4x4_pred_mode_flag,
    UWORD8 *pu1_rem_intra4x4_pred_mode, UWORD8 u1_tran_form8x8);

UWORD32 ih264d_parse_mb_type_cabac(struct _DecStruct *ps_dec);
UWORD8 ih264d_parse_mb_type_intra_cabac(UWORD8 u1_inter,
                                        struct _DecStruct *ps_dec);

UWORD32 ih264d_parse_submb_type_cabac(const UWORD8 u1_slc_type_p,
                                      decoding_envirnoment_t *ps_cab_env,
                                      dec_bit_stream_t *ps_bitstrm,
                                      bin_ctxt_model_t *ps_sub_mb_cxt);
WORD32 ih264d_parse_ref_idx_cabac(const UWORD8 u1_num_part, const UWORD8 u1_b2,
                                  const UWORD8 u1_max_ref_minus1,
                                  const UWORD8 u1_mb_mode, WORD8 *pi1_ref_idx,
                                  WORD8 *const pi1_lft_cxt,
                                  WORD8 *const pi1_top_cxt,
                                  decoding_envirnoment_t *const ps_cab_env,
                                  dec_bit_stream_t *const ps_bitstrm,
                                  bin_ctxt_model_t *const ps_ref_cxt);

WORD32 ih264d_parse_mb_qp_delta_cabac(struct _DecStruct *ps_dec,
                                      WORD8 *pi1_mb_qp_delta);
WORD8 ih264d_parse_chroma_pred_mode_cabac(struct _DecStruct *ps_dec);

UWORD32 ih264d_parse_ctx_cbp_cabac(struct _DecStruct *ps_dec);

UWORD8 ih264d_parse_transform8x8flag_cabac(struct _DecStruct *ps_dec,
                                           dec_mb_info_t *ps_cur_mb_info);

void ih264d_get_mvd_cabac(UWORD8 u1_sub_mb, UWORD8 u1_b2, UWORD8 u1_part_wd,
                          UWORD8 u1_part_ht, UWORD8 u1_dec_mvd,
                          dec_struct_t *ps_dec, mv_pred_t *ps_mv);

WORD16 ih264d_parse_mvd_cabac(dec_bit_stream_t *ps_bitstrm,
                              decoding_envirnoment_t *ps_cab_env,
                              bin_ctxt_model_t *p_ctxt_mvd, UWORD32 temp);

#endif /* _IH264D_PARSE_MB_HEADER_H_ */
