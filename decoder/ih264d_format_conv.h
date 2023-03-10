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
/*****************************************************************************/
/*                                                                           */
/*  File Name         : ih264d_format_conv.h                                */
/*                                                                           */
/*  Description       : Contains coefficients and constant reqquired for     */
/*                      converting from rgb and gray color spaces to yuv422i */
/*                      color space                                          */
/*                                                                           */
/*  List of Functions : None                                                 */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         27 08 2007  Naveen Kumar T        Draft                           */
/*                                                                           */
/*****************************************************************************/

#ifndef _IH264D_FORMAT_CONV_H_
#define _IH264D_FORMAT_CONV_H_

/*****************************************************************************/
/* Typedefs                                                                  */
/*****************************************************************************/

#define COEFF_0_Y 66
#define COEFF_1_Y 129
#define COEFF_2_Y 25
#define COEFF_0_U -38
#define COEFF_1_U -75
#define COEFF_2_U 112
#define COEFF_0_V 112
#define COEFF_1_V -94
#define COEFF_2_V -18
#define CONST_RGB_YUV1 4096
#define CONST_RGB_YUV2 32768
#define CONST_GRAY_YUV 128
#define COEF_2_V2_U 0xFFEE0070

#define COF_2Y_0Y 0X00190042
#define COF_1U_0U 0XFFB5FFDA
#define COF_1V_0V 0XFFA20070

void ih264d_fmt_conv_420sp_to_420p(UWORD8 *pu1_y_src, UWORD8 *pu1_uv_src,
                                   UWORD8 *pu1_y_dst, UWORD8 *pu1_u_dst,
                                   UWORD8 *pu1_v_dst, WORD32 wd, WORD32 ht,
                                   WORD32 src_y_strd, WORD32 src_uv_strd,
                                   WORD32 dst_y_strd, WORD32 dst_uv_strd,
                                   WORD32 is_u_first, WORD32 disable_luma_copy);

void ih264d_fmt_conv_420sp_to_420sp_swap_uv(
    UWORD8 *pu1_y_src, UWORD8 *pu1_uv_src, UWORD8 *pu1_y_dst,
    UWORD8 *pu1_uv_dst, WORD32 wd, WORD32 ht, WORD32 src_y_strd,
    WORD32 src_uv_strd, WORD32 dst_y_strd, WORD32 dst_uv_strd);

void ih264d_fmt_conv_420sp_to_420sp(UWORD8 *pu1_y_src, UWORD8 *pu1_uv_src,
                                    UWORD8 *pu1_y_dst, UWORD8 *pu1_uv_dst,
                                    WORD32 wd, WORD32 ht, WORD32 src_y_strd,
                                    WORD32 src_uv_strd, WORD32 dst_y_strd,
                                    WORD32 dst_uv_strd);

void ih264d_fmt_conv_420sp_to_rgb565(UWORD8 *pu1_y_src, UWORD8 *pu1_uv_src,
                                     UWORD16 *pu2_rgb_dst, WORD32 wd, WORD32 ht,
                                     WORD32 src_y_strd, WORD32 src_uv_strd,
                                     WORD32 dst_strd, WORD32 is_u_first);
#define COEFF1 13073
#define COEFF2 -3207
#define COEFF3 -6664
#define COEFF4 16530

void ih264d_format_convert(dec_struct_t *ps_dec,
                           ivd_get_display_frame_op_t *pv_disp_op,
                           UWORD32 u4_start_y, UWORD32 u4_num_rows_y);

#endif /* _IH264D_FORMAT_CONV_H_ */
