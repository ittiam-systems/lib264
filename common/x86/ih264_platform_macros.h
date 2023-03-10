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
*  ih264_platform_macros.h
*
* @brief
*  Platform specific Macro definitions used in the codec
*
* @author
*  Ittiam
*
* @remarks
*  None
*
*******************************************************************************
*/

#ifndef _IH264_PLATFORM_MACROS_H_
#define _IH264_PLATFORM_MACROS_H_

#include <immintrin.h>

#define CLIP_U8(x) CLIP3(0, 255, (x))
#define CLIP_S8(x) CLIP3(-128, 127, (x))

#define CLIP_U10(x) CLIP3(0, 1023, (x))
#define CLIP_S10(x) CLIP3(-512, 511, (x))

#define CLIP_U12(x) CLIP3(0, 4095, (x))
#define CLIP_S12(x) CLIP3(-2048, 2047, (x))

#define CLIP_U16(x) CLIP3(0, 65535, (x))
#define CLIP_S16(x) CLIP3(-32768, 32767, (x))

#define MEM_ALIGN16 __attribute__((aligned(16)))

#define SHL(x, y) (((y) < 32) ? ((x) << (y)) : 0)
#define SHR(x, y) (((y) < 32) ? ((x) >> (y)) : 0)

#define SHR_NEG(val, shift) ((shift > 0) ? (val >> shift) : (val << (-shift)))
#define SHL_NEG(val, shift) ((shift < 0) ? (val >> (-shift)) : (val << shift))

#define ITT_BIG_ENDIAN(x)                                           \
  ((x << 24)) | ((x & 0x0000ff00) << 8) | ((x & 0x00ff0000) >> 8) | \
      ((UWORD32) x >> 24);

#define NOP(nop_cnt)                          \
  {                                           \
    UWORD32 nop_i;                            \
    for (nop_i = 0; nop_i < nop_cnt; nop_i++) \
      ;                                       \
  }

#define PLD(a)

static __inline UWORD32 CLZ(UWORD32 u4_word) {
#if WINDOWS
    unsigned long index;
    if(_BitScanReverse(&index, u4_word))
        return 31 - index;
    else
        return 32;
#else
  if (u4_word)
    return (__builtin_clz(u4_word));
  else
    return 32;
#endif
}

static __inline UWORD32 CTZ(UWORD32 u4_word) {
  if (0 == u4_word)
    return 31;
  else {
    unsigned int index;
    index = __builtin_ctz(u4_word);
    return (UWORD32) index;
  }
}

#if WINDOWS
  #define DATA_SYNC() _ReadWriteBarrier()
#else
  #define DATA_SYNC() __sync_synchronize()
#endif

// #define INLINE __inline
#define INLINE

#define PREFETCH_ENABLE 1

#if PREFETCH_ENABLE
#define PREFETCH(ptr, type) _mm_prefetch(ptr, type);
#else
#define PREFETCH(ptr, type)
#endif

#define MEM_ALIGN8 __attribute__((aligned(8)))
#define MEM_ALIGN16 __attribute__((aligned(16)))
#define MEM_ALIGN32 __attribute__((aligned(32)))

#endif /* _IH264_PLATFORM_MACROS_H_ */
