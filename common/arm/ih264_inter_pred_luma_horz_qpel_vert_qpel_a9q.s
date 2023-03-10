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
@*  ih264_inter_pred_luma_horz_qpel_vert_qpel_a9q.s
@*
@* @brief
@*  Contains function definitions for inter prediction  interpolation.
@*
@* @author
@*  Mohit
@*
@* @par List of Functions:
@*
@*  - ih264_inter_pred_luma_horz_qpel_vert_qpel_a9q()
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@*

@* All the functions here are replicated from ih264_inter_pred_filters.c
@

@*******************************************************************************
@*
@* @brief
@*   This function implements two six tap filters. It
@*    applies the six tap filter in the horizontal direction on the
@*    predictor values, then applies the same filter in the
@*    vertical direction on the predictor values. It then averages these
@*    two outputs to obtain quarter pel values in horizontal and vertical direction.
@*    The six tap filtering operation is described in sec 8.4.2.2.1 titled
@*    "Luma sample interpolation process"
@*
@* @par Description:
@*    This function is called to obtain pixels lying at the following
@*    location (1/4,1/4) or (3/4,1/4) or (1/4,3/4) or (3/4,3/4).
@*    The function interpolates the predictors first in the horizontal direction
@*    and then in the vertical direction, and then averages these two
@*    values.
@*
@* @param[in] pu1_src
@*  UWORD8 pointer to the source
@*
@* @param[out] pu1_dst
@*  UWORD8 pointer to the destination
@*
@* @param[in] src_strd
@*  integer source stride
@*
@* @param[in] dst_strd
@*  integer destination stride
@*
@* @param[in] ht
@*  integer height of the array
@*
@* @param[in] wd
@*  integer width of the array
@*
@* @param[in] pu1_tmp: temporary buffer
@*
@* @param[in] dydx: x and y reference offset for qpel calculations
@*
@* @returns
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@*;

@void ih264_inter_pred_luma_horz_qpel_vert_qpel(UWORD8 *pu1_src,
@                                UWORD8 *pu1_dst,
@                                WORD32 src_strd,,
@                                WORD32 dst_strd,
@                                WORD32 ht,
@                                WORD32 wd,
@                                UWORD8* pu1_tmp,
@                                UWORD32 dydx)

@**************Variables Vs Registers*****************************************
@   r0 => *pu1_src
@   r1 => *pu1_dst
@   r2 =>  src_strd
@   r3 =>  dst_strd
@   r4 =>  ht
@   r5 =>  wd
@   r6 =>  dydx

.text
.p2align 2

    .global ih264_inter_pred_luma_horz_qpel_vert_qpel_a9q

ih264_inter_pred_luma_horz_qpel_vert_qpel_a9q:

    stmfd         sp!, {r4-r12, r14}    @store register values to stack
    vstmdb        sp!, {d8-d15}         @push neon registers to stack
    ldr           r4, [sp, #104]        @ loads ht
    ldr           r5, [sp, #108]        @ loads wd
    ldr           r6, [sp, #116]        @dydx
    and           r7, r6, #3
    add           r7, r0, r7, lsr #1    @pu1_pred_vert = pu1_src + (x_offset>>1)

    and           r6, r6, #12           @Finds y-offset
    lsr           r6, r6, #3            @dydx>>3
    mul           r6, r2, r6
    add           r6, r0, r6            @pu1_pred_horz = pu1_src + (y_offset>>1)*src_strd
    sub           r7, r7, r2, lsl #1    @pu1_pred_vert-2*src_strd
    sub           r6, r6, #2            @pu1_pred_horz-2
    vmov.u8       d30, #20              @ Filter coeff 20
    vmov.u8       d31, #5               @ Filter coeff 5

    subs          r12, r5, #4           @if wd=4 branch to loop_4
    beq           loop_4
    subs          r12, r5, #8           @if wd=8 branch to loop_8
    beq           loop_8

loop_16:
    vld1.32       {q0}, [r7], r2        @ Vector load from src[0_0]
    vld1.32       {q1}, [r7], r2        @ Vector load from src[1_0]
    vld1.32       {q2}, [r7], r2        @ Vector load from src[2_0]
    vld1.32       {q3}, [r7], r2        @ Vector load from src[3_0]
    vld1.32       {q4}, [r7], r2        @ Vector load from src[4_0]
    add           r11, r6, #8
    vld1.32       {q5}, [r7], r2        @ Vector load from src[5_0]
    vld1.32       {q9}, [r6], r2        @ horz row0, col 0
    vaddl.u8      q12, d0, d10
    vmlal.u8      q12, d4, d30
    vmlal.u8      q12, d6, d30
    vmlsl.u8      q12, d2, d31
    vmlsl.u8      q12, d8, d31
    vext.8        d23, d18, d19, #5
    vext.8        d20, d18, d19, #2
    vext.8        d21, d18, d19, #3
    vext.8        d22, d18, d19, #4
    vext.8        d19, d18, d19, #1
    vqrshrun.s16  d26, q12, #5
    vaddl.u8      q14, d18, d23
    vmlal.u8      q14, d20, d30
    vmlal.u8      q14, d21, d30
    vmlsl.u8      q14, d19, d31
    vmlsl.u8      q14, d22, d31
    vld1.32       {q9}, [r11], r2       @ horz row 0, col 1
    vaddl.u8      q12, d1, d11
    vmlal.u8      q12, d5, d30
    vmlal.u8      q12, d7, d30
    vmlsl.u8      q12, d3, d31
    vmlsl.u8      q12, d9, d31
    vqrshrun.s16  d28, q14, #5
    vext.8        d23, d18, d19, #5
    vext.8        d20, d18, d19, #2
    vext.8        d21, d18, d19, #3
    vext.8        d22, d18, d19, #4
    vext.8        d19, d18, d19, #1
    vqrshrun.s16  d27, q12, #5
    vld1.32       {q6}, [r7], r2        @ src[6_0]

    vaddl.u8      q12, d18, d23
    vmlal.u8      q12, d20, d30
    vmlal.u8      q12, d21, d30
    vmlsl.u8      q12, d19, d31
    vmlsl.u8      q12, d22, d31

    vaddl.u8      q8, d2, d12
    vmlal.u8      q8, d6, d30
    vmlal.u8      q8, d8, d30
    vmlsl.u8      q8, d4, d31
    vmlsl.u8      q8, d10, d31
    vqrshrun.s16  d29, q12, #5
    vld1.32       {q9}, [r6], r2        @ horz row 1, col 0

    vaddl.u8      q12, d3, d13
    vmlal.u8      q12, d7, d30
    vmlal.u8      q12, d9, d30
    vmlsl.u8      q12, d5, d31
    vmlsl.u8      q12, d11, d31
    vrhadd.u8     q14, q14, q13
    vqrshrun.s16  d26, q8, #5
    vext.8        d23, d18, d19, #5
    vext.8        d20, d18, d19, #2
    vext.8        d21, d18, d19, #3
    vext.8        d22, d18, d19, #4
    vst1.32       {q14}, [r1], r3       @ store row 0
    vext.8        d19, d18, d19, #1
    vqrshrun.s16  d27, q12, #5

    vaddl.u8      q14, d18, d23
    vmlal.u8      q14, d20, d30
    vmlal.u8      q14, d21, d30
    vmlsl.u8      q14, d19, d31
    vmlsl.u8      q14, d22, d31

    vld1.32       {q9}, [r11], r2       @ horz row 1, col 1

    vext.8        d23, d18, d19, #5
    vext.8        d20, d18, d19, #2
    vext.8        d21, d18, d19, #3
    vext.8        d22, d18, d19, #4
    vext.8        d19, d18, d19, #1

    vqrshrun.s16  d28, q14, #5
    vaddl.u8      q12, d18, d23
    vmlal.u8      q12, d20, d30
    vmlal.u8      q12, d21, d30
    vmlsl.u8      q12, d19, d31
    vmlsl.u8      q12, d22, d31

    vqrshrun.s16  d29, q12, #5
    vrhadd.u8     q14, q14, q13
    vst1.32       {q14}, [r1], r3       @ store row 1

    subs          r4, r4, #2            @ 2 rows processed, decrement by 2
    subne         r7, r7 , r2, lsl #2
    subne         r7, r7, r2
    beq           end_func              @ Branch if height==4

    b             loop_16               @ looping if height = 8 or 16


loop_8:
    vld1.32       d0, [r7], r2          @ Vector load from src[0_0]
    vld1.32       d1, [r7], r2          @ Vector load from src[1_0]
    vld1.32       d2, [r7], r2          @ Vector load from src[2_0]
    vld1.32       d3, [r7], r2          @ Vector load from src[3_0]
    vld1.32       d4, [r7], r2          @ Vector load from src[4_0]
    vld1.32       d5, [r7], r2          @ Vector load from src[5_0]
    vaddl.u8      q5, d0, d5
    vmlal.u8      q5, d2, d30
    vmlal.u8      q5, d3, d30
    vmlsl.u8      q5, d1, d31
    vmlsl.u8      q5, d4, d31
    vld1.32       {q6}, [r6], r2        @horz row 0
    vext.8        d17, d12, d13, #5
    vext.8        d14, d12, d13, #2
    vext.8        d15, d12, d13, #3
    vext.8        d16, d12, d13, #4
    vext.8        d13, d12, d13, #1
    vqrshrun.s16  d26, q5, #5
    vld1.32       d6, [r7], r2          @ src[6_0]
    vaddl.u8      q5, d12, d17
    vmlal.u8      q5, d14, d30
    vmlal.u8      q5, d15, d30
    vmlsl.u8      q5, d13, d31
    vmlsl.u8      q5, d16, d31
    vld1.32       {q6}, [r6], r2        @ horz row 1
    vaddl.u8      q9, d1, d6
    vmlal.u8      q9, d3, d30
    vmlal.u8      q9, d4, d30
    vmlsl.u8      q9, d2, d31
    vmlsl.u8      q9, d5, d31
    vqrshrun.s16  d28, q5, #5
    vext.8        d17, d12, d13, #5
    vext.8        d14, d12, d13, #2
    vext.8        d15, d12, d13, #3
    vext.8        d16, d12, d13, #4
    vext.8        d13, d12, d13, #1
    vqrshrun.s16  d27, q9, #5
    vaddl.u8      q5, d12, d17
    vmlal.u8      q5, d14, d30
    vmlal.u8      q5, d15, d30
    vmlsl.u8      q5, d13, d31
    vmlsl.u8      q5, d16, d31
    vqrshrun.s16  d29, q5, #5
    vrhadd.u8     q13, q13, q14
    vst1.32       d26, [r1], r3
    vst1.32       d27, [r1], r3

    subs          r4, r4, #2            @ 2 rows processed, decrement by 2
    subne         r7, r7 , r2, lsl #2
    subne         r7, r7, r2
    beq           end_func              @ Branch if height==4
    b             loop_8                @looping if height == 8 or 16

loop_4:
    vld1.32       d0[0], [r7], r2       @ Vector load from src[0_0]
    vld1.32       d1[0], [r7], r2       @ Vector load from src[1_0]
    vld1.32       d2[0], [r7], r2       @ Vector load from src[2_0]
    vld1.32       d3[0], [r7], r2       @ Vector load from src[3_0]
    vld1.32       d4[0], [r7], r2       @ Vector load from src[4_0]
    vld1.32       d5[0], [r7], r2       @ Vector load from src[5_0]
    vaddl.u8      q5, d0, d5
    vmlal.u8      q5, d2, d30
    vmlal.u8      q5, d3, d30
    vmlsl.u8      q5, d1, d31
    vmlsl.u8      q5, d4, d31
    vld1.32       {q6}, [r6], r2        @load for horz filter row 0
    vext.8        d17, d12, d13, #5
    vext.8        d14, d12, d13, #2
    vext.8        d15, d12, d13, #3
    vext.8        d16, d12, d13, #4
    vext.8        d13, d12, d13, #1
    vqrshrun.s16  d26, q5, #5
    vld1.32       d6[0], [r7], r2       @ Vector load from src[6_0]
    vaddl.u8      q5, d12, d17
    vmlal.u8      q5, d14, d30
    vmlal.u8      q5, d15, d30
    vmlsl.u8      q5, d13, d31
    vmlsl.u8      q5, d16, d31
    vld1.32       {q6}, [r6], r2        @horz row 1
    vaddl.u8      q9, d1, d6
    vmlal.u8      q9, d3, d30
    vmlal.u8      q9, d4, d30
    vmlsl.u8      q9, d2, d31
    vmlsl.u8      q9, d5, d31
    vqrshrun.s16  d28, q5, #5
    vext.8        d17, d12, d13, #5
    vext.8        d14, d12, d13, #2
    vext.8        d15, d12, d13, #3
    vext.8        d16, d12, d13, #4
    vext.8        d13, d12, d13, #1
    vqrshrun.s16  d27, q9, #5
    vaddl.u8      q5, d12, d17
    vmlal.u8      q5, d14, d30
    vmlal.u8      q5, d15, d30
    vmlsl.u8      q5, d13, d31
    vmlsl.u8      q5, d16, d31
    vqrshrun.s16  d29, q5, #5
    vrhadd.u8     q13, q13, q14
    vst1.32       d26[0], [r1], r3
    vst1.32       d27[0], [r1], r3

    subs          r4, r4, #2            @ 2 rows processed, decrement by 2
    subne         r7, r7 , r2, lsl #2
    subne         r7, r7, r2
    beq           end_func              @ Branch if height==4
    b             loop_4                @ Loop if height==8
end_func:
    vldmia        sp!, {d8-d15}         @ Restore neon registers that were saved
    ldmfd         sp!, {r4-r12, pc}     @Restoring registers from stack


