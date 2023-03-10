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
@******************************************************************************
@* @file
@*  ih264_inter_pred_luma_bilinear_a9q.s
@*
@* @brief
@*  Contains function definitions for inter prediction  interpolation.
@*
@* @author
@* Ittiam
@*
@* @par List of Functions:
@*
@*  - ih264_inter_pred_luma_bilinear_a9q()
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@*

@* All the functions here are replicated from ih264_inter_pred_filters.c
@

@**
@**
@**
@ *******************************************************************************
@ *  function:ih264_inter_pred_luma_bilinear
@ *
@* @brief
@*    This routine applies the bilinear filter to the predictors .
@*    The  filtering operation is described in
@*    sec 8.4.2.2.1 titled "Luma sample interpolation process"
@*
@* @par Description:
@\note
@*     This function is called to obtain pixels lying at the following
@*    locations (1/4,1), (3/4,1),(1,1/4), (1,3/4) ,(1/4,1/2), (3/4,1/2),(1/2,1/4), (1/2,3/4),(3/4,1/4),(1/4,3/4),(3/4,3/4)&& (1/4,1/4) .
@*    The function averages the two adjacent values from the two input arrays in horizontal direction.
@*
@*
@* @param[in] pu1_src1:
@*  UWORD8 Pointer to the buffer containing the first input array.
@*
@* @param[in] pu1_src2:
@*  UWORD8 Pointer to the buffer containing the second input array.
@*
@* @param[out] pu1_dst
@*  UWORD8 pointer to the destination where the output of bilinear filter is stored.
@*
@* @param[in] src_strd1
@*  Stride of the first input buffer
@*
@* @param[in] src_strd2
@*  Stride of the second input buffer
@*
@* @param[in] dst_strd
@*  integer destination stride of pu1_dst
@*
@* @param[in] ht
@*  integer height of the array
@*
@* @param[in] wd
@*  integer width of the array
@*
@* @returns
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@*

@void ih264_inter_pred_luma_bilinear(UWORD8 *pu1_src1,
@                                   UWORD8 *pu1_src2,
@                                   UWORD8 *pu1_dst,
@                                   WORD32 src_strd1,
@                                   WORD32 src_strd2,
@                                   WORD32 dst_strd,
@                                   WORD32 height,
@                                   WORD32 width)
@
@**************Variables Vs Registers*****************************************
@   r0 => *pu1_src1
@   r1 => *pu1_src2
@   r2 => *pu1_dst
@   r3 =>  src_strd1
@   r4 =>  src_strd2
@   r5 =>  dst_strd
@   r6 =>  height
@   r7 => width
@
.text
.p2align 2

    .global ih264_inter_pred_luma_bilinear_a9q

ih264_inter_pred_luma_bilinear_a9q:



    stmfd         sp!, {r4-r12, r14}    @store register values to stack
    vstmdb        sp!, {d8-d15}         @push neon registers to stack
    ldr           r4, [sp, #104]
    ldr           r5, [sp, #108]        @
    ldr           r6, [sp, #112]
    ldr           r7, [sp, #116]

    subs          r12, r7, #4           @if wd=4 branch to loop_4
    beq           loop_4
    subs          r12, r7, #8           @if wd=8 branch to loop_8
    beq           loop_8

loop_16:                                @when  wd=16

    vld1.8        {q0}, [r0], r3        @// Load row0 ;src1
    vld1.8        {q2}, [r1], r4        @// Load row0  ;src2
    vld1.8        {q1}, [r0], r3        @// Load row1 ;src1
    vaddl.u8      q10, d0, d4
    vld1.8        {q3}, [r1], r4        @// Load row1  ;src2
    vaddl.u8      q11, d1, d5
    vld1.8        {q4}, [r0], r3        @// Load row2 ;src1
    vaddl.u8      q12, d2, d6
    vld1.8        {q5}, [r0], r3        @// Load row3 ;src1
    vaddl.u8      q13, d3, d7
    vld1.8        {q6}, [r1], r4        @// Load row2  ;src2
    vaddl.u8      q8, d8, d12
    vld1.8        {q7}, [r1], r4        @// Load row3  ;src2
    vaddl.u8      q9, d9, d13
    vqrshrun.s16  d28, q10, #1
    vqrshrun.s16  d29, q11, #1
    vaddl.u8      q10, d10, d14
    vqrshrun.s16  d30, q12, #1
    vqrshrun.s16  d31, q13, #1
    vst1.8        {q14}, [r2], r5       @//Store dest row0
    vaddl.u8      q11, d11, d15
    vst1.8        {q15}, [r2], r5       @//Store dest row1
    vqrshrun.s16  d28, q8, #1
    vld1.8        {q0}, [r0], r3        @// Load row4 ;src1
    vqrshrun.s16  d29, q9, #1
    vld1.8        {q1}, [r0], r3        @// Load row5 ;src1
    vqrshrun.s16  d30, q10, #1
    vld1.8        {q2}, [r1], r4        @// Load row4  ;src2
    vqrshrun.s16  d31, q11, #1
    vld1.8        {q3}, [r1], r4        @// Load row5  ;src2
    vaddl.u8      q10, d0, d4
    vst1.8        {q14}, [r2], r5       @//Store dest row2
    vaddl.u8      q13, d3, d7
    vst1.8        {q15}, [r2], r5       @//Store dest row3
    vaddl.u8      q11, d1, d5
    vld1.8        {q4}, [r0], r3        @// Load row6 ;src1
    vaddl.u8      q12, d2, d6
    vld1.8        {q5}, [r0], r3        @// Load row7 ;src1
    vqrshrun.s16  d28, q10, #1
    vld1.8        {q6}, [r1], r4        @// Load row6  ;src2
    vqrshrun.s16  d29, q11, #1
    vld1.8        {q7}, [r1], r4        @// Load row7  ;src2
    vaddl.u8      q8, d8, d12
    vaddl.u8      q9, d9, d13
    vaddl.u8      q10, d10, d14
    vqrshrun.s16  d30, q12, #1
    vqrshrun.s16  d31, q13, #1
    vst1.8        {q14}, [r2], r5       @//Store dest row4
    vaddl.u8      q11, d11, d15
    vst1.8        {q15}, [r2], r5       @//Store dest row5
    vqrshrun.s16  d28, q8, #1
    vqrshrun.s16  d30, q10, #1
    vqrshrun.s16  d29, q9, #1
    vld1.8        {q2}, [r1], r4        @// Load row8  ;src2
    vqrshrun.s16  d31, q11, #1
    vst1.8        {q14}, [r2], r5       @//Store dest row6
    subs          r12, r6, #8
    vst1.8        {q15}, [r2], r5       @//Store dest row7

    beq           end_func              @ end function if ht=8

    vld1.8        {q0}, [r0], r3        @// Load row8 ;src1
    vaddl.u8      q10, d0, d4
    vld1.8        {q1}, [r0], r3        @// Load row9 ;src1
    vaddl.u8      q11, d1, d5
    vld1.8        {q3}, [r1], r4        @// Load row9  ;src2
    vqrshrun.s16  d28, q10, #1
    vld1.8        {q4}, [r0], r3        @// Load row10 ;src1
    vqrshrun.s16  d29, q11, #1
    vld1.8        {q5}, [r0], r3        @// Load row11 ;src1
    vaddl.u8      q12, d2, d6
    vld1.8        {q6}, [r1], r4        @// Load row10  ;src2
    vaddl.u8      q13, d3, d7
    vld1.8        {q7}, [r1], r4        @// Load row11 ;src2
    vaddl.u8      q8, d8, d12
    vaddl.u8      q9, d9, d13
    vaddl.u8      q10, d10, d14
    vqrshrun.s16  d30, q12, #1
    vst1.8        {q14}, [r2], r5       @//Store dest row8
    vqrshrun.s16  d31, q13, #1
    vst1.8        {q15}, [r2], r5       @//Store dest row9
    vqrshrun.s16  d28, q8, #1
    vld1.8        {q0}, [r0], r3        @// Load row12 ;src1
    vaddl.u8      q11, d11, d15
    vld1.8        {q1}, [r0], r3        @// Load row13 ;src1
    vqrshrun.s16  d29, q9, #1
    vld1.8        {q2}, [r1], r4        @// Load row12  ;src2
    vqrshrun.s16  d30, q10, #1
    vld1.8        {q3}, [r1], r4        @// Load row13  ;src2
    vqrshrun.s16  d31, q11, #1
    vst1.8        {q14}, [r2], r5       @//Store dest row10
    vaddl.u8      q10, d0, d4
    vst1.8        {q15}, [r2], r5       @//Store dest row11
    vaddl.u8      q11, d1, d5
    vld1.8        {q4}, [r0], r3        @// Load row14 ;src1
    vaddl.u8      q13, d3, d7
    vld1.8        {q5}, [r0], r3        @// Load row15 ;src1
    vaddl.u8      q12, d2, d6
    vld1.8        {q6}, [r1], r4        @// Load row14  ;src2
    vaddl.u8      q8, d8, d12
    vld1.8        {q7}, [r1], r4        @// Load row15  ;src2
    vaddl.u8      q9, d9, d13
    vqrshrun.s16  d28, q10, #1
    vqrshrun.s16  d29, q11, #1
    vaddl.u8      q10, d10, d14
    vst1.8        {q14}, [r2], r5       @//Store dest row12
    vqrshrun.s16  d30, q12, #1
    vqrshrun.s16  d31, q13, #1
    vaddl.u8      q11, d11, d15
    vst1.8        {q15}, [r2], r5       @//Store dest row13
    vqrshrun.s16  d28, q8, #1
    vqrshrun.s16  d29, q9, #1
    vqrshrun.s16  d30, q10, #1
    vst1.8        {q14}, [r2], r5       @//Store dest row14
    vqrshrun.s16  d31, q11, #1
    vst1.8        {q15}, [r2], r5       @//Store dest row15
    b             end_func



loop_8: @wd=8;
    vld1.8        {d0}, [r0], r3        @// Load row0 ;src1
    vld1.8        {d4}, [r1], r4        @// Load row0  ;src2
    vld1.8        {d1}, [r0], r3        @// Load row1 ;src1
    vaddl.u8      q10, d0, d4
    vld1.8        {d5}, [r1], r4        @// Load row1  ;src2
    vld1.8        {d2}, [r0], r3        @// Load row2 ;src1
    vqrshrun.s16  d28, q10, #1
    vld1.8        {d6}, [r1], r4        @// Load row2  ;src2
    vaddl.u8      q11, d1, d5
    vld1.8        {d3}, [r0], r3        @// Load row3 ;src1
    vaddl.u8      q12, d2, d6
    vst1.8        {d28}, [r2], r5       @//Store dest row0
    vqrshrun.s16  d29, q11, #1
    vld1.8        {d7}, [r1], r4        @// Load row3  ;src2
    vqrshrun.s16  d30, q12, #1
    vst1.8        {d29}, [r2], r5       @//Store dest row1
    vaddl.u8      q13, d3, d7
    vst1.8        {d30}, [r2], r5       @//Store dest row2
    vqrshrun.s16  d31, q13, #1
    subs          r12, r6, #4
    vst1.8        {d31}, [r2], r5       @//Store dest row3
    beq           end_func              @ end function if ht=4

    vld1.8        {d12}, [r1], r4       @// Load row4 ;src2
    vld1.8        {d8}, [r0], r3        @// Load row4 ;src1
    vld1.8        {d9}, [r0], r3        @// Load row5 ;src1
    vaddl.u8      q8, d8, d12
    vld1.8        {d13}, [r1], r4       @// Load row5  ;src2
    vld1.8        {d10}, [r0], r3       @// Load row6;src1
    vaddl.u8      q9, d9, d13
    vld1.8        {d14}, [r1], r4       @// Load row6  ;src2
    vqrshrun.s16  d28, q8, #1
    vld1.8        {d11}, [r0], r3       @// Load row7 ;src1
    vqrshrun.s16  d29, q9, #1
    vst1.8        {d28}, [r2], r5       @//Store dest row4
    vaddl.u8      q10, d10, d14
    vst1.8        {d29}, [r2], r5       @//Store dest row5
    vqrshrun.s16  d30, q10, #1
    vld1.8        {d15}, [r1], r4       @// Load row7 ;src2
    vaddl.u8      q11, d11, d15
    vst1.8        {d30}, [r2], r5       @//Store dest row6
    vqrshrun.s16  d31, q11, #1
    subs          r12, r6, #8
    vst1.8        {d31}, [r2], r5       @//Store dest row7
    beq           end_func              @ end function if ht=8

    vld1.8        {d0}, [r0], r3        @// Load row8 ;src1
    vld1.8        {d4}, [r1], r4        @// Load row8  ;src2
    vld1.8        {d1}, [r0], r3        @// Load row9 ;src1
    vaddl.u8      q10, d0, d4
    vld1.8        {d5}, [r1], r4        @// Load row9  ;src2
    vld1.8        {d2}, [r0], r3        @// Load row10 ;src1
    vaddl.u8      q11, d1, d5
    vld1.8        {d6}, [r1], r4        @// Load row10  ;src2
    vqrshrun.s16  d28, q10, #1
    vld1.8        {d3}, [r0], r3        @// Load row11 ;src1
    vaddl.u8      q12, d2, d6
    vld1.8        {d7}, [r1], r4        @// Load row11  ;src2
    vqrshrun.s16  d29, q11, #1
    vld1.8        {d8}, [r0], r3        @// Load row12 ;src1
    vaddl.u8      q13, d3, d7
    vst1.8        {d28}, [r2], r5       @//Store dest row8
    vqrshrun.s16  d30, q12, #1
    vld1.8        {d12}, [r1], r4       @// Load row12  ;src2
    vqrshrun.s16  d31, q13, #1
    vst1.8        {d29}, [r2], r5       @//Store dest row9
    vaddl.u8      q8, d8, d12
    vld1.8        {d9}, [r0], r3        @// Load row13 ;src1
    vqrshrun.s16  d28, q8, #1
    vld1.8        {d13}, [r1], r4       @// Load row13  ;src2
    vld1.8        {d10}, [r0], r3       @// Load row14;src1
    vaddl.u8      q9, d9, d13
    vld1.8        {d11}, [r0], r3       @// Load row15 ;src1
    vld1.8        {d14}, [r1], r4       @// Load row14  ;src2
    vqrshrun.s16  d29, q9, #1
    vld1.8        {d15}, [r1], r4       @// Load roW15 ;src2
    vaddl.u8      q10, d10, d14
    vst1.8        {d30}, [r2], r5       @//Store dest row10
    vaddl.u8      q11, d11, d15
    vst1.8        {d31}, [r2], r5       @//Store dest row11
    vqrshrun.s16  d30, q10, #1
    vst1.8        {d28}, [r2], r5       @//Store dest row12
    vqrshrun.s16  d31, q11, #1
    vst1.8        {d29}, [r2], r5       @//Store dest row13
    vst1.8        {d30}, [r2], r5       @//Store dest row14
    vst1.8        {d31}, [r2], r5       @//Store dest row15

    b             end_func



loop_4:
    vld1.32       d0[0], [r0], r3       @// Load row0 ;src1
    vld1.32       d4[0], [r1], r4       @// Load row0  ;src2
    vld1.32       d1[0], [r0], r3       @// Load row1 ;src1
    vaddl.u8      q10, d0, d4
    vld1.32       d5[0], [r1], r4       @// Load row1  ;src2
    vld1.32       d2[0], [r0], r3       @// Load row2 ;src1
    vqrshrun.s16  d28, q10, #1
    vld1.32       d6[0], [r1], r4       @// Load row2  ;src2
    vaddl.u8      q11, d1, d5
    vld1.32       d3[0], [r0], r3       @// Load row3 ;src1
    vaddl.u8      q12, d2, d6
    vst1.32       d28[0], [r2], r5      @//Store dest row0
    vqrshrun.s16  d29, q11, #1
    vld1.32       d7[0], [r1], r4       @// Load row3  ;src2
    vqrshrun.s16  d30, q12, #1
    vst1.32       d29[0], [r2], r5      @//Store dest row1
    vaddl.u8      q13, d3, d7
    vst1.32       d30[0], [r2], r5      @//Store dest row2
    vqrshrun.s16  d31, q13, #1
    subs          r12, r6, #4
    vst1.32       d31[0], [r2], r5      @//Store dest row3
    beq           end_func              @ end function if ht=4

    vld1.32       d12[0], [r1], r4      @// Load row4 ;src2
    vld1.32       d8[0], [r0], r3       @// Load row4 ;src1
    vld1.32       d9[0], [r0], r3       @// Load row5 ;src1
    vaddl.u8      q8, d8, d12
    vld1.32       d13[0], [r1], r4      @// Load row5  ;src2
    vld1.32       d10[0], [r0], r3      @// Load row6;src1
    vaddl.u8      q9, d9, d13
    vld1.32       d14[0], [r1], r4      @// Load row6  ;src2
    vqrshrun.s16  d28, q8, #1
    vld1.32       d11[0], [r0], r3      @// Load row7 ;src1
    vqrshrun.s16  d29, q9, #1
    vst1.32       d28[0], [r2], r5      @//Store dest row4
    vaddl.u8      q10, d10, d14
    vst1.32       d29[0], [r2], r5      @//Store dest row5
    vqrshrun.s16  d30, q10, #1
    vld1.32       d15[0], [r1], r4      @// Load row7 ;src2
    vaddl.u8      q11, d11, d15
    vst1.32       d30[0], [r2], r5      @//Store dest row6
    vqrshrun.s16  d31, q11, #1
    vst1.32       d31[0], [r2], r5      @//Store dest row7

end_func:

    vldmia        sp!, {d8-d15}         @ Restore neon registers that were saved
    ldmfd         sp!, {r4-r12, pc}     @Restoring registers from stack


