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
#ifndef _IH264D_UTILS_H_
#define _IH264D_UTILS_H_
/*!
**************************************************************************
* \file ih264d_utils.h
*
* \brief
*    Contains declaration of routines
*    that handle of start and end of pic processing
*
* \date
*    19/12/2002
*
* \author  AI
**************************************************************************
*/
#include "ih264d_defs.h"
#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264d_structs.h"
#include "ih264d_parse_cavlc.h"

void pad_frm_buff_vert(dec_struct_t *ps_dec);

UWORD8 ih264d_is_end_of_pic(UWORD16 u2_frame_num, UWORD8 u1_nal_ref_idc,
                            pocstruct_t *ps_cur_poc, pocstruct_t *ps_prev_poc,
                            dec_slice_params_t *ps_prev_slice,
                            UWORD8 u1_pic_order_cnt_type,
                            UWORD8 u1_nal_unit_type, UWORD32 u4_idr_pic_id,
                            UWORD8 u1_field_pic_flag,
                            UWORD8 u1_bottom_field_flag);

WORD32 ih264d_end_of_pic_processing(dec_struct_t *ps_dec);

WORD32 ih264d_init_pic(dec_struct_t *ps_dec, UWORD16 u2_frame_num,
                       WORD32 i4_poc, dec_pic_params_t *ps_pps);

WORD32 ih264d_end_of_pic_processing(dec_struct_t *ps_dec);
WORD32 ih264d_decode_pic_order_cnt(
    UWORD8 u1_is_idr_slice, UWORD32 u2_frame_num, pocstruct_t *ps_prev_poc,
    pocstruct_t *ps_cur_poc, dec_slice_params_t *ps_cur_slice,
    dec_pic_params_t *ps_pps, UWORD8 u1_nal_ref_idc,
    UWORD8 u1_bottom_field_flag, UWORD8 u1_field_pic_flag, WORD32 *pi4_poc);
void ih264d_release_display_bufs(dec_struct_t *ps_dec);
WORD32 ih264d_assign_display_seq(dec_struct_t *ps_dec);
void ih264d_assign_pic_num(dec_struct_t *ps_dec);

void ih264d_unpack_coeff4x4_dc_4x4blk(tu_sblk4x4_coeff_data_t *ps_tu_4x4,
                                      WORD16 *pi2_out_coeff_data,
                                      UWORD8 *pu1_inv_scan);

WORD32 ih264d_update_qp(dec_struct_t *ps_dec, const WORD8 i1_qp);
WORD32 ih264d_decode_gaps_in_frame_num(dec_struct_t *ps_dec,
                                       UWORD16 u2_frame_num);

WORD32 ih264d_get_next_display_field(dec_struct_t *ps_dec,
                                     ivd_out_bufdesc_t *ps_out_buffer,
                                     ivd_get_display_frame_op_t *pv_disp_op);

void ih264d_release_display_field(dec_struct_t *ps_dec,
                                  ivd_get_display_frame_op_t *pv_disp_op);
void ih264d_close_video_decoder(iv_obj_t *iv_obj_t);
WORD32 ih264d_get_dpb_size_new(UWORD32 u4_level_idc, UWORD32 width,
                               UWORD32 height);
WORD32 ih264d_get_next_nal_unit(UWORD8 *pu1_buf, UWORD32 u4_cur_pos,
                                UWORD32 u4_max_ofst,
                                UWORD32 *pu4_length_of_start_code);

#endif /* _IH264D_UTILS_H_ */
