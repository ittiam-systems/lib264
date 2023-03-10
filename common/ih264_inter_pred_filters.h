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
 *  ih264_inter_pred_filters.h
 *
 * @brief
 *  Declarations of functions used for inter prediction
 *
 * @author
 *  Ittiam
 *
 * @par List of Functions:
 *  -ih264_inter_pred_luma_copy
 *  -ih264_interleave_copy
 *  -ih264_inter_pred_luma_horz
 *  -ih264_inter_pred_luma_vert
 *  -ih264_inter_pred_luma_horz_hpel_vert_hpel
 *  -ih264_inter_pred_luma_vert_qpel
 *  -ih264_inter_pred_luma_horz_qpel
 *  -ih264_inter_pred_luma_horz_qpel_vert_qpel
 *  -ih264_inter_pred_luma_horz_qpel_vert_hpel
 *  -ih264_inter_pred_luma_horz_hpel_vert_qpel
 *  -ih264_inter_pred_luma_bilinear
 *  -ih264_inter_pred_chroma
 *  -ih264_inter_pred_luma_copy_a9q
 *  -ih264_interleave_copy_a9
 *  -ih264_inter_pred_luma_horz_a9q
 *  -ih264_inter_pred_luma_vert_a9q
 *  -ih264_inter_pred_luma_bilinear_a9q
 *  -ih264_inter_pred_luma_horz_hpel_vert_hpel_a9q
 *  -ih264_inter_pred_luma_horz_qpel_a9q
 *  -ih264_inter_pred_luma_vert_qpel_a9q
 *  -ih264_inter_pred_luma_horz_qpel_vert_qpel_a9q
 *  -ih264_inter_pred_luma_horz_qpel_vert_hpel_a9q
 *  -ih264_inter_pred_luma_horz_hpel_vert_qpel_a9q
 *  -ih264_inter_pred_chroma_a9q
 *  -ih264_inter_pred_luma_copy_av8
 *  -ih264_interleave_copy_av8
 *  -ih264_inter_pred_luma_horz_av8
 *  -ih264_inter_pred_luma_vert_av8
 *  -ih264_inter_pred_luma_bilinear_av8
 *  -ih264_inter_pred_luma_horz_hpel_vert_hpel_av8
 *  -ih264_inter_pred_luma_horz_qpel_av8
 *  -ih264_inter_pred_luma_vert_qpel_av8
 *  -ih264_inter_pred_luma_horz_qpel_vert_qpel_av8
 *  -ih264_inter_pred_luma_horz_qpel_vert_hpel_av8
 *  -ih264_inter_pred_luma_horz_hpel_vert_qpel_av8
 *  -ih264_inter_pred_chroma_av8
 *  -ih264_inter_pred_chroma_dx_zero_av8
 *  -ih264_inter_pred_chroma_dy_zero_av8
 *  -ih264_inter_pred_luma_copy_ssse3
 *  -ih264_inter_pred_luma_copy_ssse3
 *  -ih264_inter_pred_luma_horz_ssse3
 *  -ih264_inter_pred_luma_vert_ssse3
 *  -ih264_inter_pred_luma_bilinear_ssse3
 *  -ih264_inter_pred_luma_horz_hpel_vert_hpel_ssse3
 *  -ih264_inter_pred_luma_horz_qpel_ssse3
 *  -ih264_inter_pred_luma_vert_qpel_ssse3
 *  -ih264_inter_pred_luma_horz_qpel_vert_qpel_ssse3
 *  -ih264_inter_pred_luma_horz_qpel_vert_hpel_ssse3
 *  -ih264_inter_pred_luma_horz_hpel_vert_qpel_ssse3
 *  -ih264_inter_pred_chroma_ssse3
 *
 * @remarks
 *  None
 *
 *******************************************************************************
 */

#ifndef _IH264_INTER_PRED_H_
#define _IH264_INTER_PRED_H_

/*****************************************************************************/
/* Constant Data variables                                                   */
/*****************************************************************************/

extern const WORD32 ih264_g_six_tap[3]; /* coefficients for 6 tap filtering*/

/*****************************************************************************/
/* Extern Function Declarations                                              */
/*****************************************************************************/

typedef void ih264_inter_pred_luma_ft(UWORD8 *pu1_src, UWORD8 *pu1_dst,
                                      WORD32 src_strd, WORD32 dst_strd,
                                      WORD32 ht, WORD32 wd, UWORD8 *pu1_tmp,
                                      WORD32 dydx);

typedef void ih264_interleave_copy_ft(UWORD8 *pu1_src, UWORD8 *pu1_dst,
                                      WORD32 src_strd, WORD32 dst_strd,
                                      WORD32 ht, WORD32 wd);

typedef void ih264_inter_pred_luma_bilinear_ft(
    UWORD8 *pu1_src1, UWORD8 *pu1_src2, UWORD8 *pu1_dst, WORD32 src_strd1,
    WORD32 src_strd2, WORD32 dst_strd, WORD32 height, WORD32 width);

typedef void ih264_inter_pred_chroma_ft(UWORD8 *pu1_src, UWORD8 *pu1_dst,
                                        WORD32 src_strd, WORD32 dst_strd,
                                        WORD32 dx, WORD32 dy, WORD32 ht,
                                        WORD32 wd);

/* No NEON Declarations */

ih264_inter_pred_luma_ft ih264_inter_pred_luma_copy;

ih264_interleave_copy_ft ih264_interleave_copy;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_vert;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_hpel_vert_hpel;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_vert_qpel;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_qpel;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_qpel_vert_qpel;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_qpel_vert_hpel;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_hpel_vert_qpel;

ih264_inter_pred_luma_bilinear_ft ih264_inter_pred_luma_bilinear;

ih264_inter_pred_chroma_ft ih264_inter_pred_chroma;

/* A9 NEON Declarations */
ih264_inter_pred_luma_ft ih264_inter_pred_luma_copy_a9q;

ih264_interleave_copy_ft ih264_interleave_copy_a9;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_a9q;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_vert_a9q;

ih264_inter_pred_luma_bilinear_ft ih264_inter_pred_luma_bilinear_a9q;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_hpel_vert_hpel_a9q;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_qpel_a9q;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_vert_qpel_a9q;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_qpel_vert_qpel_a9q;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_qpel_vert_hpel_a9q;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_hpel_vert_qpel_a9q;

ih264_inter_pred_chroma_ft ih264_inter_pred_chroma_a9q;

/* AV8 NEON Declarations */
ih264_inter_pred_luma_ft ih264_inter_pred_luma_copy_av8;

ih264_interleave_copy_ft ih264_interleave_copy_av8;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_av8;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_vert_av8;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_hpel_vert_hpel_av8;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_qpel_av8;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_vert_qpel_av8;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_qpel_vert_qpel_av8;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_qpel_vert_hpel_av8;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_hpel_vert_qpel_av8;

ih264_inter_pred_chroma_ft ih264_inter_pred_chroma_av8;

ih264_inter_pred_chroma_ft ih264_inter_pred_chroma_dx_zero_av8;

ih264_inter_pred_chroma_ft ih264_inter_pred_chroma_dy_zero_av8;

/* SSSE3 Intrinsic Declarations */
ih264_inter_pred_luma_ft ih264_inter_pred_luma_copy_ssse3;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_ssse3;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_vert_ssse3;

ih264_inter_pred_luma_bilinear_ft ih264_inter_pred_luma_bilinear_ssse3;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_hpel_vert_hpel_ssse3;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_qpel_ssse3;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_vert_qpel_ssse3;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_qpel_vert_qpel_ssse3;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_qpel_vert_hpel_ssse3;

ih264_inter_pred_luma_ft ih264_inter_pred_luma_horz_hpel_vert_qpel_ssse3;

ih264_inter_pred_chroma_ft ih264_inter_pred_chroma_ssse3;

#endif

/** Nothing past this point */
