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
*  ih264_padding_atom_intr.c
*
* @brief
*  Contains function definitions for Padding
*
* @author
*  Srinivas T
*
* @par List of Functions:
*   - ih264_pad_left_luma_ssse3()
*   - ih264_pad_left_chroma_ssse3()
*   - ih264_pad_right_luma_ssse3()
*   - ih264_pad_right_chroma_ssse3()
*
* @remarks
*  None
*
*******************************************************************************
*/

#include <string.h>
#include <assert.h>
#include "ih264_typedefs.h"
#include "ih264_platform_macros.h"
#include "ih264_mem_fns.h"
#include "ih264_debug.h"

#include <immintrin.h>

/**
*******************************************************************************
*
* @brief
*   Padding (luma block) at the left of a 2d array
*
* @par Description:
*   The left column of a 2d array is replicated for pad_size times at the left
*
*
* @param[in] pu1_src
*  UWORD8 pointer to the source
*
* @param[in] src_strd
*  integer source stride
*
* @param[in] ht
*  integer height of the array
*
* @param[in] wd
*  integer width of the array
*
* @param[in] pad_size
*  integer -padding size of the array
*
* @param[in] ht
*  integer height of the array
*
* @param[in] wd
*  integer width of the array
*
* @returns
*
* @remarks
*  None
*
*******************************************************************************
*/

void ih264_pad_left_luma_ssse3(UWORD8 *pu1_src, WORD32 src_strd, WORD32 ht,
                               WORD32 pad_size) {
  WORD32 row;
  WORD32 i;
  UWORD8 *pu1_dst;
  __m128i const0_16x8b;

  const0_16x8b = _mm_setzero_si128();

  ASSERT(pad_size % 8 == 0);

  for (row = 0; row < ht; row++) {
    __m128i src_temp0_16x8b;

    src_temp0_16x8b = _mm_loadu_si128((__m128i *) pu1_src);
    pu1_dst = pu1_src - pad_size;
    src_temp0_16x8b = _mm_shuffle_epi8(src_temp0_16x8b, const0_16x8b);
    for (i = 0; i < pad_size; i += 8) {
      _mm_storel_epi64((__m128i *) (pu1_dst + i), src_temp0_16x8b);
    }
    pu1_src += src_strd;
  }
}

/**
*******************************************************************************
*
* @brief
*   Padding (chroma block) at the left of a 2d array
*
* @par Description:
*   The left column of a 2d array is replicated for pad_size times at the left
*
*
* @param[in] pu1_src
*  UWORD8 pointer to the source
*
* @param[in] src_strd
*  integer source stride
*
* @param[in] ht
*  integer height of the array
*
* @param[in] wd
*  integer width of the array (each colour component)
*
* @param[in] pad_size
*  integer -padding size of the array
*
* @param[in] ht
*  integer height of the array
*
* @param[in] wd
*  integer width of the array
*
* @returns
*
* @remarks
*  None
*
*******************************************************************************
*/

void ih264_pad_left_chroma_ssse3(UWORD8 *pu1_src, WORD32 src_strd, WORD32 ht,
                                 WORD32 pad_size) {
  WORD32 row;
  WORD32 col;
  UWORD8 *pu1_dst;
  __m128i const0_16x8b, const1_16x8b;
  const0_16x8b = _mm_setzero_si128();
  const1_16x8b = _mm_set1_epi8(1);
  const0_16x8b = _mm_unpacklo_epi8(const0_16x8b, const1_16x8b);

  ASSERT(pad_size % 8 == 0);
  for (row = 0; row < ht; row++) {
    __m128i src_temp0_16x8b;

    src_temp0_16x8b = _mm_loadu_si128((__m128i *) pu1_src);
    pu1_dst = pu1_src - pad_size;
    src_temp0_16x8b = _mm_shuffle_epi8(src_temp0_16x8b, const0_16x8b);

    for (col = 0; col < pad_size; col += 8) {
      _mm_storel_epi64((__m128i *) (pu1_dst + col), src_temp0_16x8b);
    }
    pu1_src += src_strd;
  }
}

/**
*******************************************************************************
*
* @brief
* Padding (luma block) at the right of a 2d array
*
* @par Description:
* The right column of a 2d array is replicated for pad_size times at the right
*
*
* @param[in] pu1_src
*  UWORD8 pointer to the source
*
* @param[in] src_strd
*  integer source stride
*
* @param[in] ht
*  integer height of the array
*
* @param[in] wd
*  integer width of the array
*
* @param[in] pad_size
*  integer -padding size of the array
*
* @param[in] ht
*  integer height of the array
*
* @param[in] wd
*  integer width of the array
*
* @returns
*
* @remarks
*  None
*
*******************************************************************************
*/

void ih264_pad_right_luma_ssse3(UWORD8 *pu1_src, WORD32 src_strd, WORD32 ht,
                                WORD32 pad_size) {
  WORD32 row;
  WORD32 col;
  UWORD8 *pu1_dst;
  __m128i const0_16x8b;

  ASSERT(pad_size % 8 == 0);

  for (row = 0; row < ht; row++) {
    __m128i src_temp0_16x8b;

    src_temp0_16x8b = _mm_loadu_si128((__m128i *) (pu1_src - 1));
    const0_16x8b = _mm_setzero_si128();
    pu1_dst = pu1_src;
    src_temp0_16x8b = _mm_shuffle_epi8(src_temp0_16x8b, const0_16x8b);
    for (col = 0; col < pad_size; col += 8) {
      _mm_storel_epi64((__m128i *) (pu1_dst + col), src_temp0_16x8b);
    }
    pu1_src += src_strd;
  }
}

/**
*******************************************************************************
*
* @brief
* Padding (chroma block) at the right of a 2d array
*
* @par Description:
* The right column of a 2d array is replicated for pad_size times at the right
*
*
* @param[in] pu1_src
*  UWORD8 pointer to the source
*
* @param[in] src_strd
*  integer source stride
*
* @param[in] ht
*  integer height of the array
*
* @param[in] wd
*  integer width of the array (each colour component)
*
* @param[in] pad_size
*  integer -padding size of the array
*
* @param[in] ht
*  integer height of the array
*
* @param[in] wd
*  integer width of the array
*
* @returns
*
* @remarks
*  None
*
*******************************************************************************
*/

void ih264_pad_right_chroma_ssse3(UWORD8 *pu1_src, WORD32 src_strd, WORD32 ht,
                                  WORD32 pad_size) {
  WORD32 row;
  WORD32 col;
  UWORD8 *pu1_dst;
  __m128i const0_16x8b, const1_16x8b;
  const0_16x8b = _mm_setzero_si128();
  const1_16x8b = _mm_set1_epi8(1);
  const0_16x8b = _mm_unpacklo_epi8(const0_16x8b, const1_16x8b);

  ASSERT(pad_size % 8 == 0);

  for (row = 0; row < ht; row++) {
    __m128i src_temp0_16x8b;

    src_temp0_16x8b = _mm_loadu_si128((__m128i *) (pu1_src - 2));
    pu1_dst = pu1_src;
    src_temp0_16x8b = _mm_shuffle_epi8(src_temp0_16x8b, const0_16x8b);
    for (col = 0; col < pad_size; col += 8) {
      _mm_storel_epi64((__m128i *) (pu1_dst + col), src_temp0_16x8b);
    }

    pu1_src += src_strd;
  }
}
