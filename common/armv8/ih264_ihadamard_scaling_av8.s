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
// *  ih264_ihadamard_scaling_av8.s
// *
// * @brief
// *  Contains function definitions for inverse hadamard transform on 4x4 DC outputs
// *  of 16x16 intra-prediction
// *
// * @author
// *  Mohit
// *
// * @par List of Functions:
// *  - ih264_ihadamard_scaling_4x4_av8()
// *
// * @remarks
// *  None
// *
.include "ih264_neon_macros.s"

// *******************************************************************************
// */
// * @brief This function performs a 4x4 inverse hadamard transform on the 4x4 DC coefficients
// * of a 16x16 intra prediction macroblock, and then performs scaling.
// * prediction buffer
// *
// * @par Description:
// *  The DC coefficients pass through a 2-stage inverse hadamard transform.
// *  This inverse transformed content is scaled to based on Qp value.
// *
// * @param[in] pi2_src
// *  input 4x4 block of DC coefficients
// *
// * @param[out] pi2_out
// *  output 4x4 block
// *
// * @param[in] pu2_iscal_mat
// *  pointer to scaling list
// *
// * @param[in] pu2_weigh_mat
// *  pointer to weight matrix
// *
// * @param[in] u4_qp_div_6
// *  Floor (qp/6)
// *
// * @param[in] pi4_tmp
// * temporary buffer of size 1*16
// *
// * @returns none
// *
// * @remarks none
// *
// *******************************************************************************
// */
// *
// *******************************************************************************
// */
// void ih264_ihadamard_scaling_4x4(word16* pi2_src,
//        word16* pi2_out,
//        const uword16 *pu2_iscal_mat,
//        const uword16 *pu2_weigh_mat,
//        uword32 u4_qp_div_6,
//        word32* pi4_tmp)
//**************variables vs registers*****************************************
//x0 => *pi2_src
//x1 => *pi2_out
//x2 => *pu2_iscal_mat
//x3 => *pu2_weigh_mat
//x4=>   u4_qp_div_6

.text
.p2align 2

    .global ih264_ihadamard_scaling_4x4_av8
ih264_ihadamard_scaling_4x4_av8:

//only one shift is done in horizontal inverse because,
//if u4_qp_div_6 is lesser than 4 then shift value will be neagative and do negative left shift, in this case rnd_factor has value
//if u4_qp_div_6 is greater than 4 then shift value will be positive and do left shift, here rnd_factor is 0
    push_v_regs

//=======================inverse hadamard transform================================

    ld4       {v0.4h-v3.4h}, [x0]       //load x4,x5,x6,x7

    dup       v14.4s, w4                // populate the u4_qp_div_6
    ld1       {v15.h}[0], [x3]          // pu2_weigh_mat
    ld1       {v16.h}[0], [x2]          //pu2_iscal_mat

    saddl     v4.4s, v0.4h, v3.4h       //x0 = x4 + x7
    saddl     v5.4s, v1.4h, v2.4h       //x1 = x5 + x6
    ssubl     v6.4s, v1.4h, v2.4h       //x2 = x5 - x6
    ssubl     v7.4s, v0.4h, v3.4h       //x3 = x4 - x7

    add       v0.4s, v4.4s, v5.4s       //pi4_tmp_ptr[0] = x0 + x1
    add       v1.4s, v7.4s, v6.4s       //pi4_tmp_ptr[1] = x3 + x2
    sub       v2.4s, v4.4s, v5.4s       //pi4_tmp_ptr[2] = x0 - x1
    sub       v3.4s, v7.4s, v6.4s       //pi4_tmp_ptr[3] = x3 - x2

    umull     v15.4s, v15.4h, v16.4h
    dup       v15.4s, v15.s[0]          //pu2_weigh_mat[0]*pu2_iscal_mat[0]

    //transpose
    trn1      v4.4s, v0.4s, v1.4s
    trn2      v5.4s, v0.4s, v1.4s
    trn1      v6.4s, v2.4s, v3.4s
    trn2      v7.4s, v2.4s, v3.4s

    trn1      v0.2d, v4.2d, v6.2d
    trn2      v2.2d, v4.2d, v6.2d
    trn1      v1.2d, v5.2d, v7.2d
    trn2      v3.2d, v5.2d, v7.2d
    //end transpose

    add       v4.4s, v0.4s, v3.4s       //x0 = x4+x7
    add       v5.4s, v1.4s, v2.4s       //x1 = x5+x6
    sub       v6.4s, v1.4s, v2.4s       //x2 = x5-x6
    sub       v7.4s, v0.4s, v3.4s       //x3 = x4-x7

    add       v0.4s, v4.4s, v5.4s       //pi4_tmp_ptr[0] = x0 + x1
    add       v1.4s, v7.4s, v6.4s       //pi4_tmp_ptr[1] = x3 + x2
    sub       v2.4s, v4.4s, v5.4s       //pi4_tmp_ptr[2] = x0 - x1
    sub       v3.4s, v7.4s, v6.4s       //pi4_tmp_ptr[3] = x3 - x2

    mul       v0.4s, v0.4s, v15.4s      // q0  = p[i] = (x[i] * trns_coeff[i]) where i = 0..3
    mul       v1.4s, v1.4s, v15.4s      // q1  = p[i] = (x[i] * trns_coeff[i]) where i = 4..7
    mul       v2.4s, v2.4s, v15.4s      // q2  = p[i] = (x[i] * trns_coeff[i]) where i = 8..11
    mul       v3.4s, v3.4s, v15.4s      // q3  = p[i] = (x[i] * trns_coeff[i]) where i = 12..15

    sshl      v0.4s, v0.4s, v14.4s      // q0  = q[i] = (p[i] << (qp/6)) where i = 0..3
    sshl      v1.4s, v1.4s, v14.4s      // q1  = q[i] = (p[i] << (qp/6)) where i = 4..7
    sshl      v2.4s, v2.4s, v14.4s      // q2  = q[i] = (p[i] << (qp/6)) where i = 8..11
    sshl      v3.4s, v3.4s, v14.4s      // q3  = q[i] = (p[i] << (qp/6)) where i = 12..15

    sqrshrn   v0.4h, v0.4s, #6          // d0  = c[i] = ((q[i] + 32) >> 4) where i = 0..3
    sqrshrn   v1.4h, v1.4s, #6          // d1  = c[i] = ((q[i] + 32) >> 4) where i = 4..7
    sqrshrn   v2.4h, v2.4s, #6          // d2  = c[i] = ((q[i] + 32) >> 4) where i = 8..11
    sqrshrn   v3.4h, v3.4s, #6          // d3  = c[i] = ((q[i] + 32) >> 4) where i = 12..15

    st1       {v0.4h-v3.4h}, [x1]       //store the result

    pop_v_regs
    ret


// *******************************************************************************
// */
// * @brief This function performs a 2x2 inverse hadamard transform for chroma block
// *
// * @par Description:
// *  The DC coefficients pass through a 2-stage inverse hadamard transform.
// *  This inverse transformed content is scaled to based on Qp value.
// *  Both DC blocks of U and v blocks are processesd
// *
// * @param[in] pi2_src
// *  input 1x8 block of ceffs. First 4 are from U and next from V
// *
// * @param[out] pi2_out
// *  output 1x8 block
// *
// * @param[in] pu2_iscal_mat
// *  pointer to scaling list
// *
// * @param[in] pu2_weigh_mat
// *  pointer to weight matrix
// *
// * @param[in] u4_qp_div_6
// *  Floor (qp/6)
// *
// * @returns none
// *
// * @remarks none
// *
// *******************************************************************************
// */
// *
// *******************************************************************************
// */
// void ih264_ihadamard_scaling_2x2_uv(WORD16* pi2_src,
//                                  WORD16* pi2_out,
//                                  const UWORD16 *pu2_iscal_mat,
//                                  const UWORD16 *pu2_weigh_mat,
//                                  UWORD32 u4_qp_div_6,

    .global ih264_ihadamard_scaling_2x2_uv_av8
ih264_ihadamard_scaling_2x2_uv_av8:

//Registers used
//   x0 : *pi2_src
//   x1 : *pi2_out
//   x2 : *pu2_iscal_mat
//   x3 : *pu2_weigh_mat
//   x4 : u4_qp_div_6
    push_v_regs
    ld1       {v26.h}[0], [x2]
    ld1       {v27.h}[0], [x3]

    sub       w4, w4, #5                //qp/6 - 4
    dup       v28.4s, w4                //load qp/6

    ld2       {v0.4h, v1.4h}, [x0]      //load 8 dc coeffs
                                        //i2_x4,i2_x6,i2_y4,i1_y6 -> d0
                                        //i2_x5,i2_x7,i2_y5,i1_y6 -> d1

    saddl     v2.4s, v0.4h, v1.4h       //i4_x0 = i4_x4 + i4_x5;...x2
    ssubl     v4.4s, v0.4h, v1.4h       //i4_x1 = i4_x4 - i4_x5;...x3

    umull     v30.4s, v26.4h, v27.4h    //pu2_iscal_mat[0]*pu2_weigh_mat[0]
    dup       v30.4s, v30.s[0]

    trn1      v0.4s, v2.4s, v4.4s
    trn2      v1.4s, v2.4s, v4.4s       //i4_x0 i4_x1 -> q1

    add       v2.4s, v0.4s, v1.4s       //i4_x4 = i4_x0+i4_x2;.. i4_x5
    sub       v3.4s, v0.4s, v1.4s       //i4_x6 = i4_x0-i4_x2;.. i4_x7

    mul       v2.4s, v2.4s, v30.4s
    mul       v3.4s, v3.4s, v30.4s

    sshl      v2.4s, v2.4s, v28.4s
    sshl      v3.4s, v3.4s, v28.4s

    xtn       v0.4h, v2.4s              //i4_x4 i4_x5 i4_y4 i4_y5
    xtn       v1.4h, v3.4s              //i4_x6 i4_x7 i4_y6 i4_y7

    st2       {v0.4s-v1.4s}, [x1]
    pop_v_regs
    ret



