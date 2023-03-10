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

//******************************************************************************
//* @file
//*  ih264_intra_pred_luma_16x16_av8.s
//*
//* @brief
//*  Contains function definitions for intra 16x16 Luma prediction .
//*
//* @author
//*  Ittiam
//*
//* @par List of Functions:
//*
//*  - ih264_intra_pred_luma_16x16_mode_vert_av8()
//*  - ih264_intra_pred_luma_16x16_mode_horz_av8()
//*  - ih264_intra_pred_luma_16x16_mode_dc_av8()
//*  - ih264_intra_pred_luma_16x16_mode_plane_av8()
//*
//* @remarks
//*  None
//*
//*******************************************************************************
//*/

///* All the functions here are replicated from ih264_intra_pred_filters.c
//

///**
///**
///**
//


.text
.p2align 2
.include "ih264_neon_macros.s"
.extern ih264_gai1_intrapred_luma_plane_coeffs



///**
//*******************************************************************************
//*
//*ih264_intra_pred_luma_16x16_mode_vert
//*
//* @brief
//*   Perform Intra prediction for  luma_16x16 mode:vertical
//*
//* @par Description:
//* Perform Intra prediction for  luma_16x16 mode:Vertical ,described in sec 8.3.3.1
//*
//* @param[in] pu1_src
//*  UWORD8 pointer to the source
//*
//* @param[out] pu1_dst
//*  UWORD8 pointer to the destination
//*
//* @param[in] src_strd
//*  integer source stride
//*
//* @param[in] dst_strd
//*  integer destination stride
//*
//* @param[in] ui_neighboravailability
//* availability of neighbouring pixels(Not used in this function)
//*
//* @returns
//*
//* @remarks
//*  None
//*
//*******************************************************************************
//void ih264_intra_pred_luma_16x16_mode_vert(UWORD8 *pu1_src,
//                                        UWORD8 *pu1_dst,
//                                        WORD32 src_strd,
//                                        WORD32 dst_strd,
//                                        WORD32 ui_neighboravailability)

//**************Variables Vs Registers*****************************************
//    x0 => *pu1_src
//    x1 => *pu1_dst
//    w2 =>  src_strd
//    w3 =>  dst_strd
//    w4 =>  ui_neighboravailability


    .global ih264_intra_pred_luma_16x16_mode_vert_av8

ih264_intra_pred_luma_16x16_mode_vert_av8:

    push_v_regs
    sxtw      x3, w3


    add       x0, x0, #17
    ld1       {v0.8b, v1.8b}, [x0]

    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3
    st1       {v0.8b, v1.8b}, [x1], x3

    pop_v_regs
    ret





///******************************************************************************


///**
//*******************************************************************************
//*
//*ih264_intra_pred_luma_16x16_mode_horz
//*
//* @brief
//*  Perform Intra prediction for  luma_16x16 mode:horizontal
//*
//* @par Description:
//*  Perform Intra prediction for  luma_16x16 mode:horizontal ,described in sec 8.3.3.2
//*
//* @param[in] pu1_src
//*  UWORD8 pointer to the source
//*
//* @param[out] pu1_dst
//*  UWORD8 pointer to the destination
//*
//* @param[in] src_strd
//*  integer source stride
//*
//* @param[in] dst_strd
//*  integer destination stride
//*
//* @param[in] ui_neighboravailability
//* availability of neighbouring pixels(Not used in this function)
//*
//* @returns
//*
//* @remarks
//*  None
//*
//*******************************************************************************
//*/
//void ih264_intra_pred_luma_16x16_mode_horz(UWORD8 *pu1_src,
//                                         UWORD8 *pu1_dst,
//                                         WORD32 src_strd,
//                                         WORD32 dst_strd,
//                                         WORD32 ui_neighboravailability)
//**************Variables Vs Registers*****************************************
//    x0 => *pu1_src
//    x1 => *pu1_dst
//    w2 =>  src_strd
//    w3 =>  dst_strd
//    w4 =>  ui_neighboravailability

    .global ih264_intra_pred_luma_16x16_mode_horz_av8

ih264_intra_pred_luma_16x16_mode_horz_av8:



    push_v_regs
    sxtw      x3, w3

    ld1       {v0.16b}, [x0]



    dup       v10.16b, v0.b[15]
    dup       v11.16b, v0.b[14]
    dup       v12.16b, v0.b[13]
    dup       v13.16b, v0.b[12]
    st1       {v10.16b}, [x1], x3
    dup       v14.16b, v0.b[11]
    st1       {v11.16b}, [x1], x3
    dup       v15.16b, v0.b[10]
    st1       {v12.16b}, [x1], x3
    dup       v16.16b, v0.b[9]
    st1       {v13.16b}, [x1], x3
    dup       v17.16b, v0.b[8]
    st1       {v14.16b}, [x1], x3
    dup       v18.16b, v0.b[7]
    st1       {v15.16b}, [x1], x3
    dup       v19.16b, v0.b[6]
    st1       {v16.16b}, [x1], x3
    dup       v20.16b, v0.b[5]
    st1       {v17.16b}, [x1], x3
    dup       v21.16b, v0.b[4]
    st1       {v18.16b}, [x1], x3
    dup       v22.16b, v0.b[3]
    st1       {v19.16b}, [x1], x3
    dup       v23.16b, v0.b[2]
    st1       {v20.16b}, [x1], x3
    dup       v24.16b, v0.b[1]
    st1       {v21.16b}, [x1], x3
    dup       v25.16b, v0.b[0]
    st1       {v22.16b}, [x1], x3
    st1       {v23.16b}, [x1], x3
    st1       {v24.16b}, [x1], x3
    st1       {v25.16b}, [x1], x3

    pop_v_regs
    ret







///******************************************************************************


///**
//*******************************************************************************
//*
//*ih264_intra_pred_luma_16x16_mode_dc
//*
//* @brief
//*  Perform Intra prediction for  luma_16x16 mode:DC
//*
//* @par Description:
//*  Perform Intra prediction for  luma_16x16 mode:DC ,described in sec 8.3.3.3
//*
//* @param[in] pu1_src
//*  UWORD8 pointer to the source
//*
//* @param[out] pu1_dst
//*  UWORD8 pointer to the destination
//*
//* @param[in] src_strd
//*  integer source stride
//*
//* @param[in] dst_strd
//*  integer destination stride
//*
//* @param[in] ui_neighboravailability
//*  availability of neighbouring pixels
//*
//* @returns
//*
//* @remarks
//*  None
//*
//*******************************************************************************/
//void ih264_intra_pred_luma_16x16_mode_dc(UWORD8 *pu1_src,
//                                       UWORD8 *pu1_dst,
//                                       WORD32 src_strd,
//                                       WORD32 dst_strd,
//                                       WORD32 ui_neighboravailability)

//**************Variables Vs Registers*****************************************
//    x0 => *pu1_src
//    x1 => *pu1_dst
//    w2 =>  src_strd
//    w3 =>  dst_strd
//    w4 =>  ui_neighboravailability

    .global ih264_intra_pred_luma_16x16_mode_dc_av8

ih264_intra_pred_luma_16x16_mode_dc_av8:



    push_v_regs
    stp       x19, x20, [sp, #-16]!
    sxtw      x3, w3

    sub       v0.16b, v0.16b, v0.16b
    sub       v1.16b, v1.16b, v1.16b
    mov       w10, #0
    mov       w11 , #3
    ands      w6, w4, #0x01
    beq       top_available             //LEFT NOT AVAILABLE
    ld1       {v0.16b}, [x0]
    add       w10, w10, #8
    add       w11, w11, #1
top_available:
    ands      w6, w4, #0x04
    beq       none_available
    add       x6, x0, #17
    ld1       {v1.16b}, [x6]
    add       w10, w10, #8
    add       w11, w11, #1
    b         summation
none_available:
    cmp       w4, #0
    bne       summation
    mov       w15, #128
    dup       v20.16b, w15
    b         store
summation:
    uaddl     v2.8h, v0.8b, v1.8b
    uaddl2    v3.8h, v0.16b, v1.16b
    dup       v10.8h, w10
    neg       w11, w11
    dup       v20.8h, w11
    add       v0.8h, v2.8h, v3.8h
    mov       v1.d[0], v0.d[1]
    add       v0.4h, v0.4h, v1.4h
    addp      v0.4h, v0.4h , v0.4h
    addp      v0.4h, v0.4h , v0.4h
    add       v0.4h, v0.4h, v10.4h
    uqshl     v0.8h, v0.8h, v20.8h
    sqxtun    v0.8b, v0.8h
    dup       v20.16b, v0.b[0]

store:

    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3



end_func:

    ldp       x19, x20, [sp], #16
    pop_v_regs
    ret





///******************************************************************************


///**
//*******************************************************************************
//*
//*ih264_intra_pred_luma_16x16_mode_plane
//*
//* @brief
//*  Perform Intra prediction for  luma_16x16 mode:PLANE
//*
//* @par Description:
//*  Perform Intra prediction for  luma_16x16 mode:PLANE ,described in sec 8.3.3.4
//*
//* @param[in] pu1_src
//*  UWORD8 pointer to the source
//*
//* @param[out] pu1_dst
//*  UWORD8 pointer to the destination
//*
//* @param[in] src_strd
//*  integer source stride
//*
//* @param[in] dst_strd
//*  integer destination stride
//*
//* @param[in] ui_neighboravailability
//*  availability of neighbouring pixels
//*
//* @returns
//*
//* @remarks
//*  None
//*
//*******************************************************************************/
//void ih264_intra_pred_luma_16x16_mode_plane(UWORD8 *pu1_src,
//                                        UWORD8 *pu1_dst,
//                                        WORD32 src_strd,
//                                        WORD32 dst_strd,
//                                        WORD32 ui_neighboravailability)

//**************Variables Vs Registers*****************************************
//    x0 => *pu1_src
//    x1 => *pu1_dst
//    w2 =>  src_strd
//    w3 =>  dst_strd
//    w4 =>  ui_neighboravailability

    .global ih264_intra_pred_luma_16x16_mode_plane_av8
ih264_intra_pred_luma_16x16_mode_plane_av8:

    push_v_regs
    stp       x19, x20, [sp, #-16]!
    sxtw      x3, w3
    mov       x2, x1
    add       x1, x0, #17
    add       x0, x0, #15
    mov       x8, #9
    sub       x1, x1, #1
    mov       x10, x1                   //top_left
    mov       x4, #-1
    ld1       {v2.2s}, [x1], x8

    adrp      x7, :got:ih264_gai1_intrapred_luma_plane_coeffs
    ldr       x7, [x7, #:got_lo12:ih264_gai1_intrapred_luma_plane_coeffs]

    ld1       {v0.2s}, [x1]
    rev64     v2.8b, v2.8b
    ld1       {v6.2s, v7.2s}, [x7]
    usubl     v0.8h, v0.8b, v2.8b
    uxtl      v16.8h, v6.8b
    mul       v0.8h, v0.8h , v16.8h
    uxtl      v18.8h, v7.8b
    add       x7, x0, x4, lsl #3
    sub       x0, x7, x4, lsl #1
    neg       x14, x4
    addp      v0.8h, v0.8h, v1.8h
    ldrb      w8, [x7], #-1
    ldrb      w9, [x0], #1
    saddlp    v0.2s, v0.4h
    sub       w12, w8, w9
    ldrb      w8, [x7], #-1
    saddlp    v0.1d, v0.2s
    ldrb      w9, [x0], #1
    sub       w8, w8, w9
    shl       v2.2s, v0.2s, #2
    add       w12, w12, w8, lsl #1
    add       v0.2s, v0.2s , v2.2s
    ldrb      w8, [x7], #-1
    ldrb      w9, [x0], #1
    srshr     v0.2s, v0.2s, #6          // i_b = D0[0]
    sub       w8, w8, w9
    ldrb      w5, [x7], #-1
    add       w8, w8, w8, lsl #1
    dup       v4.8h, v0.h[0]
    add       w12, w12, w8
    ldrb      w9, [x0], #1
    mul       v0.8h, v4.8h , v16.8h
    sub       w5, w5, w9
    mul       v2.8h, v4.8h , v18.8h
    add       w12, w12, w5, lsl #2
    ldrb      w8, [x7], #-1
    ldrb      w9, [x0], #1
    sub       w8, w8, w9
    ldrb      w5, [x7], #-1
    add       w8, w8, w8, lsl #2
    ldrb      w6, [x0], #1
    add       w12, w12, w8
    ldrb      w8, [x7], #-1
    ldrb      w9, [x0], #1
    sub       w5, w5, w6
    sub       w8, w8, w9
    add       w5, w5, w5, lsl #1
    sub       w20, w8, w8, lsl #3
    neg       w8, w20
    add       w12, w12, w5, lsl #1
    ldrb      w5, [x7], #-1
    ldrb      w6, [x10]                 //top_left
    add       w12, w12, w8
    sub       w9, w5, w6
    ldrb      w6, [x1, #7]
    add       w12, w12, w9, lsl #3      // i_c = w12
    add       w8, w5, w6
    add       w12, w12, w12, lsl #2
    lsl       w8, w8, #4                // i_a = w8
    add       w12, w12, #0x20
    lsr       w12, w12, #6
    shl       v28.8h, v4.8h, #3
    dup       v6.8h, w12
    dup       v30.8h, w8
    shl       v26.8h, v6.8h, #3
    sub       v30.8h, v30.8h , v28.8h
    sub       v30.8h, v30.8h , v26.8h
    add       v28.8h, v30.8h , v6.8h
    add       v26.8h, v28.8h , v0.8h
    add       v28.8h, v28.8h , v2.8h
    sqrshrun  v20.8b, v26.8h, #5
    sqrshrun  v21.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v22.8b, v26.8h, #5
    st1       {v20.2s, v21.2s}, [x2], x3
    sqrshrun  v23.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v20.8b, v26.8h, #5
    st1       {v22.2s, v23.2s}, [x2], x3
    sqrshrun  v21.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v22.8b, v26.8h, #5
    st1       {v20.2s, v21.2s}, [x2], x3
    sqrshrun  v23.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v20.8b, v26.8h, #5
    st1       {v22.2s, v23.2s}, [x2], x3
    sqrshrun  v21.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v22.8b, v26.8h, #5
    st1       {v20.2s, v21.2s}, [x2], x3
    sqrshrun  v23.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v20.8b, v26.8h, #5
    st1       {v22.2s, v23.2s}, [x2], x3
    sqrshrun  v21.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v22.8b, v26.8h, #5
    st1       {v20.2s, v21.2s}, [x2], x3
    sqrshrun  v23.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v20.8b, v26.8h, #5
    st1       {v22.2s, v23.2s}, [x2], x3
    sqrshrun  v21.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v22.8b, v26.8h, #5
    st1       {v20.2s, v21.2s}, [x2], x3
    sqrshrun  v23.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v20.8b, v26.8h, #5
    st1       {v22.2s, v23.2s}, [x2], x3
    sqrshrun  v21.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v22.8b, v26.8h, #5
    st1       {v20.2s, v21.2s}, [x2], x3
    sqrshrun  v23.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v20.8b, v26.8h, #5
    st1       {v22.2s, v23.2s}, [x2], x3
    sqrshrun  v21.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v22.8b, v26.8h, #5
    st1       {v20.2s, v21.2s}, [x2], x3
    sqrshrun  v23.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v20.8b, v26.8h, #5
    st1       {v22.2s, v23.2s}, [x2], x3
    sqrshrun  v21.8b, v28.8h, #5
    add       v26.8h, v26.8h , v6.8h
    add       v28.8h, v28.8h , v6.8h
    sqrshrun  v22.8b, v26.8h, #5
    st1       {v20.2s, v21.2s}, [x2], x3
    sqrshrun  v23.8b, v28.8h, #5
    st1       {v22.2s, v23.2s}, [x2], x3

end_func_plane:

    ldp       x19, x20, [sp], #16
    pop_v_regs
    ret

