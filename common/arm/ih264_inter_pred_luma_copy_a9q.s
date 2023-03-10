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
@/**
@*******************************************************************************
@*
@* @brief
@*     Interprediction luma function for copy
@*
@* @par Description:
@*   Copies the array of width 'wd' and height 'ht' from the  location pointed
@*   by 'src' to the location pointed by 'dst'
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
@void ih264_inter_pred_luma_copy (
@                            UWORD8 *pu1_src,
@                            UWORD8 *pu1_dst,
@                            WORD32 src_strd,
@                            WORD32 dst_strd,
@                            WORD32 ht,
@                            WORD32 wd   )

@**************Variables Vs Registers*****************************************
@   r0 => *pu1_src
@   r1 => *pu1_dst
@   r2 =>  src_strd
@   r3 =>  dst_strd
@   r7 =>  ht
@   r12 => wd

.text
.p2align 2

    .global ih264_inter_pred_luma_copy_a9q

ih264_inter_pred_luma_copy_a9q:
    stmfd         sp!, {r4-r12, r14}    @stack stores the values of the arguments
    vstmdb        sp!, {d8-d15}         @push neon registers to stack
    ldr           r12, [sp, #108]       @Loads wd
    ldr           r7, [sp, #104]        @Loads ht
    cmp           r7, #0                @checks ht == 0
    ble           end_loops
    tst           r12, #15              @checks wd for multiples for 4 & 8
    beq           core_loop_wd_16
    tst           r12, #7               @checks wd for multiples for 4 & 8
    beq           core_loop_wd_8
    sub           r11, r12, #4

outer_loop_wd_4:
    subs          r4, r12, #0           @checks wd == 0
    ble           end_inner_loop_wd_4

inner_loop_wd_4:
    vld1.32       {d0[0]}, [r0]         @vld1_lane_u32((uint32_t *)pu1_src_tmp, src_tmp, 0)
    add           r5, r0, r2            @pu1_src_tmp += src_strd
    add           r6, r1, r3            @pu1_dst_tmp += dst_strd
    vst1.32       {d0[0]}, [r1]         @vst1_lane_u32((uint32_t *)pu1_dst_tmp, src_tmp, 0)
    vld1.32       {d0[0]}, [r5], r2     @vld1_lane_u32((uint32_t *)pu1_src_tmp, src_tmp, 0)
    add           r0, r0, #4            @pu1_src += 4
    vst1.32       {d0[0]}, [r6], r3     @vst1_lane_u32((uint32_t *)pu1_dst_tmp, src_tmp, 0)
    vld1.32       {d0[0]}, [r5], r2     @vld1_lane_u32((uint32_t *)pu1_src_tmp, src_tmp, 0)
    subs          r4, r4, #4            @(wd -4)
    vst1.32       {d0[0]}, [r6], r3     @vst1_lane_u32((uint32_t *)pu1_dst_tmp, src_tmp, 0)
    vld1.32       {d0[0]}, [r5], r2     @vld1_lane_u32((uint32_t *)pu1_src_tmp, src_tmp, 0)
    add           r1, r1, #4            @pu1_dst += 4
    vst1.32       {d0[0]}, [r6], r3     @vst1_lane_u32((uint32_t *)pu1_dst_tmp, src_tmp, 0)

    bgt           inner_loop_wd_4

end_inner_loop_wd_4:
    subs          r7, r7, #4            @ht - 4
    sub           r0, r5, r11           @pu1_src = pu1_src_tmp
    sub           r1, r6, r11           @pu1_dst = pu1_dst_tmp
    bgt           outer_loop_wd_4

end_loops:
    vldmia        sp!, {d8-d15}         @ Restore neon registers that were saved
    ldmfd         sp!, {r4-r12, r15}    @Reload the registers from SP



core_loop_wd_8:
    sub           r11, r12, #8

outer_loop_wd_8:
    subs          r4, r12, #0           @checks wd
    ble           end_inner_loop_wd_8

inner_loop_wd_8:
    add           r5, r0, r2            @pu1_src_tmp += src_strd
    vld1.8        {d0}, [r0]!           @vld1_u8(pu1_src_tmp)
    add           r6, r1, r3            @pu1_dst_tmp += dst_strd
    vst1.8        {d0}, [r1]!           @vst1_u8(pu1_dst_tmp, tmp_src)
    vld1.8        {d1}, [r5], r2        @vld1_u8(pu1_src_tmp)
    vst1.8        {d1}, [r6], r3        @vst1_u8(pu1_dst_tmp, tmp_src)
    subs          r4, r4, #8            @wd - 8(Loop condition)
    vld1.8        {d2}, [r5], r2        @vld1_u8(pu1_src_tmp)
    vst1.8        {d2}, [r6], r3        @vst1_u8(pu1_dst_tmp, tmp_src)
    vld1.8        {d3}, [r5], r2        @vld1_u8(pu1_src_tmp)
    vst1.8        {d3}, [r6], r3        @vst1_u8(pu1_dst_tmp, tmp_src)
    bgt           inner_loop_wd_8

end_inner_loop_wd_8:
    subs          r7, r7, #4            @ht -= 4
    sub           r0, r5, r11           @pu1_src = pu1_src_tmp
    sub           r1, r6, r11           @pu1_dst = pu1_dst_tmp
    bgt           outer_loop_wd_8

    vldmia        sp!, {d8-d15}         @ Restore neon registers that were saved
    ldmfd         sp!, {r4-r12, r15}    @Reload the registers from SP

core_loop_wd_16:
    sub           r11, r12, #16

outer_loop_wd_16:
    subs          r4, r12, #0           @checks wd
    ble           end_inner_loop_wd_16

inner_loop_wd_16:
    add           r5, r0, r2            @pu1_src_tmp += src_strd
    vld1.8        {q0}, [r0]!           @vld1_u8(pu1_src_tmp)
    add           r6, r1, r3            @pu1_dst_tmp += dst_strd
    vst1.8        {q0}, [r1]!           @vst1_u8(pu1_dst_tmp, tmp_src)
    vld1.8        {q1}, [r5], r2        @vld1_u8(pu1_src_tmp)
    vst1.8        {q1}, [r6], r3        @vst1_u8(pu1_dst_tmp, tmp_src)
    subs          r4, r4, #16           @wd - 8(Loop condition)
    vld1.8        {q2}, [r5], r2        @vld1_u8(pu1_src_tmp)
    vst1.8        {q2}, [r6], r3        @vst1_u8(pu1_dst_tmp, tmp_src)
    vld1.8        {q3}, [r5], r2        @vld1_u8(pu1_src_tmp)
    vst1.8        {q3}, [r6], r3        @vst1_u8(pu1_dst_tmp, tmp_src)
    bgt           inner_loop_wd_16

end_inner_loop_wd_16:
    subs          r7, r7, #4            @ht -= 4
    sub           r0, r5, r11           @pu1_src = pu1_src_tmp
    sub           r1, r6, r11           @pu1_dst = pu1_dst_tmp
    bgt           outer_loop_wd_16

    vldmia        sp!, {d8-d15}         @ Restore neon registers that were saved
    ldmfd         sp!, {r4-r12, r15}    @Reload the registers from SP


@ *
@ ********************************************************************************
@ *
@ * @brief This function copies a 4x4 block to destination
@ *
@ * @par Description:
@ * Copies a 4x4 block to destination, where both src and dst are interleaved
@ *
@ * @param[in] pi2_src
@ *  Source
@ *
@ * @param[in] pu1_out
@ *  Output pointer
@ *
@ * @param[in] pred_strd,
@ *  Prediction buffer stride
@ *
@ * @param[in] out_strd
@ *  output buffer buffer Stride
@ *
@ * @returns none
@ *
@ * @remarks none
@ * Currently wd and height is not used, ie a 4x4 block is always copied
@ *
@ *******************************************************************************
@ *
@ void ih264_interleave_copy(WORD16 *pi2_src,
@                            UWORD8 *pu1_out,
@                            WORD32 pred_strd,
@                            WORD32 out_strd
@                            WORD32 wd
@                            WORD32 ht)
@ Register Usage
@ r0 : pi2_src
@ r1 : pu1_out
@ r2 : src_strd
@ r3 : out_strd
@ Neon registers d0-d7, d16-d30 are used
@ No need for pushing  arm and neon registers

    .global ih264_interleave_copy_a9
ih264_interleave_copy_a9:

    vld1.u8       d2, [r0], r2          @load src plane 1 => d2 &pred palne 2 => d3
    vld1.u8       d3, [r0], r2
    vld1.u8       d4, [r0], r2
    vld1.u8       d5, [r0], r2

    mov           r0, r1

    vld1.u8       d18, [r1], r3         @load out [8 bit size) -8 coeffs
    vld1.u8       d19, [r1], r3
    vmov.u16      q15, #0x00ff
    vld1.u8       d20, [r1], r3
    vld1.u8       d21, [r1], r3

    vbit.u8       q9, q1, q15
    vbit.u8       q10, q2, q15

    vst1.u8       d18, [r0], r3         @store  out
    vst1.u8       d19, [r0], r3
    vst1.u8       d20, [r0], r3
    vst1.u8       d21, [r0], r3

    bx            lr



