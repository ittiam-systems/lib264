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
#ifndef _IH264D_DEBLOCKING_H_
#define _IH264D_DEBLOCKING_H_
/*!
 **************************************************************************
 * \file ih264d_deblocking.h
 *
 * \brief
 *    Declarations of deblocking functions
 *
 * \date
 *    23/11/2002
 *
 * \author  AI
 **************************************************************************
 */
#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264d_structs.h"

WORD8 ih264d_set_deblocking_parameters(deblk_mb_t *ps_cur_deblk_mb,
                                       dec_slice_params_t *ps_slice,
                                       UWORD8 u1_mb_ngbr_availablity,
                                       UWORD8 u1_mb_field_decoding_flag);

void FilterBoundaryLeft(tfr_ctxt_t *const ps_tfr_cxt,
                        const WORD8 i1_cb_qp_idx_ofst,
                        const WORD8 i1_cr_qp_idx_ofst,
                        deblk_mb_t *const ps_cur_mb, UWORD16 u2_strd_y,
                        UWORD16 u2_strd_uv, deblk_mb_t *const ps_left_mb,
                        const UWORD32 pu4_bs_tab[], const UWORD8 u1_cur_fld);
void FilterBoundaryTop(tfr_ctxt_t *const ps_tfr_cxt,
                       const WORD8 i1_cb_qp_idx_ofst,
                       const WORD8 i1_cr_qp_idx_ofst,
                       deblk_mb_t *const ps_cur_mb, const UWORD16 u2_strd_y,
                       const UWORD16 u2_strd_uv, deblk_mb_t *const ps_top_mb,
                       const UWORD32 u4_bs);
void deblock_mb(tfr_ctxt_t *const ps_tfr_cxt, const WORD8 i1_cb_qp_idx_ofst,
                const WORD8 i1_cr_qp_idx_ofst, deblk_mb_t *const ps_cur_mb,
                WORD32 i4_strd_y, WORD32 i4_strd_uv,
                deblk_mb_t *const ps_top_mb, deblk_mb_t *const ps_left_mb,
                const UWORD8 u1_cur_fld, const UWORD8 u1_extra_top_edge);
void ih264d_deblock_mb_mbaff(dec_struct_t *ps_dec, tfr_ctxt_t *ps_tfr_cxt,
                             WORD8 i1_cb_qp_idx_ofst, WORD8 i1_cr_qp_idx_ofst,
                             deblk_mb_t *ps_cur_mb, WORD32 i4_strd_y,
                             WORD32 i4_strd_uv, deblk_mb_t *ps_top_mb,
                             deblk_mb_t *ps_left_mb, UWORD8 u1_cur_fld,
                             UWORD8 u1_extra_top_edge);

void ih264d_deblock_picture_mbaff(dec_struct_t *ps_dec);

void ih264d_deblock_picture_non_mbaff(dec_struct_t *ps_dec);

void ih264d_deblock_picture_progressive(dec_struct_t *ps_dec);

void ih264d_compute_bs_mbaff(dec_struct_t *ps_dec,
                             dec_mb_info_t *ps_cur_mb_info,
                             const UWORD16 u2_mbxn_mb);
void ih264d_compute_bs_non_mbaff(dec_struct_t *ps_dec,
                                 dec_mb_info_t *ps_cur_mb_info,
                                 const UWORD16 u2_mbxn_mb);

void ih264d_fill_bs_mbedge_2(dec_struct_t *ps_dec,
                             dec_mb_info_t *ps_cur_mb_info,
                             const UWORD16 u2_mbxn_mb);

void ih264d_fill_bs_mbedge_4(dec_struct_t *ps_dec,
                             dec_mb_info_t *ps_cur_mb_info,
                             const UWORD16 u2_mbxn_mb);

void ih264d_fill_bs1_16x16mb_pslice(
    mv_pred_t *ps_cur_mv_pred, mv_pred_t *ps_top_mv_pred,
    void **ppv_map_ref_idx_to_poc, UWORD32 *pu4_bs_table,
    mv_pred_t *ps_leftmost_mv_pred, neighbouradd_t *ps_left_addr,
    void **u4_pic_addrress, WORD32 i4_ver_mvlimit);

void ih264d_fill_bs1_non16x16mb_pslice(
    mv_pred_t *ps_cur_mv_pred, mv_pred_t *ps_top_mv_pred,
    void **ppv_map_ref_idx_to_poc, UWORD32 *pu4_bs_table,
    mv_pred_t *ps_leftmost_mv_pred, neighbouradd_t *ps_left_addr,
    void **u4_pic_addrress, WORD32 i4_ver_mvlimit);

void ih264d_fill_bs1_16x16mb_bslice(
    mv_pred_t *ps_cur_mv_pred, mv_pred_t *ps_top_mv_pred,
    void **ppv_map_ref_idx_to_poc, UWORD32 *pu4_bs_table,
    mv_pred_t *ps_leftmost_mv_pred, neighbouradd_t *ps_left_addr,
    void **u4_pic_addrress, WORD32 i4_ver_mvlimit);

void ih264d_fill_bs1_non16x16mb_bslice(
    mv_pred_t *ps_cur_mv_pred, mv_pred_t *ps_top_mv_pred,
    void **ppv_map_ref_idx_to_poc, UWORD32 *pu4_bs_table,
    mv_pred_t *ps_leftmost_mv_pred, neighbouradd_t *ps_left_addr,
    void **u4_pic_addrress, WORD32 i4_ver_mvlimit);

void ih264d_fill_bs_xtra_left_edge_cur_fld(UWORD32 *pu4_bs,
                                           WORD32 u4_left_mb_t_csbp,
                                           WORD32 u4_left_mb_b_csbp,
                                           WORD32 u4_cur_mb_csbp,
                                           UWORD32 u4_cur_mb_top);

void ih264d_fill_bs_xtra_left_edge_cur_frm(UWORD32 *pu4_bs,
                                           WORD32 u4_left_mb_t_csbp,
                                           WORD32 u4_left_mb_b_csbp,
                                           WORD32 u4_cur_mb_csbp,
                                           UWORD32 u4_cur_mb_top);

void ih264d_deblock_mb_nonmbaff(dec_struct_t *ps_dec, tfr_ctxt_t *ps_tfr_cxt,
                                WORD8 i1_cb_qp_idx_ofst,
                                WORD8 i1_cr_qp_idx_ofst, deblk_mb_t *ps_cur_mb,
                                WORD32 i4_strd_y, WORD32 i4_strd_uv,
                                deblk_mb_t *ps_top_mb, deblk_mb_t *ps_left_mb);

void ih264d_init_deblk_tfr_ctxt(dec_struct_t *ps_dec, pad_mgr_t *ps_pad_mgr,
                                tfr_ctxt_t *ps_tfr_cxt, UWORD16 u2_image_wd_mb,
                                UWORD8 u1_mbaff);

void ih264d_deblock_mb_level(dec_struct_t *ps_dec,
                             dec_mb_info_t *ps_cur_mb_info, UWORD32 nmb_index);

#endif /* _IH264D_DEBLOCKING_H_ */
