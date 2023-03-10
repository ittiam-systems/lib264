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
@*  ih264_inter_pred_chroma_a9q.s
@*
@* @brief
@*  Contains function definitions for inter prediction  interpolation.
@*
@* @author
@*  Ittaim
@*
@* @par List of Functions:
@*
@*  - ih264_inter_pred_chroma_a9q()
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
@
@**
@*******************************************************************************
@*
@* @brief
@*    Interprediction chroma filter
@*
@* @par Description:
@*   Applies filtering to chroma samples as mentioned in
@*    sec 8.4.2.2.2 titled "chroma sample interpolation process"
@*
@* @param[in] pu1_src
@*  UWORD8 pointer to the source containing alternate U and V samples
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
@* @param[in]uc_dx
@*  dx value where the sample is to be produced(refer sec 8.4.2.2.2 )
@*
@* @param[in] uc_dy
@*  dy value where the sample is to be produced(refer sec 8.4.2.2.2 )
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

@void ih264_inter_pred_chroma(UWORD8 *pu1_src,
@                             UWORD8 *pu1_dst,
@                             WORD32 src_strd,
@                             WORD32 dst_strd,
@                             WORD32 u1_dx,
@                             WORD32 u1_dy,
@                             WORD32 ht,
@                             WORD32 wd)
@**************Variables Vs Registers*****************************************
@   r0 => *pu1_src
@   r1 => *pu1_dst
@   r2 =>  src_strd
@   r3 =>  dst_strd
@   r4 =>  u1_dx
@   r5 =>  u1_dy
@   r6 =>  height
@   r7 => width
@
.text
.p2align 2

    .global ih264_inter_pred_chroma_a9q

ih264_inter_pred_chroma_a9q:

    stmfd         sp!, {r4-r12, r14}    @store register values to stack
    vstmdb        sp!, {d8-d15}         @push neon registers to stack
    ldr           r4, [sp, #104]
    ldr           r5, [sp, #108]
    ldr           r6, [sp, #112]
    ldr           r7, [sp, #116]

    rsb           r8, r4, #8            @8-u1_dx
    rsb           r9, r5, #8            @8-u1_dy
    mul           r10, r8, r9
    mul           r11, r4, r9

    vdup.u8       d28, r10
    vdup.u8       d29, r11

    mul           r10, r8, r5
    mul           r11, r4, r5

    vdup.u8       d30, r10
    vdup.u8       d31, r11

    subs          r12, r7, #2           @if wd=4 branch to loop_4
    beq           loop_2
    subs          r12, r7, #4           @if wd=8 branch to loop_8
    beq           loop_4

loop_8:
    sub           r6, #1
    vld1.8        {d0, d1, d2}, [r0], r2 @ Load row0
    vld1.8        {d5, d6, d7}, [r0], r2 @ Load row1
    vext.8        d3, d0, d1, #2
    vext.8        d8, d5, d6, #2

    vmull.u8      q5, d0, d28
    vmlal.u8      q5, d5, d30
    vmlal.u8      q5, d3, d29
    vmlal.u8      q5, d8, d31
    vext.8        d9, d6, d7, #2
    vext.8        d4, d1, d2, #2

inner_loop_8:
    vmull.u8      q6, d6, d30
    vmlal.u8      q6, d1, d28
    vmlal.u8      q6, d9, d31
    vmlal.u8      q6, d4, d29
    vmov          d0, d5
    vmov          d3, d8

    vqrshrun.s16  d14, q5, #6
    vmov          d1, d6
    vmov          d4, d9

    vld1.8        {d5, d6, d7}, [r0], r2 @ Load row1
    vqrshrun.s16  d15, q6, #6

    vext.8        d8, d5, d6, #2
    subs          r6, #1
    vext.8        d9, d6, d7, #2
    vst1.8        {q7}, [r1], r3        @ Store dest row

    vmull.u8      q5, d0, d28
    vmlal.u8      q5, d5, d30
    vmlal.u8      q5, d3, d29
    vmlal.u8      q5, d8, d31
    bne           inner_loop_8

    vmull.u8      q6, d6, d30
    vmlal.u8      q6, d1, d28
    vmlal.u8      q6, d9, d31
    vmlal.u8      q6, d4, d29

    vqrshrun.s16  d14, q5, #6
    vqrshrun.s16  d15, q6, #6

    vst1.8        {q7}, [r1], r3        @ Store dest row

    b             end_func

loop_4:
    sub           r6, #1
    vld1.8        {d0, d1}, [r0], r2    @ Load row0
    vld1.8        {d2, d3}, [r0], r2    @ Load row1
    vext.8        d1, d0, d1, #2
    vext.8        d3, d2, d3, #2

    vmull.u8      q2, d2, d30
    vmlal.u8      q2, d0, d28
    vmlal.u8      q2, d3, d31
    vmlal.u8      q2, d1, d29

inner_loop_4:
    subs          r6, #1
    vmov          d0, d2
    vmov          d1, d3

    vld1.8        {d2, d3}, [r0], r2    @ Load row1
    vqrshrun.s16  d6, q2, #6

    vext.8        d3, d2, d3, #2
    vst1.8        {d6}, [r1], r3        @ Store dest row

    vmull.u8      q2, d0, d28
    vmlal.u8      q2, d2, d30
    vmlal.u8      q2, d1, d29
    vmlal.u8      q2, d3, d31
    bne           inner_loop_4

    vqrshrun.s16  d6, q2, #6
    vst1.8        {d6}, [r1], r3        @ Store dest row

    b             end_func

loop_2:
    vld1.8        {d0}, [r0], r2        @ Load row0
    vext.8        d1, d0, d0, #2
    vld1.8        {d2}, [r0], r2        @ Load row1
    vext.8        d3, d2, d2, #2
    vmull.u8      q2, d0, d28
    vmlal.u8      q2, d1, d29
    vmlal.u8      q2, d2, d30
    vmlal.u8      q2, d3, d31
    vld1.8        {d6}, [r0]            @ Load row2
    vqrshrun.s16  d4, q2, #6
    vext.8        d7, d6, d6, #2
    vst1.32       d4[0], [r1], r3       @ Store dest row0
    vmull.u8      q4, d2, d28
    vmlal.u8      q4, d3, d29
    vmlal.u8      q4, d6, d30
    vmlal.u8      q4, d7, d31
    subs          r6, #2
    vqrshrun.s16  d8, q4, #6
    vst1.32       d8[0], [r1], r3       @ Store dest row1
    bne           loop_2                @ repeat if ht=2

end_func:
    vldmia        sp!, {d8-d15}         @ Restore neon registers that were saved
    ldmfd         sp!, {r4-r12, pc}     @ Restoring registers from stack

