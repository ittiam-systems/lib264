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
 **************************************************************************
 * \file ih264d_parse_islice.h
 *
 * \brief
 *    Contains routines that decode a I slice type
 *
 * Detailed_description
 *
 * \date
 *    07/07/2003
 *
 * \author  NS
 **************************************************************************
 */

#ifndef _IH264D_PARSE_ISLICE_H_
#define _IH264D_PARSE_ISLICE_H_

#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264d_tables.h"

WORD32 ih264d_parse_residual4x4_cavlc(dec_struct_t *ps_dec,
                                      dec_mb_info_t *ps_cur_mb_info,
                                      UWORD8 u1_offset);
WORD32 ih264d_parse_residual4x4_cabac(dec_struct_t *ps_dec,
                                      dec_mb_info_t *ps_cur_mb_info,
                                      UWORD8 u1_offset);
WORD32 ih264d_parse_imb_cavlc(dec_struct_t *ps_dec,
                              dec_mb_info_t *ps_cur_mb_info, UWORD8 u1_mb_num,
                              UWORD8 u1_mb_type);
WORD32 ih264d_parse_imb_cabac(dec_struct_t *ps_dec,
                              dec_mb_info_t *ps_cur_mb_info, UWORD8 u1_mb_type);

WORD32 ih264d_parse_islice_data_cavlc(dec_struct_t *ps_dec,
                                      dec_slice_params_t *ps_slice,
                                      UWORD16 u2_first_mb_in_slice);
WORD32 ih264d_parse_islice_data_cabac(dec_struct_t *ps_dec,
                                      dec_slice_params_t *ps_slice,
                                      UWORD16 u2_first_mb_in_slice);
WORD32 ih264d_parse_pmb_cavlc(dec_struct_t *ps_dec,
                              dec_mb_info_t *ps_cur_mb_info, UWORD8 u1_mb_num,
                              UWORD8 u1_num_mbsNby2);
WORD32 ih264d_parse_pmb_cabac(dec_struct_t *ps_dec,
                              dec_mb_info_t *ps_cur_mb_info, UWORD8 u1_mb_num,
                              UWORD8 u1_num_mbsNby2);

WORD32 ih264d_parse_bmb_non_direct_cavlc(dec_struct_t *ps_dec,
                                         dec_mb_info_t *ps_cur_mb_info,
                                         UWORD8 u1_mb_num,
                                         UWORD8 u1_mbNumModNBy2);

WORD32 ih264d_parse_bmb_non_direct_cabac(dec_struct_t *ps_dec,
                                         dec_mb_info_t *ps_cur_mb_info,
                                         UWORD8 u1_mb_num,
                                         UWORD8 u1_mbNumModNBy2);

WORD32 ih264d_parse_bmb_cavlc(dec_struct_t *ps_dec,
                              dec_mb_info_t *ps_cur_mb_info, UWORD8 u1_mb_num,
                              UWORD8 u1_num_mbsNby2);

WORD32 ih264d_parse_bmb_cabac(dec_struct_t *ps_dec,
                              dec_mb_info_t *ps_cur_mb_info, UWORD8 u1_mb_num,
                              UWORD8 u1_num_mbsNby2);

WORD32 ih264d_parse_inter_slice_data_cavlc(dec_struct_t *ps_dec,
                                           dec_slice_params_t *ps_slice,
                                           UWORD16 u2_first_mb_in_slice);

WORD32 ih264d_parse_inter_slice_data_cabac(dec_struct_t *ps_dec,
                                           dec_slice_params_t *ps_slice,
                                           UWORD16 u2_first_mb_in_slice);

WORD32 ParseBMb(dec_struct_t *ps_dec, dec_mb_info_t *ps_cur_mb_info,
                UWORD8 u1_mb_num, UWORD8 u1_num_mbsNby2);

WORD32 ih264d_parse_ipcm_mb(dec_struct_t *ps_dec, dec_mb_info_t *ps_cur_mb_info,
                            UWORD8 u1_mbNum);
WORD32 ih264d_parse_islice(dec_struct_t *ps_dec, UWORD16 u2_first_mb_in_slice);

#endif /* _IH264D_PARSE_ISLICE_H_ */
