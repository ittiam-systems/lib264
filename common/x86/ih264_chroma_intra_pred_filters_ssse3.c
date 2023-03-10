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
*  ih264_chroma_intra_pred_filters_ssse3.c
*
* @brief
*  Contains function definitions for chroma intra prediction filters in x86
*  intrinsics
*
* @author
*  Ittiam
*
* @par List of Functions:
*  -ih264_intra_pred_chroma_8x8_mode_horz_ssse3
*  -ih264_intra_pred_chroma_8x8_mode_vert_ssse3
*  -ih264_intra_pred_chroma_8x8_mode_plane_ssse3
*
* @remarks
*  None
*
*******************************************************************************
*/

/*****************************************************************************/
/* File Includes                                                             */
/*****************************************************************************/

/* System include files */
#include <stdio.h>
#include <stddef.h>
#include <string.h>

/* User include files */
#include "ih264_defs.h"
#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264_intra_pred_filters.h"

/*****************************************************************************/
/* Chroma Intra prediction 8x8 filters                                       */
/*****************************************************************************/
/**
*******************************************************************************
*
* ih264_intra_pred_chroma_8x8_mode_horz_ssse3
*
* @brief
*  Perform Intra prediction for chroma_8x8 mode:Horizontal
*
* @par Description:
*  Perform Intra prediction for chroma_8x8 mode:Horizontal ,described in
*sec 8.3.4.2
*
* @param[in] pu1_src
*  UWORD8 pointer to the source containing alternate U and V samples
*
* @param[out] pu1_dst
*  UWORD8 pointer to the destination with alternate U and V samples
*
* @param[in] src_strd
*  integer source stride
*
* @param[in] dst_strd
*  integer destination stride
*
* @param[in] ngbr_avail
* availability of neighbouring pixels(Not used in this function)
*
* @returns
*
* @remarks
*  None
*
******************************************************************************
*/
void ih264_intra_pred_chroma_8x8_mode_horz_ssse3(UWORD8 *pu1_src,
                                                 UWORD8 *pu1_dst,
                                                 WORD32 src_strd,
                                                 WORD32 dst_strd,
                                                 WORD32 ngbr_avail) {
  UWORD8 *pu1_left; /* Pointer to start of top predictors */
  WORD32 dst_strd2;

  __m128i left_16x8b, left_sh_16x8b;
  __m128i row1_16x8b, row2_16x8b;
  __m128i const_14_15_16x8b;

  UNUSED(src_strd);
  UNUSED(ngbr_avail);

  pu1_left = pu1_src + 2 * BLK8x8SIZE - 2;

  left_16x8b = _mm_loadu_si128((__m128i *) (pu1_left - 14));

  const_14_15_16x8b = _mm_set1_epi16(0x0f0e);

  dst_strd2 = dst_strd << 1;
  left_sh_16x8b = _mm_slli_si128(left_16x8b, 2);
  row1_16x8b = _mm_shuffle_epi8(left_16x8b, const_14_15_16x8b);
  row2_16x8b = _mm_shuffle_epi8(left_sh_16x8b, const_14_15_16x8b);
  _mm_storeu_si128((__m128i *) pu1_dst, row1_16x8b);
  _mm_storeu_si128((__m128i *) (pu1_dst + dst_strd), row2_16x8b);

  left_16x8b = _mm_slli_si128(left_16x8b, 4);
  left_sh_16x8b = _mm_slli_si128(left_sh_16x8b, 4);
  pu1_dst += dst_strd2;
  row1_16x8b = _mm_shuffle_epi8(left_16x8b, const_14_15_16x8b);
  row2_16x8b = _mm_shuffle_epi8(left_sh_16x8b, const_14_15_16x8b);
  _mm_storeu_si128((__m128i *) pu1_dst, row1_16x8b);
  _mm_storeu_si128((__m128i *) (pu1_dst + dst_strd), row2_16x8b);

  left_16x8b = _mm_slli_si128(left_16x8b, 4);
  left_sh_16x8b = _mm_slli_si128(left_sh_16x8b, 4);
  pu1_dst += dst_strd2;
  row1_16x8b = _mm_shuffle_epi8(left_16x8b, const_14_15_16x8b);
  row2_16x8b = _mm_shuffle_epi8(left_sh_16x8b, const_14_15_16x8b);
  _mm_storeu_si128((__m128i *) pu1_dst, row1_16x8b);
  _mm_storeu_si128((__m128i *) (pu1_dst + dst_strd), row2_16x8b);

  left_16x8b = _mm_slli_si128(left_16x8b, 4);
  left_sh_16x8b = _mm_slli_si128(left_sh_16x8b, 4);
  pu1_dst += dst_strd2;
  row1_16x8b = _mm_shuffle_epi8(left_16x8b, const_14_15_16x8b);
  row2_16x8b = _mm_shuffle_epi8(left_sh_16x8b, const_14_15_16x8b);
  _mm_storeu_si128((__m128i *) pu1_dst, row1_16x8b);
  _mm_storeu_si128((__m128i *) (pu1_dst + dst_strd), row2_16x8b);
}

/**
*******************************************************************************
*
* ih264_intra_pred_chroma_8x8_mode_vert_ssse3
*
* @brief
*  Perform Intra prediction for  chroma_8x8 mode:vertical
*
* @par Description:
*  Perform Intra prediction for  chroma_8x8 mode:vertical ,described in
*sec 8.3.4.3
*
* @param[in] pu1_src
*  UWORD8 pointer to the source containing alternate U and V samples
*
* @param[out] pu1_dst
*  UWORD8 pointer to the destination with alternate U and V samples
*
* @param[in] src_strd
*  integer source stride
*
* @param[in] dst_strd
*  integer destination stride
*
* @param[in] ngbr_avail
* availability of neighbouring pixels(Not used in this function)
*
* @returns
*
* @remarks
*  None
*
*******************************************************************************
*/
void ih264_intra_pred_chroma_8x8_mode_vert_ssse3(UWORD8 *pu1_src,
                                                 UWORD8 *pu1_dst,
                                                 WORD32 src_strd,
                                                 WORD32 dst_strd,
                                                 WORD32 ngbr_avail) {
  UWORD8 *pu1_top; /* Pointer to start of top predictors */
  WORD32 dst_strd2;

  __m128i top_16x8b;

  UNUSED(src_strd);
  UNUSED(ngbr_avail);

  pu1_top = pu1_src + 2 * BLK8x8SIZE + 2;

  top_16x8b = _mm_loadu_si128((__m128i *) pu1_top);

  dst_strd2 = dst_strd << 1;
  _mm_storeu_si128((__m128i *) pu1_dst, top_16x8b);
  _mm_storeu_si128((__m128i *) (pu1_dst + dst_strd), top_16x8b);

  pu1_dst += dst_strd2;
  _mm_storeu_si128((__m128i *) pu1_dst, top_16x8b);
  _mm_storeu_si128((__m128i *) (pu1_dst + dst_strd), top_16x8b);

  pu1_dst += dst_strd2;
  _mm_storeu_si128((__m128i *) pu1_dst, top_16x8b);
  _mm_storeu_si128((__m128i *) (pu1_dst + dst_strd), top_16x8b);

  pu1_dst += dst_strd2;
  _mm_storeu_si128((__m128i *) pu1_dst, top_16x8b);
  _mm_storeu_si128((__m128i *) (pu1_dst + dst_strd), top_16x8b);
}

/**
*******************************************************************************
*
* ih264_intra_pred_chroma_8x8_mode_plane_ssse3
*
* @brief
*  Perform Intra prediction for chroma_8x8 mode:PLANE
*
* @par Description:
*  Perform Intra prediction for chroma_8x8 mode:PLANE ,described in sec 8.3.4.4
*
* @param[in] pu1_src
*  UWORD8 pointer to the source containing alternate U and V samples
*
* @param[out] pu1_dst
*  UWORD8 pointer to the destination with alternate U and V samples
*
* @param[in] src_strd
*  integer source stride
*
* @param[in] dst_strd
*  integer destination stride
*
* @param[in] ngbr_avail
* availability of neighbouring pixels(Not used in this function)
*
* @returns
*
* @remarks
*  None
*
******************************************************************************
*/
void ih264_intra_pred_chroma_8x8_mode_plane_ssse3(UWORD8 *pu1_src,
                                                  UWORD8 *pu1_dst,
                                                  WORD32 src_strd,
                                                  WORD32 dst_strd,
                                                  WORD32 ngbr_avail) {
  UWORD8 *pu1_left, *pu1_top;
  WORD32 a_u, a_v, b_u, b_v, c_u, c_v;

  __m128i mul_8x16b, shuffle_8x16b;

  UNUSED(src_strd);
  UNUSED(ngbr_avail);

  pu1_top = pu1_src + MB_SIZE + 2;
  pu1_left = pu1_src + MB_SIZE - 2;

  mul_8x16b = _mm_setr_epi16(1, 2, 3, 4, 1, 2, 3, 4);
  shuffle_8x16b = _mm_setr_epi16(0xff00, 0xff02, 0xff04, 0xff06, 0xff01, 0xff03,
                                 0xff05, 0xff07);

  // calculating a, b and c
  {
    WORD32 h_u, h_v, v_u, v_v;
    WORD32 temp1, temp2;

    __m128i h_val1_16x8b, h_val2_16x8b;
    __m128i h_val1_8x16b, h_val2_8x16b, h_val_4x32b;
    __m128i v_val1_16x8b, v_val2_16x8b;
    __m128i v_val1_8x16b, v_val2_8x16b, v_val_4x32b;
    __m128i hv_val_4x32b;

    h_val1_16x8b = _mm_loadl_epi64((__m128i *) (pu1_top + 8));
    h_val2_16x8b = _mm_loadl_epi64((__m128i *) (pu1_top - 2));
    v_val1_16x8b = _mm_loadl_epi64((__m128i *) (pu1_left - 14));
    v_val2_16x8b = _mm_loadl_epi64((__m128i *) (pu1_left - 4));

    // reversing the order
    h_val2_16x8b = _mm_shufflelo_epi16(h_val2_16x8b, 0x1b);
    v_val1_16x8b = _mm_shufflelo_epi16(v_val1_16x8b, 0x1b);

    // separating u and v and 8-bit to 16-bit conversion
    h_val1_8x16b = _mm_shuffle_epi8(h_val1_16x8b, shuffle_8x16b);
    h_val2_8x16b = _mm_shuffle_epi8(h_val2_16x8b, shuffle_8x16b);
    v_val1_8x16b = _mm_shuffle_epi8(v_val1_16x8b, shuffle_8x16b);
    v_val2_8x16b = _mm_shuffle_epi8(v_val2_16x8b, shuffle_8x16b);

    h_val1_8x16b = _mm_sub_epi16(h_val1_8x16b, h_val2_8x16b);
    v_val1_8x16b = _mm_sub_epi16(v_val1_8x16b, v_val2_8x16b);

    h_val_4x32b = _mm_madd_epi16(mul_8x16b, h_val1_8x16b);
    v_val_4x32b = _mm_madd_epi16(mul_8x16b, v_val1_8x16b);

    temp1 = _mm_extract_epi16(h_val1_16x8b, 3);
    temp2 = _mm_extract_epi16(v_val1_16x8b, 3);

    hv_val_4x32b = _mm_hadd_epi32(h_val_4x32b, v_val_4x32b);

    a_u = ((temp1 & 0xff) + (temp2 & 0xff)) << 4;
    a_v = ((temp1 >> 8) + (temp2 >> 8)) << 4;

    h_u = _mm_extract_epi16(hv_val_4x32b, 0);
    h_v = _mm_extract_epi16(hv_val_4x32b, 2);
    v_u = _mm_extract_epi16(hv_val_4x32b, 4);
    v_v = _mm_extract_epi16(hv_val_4x32b, 6);

    h_u = (h_u << 16) >> 15;  // sign-extension and multiplication by 2
    h_v = (h_v << 16) >> 15;
    v_u = (v_u << 16) >> 15;
    v_v = (v_v << 16) >> 15;

    b_u = ((h_u << 4) + h_u + 32) >> 6;
    b_v = ((h_v << 4) + h_v + 32) >> 6;
    c_u = ((v_u << 4) + v_u + 32) >> 6;
    c_v = ((v_v << 4) + v_v + 32) >> 6;
  }
  // using a, b and c to compute the fitted plane values
  {
    __m128i const_8x16b, c2_8x16b;
    __m128i res1_l_8x16b, res1_h_8x16b;
    __m128i res2_l_8x16b, res2_h_8x16b;
    __m128i res1_sh_l_8x16b, res1_sh_h_8x16b, res1_16x8b;
    __m128i res2_sh_l_8x16b, res2_sh_h_8x16b, res2_16x8b;

    WORD32 b_u2, b_v2, b_u3, b_v3;
    WORD32 const_u, const_v;
    WORD32 dst_strd2;

    const_u = a_u - (c_u << 1) - c_u + 16;
    const_v = a_v - (c_v << 1) - c_v + 16;

    b_u2 = b_u << 1;
    b_v2 = b_v << 1;
    b_u3 = b_u + b_u2;
    b_v3 = b_v + b_v2;

    const_8x16b = _mm_setr_epi16(const_u, const_v, const_u, const_v, const_u,
                                 const_v, const_u, const_v);
    res1_l_8x16b = _mm_setr_epi16(-b_u3, -b_v3, -b_u2, -b_v2, -b_u, -b_v, 0, 0);
    // contains {-b*3, -b*2, -b*1, b*0}
    res1_h_8x16b =
        _mm_setr_epi16(b_u, b_v, b_u2, b_v2, b_u3, b_v3, b_u << 2, b_v << 2);
    // contains {b*1, b*2, b*3, b*4}
    c2_8x16b = _mm_setr_epi16(c_u, c_v, c_u, c_v, c_u, c_v, c_u, c_v);

    // rows 1, 2
    res1_l_8x16b = _mm_add_epi16(res1_l_8x16b, const_8x16b);
    res1_h_8x16b = _mm_add_epi16(res1_h_8x16b, const_8x16b);
    res2_l_8x16b = _mm_add_epi16(res1_l_8x16b, c2_8x16b);
    res2_h_8x16b = _mm_add_epi16(res1_h_8x16b, c2_8x16b);

    res1_sh_l_8x16b = _mm_srai_epi16(res1_l_8x16b, 5);
    res1_sh_h_8x16b = _mm_srai_epi16(res1_h_8x16b, 5);
    res2_sh_l_8x16b = _mm_srai_epi16(res2_l_8x16b, 5);
    res2_sh_h_8x16b = _mm_srai_epi16(res2_h_8x16b, 5);

    dst_strd2 = dst_strd << 1;
    c2_8x16b = _mm_slli_epi16(c2_8x16b, 1);

    res1_16x8b = _mm_packus_epi16(res1_sh_l_8x16b, res1_sh_h_8x16b);
    res2_16x8b = _mm_packus_epi16(res2_sh_l_8x16b, res2_sh_h_8x16b);

    _mm_storeu_si128((__m128i *) pu1_dst, res1_16x8b);
    _mm_storeu_si128((__m128i *) (pu1_dst + dst_strd), res2_16x8b);

    // rows 3, 4
    res1_l_8x16b = _mm_add_epi16(res1_l_8x16b, c2_8x16b);
    res1_h_8x16b = _mm_add_epi16(res1_h_8x16b, c2_8x16b);
    res2_l_8x16b = _mm_add_epi16(res2_l_8x16b, c2_8x16b);
    res2_h_8x16b = _mm_add_epi16(res2_h_8x16b, c2_8x16b);

    res1_sh_l_8x16b = _mm_srai_epi16(res1_l_8x16b, 5);
    res1_sh_h_8x16b = _mm_srai_epi16(res1_h_8x16b, 5);
    res2_sh_l_8x16b = _mm_srai_epi16(res2_l_8x16b, 5);
    res2_sh_h_8x16b = _mm_srai_epi16(res2_h_8x16b, 5);

    pu1_dst += dst_strd2;

    res1_16x8b = _mm_packus_epi16(res1_sh_l_8x16b, res1_sh_h_8x16b);
    res2_16x8b = _mm_packus_epi16(res2_sh_l_8x16b, res2_sh_h_8x16b);

    _mm_storeu_si128((__m128i *) pu1_dst, res1_16x8b);
    _mm_storeu_si128((__m128i *) (pu1_dst + dst_strd), res2_16x8b);

    // rows 5, 6
    res1_l_8x16b = _mm_add_epi16(res1_l_8x16b, c2_8x16b);
    res1_h_8x16b = _mm_add_epi16(res1_h_8x16b, c2_8x16b);
    res2_l_8x16b = _mm_add_epi16(res2_l_8x16b, c2_8x16b);
    res2_h_8x16b = _mm_add_epi16(res2_h_8x16b, c2_8x16b);

    res1_sh_l_8x16b = _mm_srai_epi16(res1_l_8x16b, 5);
    res1_sh_h_8x16b = _mm_srai_epi16(res1_h_8x16b, 5);
    res2_sh_l_8x16b = _mm_srai_epi16(res2_l_8x16b, 5);
    res2_sh_h_8x16b = _mm_srai_epi16(res2_h_8x16b, 5);

    pu1_dst += dst_strd2;

    res1_16x8b = _mm_packus_epi16(res1_sh_l_8x16b, res1_sh_h_8x16b);
    res2_16x8b = _mm_packus_epi16(res2_sh_l_8x16b, res2_sh_h_8x16b);

    _mm_storeu_si128((__m128i *) pu1_dst, res1_16x8b);
    _mm_storeu_si128((__m128i *) (pu1_dst + dst_strd), res2_16x8b);

    // rows 7, 8
    res1_l_8x16b = _mm_add_epi16(res1_l_8x16b, c2_8x16b);
    res1_h_8x16b = _mm_add_epi16(res1_h_8x16b, c2_8x16b);
    res2_l_8x16b = _mm_add_epi16(res2_l_8x16b, c2_8x16b);
    res2_h_8x16b = _mm_add_epi16(res2_h_8x16b, c2_8x16b);

    res1_sh_l_8x16b = _mm_srai_epi16(res1_l_8x16b, 5);
    res1_sh_h_8x16b = _mm_srai_epi16(res1_h_8x16b, 5);
    res2_sh_l_8x16b = _mm_srai_epi16(res2_l_8x16b, 5);
    res2_sh_h_8x16b = _mm_srai_epi16(res2_h_8x16b, 5);

    pu1_dst += dst_strd2;

    res1_16x8b = _mm_packus_epi16(res1_sh_l_8x16b, res1_sh_h_8x16b);
    res2_16x8b = _mm_packus_epi16(res2_sh_l_8x16b, res2_sh_h_8x16b);

    _mm_storeu_si128((__m128i *) pu1_dst, res1_16x8b);
    _mm_storeu_si128((__m128i *) (pu1_dst + dst_strd), res2_16x8b);
  }
}
