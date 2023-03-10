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
 *  ih264_mem_fns.c
 *
 * @brief
 *  Functions used for memory operations
 *
 * @author
 *  Ittiam
 *
 * @par List of Functions:
 *  ih264_memcpy()
 *  ih264_memcpy_mul_8()
 *  ih264_memset()
 *  ih264_memset_mul_8()
 *  ih264_memset_16bit()
 *  ih264_memset_16bit_mul_8()
 *
 * @remarks
 *  None
 *
 ******************************************************************************
 */

/*****************************************************************************/
/* File Includes                                                             */
/*****************************************************************************/
/* System include files */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* User include files */
#include "ih264_typedefs.h"
#include "ih264_mem_fns.h"

/**
 *******************************************************************************
 *
 * @brief
 *   memcpy of a 8,16 or 32 bytes
 *
 * @par Description:
 *   Does memcpy of 8bit data from source to destination for 8,16 or 32 number
 *of bytes
 *
 * @param[in] pu1_dst
 *  UWORD8 pointer to the destination
 *
 * @param[in] pu1_src
 *  UWORD8 pointer to the source
 *
 * @param[in] num_bytes
 *  number of bytes to copy
 * @returns
 *
 * @remarks
 *  None
 *
 *******************************************************************************
 */

void ih264_memcpy(UWORD8 *pu1_dst, UWORD8 *pu1_src, UWORD32 num_bytes) {
  memcpy(pu1_dst, pu1_src, num_bytes);
}

void ih264_memcpy_mul_8(UWORD8 *pu1_dst, UWORD8 *pu1_src, UWORD32 num_bytes) {
  memcpy(pu1_dst, pu1_src, num_bytes);
}

/**
 *******************************************************************************
 *
 * @brief
 *   memset of a 8,16 or 32 bytes
 *
 * @par Description:
 *   Does memset of 8bit data for 8,16 or 32 number of bytes
 *
 * @param[in] pu1_dst
 *  UWORD8 pointer to the destination
 *
 * @param[in] value
 *  UWORD8 value used for memset
 *
 * @param[in] num_bytes
 *  number of bytes to set
 * @returns
 *
 * @remarks
 *  None
 *
 *******************************************************************************
 */

void ih264_memset(UWORD8 *pu1_dst, UWORD8 value, UWORD32 num_bytes) {
  memset(pu1_dst, value, num_bytes);
}

void ih264_memset_mul_8(UWORD8 *pu1_dst, UWORD8 value, UWORD32 num_bytes) {
  memset(pu1_dst, value, num_bytes);
}

/**
 *******************************************************************************
 *
 * @brief
 *   memset of 16bit data of a 8,16 or 32 bytes
 *
 * @par Description:
 *   Does memset of 16bit data for 8,16 or 32 number of bytes
 *
 * @param[in] pu2_dst
 *  UWORD8 pointer to the destination
 *
 * @param[in] value
 *  UWORD16 value used for memset
 *
 * @param[in] num_words
 *  number of words to set
 * @returns
 *
 * @remarks
 *  None
 *
 *******************************************************************************
 */

void ih264_memset_16bit(UWORD16 *pu2_dst, UWORD16 value, UWORD32 num_words) {
  UWORD32 i;
  for (i = 0; i < num_words; i++) {
    *pu2_dst++ = value;
  }
}

void ih264_memset_16bit_mul_8(UWORD16 *pu2_dst, UWORD16 value,
                              UWORD32 num_words) {
  UWORD32 i;
  for (i = 0; i < num_words; i++) {
    *pu2_dst++ = value;
  }
}
