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

#ifndef _IH264D_BITSTRM_H_
#define _IH264D_BITSTRM_H_
/*!
 *************************************************************************
 * \file ih264d_bitstrm.h
 *
 * \brief
 *  Contains all the declarations of bitstream reading routines
 *
 * \date
 *    20/11/2002
 *
 * \author  AI
 *************************************************************************
 */

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"

#define INT_IN_BYTES 4
#define INT_IN_BITS 32

/* Based on level 1.2 of baseline profile */
/* 396[MAX_FS] * 128 * 1.5 [ChromaFormatParameter] / sizeof(UWORD32)
 i.e  396 * 128 * 1.5 / 4 = 19008 */
/* Based on level 3 of main profile */
/* 1620[MAX_FS] * 128 * 1.5 [ChromaFormatParameter] / sizeof(UWORD32)
 i.e  1620 * 128 * 1.5 / 4= 77760 */
#define SIZE_OF_BUFFER 77760

/* Structure for the ps_bitstrm */
typedef struct {
  UWORD32 u4_ofst;     /* Offset in the buffer for the current bit */
  UWORD32 *pu4_buffer; /* Bitstream Buffer  */
  UWORD32 u4_max_ofst; /* Position of the last bit read in the current buffer */
  void *pv_codec_handle; /* For Error Handling */
} dec_bit_stream_t;

/* To read the next bit */
UWORD8 ih264d_get_bit_h264(dec_bit_stream_t *);

/* To read the next specified number of bits */
UWORD32 ih264d_get_bits_h264(dec_bit_stream_t *, UWORD32);

/* To see the next specified number of bits */
UWORD32 ih264d_next_bits_h264(dec_bit_stream_t *, UWORD32);

/* To flush a specified number of bits*/
WORD32 ih264d_flush_bits_h264(dec_bit_stream_t *, WORD32);

/*!
 **************************************************************************
 * \if Function name : MoreRbspData \endif
 *
 * \brief
 *    Determines whether there is more data in RBSP or not.
 *
 * \param ps_bitstrm : Pointer to bitstream
 *
 * \return
 *    Returns 1 if there is more data in RBSP before rbsp_trailing_bits().
 *    Otherwise it returns FALSE.
 **************************************************************************
 */

#define MORE_RBSP_DATA(ps_bitstrm) \
  (ps_bitstrm->u4_ofst < ps_bitstrm->u4_max_ofst)
#define EXCEED_OFFSET(ps_bitstrm) \
  (ps_bitstrm->u4_ofst > ps_bitstrm->u4_max_ofst)

void GoToByteBoundary(dec_bit_stream_t *ps_bitstrm);
UWORD8 ih264d_check_byte_aligned(dec_bit_stream_t *ps_bitstrm);

/*****************************************************************************/
/* Define a macro for inlining of GETBIT:                                    */
/*****************************************************************************/
#define GETBIT(u4_code, u4_offset, pu4_bitstream) \
  {                                               \
    UWORD32 *pu4_buf = (pu4_bitstream);           \
    UWORD32 u4_word_off = ((u4_offset) >> 5);     \
    UWORD32 u4_bit_off = (u4_offset) &0x1F;       \
    u4_code = pu4_buf[u4_word_off] << u4_bit_off; \
    (u4_offset)++;                                \
    u4_code = (u4_code >> 31);                    \
  }

/*****************************************************************************/
/* Define a macro for inlining of GETBITS: u4_no_bits shall not exceed 32    */
/*****************************************************************************/
#define GETBITS(u4_code, u4_offset, pu4_bitstream, u4_no_bits)         \
  {                                                                    \
    UWORD32 *pu4_buf = (pu4_bitstream);                                \
    UWORD32 u4_word_off = ((u4_offset) >> 5);                          \
    UWORD32 u4_bit_off = (u4_offset) &0x1F;                            \
    u4_code = pu4_buf[u4_word_off++] << u4_bit_off;                    \
                                                                       \
    if (u4_bit_off)                                                    \
      u4_code |= (pu4_buf[u4_word_off] >> (INT_IN_BITS - u4_bit_off)); \
    u4_code = u4_code >> (INT_IN_BITS - u4_no_bits);                   \
    (u4_offset) += u4_no_bits;                                         \
  }

/*****************************************************************************/
/* Define a macro for inlining of NEXTBITS                                   */
/*****************************************************************************/
#define NEXTBITS(u4_word, u4_offset, pu4_bitstream, u4_no_bits)        \
  {                                                                    \
    UWORD32 *pu4_buf = (pu4_bitstream);                                \
    UWORD32 u4_word_off = ((u4_offset) >> 5);                          \
    UWORD32 u4_bit_off = (u4_offset) &0x1F;                            \
    u4_word = pu4_buf[u4_word_off++] << u4_bit_off;                    \
    if (u4_bit_off)                                                    \
      u4_word |= (pu4_buf[u4_word_off] >> (INT_IN_BITS - u4_bit_off)); \
    u4_word = u4_word >> (INT_IN_BITS - u4_no_bits);                   \
  }
/*****************************************************************************/
/* Define a macro for inlining of NEXTBITS_32                                */
/*****************************************************************************/
#define NEXTBITS_32(u4_word, u4_offset, pu4_bitstream)                 \
  {                                                                    \
    UWORD32 *pu4_buf = (pu4_bitstream);                                \
    UWORD32 u4_word_off = ((u4_offset) >> 5);                          \
    UWORD32 u4_bit_off = (u4_offset) &0x1F;                            \
                                                                       \
    u4_word = pu4_buf[u4_word_off++] << u4_bit_off;                    \
    if (u4_bit_off)                                                    \
      u4_word |= (pu4_buf[u4_word_off] >> (INT_IN_BITS - u4_bit_off)); \
  }

/*****************************************************************************/
/* Define a macro for inlining of FIND_ONE_IN_STREAM_32                      */
/*****************************************************************************/
#define FIND_ONE_IN_STREAM_32(u4_ldz, u4_offset, pu4_bitstream) \
  {                                                             \
    UWORD32 u4_word;                                            \
    NEXTBITS_32(u4_word, u4_offset, pu4_bitstream);             \
    u4_ldz = CLZ(u4_word);                                      \
    (u4_offset) += (u4_ldz + 1);                                \
  }

/*****************************************************************************/
/* Define a macro for inlining of FIND_ONE_IN_STREAM_LEN                     */
/*****************************************************************************/
#define FIND_ONE_IN_STREAM_LEN(u4_ldz, u4_offset, pu4_bitstream, u4_len) \
  {                                                                      \
    UWORD32 u4_word;                                                     \
    NEXTBITS_32(u4_word, u4_offset, pu4_bitstream);                      \
    u4_ldz = CLZ(u4_word);                                               \
    if (u4_ldz < u4_len)                                                 \
      (u4_offset) += (u4_ldz + 1);                                       \
    else {                                                               \
      u4_ldz = u4_len;                                                   \
      (u4_offset) += u4_ldz;                                             \
    }                                                                    \
  }

/*****************************************************************************/
/* Define a macro for inlining of FLUSHBITS                                  */
/*****************************************************************************/
#define FLUSHBITS(u4_offset, u4_no_bits) \
  { (u4_offset) += (u4_no_bits); }

#endif /* _BITSTREAM_H_ */
