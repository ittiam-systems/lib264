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
#ifndef _IH264D_PARSE_BSLICE_H_
#define _IH264D_PARSE_BSLICE_H_
/*!
**************************************************************************
* \file ih264d_process_bslice.h
*
* \brief
*    Contains declarations of routines that decode a B slice type
*
* Detailed_description
*
* \date
*    21/12/2002
*
* \author  NS
**************************************************************************
*/
#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264d_structs.h"
WORD32 ih264d_parse_bslice(dec_struct_t *ps_dec, UWORD16 u2_first_mb_in_slice);
WORD32 ih264d_decode_spatial_direct(dec_struct_t *ps_dec, UWORD8 u1_wd_x,
                                    dec_mb_info_t *ps_cur_mb_info,
                                    UWORD8 u1_mb_num);
WORD32 ih264d_decode_temporal_direct(dec_struct_t *ps_dec, UWORD8 u1_wd_x,
                                     dec_mb_info_t *ps_cur_mb_info,
                                     UWORD8 u1_mb_num);
WORD32 parseBSliceData(dec_struct_t *ps_dec, dec_slice_params_t *ps_slice,
                       UWORD16 u2_first_mb_in_slice);
WORD32 parseBSliceData(dec_struct_t *ps_dec, dec_slice_params_t *ps_slice,
                       UWORD16 u2_first_mb_in_slice);

void ih264d_init_ref_idx_lx_b(dec_struct_t *ps_dec);

void ih264d_convert_frm_to_fld_list(struct pic_buffer_t *ps_ref_pic_buf_lx,
                                    UWORD8 *pu1_L0, dec_struct_t *ps_dec,
                                    UWORD8 u1_num_short_term_bufs);

void ih264d_convert_frm_mbaff_list(dec_struct_t *ps_dec);
void ih264d_one_to_one(dec_struct_t *ps_dec, struct pic_buffer_t *ps_col_pic,
                       directmv_t *ps_direct, UWORD8 u1_wd_x,
                       WORD32 u2_sub_mb_ofst, dec_mb_info_t *ps_cur_mb_info);
void ih264d_mbaff_cross_pmbair(dec_struct_t *ps_dec,
                               struct pic_buffer_t *ps_col_pic,
                               directmv_t *ps_direct, UWORD8 u1_wd_x,
                               WORD32 u2_sub_mb_ofst,
                               dec_mb_info_t *ps_cur_mb_info);
void ih264d_frm_to_fld(dec_struct_t *ps_dec, struct pic_buffer_t *ps_col_pic,
                       directmv_t *ps_direct, UWORD8 u1_wd_x,
                       WORD32 u2_sub_mb_ofst, dec_mb_info_t *ps_cur_mb_info);
void ih264d_fld_to_frm(dec_struct_t *ps_dec, struct pic_buffer_t *ps_col_pic,
                       directmv_t *ps_direct, UWORD8 u1_wd_x,
                       WORD32 u2_sub_mb_ofst, dec_mb_info_t *ps_cur_mb_info);
void ih264d_mbaff_to_fld(dec_struct_t *ps_dec, struct pic_buffer_t *ps_col_pic,
                         directmv_t *ps_direct, UWORD8 u1_wd_x,
                         WORD32 u2_sub_mb_ofst, dec_mb_info_t *ps_cur_mb_info);
void ih264d_fld_to_mbaff(dec_struct_t *ps_dec, struct pic_buffer_t *ps_col_pic,
                         directmv_t *ps_direct, UWORD8 u1_wd_x,
                         WORD32 u2_sub_mb_ofst, dec_mb_info_t *ps_cur_mb_info);
WORD32 ih264d_cal_col_pic(dec_struct_t *ps_dec);

WORD32 ih264d_mv_pred_ref_tfr_nby2_bmb(dec_struct_t *ps_dec, UWORD8 u1_num_mbs,
                                       UWORD8 u1_num_mbsNby2);

#endif /* _IH264D_PARSE_BSLICE_H_ */
