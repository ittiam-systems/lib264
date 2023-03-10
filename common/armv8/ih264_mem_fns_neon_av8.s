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

// *******************************************************************************
// * @file
// *  ih264_mem_fns_neon.s
// *
// * @brief
// *  Contains function definitions for memory manipulation
// *
// * @author
// *     Naveen SR
// *
// * @par List of Functions:
// *  - ih264_memcpy_av8()
// *  - ih264_memcpy_mul_8_av8()
// *  - ih264_memset_mul_8_av8()
// *  - ih264_memset_16bit_mul_8_av8()
// *  - ih264_memset_16bit_av8()
// *
// * @remarks
// *  None
// *
// *******************************************************************************
//*/

.text
.p2align 2
.include "ih264_neon_macros.s"
///**
//*******************************************************************************
//*
//* @brief
//*   memcpy of a 1d array
//*
//* @par Description:
//*   Does memcpy of 8bit data from source to destination for 8,16 or 32 number of bytes
//*
//* @param[in] pu1_dst
//*  UWORD8 pointer to the destination
//*
//* @param[in] pu1_src
//*  UWORD8 pointer to the source
//*
//* @param[in] num_bytes
//*  number of bytes to copy
//* @returns
//*
//* @remarks
//*  None
//*
//*******************************************************************************
//*/
//void ih264_memcpy_mul_8(UWORD8 *pu1_dst,
//                      UWORD8 *pu1_src,
//                      UWORD32 num_bytes)
//**************Variables Vs Registers*************************
//    x0 => *pu1_dst
//    x1 => *pu1_src
//    w2 => num_bytes





    .global ih264_memcpy_mul_8_av8

ih264_memcpy_mul_8_av8:

loop_neon_memcpy_mul_8:
    // Memcpy 8 bytes
    ld1       {v0.8b}, [x1], #8
    st1       {v0.8b}, [x0], #8

    subs      w2, w2, #8
    bne       loop_neon_memcpy_mul_8
    ret



//*******************************************************************************
//*/
//void ih264_memcpy(UWORD8 *pu1_dst,
//                  UWORD8 *pu1_src,
//                  UWORD32 num_bytes)
//**************Variables Vs Registers*************************
//    x0 => *pu1_dst
//    x1 => *pu1_src
//    w2 => num_bytes



    .global ih264_memcpy_av8

ih264_memcpy_av8:
    subs      w2, w2, #8
    blt       arm_memcpy
loop_neon_memcpy:
    // Memcpy 8 bytes
    ld1       {v0.8b}, [x1], #8
    st1       {v0.8b}, [x0], #8

    subs      w2, w2, #8
    bge       loop_neon_memcpy
    cmn       w2, #8
    beq       end_func1

arm_memcpy:
    add       w2, w2, #8

loop_arm_memcpy:
    ldrb      w3, [x1], #1
    strb      w3, [x0], #1
    subs      w2, w2, #1
    bne       loop_arm_memcpy
    ret
end_func1:
    ret


//void ih264_memset_mul_8(UWORD8 *pu1_dst,
//                       UWORD8 value,
//                       UWORD32 num_bytes)
//**************Variables Vs Registers*************************
//    x0 => *pu1_dst
//    x1 => value
//    x2 => num_bytes


    .global ih264_memset_mul_8_av8

ih264_memset_mul_8_av8:

// Assumptions: numbytes is either 8, 16 or 32
    dup       v0.8b, w1
loop_memset_mul_8:
    // Memset 8 bytes
    st1       {v0.8b}, [x0], #8

    subs      w2, w2, #8
    bne       loop_memset_mul_8

    ret


//void ih264_memset(UWORD8 *pu1_dst,
//                       UWORD8 value,
//                       UWORD32 num_bytes)
//**************Variables Vs Registers*************************
//    x0 => *pu1_dst
//    w1 => value
//    w2 => num_bytes



    .global ih264_memset_av8

ih264_memset_av8:
    subs      w2, w2, #8
    blt       arm_memset
    dup       v0.8b, w1
loop_neon_memset:
    // Memcpy 8 bytes
    st1       {v0.8b}, [x0], #8

    subs      w2, w2, #8
    bge       loop_neon_memset
    cmn       w2, #8
    beq       end_func2

arm_memset:
    add       w2, w2, #8

loop_arm_memset:
    strb      w1, [x0], #1
    subs      w2, w2, #1
    bne       loop_arm_memset
    ret
end_func2:
    ret





//void ih264_memset_16bit_mul_8(UWORD16 *pu2_dst,
//                                      UWORD16 value,
//                                      UWORD32 num_words)
//**************Variables Vs Registers*************************
//    x0 => *pu2_dst
//    w1 => value
//    w2 => num_words


    .global ih264_memset_16bit_mul_8_av8

ih264_memset_16bit_mul_8_av8:

// Assumptions: num_words is either 8, 16 or 32

    // Memset 8 words
    dup       v0.4h, w1
loop_memset_16bit_mul_8:
    st1       {v0.4h}, [x0], #8
    st1       {v0.4h}, [x0], #8

    subs      w2, w2, #8
    bne       loop_memset_16bit_mul_8

    ret



//void ih264_memset_16bit(UWORD16 *pu2_dst,
//                       UWORD16 value,
//                       UWORD32 num_words)
//**************Variables Vs Registers*************************
//    x0 => *pu2_dst
//    w1 => value
//    w2 => num_words



    .global ih264_memset_16bit_av8

ih264_memset_16bit_av8:
    subs      w2, w2, #8
    blt       arm_memset_16bit
    dup       v0.4h, w1
loop_neon_memset_16bit:
    // Memset 8 words
    st1       {v0.4h}, [x0], #8
    st1       {v0.4h}, [x0], #8

    subs      w2, w2, #8
    bge       loop_neon_memset_16bit
    cmn       w2, #8
    beq       end_func3

arm_memset_16bit:
    add       w2, w2, #8

loop_arm_memset_16bit:
    strh      w1, [x0], #2
    subs      w2, w2, #1
    bne       loop_arm_memset_16bit
    ret

end_func3:
    ret



