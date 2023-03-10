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
@ *  ih264_padding_neon.s
@ *
@ * @brief
@ *  Contains function definitions padding
@ *
@ * @author
@ *  Ittiam
@ *
@ * @par List of Functions:
@ *  - ih264_pad_top_a9q()
@ *  - ih264_pad_left_luma_a9q()
@ *  - ih264_pad_left_chroma_a9q()
@ *  - ih264_pad_right_luma_a9q()
@ *  - ih264_pad_right_chroma_a9q()
@ *
@ * @remarks
@ *  None
@ *
@ *******************************************************************************
@*


@**
@*******************************************************************************
@*
@* @brief pad at the top of a 2d array
@*
@* @par Description:
@*  The top row of a 2d array is replicated for pad_size times at the top
@*
@* @param[in] pu1_src
@*  UWORD8 pointer to the source
@*
@* @param[in] src_strd
@*  integer source stride
@*
@* @param[in] wd
@*  integer width of the array
@*
@* @param[in] pad_size
@*  integer -padding size of the array
@*
@* @returns none
@*
@* @remarks none
@*
@*******************************************************************************
@*
@void ih264_pad_top(UWORD8 *pu1_src,
@                   WORD32 src_strd,
@                   WORD32 wd,
@                   WORD32 pad_size)
@**************Variables Vs Registers*************************
@   r0 => *pu1_src
@   r1 => src_strd
@   r2 => wd
@   r3 => pad_size

.text
.p2align 2

    .global ih264_pad_top_a9q

ih264_pad_top_a9q:

    stmfd         sp!, {r4-r11, lr}     @stack stores the values of the arguments

    sub           r5, r0, r1
    neg           r6, r1

loop_neon_memcpy_mul_16:
    @ Load 16 bytes
    vld1.8        {d0, d1}, [r0]!
    mov           r4, r5
    mov           r7, r3
    add           r5, r5, #16

loop_neon_pad_top:
    vst1.8        {d0, d1}, [r4], r6
    subs          r7, r7, #1
    bne           loop_neon_pad_top

    subs          r2, r2, #16
    bne           loop_neon_memcpy_mul_16

    ldmfd         sp!, {r4-r11, pc}     @Reload the registers from SP




@**
@*******************************************************************************
@*
@* @brief
@*   Padding (luma block) at the left of a 2d array
@*
@* @par Description:
@*   The left column of a 2d array is replicated for pad_size times at the left
@*
@*
@* @param[in] pu1_src
@*  UWORD8 pointer to the source
@*
@* @param[in] src_strd
@*  integer source stride
@*
@* @param[in] ht
@*  integer height of the array
@*
@* @param[in] wd
@*  integer width of the array
@*
@* @param[in] pad_size
@*  integer -padding size of the array
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
@#if PAD_LEFT_LUMA == C
@void ih264_pad_left_luma(UWORD8 *pu1_src,
@                        WORD32 src_strd,
@                        WORD32 ht,
@                        WORD32 pad_size)
@**************Variables Vs Registers*************************
@   r0 => *pu1_src
@   r1 => src_strd
@   r2 => ht
@   r3 => pad_size



    .global ih264_pad_left_luma_a9q

ih264_pad_left_luma_a9q:

    stmfd         sp!, {r4-r11, lr}     @stack stores the values of the arguments


    sub           r4, r0, r3
    sub           r6, r1, #16
    subs          r5, r3, #16
    bne           loop_32
loop_16:                                @  /*hard coded for width=16  ,height =8,16*/
    ldrb          r8, [r0], r1
    ldrb          r9, [r0], r1
    vdup.u8       q0, r8
    ldrb          r10, [r0], r1
    vst1.8        {q0}, [r4], r1        @ 16 bytes store
    vdup.u8       q1, r9
    vst1.8        {q1}, [r4], r1        @ 16 bytes store
    ldrb          r11, [r0], r1
    vdup.u8       q2, r10
    vdup.u8       q3, r11
    vst1.8        {q2}, [r4], r1        @ 16 bytes store
    ldrb          r8, [r0], r1
    vst1.8        {q3}, [r4], r1        @ 16 bytes store
    ldrb          r9, [r0], r1
    vdup.u8       q0, r8
    ldrb          r10, [r0], r1
    vst1.8        {q0}, [r4], r1        @ 16 bytes store
    vdup.u8       q1, r9
    ldrb          r11, [r0], r1
    vst1.8        {q1}, [r4], r1        @ 16 bytes store
    vdup.u8       q2, r10
    vdup.u8       q3, r11
    subs          r2, r2, #8
    vst1.8        {q2}, [r4], r1        @ 16 bytes store
    vst1.8        {q3}, [r4], r1        @ 16 bytes store
    bne           loop_16
    b             end_func

loop_32:                                @  /*hard coded for width=32 ,height =8,16*/
    ldrb          r8, [r0], r1
    ldrb          r9, [r0], r1
    vdup.u8       q0, r8
    ldrb          r10, [r0], r1
    vst1.8        {q0}, [r4]!           @ 16 bytes store
    vdup.u8       q1, r9
    vst1.8        {q0}, [r4], r6
    vst1.8        {q1}, [r4]!           @ 16 bytes store
    vdup.u8       q2, r10
    vst1.8        {q1}, [r4], r6        @ 16 bytes store
    ldrb          r11, [r0], r1
    vst1.8        {q2}, [r4]!           @ 16 bytes store
    vdup.u8       q3, r11
    vst1.8        {q2}, [r4], r6        @ 16 bytes store
    ldrb          r8, [r0], r1
    vst1.8        {q3}, [r4]!           @ 16 bytes store
    vdup.u8       q0, r8
    ldrb          r9, [r0], r1
    vst1.8        {q3}, [r4], r6        @ 16 bytes store
    ldrb          r10, [r0], r1
    vst1.8        {q0}, [r4]!           @ 16 bytes store
    vdup.u8       q1, r9
    vst1.8        {q0}, [r4], r6        @ 16 bytes store
    ldrb          r11, [r0], r1
    vst1.8        {q1}, [r4]!           @ 16 bytes store
    vdup.u8       q2, r10
    vst1.8        {q1}, [r4], r6        @ 16 bytes store
    vst1.8        {q2}, [r4]!           @ 16 bytes store
    vdup.u8       q3, r11
    vst1.8        {q2}, [r4], r6        @ 16 bytes store
    subs          r2, r2, #8
    vst1.8        {q3}, [r4]!           @ 16 bytes store
    vst1.8        {q3}, [r4], r6        @ 16 bytes store
    bne           loop_32



end_func:
    ldmfd         sp!, {r4-r11, pc}     @Reload the registers from SP





@**
@*******************************************************************************
@*
@* @brief
@*   Padding (chroma block) at the left of a 2d array
@*
@* @par Description:
@*   The left column of a 2d array is replicated for pad_size times at the left
@*
@*
@* @param[in] pu1_src
@*  UWORD8 pointer to the source
@*
@* @param[in] src_strd
@*  integer source stride
@*
@* @param[in] ht
@*  integer height of the array
@*
@* @param[in] wd
@*  integer width of the array (each colour component)
@*
@* @param[in] pad_size
@*  integer -padding size of the array
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
@#if PAD_LEFT_CHROMA == C
@void ih264_pad_left_chroma(UWORD8 *pu1_src,
@                            WORD32 src_strd,
@                            WORD32 ht,
@                            WORD32 pad_size)
@{
@   r0 => *pu1_src
@   r1 => src_strd
@   r2 => ht
@   r3 => pad_size



    .global ih264_pad_left_chroma_a9q

ih264_pad_left_chroma_a9q:

    stmfd         sp!, {r4-r11, lr}     @stack stores the values of the arguments

    sub           r4, r0, r3
    sub           r6, r1, #16


loop_32_l_c:                            @  /*hard coded for width=32  ,height =4,8,12*/
    ldrh          r8, [r0], r1
    ldrh          r9, [r0], r1
    vdup.u16      q0, r8
    ldrh          r10, [r0], r1
    vst1.8        {q0}, [r4]!           @ 16 bytes store
    vdup.u16      q1, r9
    vst1.8        {q0}, [r4], r6        @ 16 bytes store
    ldrh          r11, [r0], r1
    vst1.8        {q1}, [r4]!           @ 16 bytes store
    vdup.u16      q2, r10
    vst1.8        {q1}, [r4], r6        @ 16 bytes store
    vdup.u16      q3, r11
    vst1.8        {q2}, [r4]!           @ 16 bytes store
    vst1.8        {q2}, [r4], r6        @ 16 bytes store
    subs          r2, r2, #4
    vst1.8        {q3}, [r4]!           @ 16 bytes store
    vst1.8        {q3}, [r4], r6        @ 16 bytes store


    beq           end_func_l_c          @/* Branching when ht=4*/

    ldrh          r8, [r0], r1
    ldrh          r9, [r0], r1
    vdup.u16      q0, r8
    ldrh          r10, [r0], r1
    vst1.8        {q0}, [r4]!           @ 16 bytes store
    vdup.u16      q1, r9
    vst1.8        {q0}, [r4], r6
    ldrh          r11, [r0], r1
    vst1.8        {q1}, [r4]!           @ 16 bytes store
    vdup.u16      q2, r10
    vst1.8        {q1}, [r4], r6        @ 16 bytes store
    vdup.u16      q3, r11
    vst1.8        {q2}, [r4]!           @ 16 bytes store
    vst1.8        {q2}, [r4], r6        @ 16 bytes store
    subs          r2, r2, #4
    vst1.8        {q3}, [r4]!           @ 16 bytes store
    vst1.8        {q3}, [r4], r6        @ 16 bytes store

    beq           end_func_l_c          @/* Branching when ht=8*/
    bne           loop_32_l_c

    ldrh          r8, [r0], r1
    ldrh          r9, [r0], r1
    vdup.u16      q0, r8
    ldrh          r10, [r0], r1
    vst1.8        {q0}, [r4]!           @ 16 bytes store
    vdup.u16      q1, r9
    vst1.8        {q0}, [r4], r6
    ldrh          r11, [r0], r1
    vst1.8        {q1}, [r4]!           @ 16 bytes store
    vdup.u16      q2, r10
    vst1.8        {q1}, [r4], r6        @ 16 bytes store
    vdup.u16      q3, r11
    vst1.8        {q2}, [r4]!           @ 16 bytes store
    vst1.8        {q2}, [r4], r6        @ 16 bytes store
    vst1.8        {q3}, [r4]!           @ 16 bytes store
    vst1.8        {q3}, [r4], r6        @ 16 bytes store

end_func_l_c:
    ldmfd         sp!, {r4-r11, pc}     @Reload the registers from SP





@**
@*******************************************************************************
@*
@* @brief
@* Padding (luma block) at the right of a 2d array
@*
@* @par Description:
@* The right column of a 2d array is replicated for pad_size times at the right
@*
@*
@* @param[in] pu1_src
@*  UWORD8 pointer to the source
@*
@* @param[in] src_strd
@*  integer source stride
@*
@* @param[in] ht
@*  integer height of the array
@*
@* @param[in] wd
@*  integer width of the array
@*
@* @param[in] pad_size
@*  integer -padding size of the array
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
@#if PAD_RIGHT_LUMA == C
@void ih264_pad_right_luma(UWORD8 *pu1_src,
@                        WORD32 src_strd,
@                        WORD32 ht,
@                        WORD32 pad_size)
@{
@    WORD32 row;
@
@    for(row = 0; row < ht; row++)
@    {
@        memset(pu1_src, *(pu1_src -1), pad_size);
@
@        pu1_src += src_strd;
@    }
@}
@
@   r0 => *pu1_src
@   r1 => src_strd
@   r2 => ht
@   r3 => pad_size



    .global ih264_pad_right_luma_a9q

ih264_pad_right_luma_a9q:

    stmfd         sp!, {r4-r11, lr}     @stack stores the values of the arguments

    mov           r4, r0
    sub           r6, r1, #16
    sub           r0, r0, #1
    subs          r5, r3, #16
    bne           loop_32
loop_16_r: @  /*hard coded for width=16  ,height =8,16*/
    ldrb          r8, [r0], r1
    ldrb          r9, [r0], r1
    vdup.u8       q0, r8
    ldrb          r10, [r0], r1
    vst1.8        {q0}, [r4], r1        @ 16 bytes store
    vdup.u8       q1, r9
    vst1.8        {q1}, [r4], r1        @ 16 bytes store
    ldrb          r11, [r0], r1
    vdup.u8       q2, r10
    vdup.u8       q3, r11
    vst1.8        {q2}, [r4], r1        @ 16 bytes store
    ldrb          r8, [r0], r1
    vst1.8        {q3}, [r4], r1        @ 16 bytes store
    ldrb          r9, [r0], r1
    vdup.u8       q0, r8
    ldrb          r10, [r0], r1
    vst1.8        {q0}, [r4], r1        @ 16 bytes store
    vdup.u8       q1, r9
    ldrb          r11, [r0], r1
    vst1.8        {q1}, [r4], r1        @ 16 bytes store
    vdup.u8       q2, r10
    vdup.u8       q3, r11
    subs          r2, r2, #8
    vst1.8        {q2}, [r4], r1        @ 16 bytes store
    vst1.8        {q3}, [r4], r1        @ 16 bytes store
    bne           loop_16_r
    b             end_func_r

loop_32_r:                              @  /*hard coded for width=32  ,height =8,16*/
    ldrb          r8, [r0], r1
    ldrb          r9, [r0], r1
    vdup.u8       q0, r8
    ldrb          r10, [r0], r1
    vst1.8        {q0}, [r4]!           @ 16 bytes store
    vdup.u8       q1, r9
    vst1.8        {q0}, [r4], r6
    vst1.8        {q1}, [r4]!           @ 16 bytes store
    vdup.u8       q2, r10
    vst1.8        {q1}, [r4], r6        @ 16 bytes store
    ldrb          r11, [r0], r1
    vst1.8        {q2}, [r4]!           @ 16 bytes store
    vdup.u8       q3, r11
    vst1.8        {q2}, [r4], r6        @ 16 bytes store
    ldrb          r8, [r0], r1
    vst1.8        {q3}, [r4]!           @ 16 bytes store
    ldrb          r9, [r0], r1
    vdup.u8       q0, r8
    vst1.8        {q3}, [r4], r6        @ 16 bytes store
    ldrb          r10, [r0], r1
    vst1.8        {q0}, [r4]!           @ 16 bytes store
    vdup.u8       q1, r9
    vst1.8        {q0}, [r4], r6        @ 16 bytes store
    ldrb          r11, [r0], r1
    vst1.8        {q1}, [r4]!           @ 16 bytes store
    vdup.u8       q2, r10
    vst1.8        {q1}, [r4], r6        @ 16 bytes store
    vst1.8        {q2}, [r4]!           @ 16 bytes store
    vdup.u8       q3, r11
    vst1.8        {q2}, [r4], r6        @ 16 bytes store
    subs          r2, r2, #8
    vst1.8        {q3}, [r4]!           @ 16 bytes store
    vst1.8        {q3}, [r4], r6        @ 16 bytes store
    bne           loop_32_r



end_func_r:
    ldmfd         sp!, {r4-r11, pc}     @Reload the registers from SP





@**
@*******************************************************************************
@*
@* @brief
@;* Padding (chroma block) at the right of a 2d array
@*
@* @par Description:
@* The right column of a 2d array is replicated for pad_size times at the right
@*
@*
@* @param[in] pu1_src
@;*  UWORD8 pointer to the source
@*
@* @param[in] src_strd
@*  integer source stride
@*
@* @param[in] ht
@;*  integer height of the array
@*
@* @param[in] wd
@*  integer width of the array (each colour component)
@*
@* @param[in] pad_size
@*  integer -padding size of the array
@*
@* @param[in] ht
@;*  integer height of the array
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
@#if PAD_RIGHT_CHROMA == C
@void ih264_pad_right_chroma(UWORD8 *pu1_src,
@                        WORD32 src_strd,
@                        WORD32 ht,
@                        WORD32 pad_size)
@   r0 => *pu1_src
@   r1 => src_strd
@   r2 => ht
@   r3 => pad_size



    .global ih264_pad_right_chroma_a9q

ih264_pad_right_chroma_a9q:

    stmfd         sp!, {r4-r11, lr}     @stack stores the values of the arguments

    mov           r4, r0
    sub           r6, r1, #16
    sub           r0, r0, #2
loop_32_r_c: @  /*hard coded for width=32 ,height =8,4*/
    ldrh          r8, [r0], r1
    ldrh          r9, [r0], r1
    vdup.u16      q0, r8
    ldrh          r10, [r0], r1
    vst1.8        {q0}, [r4]!           @ 16 bytes store
    vdup.u16      q1, r9
    vst1.8        {q0}, [r4], r6
    vst1.8        {q1}, [r4]!           @ 16 bytes store
    vdup.u16      q2, r10
    vst1.8        {q1}, [r4], r6        @ 16 bytes store
    subs          r2, r2, #4
    ldrh          r11, [r0], r1
    vst1.8        {q2}, [r4]!           @ 16 bytes store
    vdup.u16      q3, r11
    vst1.8        {q2}, [r4], r6        @ 16 bytes store
    vst1.8        {q3}, [r4]!           @ 16 bytes store
    vst1.8        {q3}, [r4], r6        @ 16 bytes store

    beq           end_func_r_c          @/* Branching when ht=4*/

    ldrh          r8, [r0], r1
    vdup.u16      q0, r8
    ldrh          r9, [r0], r1
    ldrh          r10, [r0], r1
    vst1.8        {q0}, [r4]!           @ 16 bytes store
    vdup.u16      q1, r9
    vst1.8        {q0}, [r4], r6        @ 16 bytes store
    ldrh          r11, [r0], r1
    vst1.8        {q1}, [r4]!           @ 16 bytes store
    vdup.u16      q2, r10
    vst1.8        {q1}, [r4], r6        @ 16 bytes store
    vst1.8        {q2}, [r4]!           @ 16 bytes store
    vdup.u16      q3, r11
    vst1.8        {q2}, [r4], r6        @ 16 bytes store
    subs          r2, r2, #4
    vst1.8        {q3}, [r4]!           @ 16 bytes store
    vst1.8        {q3}, [r4], r6        @ 16 bytes store

    beq           end_func_r_c          @/* Branching when ht=8*/
    bne           loop_32_r_c

    ldrh          r8, [r0], r1
    vdup.u16      q0, r8
    ldrh          r9, [r0], r1
    ldrh          r10, [r0], r1
    vst1.8        {q0}, [r4]!           @ 16 bytes store
    vdup.u16      q1, r9
    vst1.8        {q0}, [r4], r6        @ 16 bytes store
    ldrh          r11, [r0], r1
    vst1.8        {q1}, [r4]!           @ 16 bytes store
    vdup.u16      q2, r10
    vst1.8        {q1}, [r4], r6        @ 16 bytes store
    vst1.8        {q2}, [r4]!           @ 16 bytes store
    vdup.u16      q3, r11
    vst1.8        {q2}, [r4], r6        @ 16 bytes store
    vst1.8        {q3}, [r4]!           @ 16 bytes store
    vst1.8        {q3}, [r4], r6        @ 16 bytes store

end_func_r_c:
    ldmfd         sp!, {r4-r11, pc}     @Reload the registers from SP





