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
//*  ih264_intra_pred_chroma.s
//*
//* @brief
//*  Contains function definitions for intra chroma prediction .
//*
//* @author
//*  Ittiam
//*
//* @par List of Functions:
//*
//*  - ih264_intra_pred_luma_chroma_mode_vert_av8()
//*  - ih264_intra_pred_luma_chroma_mode_horz_av8()
//*  - ih264_intra_pred_luma_chroma_mode_dc_av8()
//*  - ih264_intra_pred_luma_chroma_mode_plane_av8()
//*
//* @remarks
//*  None
//*
//*******************************************************************************
//*/

///* All the functions here are replicated from ih264_chroma_intra_pred_filters.c
//

///**
///**
///**
//


.text
.p2align 2
.include "ih264_neon_macros.s"

.extern ih264_gai1_intrapred_chroma_plane_coeffs1
.extern ih264_gai1_intrapred_chroma_plane_coeffs2



///**
//*******************************************************************************
//*
//*ih264_intra_pred_chroma_8x8_mode_dc
//*
//* @brief
//*     Perform Intra prediction for  chroma_8x8 mode:DC
//*
//* @par Description:
//*    Perform Intra prediction for  chroma_8x8 mode:DC ,described in sec 8.3.4.1
//*
//* @param[in] pu1_src
//*  UWORD8 pointer to the source containing alternate U and V samples
//*
//* @param[out] pu1_dst
//*  UWORD8 pointer to the destination with alternate U and V samples
//*
//* @param[in] src_strd
//*  integer source stride
//*
//* @param[in] dst_strd
//*  integer destination stride
//*
//** @param[in] ui_neighboravailability
//*  availability of neighbouring pixels
//*
//* @returns
//*
//* @remarks
//*  None
//*
//*******************************************************************************/
//void ih264_intra_pred_chroma_8x8_mode_dc(UWORD8 *pu1_src,
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



    .global ih264_intra_pred_chroma_8x8_mode_dc_av8

ih264_intra_pred_chroma_8x8_mode_dc_av8:


    push_v_regs
    stp       x19, x20, [sp, #-16]!
    sxtw      x3, w3

    mov       w19, #5
    ands      w6, w4, w19
    beq       none_available
    cmp       w6, #1
    beq       left_only_available
    cmp       w6, #4
    beq       top_only_available

all_available:
    ld1       {v0.8b, v1.8b}, [x0]
    add       x6, x0, #18
    ld1       {v2.8b, v3.8b}, [x6]
    uxtl      v0.8h, v0.8b
    uxtl      v1.8h, v1.8b
    addp      v0.4s, v0.4s , v0.4s
    addp      v1.4s, v1.4s , v1.4s
    addp      v0.4s, v0.4s , v0.4s
    addp      v1.4s, v1.4s , v1.4s
    uxtl      v2.8h, v2.8b
    uxtl      v3.8h, v3.8b
    addp      v2.4s, v2.4s , v2.4s
    addp      v3.4s, v3.4s , v3.4s
    addp      v2.4s, v2.4s , v2.4s
    addp      v3.4s, v3.4s , v3.4s
    rshrn     v5.8b, v0.8h, #2
    dup       v21.8h, v5.h[0]
    rshrn     v6.8b, v3.8h, #2
    dup       v20.8h, v6.h[0]
    add       v1.8h, v1.8h, v2.8h
    rshrn     v1.8b, v1.8h, #3
    dup       v23.8h, v1.h[0]
    mov       v20.d[0], v23.d[0]
    add       v0.8h, v0.8h, v3.8h
    rshrn     v0.8b, v0.8h, #3
    dup       v23.8h, v0.h[0]
    mov       v21.d[1], v23.d[0]
    b         store
left_only_available:
    ld1       {v0.8b, v1.8b}, [x0]
    uxtl      v0.8h, v0.8b
    uxtl      v1.8h, v1.8b
    addp      v0.4s, v0.4s , v0.4s
    addp      v1.4s, v1.4s , v1.4s
    addp      v0.4s, v0.4s , v0.4s
    addp      v1.4s, v1.4s , v1.4s
    rshrn     v0.8b, v0.8h, #2
    rshrn     v1.8b, v1.8h, #2
    dup       v20.8h , v1.h[0]
    dup       v21.8h, v0.h[0]
    b         store

top_only_available:
    add       x6, x0, #18
    ld1       {v0.8b, v1.8b}, [x6]
    uxtl      v0.8h, v0.8b
    uxtl      v1.8h, v1.8b
    addp      v0.4s, v0.4s , v0.4s
    addp      v1.4s, v1.4s , v1.4s
    addp      v0.4s, v0.4s , v0.4s
    addp      v1.4s, v1.4s , v1.4s
    rshrn     v0.8b, v0.8h, #2
    rshrn     v1.8b, v1.8h, #2
    dup       v20.8h , v0.h[0]
    dup       v21.8h, v1.h[0]
    mov       v20.d[1], v21.d[1]
    mov       v21.d[0], v20.d[0]
    b         store
none_available:
    mov       w15, #128
    dup       v20.16b, w15
    dup       v21.16b, w15


store:

    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v20.16b}, [x1], x3
    st1       { v21.16b}, [x1], x3
    st1       { v21.16b}, [x1], x3
    st1       { v21.16b}, [x1], x3
    st1       { v21.16b}, [x1], x3
end_func:

    ldp       x19, x20, [sp], #16
    pop_v_regs
    ret





///******************************************************************************


///**
//*******************************************************************************
//*
//*ih264_intra_pred_chroma_8x8_mode_horz
//*
//* @brief
//*  Perform Intra prediction for  chroma_8x8 mode:Horizontal
//*
//* @par Description:
//*   Perform Intra prediction for  chroma_8x8 mode:Horizontal ,described in sec 8.3.4.2
//*
//* @param[in] pu1_src
//* UWORD8 pointer to the source containing alternate U and V samples
//*
//* @param[out] pu1_dst
//*  UWORD8 pointer to the destination with alternate U and V samples
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
//void ih264_intra_pred_chroma_8x8_mode_horz(UWORD8 *pu1_src,
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


    .global ih264_intra_pred_chroma_8x8_mode_horz_av8

ih264_intra_pred_chroma_8x8_mode_horz_av8:



    push_v_regs
    sxtw      x3, w3
    ld1       {v0.8h}, [x0]

    dup       v10.8h, v0.h[7]
    dup       v11.8h, v0.h[6]
    dup       v12.8h, v0.h[5]
    dup       v13.8h, v0.h[4]
    st1       {v10.8h}, [x1], x3
    dup       v14.8h, v0.h[3]
    st1       {v11.8h}, [x1], x3
    dup       v15.8h, v0.h[2]
    st1       {v12.8h}, [x1], x3
    dup       v16.8h, v0.h[1]
    st1       {v13.8h}, [x1], x3
    dup       v17.8h, v0.h[0]
    st1       {v14.8h}, [x1], x3
    st1       {v15.8h}, [x1], x3
    st1       {v16.8h}, [x1], x3
    st1       {v17.8h}, [x1], x3


    pop_v_regs
    ret






///**
//*******************************************************************************
//*
//*ih264_intra_pred_chroma_8x8_mode_vert
//*
//* @brief
//*   Perform Intra prediction for  chroma_8x8 mode:vertical
//*
//* @par Description:
//*Perform Intra prediction for  chroma_8x8 mode:vertical ,described in sec 8.3.4.3
//*
//* @param[in] pu1_src
//* UWORD8 pointer to the source containing alternate U and V samples
//*
//* @param[out] pu1_dst
//*   UWORD8 pointer to the destination with alternate U and V samples
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
//void ih264_intra_pred_chroma_8x8_mode_vert(UWORD8 *pu1_src,
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


    .global ih264_intra_pred_chroma_8x8_mode_vert_av8

ih264_intra_pred_chroma_8x8_mode_vert_av8:

    push_v_regs
    sxtw      x3, w3

    add       x0, x0, #18
    ld1       {v0.8b, v1.8b}, [x0]

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
//*ih264_intra_pred_chroma_8x8_mode_plane
//*
//* @brief
//*   Perform Intra prediction for  chroma_8x8 mode:PLANE
//*
//* @par Description:
//*  Perform Intra prediction for  chroma_8x8 mode:PLANE ,described in sec 8.3.4.4
//*
//* @param[in] pu1_src
//*  UWORD8 pointer to the source containing alternate U and V samples
//*
//* @param[out] pu1_dst
//*  UWORD8 pointer to the destination with alternate U and V samples
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
//void ih264_intra_pred_chroma_8x8_mode_plane(UWORD8 *pu1_src,
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

    .global ih264_intra_pred_chroma_8x8_mode_plane_av8
ih264_intra_pred_chroma_8x8_mode_plane_av8:

    push_v_regs
    stp       x19, x20, [sp, #-16]!
    sxtw      x3, w3

    ld1       {v0.2s}, [x0]
    add       x10, x0, #10
    ld1       {v1.2s}, [x10]
    add       x10, x10, #6
    rev64     v5.4h, v0.4h
    ld1       {v2.2s}, [x10], #8
    add       x10, x10, #2
    rev64     v7.4h, v2.4h
    ld1       {v3.2s}, [x10]
    sub       x5, x3, #8
    adrp      x12, :got:ih264_gai1_intrapred_chroma_plane_coeffs1
    ldr       x12, [x12, #:got_lo12:ih264_gai1_intrapred_chroma_plane_coeffs1]
    usubl     v10.8h, v5.8b, v1.8b
    ld1       {v8.8b, v9.8b}, [x12]     // Load multiplication factors 1 to 8 into D3
    mov       v8.d[1], v9.d[0]
    usubl     v12.8h, v3.8b, v7.8b
    mul       v14.8h, v10.8h , v8.8h
    mul       v16.8h, v12.8h , v8.8h
    uzp1      v15.8h, v14.8h, v16.8h
    uzp2      v16.8h, v14.8h, v16.8h
    mov       v14.16b, v15.16b
    mov       v15.d[0], v14.d[1]
    mov       v17.d[0], v16.d[1]
    addp      v14.4h, v14.4h, v14.4h
    addp      v15.4h, v15.4h, v15.4h
    addp      v16.4h, v16.4h, v16.4h
    addp      v17.4h, v17.4h, v17.4h
    addp      v14.4h, v14.4h, v14.4h
    addp      v15.4h, v15.4h, v15.4h
    addp      v16.4h, v16.4h, v16.4h
    addp      v17.4h, v17.4h, v17.4h
    mov       x6, #34
    dup       v18.8h, w6
    smull     v22.4s, v14.4h, v18.4h
    smull     v24.4s, v15.4h, v18.4h
    smull     v26.4s, v16.4h, v18.4h
    smull     v28.4s, v17.4h, v18.4h
    rshrn     v10.4h, v22.4s, #6
    rshrn     v12.4h, v24.4s, #6
    rshrn     v13.4h, v26.4s, #6
    rshrn     v14.4h, v28.4s, #6
    ldrb      w6, [x0], #1
    add       x10, x0, #31
    ldrb      w8, [x0], #1
    ldrb      w7, [x10], #1
    ldrb      w9, [x10], #1
    add       w6, w6, w7
    add       w8, w8, w9
    lsl       w6, w6, #4
    lsl       w8, w8, #4
    dup       v0.8h, w6
    dup       v2.8h, w8
    dup       v4.8h, v12.h[0]
    dup       v6.8h, v10.h[0]
    dup       v24.8h, v14.h[0]
    dup       v26.8h, v13.h[0]
    zip1      v5.8h, v4.8h, v24.8h
    zip2      v24.8h, v4.8h, v24.8h
    mov       v4.16b, v5.16b
    zip1      v7.8h, v6.8h, v26.8h
    zip2      v26.8h, v6.8h, v26.8h
    mov       v6.16b, v7.16b
    zip1      v1.8h, v0.8h, v2.8h
    zip2      v2.8h, v0.8h, v2.8h
    mov       v0.16b, v1.16b

    adrp      x12, :got:ih264_gai1_intrapred_chroma_plane_coeffs2
    ldr       x12, [x12, #:got_lo12:ih264_gai1_intrapred_chroma_plane_coeffs2]

    ld1       {v8.2s, v9.2s}, [x12]
    mov       v8.d[1], v9.d[0]
    mov       v10.16b, v8.16b
    mov       v22.16b, v8.16b
    zip1      v9.8h, v8.8h, v10.8h
    zip2      v10.8h, v8.8h, v10.8h
    mov       v8.16b, v9.16b
    mul       v12.8h, v4.8h , v8.8h
    mul       v16.8h, v4.8h , v10.8h
    add       v12.8h, v0.8h , v12.8h
    add       v16.8h, v0.8h , v16.8h
    dup       v20.8h, v22.h[0]
    mul       v4.8h, v6.8h , v20.8h
    dup       v30.8h, v22.h[1]
    mul       v18.8h, v6.8h , v20.8h
    mul       v14.8h, v6.8h , v30.8h
    mul       v8.8h, v6.8h , v30.8h
    add       v24.8h, v12.8h , v4.8h
    add       v0.8h, v16.8h , v18.8h
    add       v2.8h, v12.8h , v14.8h
    sqrshrun  v28.8b, v24.8h, #5
    add       v26.8h, v16.8h , v8.8h
    sqrshrun  v29.8b, v0.8h, #5
    dup       v20.8h, v22.h[2]
    st1       {v28.8b, v29.8b}, [x1], x3
    sqrshrun  v28.8b, v2.8h, #5
    sqrshrun  v29.8b, v26.8h, #5
    mul       v4.8h, v6.8h , v20.8h
    mul       v18.8h, v6.8h , v20.8h
    st1       {v28.8b, v29.8b}, [x1], x3
    add       v24.8h, v12.8h , v4.8h
    add       v0.8h, v16.8h , v18.8h
    dup       v30.8h, v22.h[3]
    sqrshrun  v28.8b, v24.8h, #5
    sqrshrun  v29.8b, v0.8h, #5
    mul       v14.8h, v6.8h , v30.8h
    mul       v8.8h, v6.8h , v30.8h
    st1       {v28.8b, v29.8b}, [x1], x3
    add       v2.8h, v12.8h , v14.8h
    add       v26.8h, v16.8h , v8.8h
    dup       v20.8h, v22.h[4]
    sqrshrun  v28.8b, v2.8h, #5
    sqrshrun  v29.8b, v26.8h, #5
    mul       v4.8h, v6.8h , v20.8h
    mul       v18.8h, v6.8h , v20.8h
    st1       {v28.8b, v29.8b}, [x1], x3
    add       v24.8h, v12.8h , v4.8h
    add       v0.8h, v16.8h , v18.8h
    dup       v30.8h, v22.h[5]
    sqrshrun  v28.8b, v24.8h, #5
    sqrshrun  v29.8b, v0.8h, #5
    mul       v14.8h, v6.8h , v30.8h
    mul       v8.8h, v6.8h , v30.8h
    st1       {v28.8b, v29.8b}, [x1], x3
    add       v2.8h, v12.8h , v14.8h
    add       v26.8h, v16.8h , v8.8h
    dup       v20.8h, v22.h[6]
    sqrshrun  v28.8b, v2.8h, #5
    sqrshrun  v29.8b, v26.8h, #5
    mul       v4.8h, v6.8h , v20.8h
    mul       v18.8h, v6.8h , v20.8h
    st1       {v28.8b, v29.8b}, [x1], x3
    add       v24.8h, v12.8h , v4.8h
    add       v0.8h, v16.8h , v18.8h
    dup       v30.8h, v22.h[7]
    sqrshrun  v28.8b, v24.8h, #5
    sqrshrun  v29.8b, v0.8h, #5
    mul       v14.8h, v6.8h , v30.8h
    mul       v8.8h, v6.8h , v30.8h
    st1       {v28.8b, v29.8b}, [x1], x3
    add       v2.8h, v12.8h , v14.8h
    add       v26.8h, v16.8h , v8.8h
    sqrshrun  v28.8b, v2.8h, #5
    sqrshrun  v29.8b, v26.8h, #5
    st1       {v28.8b, v29.8b}, [x1], x3

end_func_plane:

    ldp       x19, x20, [sp], #16
    pop_v_regs
    ret



