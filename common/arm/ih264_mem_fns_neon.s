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
@/**
@ *******************************************************************************
@ * @file
@ *  ih264_mem_fns_neon.s
@ *
@ * @brief
@ *  Contains function definitions for memory manipulation
@ *
@ * @author
@ *  Naveen SR
@ *
@ * @par List of Functions:
@ *  - ih264_memcpy_mul_8_a9q()
@ *  - ih264_memcpy_a9q()
@ *  - ih264_memset_mul_8_a9q()
@ *  - ih264_memset_a9q()
@ *  - ih264_memset_16bit_mul_8_a9q()
@ *  - ih264_memset_a9q()
@ *
@ * @remarks
@ *  None
@ *
@ *******************************************************************************
@*

@**
@*******************************************************************************
@*
@* @brief
@*   memcpy of a 1d array
@*
@* @par Description:
@*   Does memcpy of 8bit data from source to destination for 8,16 or 32 number of bytes
@*
@* @param[in] pu1_dst
@*  UWORD8 pointer to the destination
@*
@* @param[in] pu1_src
@*  UWORD8 pointer to the source
@*
@* @param[in] num_bytes
@*  number of bytes to copy
@* @returns
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@*
@void ih264_memcpy_mul_8(UWORD8 *pu1_dst,
@                    UWORD8 *pu1_src,
@                   UWORD32 num_bytes)
@**************Variables Vs Registers*************************
@   r0 => *pu1_dst
@   r1 => *pu1_src
@   r2 => num_bytes

.text
.p2align 2


    .global ih264_memcpy_mul_8_a9q

ih264_memcpy_mul_8_a9q:

loop_neon_memcpy_mul_8:
    @ Memcpy 8 bytes
    vld1.8        d0, [r1]!
    vst1.8        d0, [r0]!

    subs          r2, r2, #8
    bne           loop_neon_memcpy_mul_8
    bx            lr



@*******************************************************************************
@*
@void ih264_memcpy(UWORD8 *pu1_dst,
@                  UWORD8 *pu1_src,
@                  UWORD32 num_bytes)
@**************Variables Vs Registers*************************
@   r0 => *pu1_dst
@   r1 => *pu1_src
@   r2 => num_bytes



    .global ih264_memcpy_a9q

ih264_memcpy_a9q:
    subs          r2, #8
    blt           memcpy
loop_neon_memcpy:
    @ Memcpy 8 bytes
    vld1.8        d0, [r1]!
    vst1.8        d0, [r0]!

    subs          r2, #8
    bge           loop_neon_memcpy
    cmp           r2, #-8
    bxeq          lr

memcpy:
    add           r2, #8

loop_memcpy:
    ldrb          r3, [r1], #1
    strb          r3, [r0], #1
    subs          r2, #1
    bne           loop_memcpy
    bx            lr




@void ih264_memset_mul_8(UWORD8 *pu1_dst,
@                       UWORD8 value,
@                       UWORD32 num_bytes)
@**************Variables Vs Registers*************************
@   r0 => *pu1_dst
@   r1 => value
@   r2 => num_bytes





    .global ih264_memset_mul_8_a9q

ih264_memset_mul_8_a9q:

@ Assumptions: numbytes is either 8, 16 or 32
    vdup.8        d0, r1
loop_memset_mul_8:
    @ Memset 8 bytes
    vst1.8        d0, [r0]!

    subs          r2, r2, #8
    bne           loop_memset_mul_8

    bx            lr




@void ih264_memset(UWORD8 *pu1_dst,
@                       UWORD8 value,
@                       UWORD8 num_bytes)
@**************Variables Vs Registers*************************
@   r0 => *pu1_dst
@   r1 => value
@   r2 => num_bytes



    .global ih264_memset_a9q

ih264_memset_a9q:
    subs          r2, #8
    blt           memset
    vdup.8        d0, r1
loop_neon_memset:
    @ Memcpy 8 bytes
    vst1.8        d0, [r0]!

    subs          r2, #8
    bge           loop_neon_memset
    cmp           r2, #-8
    bxeq          lr

memset:
    add           r2, #8

loop_memset:
    strb          r1, [r0], #1
    subs          r2, #1
    bne           loop_memset
    bx            lr




@void ih264_memset_16bit_mul_8(UWORD16 *pu2_dst,
@                                   UWORD16 value,
@                                   UWORD32 num_words)
@**************Variables Vs Registers*************************
@   r0 => *pu2_dst
@   r1 => value
@   r2 => num_words





    .global ih264_memset_16bit_mul_8_a9q

ih264_memset_16bit_mul_8_a9q:

@ Assumptions: num_words is either 8, 16 or 32

    @ Memset 8 words
    vdup.16       d0, r1
loop_memset_16bit_mul_8:
    vst1.16       d0, [r0]!
    vst1.16       d0, [r0]!

    subs          r2, r2, #8
    bne           loop_memset_16bit_mul_8

    bx            lr




@void ih264_memset_16bit(UWORD16 *pu2_dst,
@                       UWORD16 value,
@                       UWORD32 num_words)
@**************Variables Vs Registers*************************
@   r0 => *pu2_dst
@   r1 => value
@   r2 => num_words



    .global ih264_memset_16bit_a9q

ih264_memset_16bit_a9q:
    subs          r2, #8
    blt           memset_16bit
    vdup.16       d0, r1
loop_neon_memset_16bit:
    @ Memset 8 words
    vst1.16       d0, [r0]!
    vst1.16       d0, [r0]!

    subs          r2, #8
    bge           loop_neon_memset_16bit
    cmp           r2, #-8
    bxeq          lr

memset_16bit:
    add           r2, #8

loop_memset_16bit:
    strh          r1, [r0], #2
    subs          r2, #1
    bne           loop_memset_16bit
    bx            lr




