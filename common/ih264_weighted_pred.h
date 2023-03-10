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
*  ih264_weighted_pred.h
*
* @brief
*  Declarations of functions used for weighted prediction
*
* @author
*  Ittiam
*
* @par List of Functions:
*  -ih264_default_weighted_pred_luma
*  -ih264_default_weighted_pred_chroma
*  -ih264_weighted_pred_luma
*  -ih264_weighted_pred_chroma
*  -ih264_weighted_bi_pred_luma
*  -ih264_weighted_bi_pred_chroma
*  -ih264_default_weighted_pred_luma_a9q
*  -ih264_default_weighted_pred_chroma_a9q
*  -ih264_weighted_pred_luma_a9q
*  -ih264_weighted_pred_luma_a9q
*  -ih264_weighted_bi_pred_luma_a9q
*  -ih264_weighted_bi_pred_chroma_a9q
*  -ih264_default_weighted_pred_luma_av8
*  -ih264_default_weighted_pred_chroma_av8
*  -ih264_weighted_pred_luma_av8
*  -ih264_weighted_pred_chroma_av8
*  -ih264_weighted_bi_pred_luma_av8
*  -ih264_weighted_bi_pred_chroma_av8
*  -ih264_default_weighted_pred_luma_sse42
*  -ih264_default_weighted_pred_chroma_sse42
*  -ih264_weighted_pred_luma_sse42
*  -ih264_weighted_pred_chroma_sse42
*  -ih264_weighted_bi_pred_luma_sse42
*  -ih264_weighted_bi_pred_chroma_sse42
*
*
* @remarks
*  None
*
*******************************************************************************
*/

#ifndef IH264_WEIGHTED_PRED_H_
#define IH264_WEIGHTED_PRED_H_

/*****************************************************************************/
/* Extern Function Declarations                                              */
/*****************************************************************************/
typedef void ih264_default_weighted_pred_ft(UWORD8 *puc_src1, UWORD8 *puc_src2,
                                            UWORD8 *puc_dst, WORD32 src_strd1,
                                            WORD32 src_strd2, WORD32 dst_strd,
                                            WORD32 ht, WORD32 wd);

typedef void ih264_weighted_pred_ft(UWORD8 *puc_src, UWORD8 *puc_dst,
                                    WORD32 src_strd, WORD32 dst_strd,
                                    WORD32 log_wd, WORD32 wt, WORD32 ofst,
                                    WORD32 ht, WORD32 wd);

typedef void ih264_weighted_bi_pred_ft(UWORD8 *puc_src1, UWORD8 *puc_src2,
                                       UWORD8 *puc_dst, WORD32 src_strd1,
                                       WORD32 src_strd2, WORD32 dst_strd,
                                       WORD32 log_wd, WORD32 wt1, WORD32 wt2,
                                       WORD32 ofst1, WORD32 ofst2, WORD32 ht,
                                       WORD32 wd);

/* No NEON Declarations */

ih264_default_weighted_pred_ft ih264_default_weighted_pred_luma;

ih264_default_weighted_pred_ft ih264_default_weighted_pred_chroma;

ih264_weighted_pred_ft ih264_weighted_pred_luma;

ih264_weighted_pred_ft ih264_weighted_pred_chroma;

ih264_weighted_bi_pred_ft ih264_weighted_bi_pred_luma;

ih264_weighted_bi_pred_ft ih264_weighted_bi_pred_chroma;

/* A9 NEON Declarations */

ih264_default_weighted_pred_ft ih264_default_weighted_pred_luma_a9q;

ih264_default_weighted_pred_ft ih264_default_weighted_pred_chroma_a9q;

ih264_weighted_pred_ft ih264_weighted_pred_luma_a9q;

ih264_weighted_pred_ft ih264_weighted_pred_chroma_a9q;

ih264_weighted_bi_pred_ft ih264_weighted_bi_pred_luma_a9q;

ih264_weighted_bi_pred_ft ih264_weighted_bi_pred_chroma_a9q;

/* AV8 NEON Declarations */

ih264_default_weighted_pred_ft ih264_default_weighted_pred_luma_av8;

ih264_default_weighted_pred_ft ih264_default_weighted_pred_chroma_av8;

ih264_weighted_pred_ft ih264_weighted_pred_luma_av8;

ih264_weighted_pred_ft ih264_weighted_pred_chroma_av8;

ih264_weighted_bi_pred_ft ih264_weighted_bi_pred_luma_av8;

ih264_weighted_bi_pred_ft ih264_weighted_bi_pred_chroma_av8;

/* SSE42 Intrinsic Declarations */

ih264_default_weighted_pred_ft ih264_default_weighted_pred_luma_sse42;

ih264_default_weighted_pred_ft ih264_default_weighted_pred_chroma_sse42;

ih264_weighted_pred_ft ih264_weighted_pred_luma_sse42;

ih264_weighted_pred_ft ih264_weighted_pred_chroma_sse42;

ih264_weighted_bi_pred_ft ih264_weighted_bi_pred_luma_sse42;

ih264_weighted_bi_pred_ft ih264_weighted_bi_pred_chroma_sse42;

#endif /* IH264_WEIGHTED_PRED_H_ */

/** Nothing past this point */
