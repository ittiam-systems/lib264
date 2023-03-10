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
 *  ih264_intra_pred_filters.h
 *
 * @brief
 *  Declarations of functions used for intra prediction
 *
 * @author
 *  Ittiam
 *
 * @remarks
 *  None
 *
 *******************************************************************************
 */

#ifndef IH264_INTRA_PRED_FILTERS_H_

#define IH264_INTRA_PRED_FILTERS_H_

/*****************************************************************************/
/*  Macro Expansion                                                          */
/*****************************************************************************/

/*! Filter (1,2,1) i.e (a + 2b + c) / 4 */
#define FILT121(a, b, c) ((a + (b << 1) + c + 2) >> 2)
/*! Filter (1,1) i.e (a + b) / 2 */
#define FILT11(a, b) ((a + b + 1) >> 1)
/*****************************************************************************/
/*  Global Variables                                                        */
/*****************************************************************************/

/* Global variables used only in assembly files*/
extern const WORD8 ih264_gai1_intrapred_luma_plane_coeffs[];
extern const WORD8 ih264_gai1_intrapred_chroma_plane_coeffs1[];
extern const WORD8 ih264_gai1_intrapred_chroma_plane_coeffs2[];
extern const WORD8 ih264_gai1_intrapred_luma_8x8_horz_u[];

/*****************************************************************************/
/* Extern Function Declarations                                              */
/*****************************************************************************/

typedef void ih264_intra_pred_ref_filtering_ft(UWORD8 *pu1_left,
                                               UWORD8 *pu1_topleft,
                                               UWORD8 *pu1_top, UWORD8 *pu1_dst,
                                               WORD32 left_strd,
                                               WORD32 ngbr_avail);

typedef void ih264_intra_pred_luma_ft(UWORD8 *pu1_src, UWORD8 *pu1_dst,
                                      WORD32 src_strd, WORD32 dst_strd,
                                      WORD32 ngbr_avail);

/* No Neon Definitions */

/* Luma 4x4 Intra pred filters */

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_vert;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_horz;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_dc;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_diag_dl;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_diag_dr;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_vert_r;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_horz_d;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_vert_l;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_horz_u;

/* Luma 8x8 Intra pred filters */

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_vert;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_horz;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_dc;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_diag_dl;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_diag_dr;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_vert_r;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_horz_d;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_vert_l;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_horz_u;

/* Luma 16x16 Intra pred filters */

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_vert;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_horz;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_dc;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_plane;

/* Chroma 8x8 Intra pred filters */

typedef ih264_intra_pred_luma_ft ih264_intra_pred_chroma_ft;

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_dc;

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_horz;

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_vert;

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_plane;

ih264_intra_pred_ref_filtering_ft ih264_intra_pred_luma_8x8_mode_ref_filtering;

/* A9 Definition */

/* Luma 4x4 Intra pred filters */

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_vert_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_horz_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_dc_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_diag_dl_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_diag_dr_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_vert_r_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_horz_d_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_vert_l_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_horz_u_a9q;

/* Luma 8x8 Intra pred filters */

ih264_intra_pred_ref_filtering_ft
    ih264_intra_pred_luma_8x8_mode_ref_filtering_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_vert_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_horz_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_dc_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_diag_dl_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_diag_dr_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_vert_r_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_horz_d_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_vert_l_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_horz_u_a9q;

/* Luma 16x16 Intra pred filters */

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_vert_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_horz_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_dc_a9q;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_plane_a9q;

/* Chroma 8x8 Intra pred filters */

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_dc_a9q;

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_horz_a9q;

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_vert_a9q;

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_plane_a9q;

/* X86 Intrinsic Definitions */

/* Luma 4x4 Intra pred filters */

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_vert_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_horz_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_dc_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_diag_dl_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_diag_dr_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_vert_r_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_horz_d_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_vert_l_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_horz_u_ssse3;

/* Luma 8x8 Intra pred filters */

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_vert_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_horz_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_dc_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_diag_dl_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_diag_dr_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_vert_r_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_horz_d_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_vert_l_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_horz_u_ssse3;

/* Luma 16x16 Intra pred filters */

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_vert_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_horz_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_dc_ssse3;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_plane_ssse3;

/* Chroma 8x8 Intra pred filters */

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_dc_ssse3;

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_horz_ssse3;

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_vert_ssse3;

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_plane_ssse3;

/* AV8 Definition */

/* Luma 4x4 Intra pred filters */
ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_vert_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_horz_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_dc_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_diag_dl_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_diag_dr_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_vert_r_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_horz_d_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_vert_l_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_4x4_mode_horz_u_av8;

/* Luma 8x8 Intra pred filters */

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_vert_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_horz_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_dc_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_diag_dl_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_diag_dr_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_vert_r_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_horz_d_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_vert_l_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_8x8_mode_horz_u_av8;

/* Luma 16x16 Intra pred filters */

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_vert_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_horz_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_dc_av8;

ih264_intra_pred_luma_ft ih264_intra_pred_luma_16x16_mode_plane_av8;

/* Chroma 8x8 Intra pred filters */

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_dc_av8;

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_horz_av8;

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_vert_av8;

ih264_intra_pred_chroma_ft ih264_intra_pred_chroma_8x8_mode_plane_av8;

#endif /* IH264_INTRA_PRED_FILTERS_H_ */
