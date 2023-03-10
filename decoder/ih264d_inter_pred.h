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

#ifndef _IH264D_INTER_PRED_H_
#define _IH264D_INTER_PRED_H_

/*!
 **************************************************************************
 * \file ih264d_inter_pred.h
 *
 * \brief
 *    Decalaration for routines defined in MorionCompensate.c
 *
 * Detailed_description
 *
 * \date
 *    creation_date
 *
 * \author  Arvind Raman
 **************************************************************************
 */

#include "ih264d_structs.h"

#define BUFFER_WIDTH 16
/*!
 **************************************************************************
 *   \brief   PRED_BUFFER_WIDTH / HEIGHT
 *
 *   Width and height of the 16 bit (also reused a 2 8 bits buffers). The
 *   required dimensions for these buffers are 21x21, however to align the
 *   start of every row to a WORD aligned boundary the width has been increased
 *   to 24.
 **************************************************************************
 */
// #define PRED_BUFFER_WIDTH   24
// #define PRED_BUFFER_HEIGHT  21
#define PRED_BUFFER_WIDTH 24 * 2
#define PRED_BUFFER_HEIGHT 24 * 2

void ih264d_fill_pred_info(WORD16 *pi2_mv, WORD32 part_width,
                           WORD32 part_height, WORD32 sub_mb_num,
                           WORD32 pred_dir, pred_info_pkd_t *ps_pred_pkd,
                           WORD8 i1_buf_id, WORD8 i1_ref_idx,
                           UWORD32 *pu4_wt_offset, UWORD8 u1_pic_type);

WORD32 ih264d_form_mb_part_info_bp(pred_info_pkd_t *ps_pred_pkd,
                                   dec_struct_t *ps_dec, UWORD16 u2_mb_x,
                                   UWORD16 u2_mb_y, WORD32 mb_index,
                                   dec_mb_info_t *ps_cur_mb_info);

WORD32 ih264d_form_mb_part_info_mp(pred_info_pkd_t *ps_pred_pkd,
                                   dec_struct_t *ps_dec, UWORD16 u2_mb_x,
                                   UWORD16 u2_mb_y, WORD32 mb_index,
                                   dec_mb_info_t *ps_cur_mb_info);

void ih264d_motion_compensate_bp(dec_struct_t *ps_dec,
                                 dec_mb_info_t *ps_cur_mb_info);
void ih264d_motion_compensate_mp(dec_struct_t *ps_dec,
                                 dec_mb_info_t *ps_cur_mb_info);

void TransferRefBuffs(dec_struct_t *ps_dec);

void ih264d_multiplex_ref_data(dec_struct_t *ps_dec, pred_info_t *ps_pred,
                               UWORD8 *pu1_dest_y, UWORD8 *pu1_dest_u,
                               UWORD8 *pu1_dest_v,
                               dec_mb_info_t *ps_cur_mb_info,
                               UWORD16 u2_dest_wd_y, UWORD16 u2_dest_wd_uv,
                               UWORD8 u1_dir);
#endif /* _IH264D_INTER_PRED_H_ */
