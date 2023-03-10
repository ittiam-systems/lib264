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

#ifndef _IH264D_MVPRED_H_
#define _IH264D_MVPRED_H_

/**
**************************************************************************
* \file ih264d_mvpred.h
*
* \brief
*    This file contains declarations of functions specific to decoding
*    Motion vector.
*
* Detailed_description
*
* \date
*    10-12-2002
*
* \author  Arvind Raman
**************************************************************************
*/
#include "ih264d_structs.h"
#include "ih264d_defs.h"
// #include "structs.h"

/** Reference number that is not valid */
#define OUT_OF_RANGE_REF -1

#define ONE_TO_ONE 0
#define FRM_TO_FLD 1
#define FLD_TO_FRM 2

/**
**************************************************************************
*   \brief   POSITION_IN_MVBANK
*
*   a: Pointer to the top left subMb of the MB in the MV bank array
*   b: Horiz posn in terms of subMbs
*   c: Vert posn in terms of subMbs
*   d: subMb number
**************************************************************************
*/
#define POSITION_IN_MVBANK(a, b, c, d) (a) + (c) * (d) + (b)

/**
**************************************************************************
*   \brief   col4x4_t
*
*   Container to return the information related to the co-located 4x4
*   sub-macroblock.
**************************************************************************
*/
typedef struct {
  mv_pred_t *ps_mv;        /** Ptr to the Mv bank */
  UWORD16 u2_mb_addr_col;  /** Addr of the co-located MB */
  WORD16 i2_mv[2];         /** Mv of the colocated MB */
  WORD8 i1_ref_idx_col;    /** Ref idx of the co-located picture */
  UWORD8 u1_col_pic;       /** Idx of the colocated pic */
  UWORD8 u1_yM;            /** "y" coord of the colocated MB addr */
  UWORD8 u1_vert_mv_scale; /** as defined in sec 8.4.1.2.1 */
} col4x4_t;

void ih264d_update_nnz_for_skipmb(dec_struct_t *ps_dec,
                                  dec_mb_info_t *ps_cur_mb_info,
                                  UWORD8 u1_entrpy);

void ih264d_get_motion_vector_predictor(mv_pred_t *ps_result,
                                        mv_pred_t **ps_mv_pred,
                                        UWORD8 u1_ref_idx, UWORD8 u1_B,
                                        const UWORD8 *pu1_mv_pred_condition);
void ih264d_mbaff_mv_pred(mv_pred_t **ps_mv_pred, UWORD8 u1_sub_mb_num,
                          mv_pred_t *ps_mv_nmb, mv_pred_t *ps_mv_ntop,
                          dec_struct_t *ps_dec, UWORD8 uc_mb_part_width,
                          dec_mb_info_t *ps_cur_mb_info, UWORD8 *pu0_scale);
void ih264d_non_mbaff_mv_pred(mv_pred_t **ps_mv_pred, UWORD8 u1_sub_mb_num,
                              mv_pred_t *ps_mv_nmb, mv_pred_t *ps_mv_ntop,
                              dec_struct_t *ps_dec, UWORD8 uc_mb_part_width,
                              dec_mb_info_t *ps_cur_mb_info);
UWORD8 ih264d_mvpred_nonmbaff(dec_struct_t *ps_dec,
                              dec_mb_info_t *ps_cur_mb_info,
                              mv_pred_t *ps_mv_nmb, mv_pred_t *ps_mv_ntop,
                              mv_pred_t *ps_mv_final_pred, UWORD8 u1_sub_mb_num,
                              UWORD8 uc_mb_part_width, UWORD8 u1_lx_start,
                              UWORD8 u1_lxend, UWORD8 u1_mb_mc_mode);

UWORD8 ih264d_mvpred_nonmbaffB(dec_struct_t *ps_dec,
                               dec_mb_info_t *ps_cur_mb_info,
                               mv_pred_t *ps_mv_nmb, mv_pred_t *ps_mv_ntop,
                               mv_pred_t *ps_mv_final_pred,
                               UWORD8 u1_sub_mb_num, UWORD8 uc_mb_part_width,
                               UWORD8 u1_lx_start, UWORD8 u1_lxend,
                               UWORD8 u1_mb_mc_mode);

UWORD8 ih264d_mvpred_mbaff(dec_struct_t *ps_dec, dec_mb_info_t *ps_cur_mb_info,
                           mv_pred_t *ps_mv_nmb, mv_pred_t *ps_mv_ntop,
                           mv_pred_t *ps_mv_final_pred, UWORD8 u1_sub_mb_num,
                           UWORD8 uc_mb_part_width, UWORD8 u1_lx_start,
                           UWORD8 u1_lxend, UWORD8 u1_mb_mc_mode);

void ih264d_rep_mv_colz(dec_struct_t *ps_dec, mv_pred_t *ps_mv_pred_src,
                        mv_pred_t *ps_mv_pred_dst, UWORD8 u1_sub_mb_num,
                        UWORD8 u1_colz, UWORD8 u1_ht, UWORD8 u1_wd);

#endif /* _IH264D_MVPRED_H_ */
