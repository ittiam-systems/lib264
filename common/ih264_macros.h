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

/*********************************************************************************
 * @file
 *  ih264_macros.h
 *
 * @brief
 *  Macro definitions used in the codec
 *
 * @author
 *  Ittiam
 *
 * @remarks
 *  None
 *
 *******************************************************************************
 */
#ifndef _IH264_MACROS_H_
#define _IH264_MACROS_H_

/*****************************************************************************/
/* Function Macros                                                           */
/*****************************************************************************/
#define RETURN_IF(cond, retval) \
  if (cond) {                   \
    return (retval);            \
  }
#define UNUSED(x) ((void) (x))

#define ALIGN128(x) ((((x) + 127) >> 7) << 7)
#define ALIGN64(x) ((((x) + 63) >> 6) << 6)
#define ALIGN32(x) ((((x) + 31) >> 5) << 5)
#define ALIGN16(x) ((((x) + 15) >> 4) << 4)
#define ALIGN8(x) ((((x) + 7) >> 3) << 3)
#define ALIGN4(x) ((((x) + 3) >> 2) << 2)

/**
******************************************************************************
*  @brief      Min, Max
******************************************************************************
*/
#define MAX(a, b) ((a > b) ? (a) : (b))
#define MIN(a, b) ((a < b) ? (a) : (b))
#define MIN3(a, b, c) \
  ((a) < (b)) ? (((a) < (c)) ? (a) : (c)) : (((b) < (c)) ? (b) : (c))
#define MAX3(a, b, c) \
  ((a) > (b)) ? (((a) > (c)) ? (a) : (c)) : (((b) > (c)) ? (b) : (c))
/**
******************************************************************************
*  @brief      Div, Mod
******************************************************************************
*/
#define MOD(x, y) ((x) % (y))
#define DIV(x, y) ((x) / (y))

/**
******************************************************************************
*  @brief      Clip
******************************************************************************
*/
#define CLIP3(miny, maxy, y) \
  (((y) < (miny)) ? (miny) : (((y) > (maxy)) ? (maxy) : (y)))

/**
******************************************************************************
*  @brief      True, False
******************************************************************************
*/
#define BOOLEAN(x) (!!(x))

/**
******************************************************************************
*  @brief      Frequently used multiplications x2. x3, and x4
******************************************************************************
*/
#define X2(a) ((a) << 1)
#define X3(a) (((a) << 1) + (a))
#define X4(a) ((a) << 2)

/**
******************************************************************************
*  @brief      Misc
******************************************************************************
*/
#define ABS(x) ((x) < 0 ? (-(x)) : (x))
#define SIGNXY(x, y) (((y) < 0) ? (-1 * (x)) : (x))

#define SIGN(x) (((x) >= 0) ? (((x) > 0) ? 1 : 0) : -1)

#define RESET_BIT(x, pos) (x) = (x) & ~(1 << pos);
#define SET_BIT(x, pos) (x) = (x) | (1 << pos);
#define GET_BIT(x, pos) ((x) >> (pos)) & 0x1

#define INSERT_BIT(x, pos, bit) \
  {                             \
    RESET_BIT(x, pos);          \
    (x) = (x) | (bit << pos);   \
  }
#endif /*_IH264_MACROS_H_*/
