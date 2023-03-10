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
@*  ih264_intra_pred_luma_4x4_a9q.s
@*
@* @brief
@*  Contains function definitions for intra 4x4 Luma prediction .
@*
@* @author
@*  Ittiam
@*
@* @par List of Functions:
@*
@*  -ih264_intra_pred_luma_4x4_mode_vert_a9q
@*  -ih264_intra_pred_luma_4x4_mode_horz_a9q
@*  -ih264_intra_pred_luma_4x4_mode_dc_a9q
@*  -ih264_intra_pred_luma_4x4_mode_diag_dl_a9q
@*  -ih264_intra_pred_luma_4x4_mode_diag_dr_a9q
@*  -ih264_intra_pred_luma_4x4_mode_vert_r_a9q
@*  -ih264_intra_pred_luma_4x4_mode_horz_d_a9q
@*  -ih264_intra_pred_luma_4x4_mode_vert_l_a9q
@*  -ih264_intra_pred_luma_4x4_mode_horz_u_a9q
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@*

@* All the functions here are replicated from ih264_intra_pred_filters.c
@

.text
.p2align 2


@**
@*******************************************************************************
@*
@*ih264_intra_pred_luma_4x4_mode_vert
@*
@* @brief
@*  Perform Intra prediction for  luma_4x4 mode:vertical
@*
@* @par Description:
@* Perform Intra prediction for  luma_4x4 mode:vertical ,described in sec 8.3.1.2.1
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
@* @param[in] ui_neighboravailability
@* availability of neighbouring pixels(Not used in this function)
@*
@* @returns
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@void ih264_intra_pred_luma_4x4_mode_vert(UWORD8 *pu1_src,
@                                        UWORD8 *pu1_dst,
@                                        WORD32 src_strd,
@                                        WORD32 dst_strd,
@                                        WORD32 ui_neighboravailability)

@**************Variables Vs Registers*****************************************
@   r0 => *pu1_src
@   r1 => *pu1_dst
@   r2 =>  src_strd
@   r3 =>  dst_strd
@   r4 =>  ui_neighboravailability

    .global ih264_intra_pred_luma_4x4_mode_vert_a9q

ih264_intra_pred_luma_4x4_mode_vert_a9q:



    stmfd         sp!, {r4-r12, r14}    @store register values to stack

    add           r0, r0, #5

    vld1.32       d0[0], [r0]

    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3



    ldmfd         sp!, {r4-r12, pc}     @Restoring registers from stack





@******************************************************************************


@**
@*******************************************************************************
@*
@*ih264_intra_pred_luma_4x4_mode_horz
@*
@* @brief
@*  Perform Intra prediction for  luma_4x4 mode:horizontal
@*
@* @par Description:
@*  Perform Intra prediction for  luma_4x4 mode:horizontal ,described in sec 8.3.1.2.2
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
@* @param[in] ui_neighboravailability
@* availability of neighbouring pixels(Not used in this function)
@*
@* @returns
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@*
@void ih264_intra_pred_luma_4x4_mode_horz(UWORD8 *pu1_src,
@                                         UWORD8 *pu1_dst,
@                                         WORD32 src_strd,
@                                         WORD32 dst_strd,
@                                         WORD32 ui_neighboravailability)
@**************Variables Vs Registers*****************************************
@   r0 => *pu1_src
@   r1 => *pu1_dst
@   r2 =>  src_strd
@   r3 =>  dst_strd
@   r4 =>  ui_neighboravailability



    .global ih264_intra_pred_luma_4x4_mode_horz_a9q

ih264_intra_pred_luma_4x4_mode_horz_a9q:



    stmfd         sp!, {r4-r12, r14}    @store register values to stack
    add           r0, r0, #3
    mov           r2 , #-1

    ldrb          r5, [r0], r2
    vdup.u8       d0, r5
    ldrb          r6, [r0], r2
    vst1.32       d0[0], [r1], r3
    vdup.u8       d1, r6
    ldrb          r7, [r0], r2
    vst1.32       d1[0], [r1], r3
    vdup.u8       d2, r7
    ldrb          r8, [r0], r2
    vst1.32       d2[0], [r1], r3
    vdup.u8       d3, r8
    vst1.32       d3[0], [r1], r3


    ldmfd         sp!, {r4-r12, pc}     @Restoring registers from stack







@******************************************************************************


@**
@*******************************************************************************
@*
@*ih264_intra_pred_luma_4x4_mode_dc
@*
@* @brief
@*  Perform Intra prediction for  luma_4x4 mode:DC
@*
@* @par Description:
@*  Perform Intra prediction for  luma_4x4 mode:DC ,described in sec 8.3.1.2.3
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
@* @param[in] ui_neighboravailability
@*  availability of neighbouring pixels
@*
@* @returns
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@void ih264_intra_pred_luma_4x4_mode_dc(UWORD8 *pu1_src,
@                                       UWORD8 *pu1_dst,
@                                       WORD32 src_strd,
@                                       WORD32 dst_strd,
@                                       WORD32 ui_neighboravailability)

@**************Variables Vs Registers*****************************************
@   r0 => *pu1_src
@   r1 => *pu1_dst
@   r2 =>  src_strd
@   r3 =>  dst_strd
@   r4 =>  ui_neighboravailability



    .global ih264_intra_pred_luma_4x4_mode_dc_a9q

ih264_intra_pred_luma_4x4_mode_dc_a9q:



    stmfd         sp!, {r4-r12, r14}    @store register values to stack
    ldr           r4, [sp, #40]         @   r4 =>  ui_neighboravailability

    ands          r5, r4, #0x01
    beq           top_available         @LEFT NOT AVAILABLE

    add           r10, r0, #3
    mov           r2, #-1
    ldrb          r5, [r10], r2
    ldrb          r6, [r10], r2
    ldrb          r7, [r10], r2
    add           r5, r5, r6
    ldrb          r8, [r10], r2
    add           r5, r5, r7
    ands          r11, r4, #0x04        @ CHECKING IF TOP_AVAILABLE  ELSE BRANCHING TO ONLY LEFT AVAILABLE
    add           r5, r5, r8
    beq           left_available
    add           r10, r0, #5
    @    BOTH LEFT AND TOP AVAILABLE
    ldrb          r6, [r10], #1
    ldrb          r7, [r10], #1
    add           r5, r5, r6
    ldrb          r8, [r10], #1
    add           r5, r5, r7
    ldrb          r9, [r10], #1
    add           r5, r5, r8
    add           r5, r5, r9
    add           r5, r5, #4
    lsr           r5, r5, #3
    vdup.u8       d0, r5
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    b             end_func

top_available: @ ONLT TOP AVAILABLE
    ands          r11, r4, #0x04        @ CHECKING TOP AVAILABILTY  OR ELSE BRANCH TO NONE AVAILABLE
    beq           none_available

    add           r10, r0, #5
    ldrb          r6, [r10], #1
    ldrb          r7, [r10], #1
    ldrb          r8, [r10], #1
    add           r5, r6, r7
    ldrb          r9, [r10], #1
    add           r5, r5, r8
    add           r5, r5, r9
    add           r5, r5, #2
    lsr           r5, r5, #2
    vdup.u8       d0, r5
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    b             end_func

left_available: @ONLY LEFT AVAILABLE
    add           r5, r5, #2
    lsr           r5, r5, #2
    vdup.u8       d0, r5
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    b             end_func

none_available:                         @NONE AVAILABLE
    mov           r5, #128
    vdup.u8       d0, r5
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    vst1.32       d0[0], [r1], r3
    b             end_func


end_func:
    ldmfd         sp!, {r4-r12, pc}     @Restoring registers from stack







@**
@*******************************************************************************
@*
@*ih264_intra_pred_luma_4x4_mode_diag_dl
@*
@* @brief
@*  Perform Intra prediction for  luma_4x4 mode:Diagonal_Down_Left
@*
@* @par Description:
@*  Perform Intra prediction for  luma_4x4 mode:Diagonal_Down_Left ,described in sec 8.3.1.2.4
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
@* @param[in] ui_neighboravailability
@*  availability of neighbouring pixels
@*
@* @returns
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@void ih264_intra_pred_luma_4x4_mode_diag_dl(UWORD8 *pu1_src,
@                                            UWORD8 *pu1_dst,
@                                            WORD32 src_strd,
@                                            WORD32 dst_strd,
@                                            WORD32 ui_neighboravailability)

@**************Variables Vs Registers*****************************************
@   r0 => *pu1_src
@   r1 => *pu1_dst
@   r2 =>  src_strd
@   r3 =>  dst_strd
@   r4 =>  ui_neighboravailability


    .global ih264_intra_pred_luma_4x4_mode_diag_dl_a9q

ih264_intra_pred_luma_4x4_mode_diag_dl_a9q:

    stmfd         sp!, {r4-r12, r14}    @store register values to stack

    add           r0, r0, #5
    sub           r5, r3, #2
    add           r6, r0, #7
    vld1.8        {d0}, [r0]
    vext.8        d1, d0, d0, #1
    vext.8        d2, d0, d0, #2
    vld1.8        {d2[6]}, [r6]
    vaddl.u8      q10, d0, d1
    vaddl.u8      q11, d1, d2
    vadd.u16      q12, q10, q11
    vqrshrun.s16  d3, q12, #2
    vst1.32       {d3[0]}, [r1], r3
    vext.8        d4, d3, d3, #1
    vst1.32       {d4[0]}, [r1], r3
    vst1.16       {d3[1]}, [r1]!
    vst1.16       {d3[2]}, [r1], r5
    vst1.16       {d4[1]}, [r1]!
    vst1.16       {d4[2]}, [r1]

end_func_diag_dl:
    ldmfd         sp!, {r4-r12, pc}     @Restoring registers from stack









@**
@*******************************************************************************
@*
@*ih264_intra_pred_luma_4x4_mode_diag_dr
@*
@* @brief
@* Perform Intra prediction for  luma_4x4 mode:Diagonal_Down_Right
@*
@* @par Description:
@*  Perform Intra prediction for  luma_4x4 mode:Diagonal_Down_Right ,described in sec 8.3.1.2.5
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
@* @param[in] ui_neighboravailability
@*  availability of neighbouring pixels
@*
@* @returns
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@void ih264_intra_pred_luma_4x4_mode_diag_dr(UWORD8 *pu1_src,
@                                            UWORD8 *pu1_dst,
@                                            WORD32 src_strd,
@                                            WORD32 dst_strd,
@                                            WORD32 ui_neighboravailability)

@**************Variables Vs Registers*****************************************
@   r0 => *pu1_src
@   r1 => *pu1_dst
@   r2 =>  src_strd
@   r3 =>  dst_strd
@   r4 =>  ui_neighboravailability


    .global ih264_intra_pred_luma_4x4_mode_diag_dr_a9q

ih264_intra_pred_luma_4x4_mode_diag_dr_a9q:

    stmfd         sp!, {r4-r12, r14}    @store register values to stack


    vld1.u8       {d0}, [r0]
    add           r0, r0, #1
    vld1.u8       {d1}, [r0]
    vext.8        d2, d1, d1, #1
    vaddl.u8      q10, d0, d1
    vaddl.u8      q11, d1, d2
    vadd.u16      q12, q10, q11
    vqrshrun.s16  d3, q12, #2

    vext.8        d4, d3, d3, #1
    sub           r5, r3, #2
    vst1.16       {d4[1]}, [r1]!
    vst1.16       {d4[2]}, [r1], r5
    vst1.16       {d3[1]}, [r1]!
    vst1.16       {d3[2]}, [r1], r5
    vst1.32       {d4[0]}, [r1], r3
    vst1.32       {d3[0]}, [r1], r3

end_func_diag_dr:
    ldmfd         sp!, {r4-r12, pc}     @Restoring registers from stack







@**
@*******************************************************************************
@*
@*ih264_intra_pred_luma_4x4_mode_vert_r
@*
@* @brief
@* Perform Intra prediction for  luma_4x4 mode:Vertical_Right
@*
@* @par Description:
@*   Perform Intra prediction for  luma_4x4 mode:Vertical_Right ,described in sec 8.3.1.2.6
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
@* @param[in] ui_neighboravailability
@*  availability of neighbouring pixels
@*
@* @returns
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@void ih264_intra_pred_luma_4x4_mode_vert_r(UWORD8 *pu1_src,
@                                            UWORD8 *pu1_dst,
@                                            WORD32 src_strd,
@                                            WORD32 dst_strd,
@                                            WORD32 ui_neighboravailability)

@**************Variables Vs Registers*****************************************
@   r0 => *pu1_src
@   r1 => *pu1_dst
@   r2 =>  src_strd
@   r3 =>  dst_strd
@   r4 =>  ui_neighboravailability


    .global ih264_intra_pred_luma_4x4_mode_vert_r_a9q

ih264_intra_pred_luma_4x4_mode_vert_r_a9q:

    stmfd         sp!, {r4-r12, r14}    @store register values to stack


    vld1.u8       {d0}, [r0]
    add           r0, r0, #1
    vld1.u8       {d1}, [r0]
    vext.8        d2, d1, d1, #1
    vaddl.u8      q10, d0, d1
    vaddl.u8      q11, d1, d2
    vadd.u16      q12, q10, q11
    vqrshrun.s16  d4, q10, #1
    vqrshrun.s16  d3, q12, #2
    sub           r5, r3, #2
    vext.8        d5, d3, d3, #3
    vst1.32       {d4[1]}, [r1], r3
    vst1.32       {d5[0]}, [r1], r3
    sub           r8, r3, #3
    vst1.u8       {d3[2]}, [r1]!
    vst1.16       {d4[2]}, [r1]!
    vst1.u8       {d4[6]}, [r1], r8
    vst1.u8       {d3[1]}, [r1]!
    vst1.16       {d5[0]}, [r1]!
    vst1.u8       {d5[2]}, [r1]


end_func_vert_r:
    ldmfd         sp!, {r4-r12, pc}     @Restoring registers from stack





@**
@*******************************************************************************
@*
@*ih264_intra_pred_luma_4x4_mode_horz_d
@*
@* @brief
@* Perform Intra prediction for  luma_4x4 mode:Horizontal_Down
@*
@* @par Description:
@*   Perform Intra prediction for  luma_4x4 mode:Horizontal_Down ,described in sec 8.3.1.2.7
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
@* @param[in] ui_neighboravailability
@*  availability of neighbouring pixels
@*
@* @returns
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@void ih264_intra_pred_luma_4x4_mode_horz_d(UWORD8 *pu1_src,
@                                            UWORD8 *pu1_dst,
@                                            WORD32 src_strd,
@                                            WORD32 dst_strd,
@                                            WORD32 ui_neighboravailability)

@**************Variables Vs Registers*****************************************
@   r0 => *pu1_src
@   r1 => *pu1_dst
@   r2 =>  src_strd
@   r3 =>  dst_strd
@   r4 =>  ui_neighboravailability


    .global ih264_intra_pred_luma_4x4_mode_horz_d_a9q

ih264_intra_pred_luma_4x4_mode_horz_d_a9q:

    stmfd         sp!, {r4-r12, r14}    @store register values to stack

    vld1.u8       {d0}, [r0]
    add           r0, r0, #1
    vld1.u8       {d1}, [r0]
    vext.8        d2, d1, d0, #1
    vaddl.u8      q10, d0, d1
    vaddl.u8      q11, d1, d2
    vadd.u16      q12, q10, q11
    vqrshrun.s16  d4, q10, #1
    vqrshrun.s16  d5, q12, #2
    sub           r5, r3, #2
    vmov.8        d6, d5
    vtrn.8        d4, d5                @
    vst1.u16      {d5[1]}, [r1]!
    vst1.16       {d6[2]}, [r1], r5
    vst1.u16      {d4[1]}, [r1]!
    vst1.16       {d5[1]}, [r1], r5
    vst1.u16      {d5[0]}, [r1]!
    vst1.16       {d4[1]}, [r1], r5
    vst1.u16      {d4[0]}, [r1]!
    vst1.16       {d5[0]}, [r1], r5

end_func_horz_d:
    ldmfd         sp!, {r4-r12, pc}     @Restoring registers from stack







@**
@*******************************************************************************
@*
@*ih264_intra_pred_luma_4x4_mode_vert_l
@*
@* @brief
@*  Perform Intra prediction for  luma_4x4 mode:Vertical_Left
@*
@* @par Description:
@*   Perform Intra prediction for  luma_4x4 mode:Vertical_Left ,described in sec 8.3.1.2.8
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
@* @param[in] ui_neighboravailability
@*  availability of neighbouring pixels
@*
@* @returns
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@void ih264_intra_pred_luma_4x4_mode_vert_l(UWORD8 *pu1_src,
@                                            UWORD8 *pu1_dst,
@                                            WORD32 src_strd,
@                                            WORD32 dst_strd,
@                                            WORD32 ui_neighboravailability)

@**************Variables Vs Registers*****************************************
@   r0 => *pu1_src
@   r1 => *pu1_dst
@   r2 =>  src_strd
@   r3 =>  dst_strd
@   r4 =>  ui_neighboravailability


    .global ih264_intra_pred_luma_4x4_mode_vert_l_a9q

ih264_intra_pred_luma_4x4_mode_vert_l_a9q:

    stmfd         sp!, {r4-r12, r14}    @store register values to stack
    add           r0, r0, #4
    vld1.u8       {d0}, [r0]
    add           r0, r0, #1
    vld1.u8       {d1}, [r0]
    vext.8        d2, d1, d0, #1
    vaddl.u8      q10, d0, d1
    vaddl.u8      q11, d1, d2
    vadd.u16      q12, q10, q11
    vqrshrun.s16  d4, q10, #1
    vqrshrun.s16  d5, q12, #2
    vext.8        d6, d4, d4, #1
    vext.8        d7, d5, d5, #1
    vst1.32       {d6[0]}, [r1], r3
    vext.8        d16, d4, d4, #2
    vext.8        d17, d5, d5, #2
    vst1.32       {d7[0]}, [r1], r3
    vst1.32       {d16[0]}, [r1], r3
    vst1.32       {d17[0]}, [r1], r3



end_func_vert_l:
    ldmfd         sp!, {r4-r12, pc}     @Restoring registers from stack







@**
@*******************************************************************************
@*
@*ih264_intra_pred_luma_4x4_mode_horz_u
@*
@* @brief
@*     Perform Intra prediction for  luma_4x4 mode:Horizontal_Up
@*
@* @par Description:
@*      Perform Intra prediction for  luma_4x4 mode:Horizontal_Up ,described in sec 8.3.1.2.9
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
@* @param[in] ui_neighboravailability
@*  availability of neighbouring pixels
@*
@* @returns
@*
@* @remarks
@*  None
@*
@*******************************************************************************
@void ih264_intra_pred_luma_4x4_mode_horz_u(UWORD8 *pu1_src,
@                                           UWORD8 *pu1_dst,
@                                           WORD32 src_strd,
@                                           WORD32 dst_strd,
@                                           WORD32 ui_neighboravailability)

@**************Variables Vs Registers*****************************************
@   r0 => *pu1_src
@   r1 => *pu1_dst
@   r2 =>  src_strd
@   r3 =>  dst_strd
@   r4 =>  ui_neighboravailability


    .global ih264_intra_pred_luma_4x4_mode_horz_u_a9q

ih264_intra_pred_luma_4x4_mode_horz_u_a9q:

    stmfd         sp!, {r4-r12, r14}    @store register values to stack
    mov           r10, r0
    vld1.u8       {d0}, [r0]
    ldrb          r9, [r0], #1
    vext.8        d1, d0, d0, #1
    vld1.u8       {d0[7]}, [r10]
    vext.8        d2, d1, d1, #1
    vaddl.u8      q10, d0, d1
    vaddl.u8      q11, d1, d2
    vadd.u16      q12, q10, q11
    vqrshrun.s16  d4, q10, #1
    vqrshrun.s16  d5, q12, #2
    vmov          d6, d4
    vext.8        d6, d5, d4, #1
    vst1.8        {d4[2]}, [r1]!
    vst1.8        {d6[0]}, [r1]!
    vtrn.8        d6, d5                @
    sub           r5, r3, #2
    vtrn.8        d4, d6                @
    vdup.8        d7, r9
    vst1.16       {d6[0]}, [r1], r5
    vst1.16       {d6[0]}, [r1]!
    vst1.16       {d5[3]}, [r1], r5
    vst1.16       {d5[3]}, [r1]!
    vst1.16       {d7[3]}, [r1], r5
    vst1.32       {d7[0]}, [r1], r3

end_func_horz_u:
    ldmfd         sp!, {r4-r12, pc}     @Restoring registers from stack


