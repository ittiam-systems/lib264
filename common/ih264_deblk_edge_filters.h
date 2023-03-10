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
 *  ih264_deblk_edge_filters.h
 *
 * @brief
 *  This file contains declarations of functions used for deblocking
 *
 * @author
 *  Ittiam
 *
 * @remarks
 *  None
 *
 *******************************************************************************
 */

#ifndef IH264_DEBLK_H_
#define IH264_DEBLK_H_

/*****************************************************************************/
/* Extern Function Declarations                                              */
/*****************************************************************************/

typedef void ih264_deblk_edge_bslt4_ft(UWORD8 *pu1_src, WORD32 src_strd,
                                       WORD32 alpha, WORD32 beta, UWORD32 u4_bs,
                                       const UWORD8 *pu1_cliptab);

typedef void ih264_deblk_edge_bs4_ft(UWORD8 *pu1_src, WORD32 src_strd,
                                     WORD32 alpha, WORD32 beta);

typedef void ih264_deblk_chroma_edge_bslt4_ft(UWORD8 *pu1_src, WORD32 src_strd,
                                              WORD32 alpha_cb, WORD32 beta_cb,
                                              WORD32 alpha_cr, WORD32 beta_cr,
                                              UWORD32 u4_bs,
                                              const UWORD8 *pu1_cliptab_cb,
                                              const UWORD8 *pu1_cliptab_cr);

typedef void ih264_deblk_chroma_edge_bs4_ft(UWORD8 *pu1_src, WORD32 src_strd,
                                            WORD32 alpha_cb, WORD32 beta_cb,
                                            WORD32 alpha_cr, WORD32 beta_cr);

ih264_deblk_edge_bs4_ft ih264_deblk_luma_horz_bs4;
ih264_deblk_edge_bs4_ft ih264_deblk_luma_vert_bs4;
ih264_deblk_edge_bs4_ft ih264_deblk_luma_vert_bs4_mbaff;

ih264_deblk_edge_bs4_ft ih264_deblk_chroma_horz_bs4_bp;
ih264_deblk_edge_bs4_ft ih264_deblk_chroma_vert_bs4_bp;
ih264_deblk_edge_bs4_ft ih264_deblk_chroma_vert_bs4_mbaff_bp;

ih264_deblk_edge_bslt4_ft ih264_deblk_luma_horz_bslt4;
ih264_deblk_edge_bslt4_ft ih264_deblk_luma_vert_bslt4;
ih264_deblk_edge_bslt4_ft ih264_deblk_luma_vert_bslt4_mbaff;

ih264_deblk_edge_bslt4_ft ih264_deblk_chroma_horz_bslt4_bp;
ih264_deblk_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_bp;
ih264_deblk_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_mbaff_bp;

ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_vert_bs4;
ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_horz_bs4;
ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_vert_bs4_mbaff;
ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_horz_bs4_mbaff;

ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4;
ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_horz_bslt4;
ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_mbaff;
ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_horz_bslt4_mbaff;

/*A9*/
ih264_deblk_edge_bs4_ft ih264_deblk_luma_horz_bs4_a9;
ih264_deblk_edge_bs4_ft ih264_deblk_luma_vert_bs4_a9;
ih264_deblk_edge_bs4_ft ih264_deblk_luma_vert_bs4_mbaff_a9;

ih264_deblk_edge_bs4_ft ih264_deblk_chroma_horz_bs4_bp_a9;
ih264_deblk_edge_bs4_ft ih264_deblk_chroma_vert_bs4_bp_a9;
ih264_deblk_edge_bs4_ft ih264_deblk_chroma_vert_bs4_mbaff_bp_a9;

ih264_deblk_edge_bslt4_ft ih264_deblk_luma_horz_bslt4_a9;
ih264_deblk_edge_bslt4_ft ih264_deblk_luma_vert_bslt4_a9;
ih264_deblk_edge_bslt4_ft ih264_deblk_luma_vert_bslt4_mbaff_a9;

ih264_deblk_edge_bslt4_ft ih264_deblk_chroma_horz_bslt4_bp_a9;
ih264_deblk_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_bp_a9;
ih264_deblk_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_mbaff_bp_a9;

ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_vert_bs4_a9;
ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_horz_bs4_a9;
ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_vert_bs4_mbaff_a9;
ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_horz_bs4_mbaff_a9;

ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_a9;
ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_horz_bslt4_a9;
ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_mbaff_a9;
ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_horz_bslt4_mbaff_a9;

/*AV8*/
ih264_deblk_edge_bs4_ft ih264_deblk_luma_horz_bs4_av8;
ih264_deblk_edge_bs4_ft ih264_deblk_luma_vert_bs4_av8;
ih264_deblk_edge_bs4_ft ih264_deblk_luma_vert_bs4_mbaff_av8;

ih264_deblk_edge_bs4_ft ih264_deblk_chroma_horz_bs4_bp_av8;
ih264_deblk_edge_bs4_ft ih264_deblk_chroma_vert_bs4_bp_av8;
ih264_deblk_edge_bs4_ft ih264_deblk_chroma_vert_bs4_mbaff_bp_av8;

ih264_deblk_edge_bslt4_ft ih264_deblk_luma_horz_bslt4_av8;
ih264_deblk_edge_bslt4_ft ih264_deblk_luma_vert_bslt4_av8;
ih264_deblk_edge_bslt4_ft ih264_deblk_luma_vert_bslt4_mbaff_av8;

ih264_deblk_edge_bslt4_ft ih264_deblk_chroma_horz_bslt4_bp_av8;
ih264_deblk_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_bp_av8;
ih264_deblk_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_mbaff_bp_av8;

ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_vert_bs4_av8;
ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_horz_bs4_av8;
ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_vert_bs4_mbaff_av8;
ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_horz_bs4_mbaff_av8;

ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_av8;
ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_horz_bslt4_av8;
ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_mbaff_av8;
ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_horz_bslt4_mbaff_av8;

/*SSE3*/
ih264_deblk_edge_bs4_ft ih264_deblk_luma_horz_bs4_ssse3;
ih264_deblk_edge_bs4_ft ih264_deblk_luma_vert_bs4_ssse3;
ih264_deblk_edge_bs4_ft ih264_deblk_luma_vert_bs4_mbaff_ssse3;

ih264_deblk_edge_bs4_ft ih264_deblk_chroma_horz_bs4_bp_ssse3;
ih264_deblk_edge_bs4_ft ih264_deblk_chroma_vert_bs4_bp_ssse3;
ih264_deblk_edge_bs4_ft ih264_deblk_chroma_vert_bs4_mbaff_bp_ssse3;

ih264_deblk_edge_bslt4_ft ih264_deblk_luma_horz_bslt4_ssse3;
ih264_deblk_edge_bslt4_ft ih264_deblk_luma_vert_bslt4_ssse3;
ih264_deblk_edge_bslt4_ft ih264_deblk_luma_vert_bslt4_mbaff_ssse3;

ih264_deblk_edge_bslt4_ft ih264_deblk_chroma_horz_bslt4_bp_ssse3;
ih264_deblk_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_bp_ssse3;
ih264_deblk_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_mbaff_bp_ssse3;

ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_vert_bs4_ssse3;
ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_horz_bs4_ssse3;
ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_vert_bs4_mbaff_ssse3;
ih264_deblk_chroma_edge_bs4_ft ih264_deblk_chroma_horz_bs4_mbaff_ssse3;

ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_ssse3;
ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_horz_bslt4_ssse3;
ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_vert_bslt4_mbaff_ssse3;
ih264_deblk_chroma_edge_bslt4_ft ih264_deblk_chroma_horz_bslt4_mbaff_ssse3;

#endif /* IH264_DEBLK_H_ */
