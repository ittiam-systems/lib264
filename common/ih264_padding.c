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
*  ih264_padding.c
*
* @brief
*  Contains function definitions for Padding
*
* @author
*  Ittiam
*
* @par List of Functions:
*   - ih264_pad_top()
*   - ih264_pad_bottom()
*   - ih264_pad_left_luma()
*   - ih264_pad_left_chroma()
*   - ih264_pad_right_luma()
*   - ih264_pad_right_chroma()
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
#include <stddef.h>
#include <string.h>

/* User include files */
#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_padding.h"

/*****************************************************************************/
/* Function Definitions                                                      */
/*****************************************************************************/

/**
*******************************************************************************
*
* @brief pad at the top of a 2d array
*
* @par Description:
*  The top row of a 2d array is replicated for pad_size times at the top
*
* @param[in] pu1_src
*  UWORD8 pointer to the source
*
* @param[in] src_strd
*  integer source stride
*
* @param[in] wd
*  integer width of the array
*
* @param[in] pad_size
*  integer -padding size of the array
*
* @returns none
*
* @remarks none
*
*******************************************************************************
*/
void ih264_pad_top(UWORD8 *pu1_src, WORD32 src_strd, WORD32 wd,
                   WORD32 pad_size) {
  WORD32 row;

  for (row = 1; row <= pad_size; row++) {
    memcpy(pu1_src - row * src_strd, pu1_src, wd);
  }
}

/**
*******************************************************************************
*
* @brief pad at the bottom of a 2d array
*
* @par Description:
*  The bottom row of a 2d array is replicated for pad_size times at the bottom
*
* @param[in] pu1_src
*  UWORD8 pointer to the source
*
* @param[in] src_strd
*  integer source stride
*
* @param[in] wd
*  integer width of the array
*
* @param[in] pad_size
*  integer -padding size of the array
*
* @returns none
*
* @remarks none
*
*******************************************************************************
*/
void ih264_pad_bottom(UWORD8 *pu1_src, WORD32 src_strd, WORD32 wd,
                      WORD32 pad_size) {
  WORD32 row;

  for (row = 1; row <= pad_size; row++) {
    memcpy(pu1_src + (row - 1) * src_strd, pu1_src - 1 * src_strd, wd);
  }
}

/**
*******************************************************************************
*
* @brief pad (luma block) at the left of a 2d array
*
* @par Description:
*   The left column of a 2d array is replicated for pad_size times to the left
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
* @param[in] pad_size
*  integer -padding size of the array
*
* @returns none
*
* @remarks none
*
*******************************************************************************
*/
void ih264_pad_left_luma(UWORD8 *pu1_src, WORD32 src_strd, WORD32 ht,
                         WORD32 pad_size) {
  WORD32 row;

  for (row = 0; row < ht; row++) {
    memset(pu1_src - pad_size, *pu1_src, pad_size);

    pu1_src += src_strd;
  }
}

/**
*******************************************************************************
*
* @brief pad (chroma block) at the left of a 2d array
*
* @par Description:
*   The left column of a 2d array is replicated for pad_size times to the left
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
* @param[in] pad_size
*  integer -padding size of the array
*
* @returns none
*
* @remarks none
*
*******************************************************************************
*/
void ih264_pad_left_chroma(UWORD8 *pu1_src, WORD32 src_strd, WORD32 ht,
                           WORD32 pad_size) {
  /* temp var */
  WORD32 row, col;
  UWORD16 u2_uv_val;

  /* pointer to src */
  UWORD16 *pu2_src = (UWORD16 *) pu1_src;

  src_strd >>= 1;
  pad_size >>= 1;

  for (row = 0; row < ht; row++) {
    u2_uv_val = pu2_src[0];

    for (col = -pad_size; col < 0; col++) {
      pu2_src[col] = u2_uv_val;
    }

    pu2_src += src_strd;
  }
}

/**
*******************************************************************************
*
* @brief pad (luma block) at the right of a 2d array
*
* @par Description:
*  The right column of a 2d array is replicated for pad_size times at the right
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
* @param[in] pad_size
*  integer -padding size of the array
*
* @returns none
*
* @remarks none
*
*******************************************************************************
*/
void ih264_pad_right_luma(UWORD8 *pu1_src, WORD32 src_strd, WORD32 ht,
                          WORD32 pad_size) {
  WORD32 row;

  for (row = 0; row < ht; row++) {
    memset(pu1_src, *(pu1_src - 1), pad_size);

    pu1_src += src_strd;
  }
}

/**
*******************************************************************************
*
* @brief pad (chroma block) at the right of a 2d array
*
* @par Description:
*  The right column of a 2d array is replicated for pad_size times at the right
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
* @param[in] pad_size
*  integer -padding size of the array
*
* @returns none
*
* @remarks none
*
*******************************************************************************
*/
void ih264_pad_right_chroma(UWORD8 *pu1_src, WORD32 src_strd, WORD32 ht,
                            WORD32 pad_size) {
  WORD32 row, col;
  UWORD16 u2_uv_val;
  UWORD16 *pu2_src = (UWORD16 *) pu1_src;

  src_strd >>= 1;
  pad_size >>= 1;

  for (row = 0; row < ht; row++) {
    u2_uv_val = pu2_src[-1];

    for (col = 0; col < pad_size; col++) {
      pu2_src[col] = u2_uv_val;
    }

    pu2_src += src_strd;
  }
}
