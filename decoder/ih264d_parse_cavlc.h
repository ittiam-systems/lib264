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
#ifndef _IH264D_PARSE_CAVLC_H_
#define _IH264D_PARSE_CAVLC_H_
/*!
 **************************************************************************
 * \file ih264d_parse_cavlc.h
 *
 * \brief
 *    Declaration of UVLC and CAVLC functions
 *
 * \date
 *    18/12/2002
 *
 * \author  AI
 **************************************************************************
 */
#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264d_bitstrm.h"
#include "ih264d_structs.h"
#include "ih264d_cabac.h"

enum cavlcTableNum {
  tableTotalZeroOffset,
  tableTotalZero,
  tableRunBefore,
  codeGx,
  chromTab,
  offsetNumVlcTab
};

WORD32 ih264d_uvlc(dec_bit_stream_t *ps_bitstrm, UWORD32 u4_range,
                   UWORD32 *pi_bitstrm_ofst, UWORD8 u1_flag,
                   UWORD32 u4_bitstrm_ofst, UWORD32 *pi_bitstrm_buf);

UWORD32 ih264d_uev(UWORD32 *pu4_bitstrm_ofst, UWORD32 *pu4_bitstrm_buf);

WORD32 ih264d_sev(UWORD32 *pu4_bitstrm_ofst, UWORD32 *pu4_bitstrm_buf);

UWORD32 ih264d_tev_range1(UWORD32 *pu4_bitstrm_ofst, UWORD32 *pu4_bitstrm_buf);

UWORD8 RestOfResidualBlockCavlc(WORD16 *pi2_coeff_block,
                                UWORD32 u1_ofst_is_dc_max_coef_scale_fact,
                                UWORD32 u4_total_coeff_trail_one,
                                dec_bit_stream_t *ps_bitstrm,
                                UWORD8 *pu1_invscan);

WORD32 ih264d_cavlc_4x4res_block_totalcoeff_1(UWORD32 u4_isdc,
                                              UWORD32 u4_total_coeff_trail_one,
                                              dec_bit_stream_t *ps_bitstrm);

WORD32 ih264d_cavlc_4x4res_block_totalcoeff_2to10(
    UWORD32 u4_isdc, UWORD32 u4_total_coeff_trail_one,
    dec_bit_stream_t *ps_bitstrm);

WORD32 ih264d_cavlc_4x4res_block_totalcoeff_11to16(
    UWORD32 u4_isdc, UWORD32 u4_total_coeff_trail_one,
    dec_bit_stream_t *ps_bitstrm);

WORD32 ih264d_cavlc_parse4x4coeff_n0to7(WORD16 *pi2_coeff_block,
                                        UWORD32 u4_isdc, WORD32 u4_n,
                                        dec_struct_t *ps_dec,
                                        UWORD32 *pu4_total_coeff);

WORD32 ih264d_cavlc_parse4x4coeff_n8(WORD16 *pi2_coeff_block, UWORD32 u4_isdc,
                                     WORD32 u4_n, dec_struct_t *ps_dec,
                                     UWORD32 *pu4_total_coeff);

void ih264d_cavlc_parse_chroma_dc(dec_mb_info_t *ps_cur_mb_info,
                                  WORD16 *pi2_coeff_block,
                                  dec_bit_stream_t *ps_bitstrm,
                                  UWORD32 u4_scale_u, UWORD32 u4_scale_v,
                                  WORD32 i4_mb_inter_inc);

WORD32 ih264d_cavlc_parse_8x8block_none_available(
    WORD16 *pi2_coeff_block, UWORD32 u4_sub_block_strd, UWORD32 u4_isdc,
    dec_struct_t *ps_dec, UWORD8 *pu1_top_nnz, UWORD8 *pu1_left_nnz,
    UWORD8 u1_tran_form8x8, UWORD8 u1_mb_field_decodingflag, UWORD32 *pu4_csbp);

WORD32 ih264d_cavlc_parse_8x8block_left_available(
    WORD16 *pi2_coeff_block, UWORD32 u4_sub_block_strd, UWORD32 u4_isdc,
    dec_struct_t *ps_dec, UWORD8 *pu1_top_nnz, UWORD8 *pu1_left_nnz,
    UWORD8 u1_tran_form8x8, UWORD8 u1_mb_field_decodingflag, UWORD32 *pu4_csbp);

WORD32 ih264d_cavlc_parse_8x8block_top_available(
    WORD16 *pi2_coeff_block, UWORD32 u4_sub_block_strd, UWORD32 u4_isdc,
    dec_struct_t *ps_dec, UWORD8 *pu1_top_nnz, UWORD8 *pu1_left_nnz,
    UWORD8 u1_tran_form8x8, UWORD8 u1_mb_field_decodingflag, UWORD32 *pu4_csbp);

WORD32 ih264d_cavlc_parse_8x8block_both_available(
    WORD16 *pi2_coeff_block, UWORD32 u4_sub_block_strd, UWORD32 u4_isdc,
    dec_struct_t *ps_dec, UWORD8 *pu1_top_nnz, UWORD8 *pu1_left_nnz,
    UWORD8 u1_tran_form8x8, UWORD8 u1_mb_field_decodingflag, UWORD32 *pu4_csbp);

WORD8 ResidualBlockChromaDC(WORD16 *pi2_level, dec_bit_stream_t *ps_bitstrm);

void ih264d_parse_pmb_ref_index_cavlc_range1(
    UWORD32 u4_num_part, dec_bit_stream_t *ps_bitstrm, WORD8 *pi1_ref_idx,
    UWORD32 u4_num_ref_idx_active_minus1);

WORD32 ih264d_parse_pmb_ref_index_cavlc(UWORD32 u4_num_part,
                                        dec_bit_stream_t *ps_bitstrm,
                                        WORD8 *pi1_ref_idx,
                                        UWORD32 u4_num_ref_idx_active_minus1);

void ih264d_parse_bmb_ref_index_cavlc_range1(
    UWORD32 u4_num_part, dec_bit_stream_t *ps_bitstrm, WORD8 *pi1_ref_idx,
    UWORD32 u4_num_ref_idx_active_minus1);

WORD32 ih264d_parse_bmb_ref_index_cavlc(UWORD32 u4_num_part,
                                        dec_bit_stream_t *ps_bitstrm,
                                        WORD8 *pi1_ref_idx,
                                        UWORD32 u4_num_ref_idx_active_minus1);

#endif /* _IH264D_PARSE_CAVLC_H_ */
