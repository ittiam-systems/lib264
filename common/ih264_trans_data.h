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
/**
 *******************************************************************************
 * @file
 *  ih264_trans_data.h
 *
 * @brief
 *  Contains declaration of global variables for H264 transform , qnat and
 *inverse quant
 *
 * @author
 *  Ittiam
 *
 * @remarks
 *
 *******************************************************************************
 */
#ifndef IH264_GLOBAL_DATA_H_
#define IH264_GLOBAL_DATA_H_

/*****************************************************************************/
/* Extern global declarations                                                */
/*****************************************************************************/

/* Scaling matrices for h264 quantization */
extern const UWORD16 g_scal_coff_h264_4x4[16];
extern const UWORD16 g_scal_coff_h264_8x8[16];

/**
 ******************************************************************************
 * @brief  Scale Table for quantizing 4x4 subblock. To quantize a given 4x4 DCT
 * transformed block, the coefficient at index location (i,j) is scaled by one
 *of the constants in this table and right shift the result by (QP_BITS_h264_4x4
 *+ floor(qp/6)), here qp is the quantization parameter used to quantize the mb.
 *
 * input   : qp%6, index location (i,j)
 * output  : scale constant.
 *
 * @remarks 16 constants for each index position of the subblock and 6 for each
 * qp%6 in the range 0-5 inclusive.
 ******************************************************************************
 */
extern const UWORD16 gu2_quant_scale_matrix_4x4[96];

/**
 ******************************************************************************
 * @brief  Round Factor for quantizing subblock. While quantizing a given 4x4
 *DCT transformed block, the coefficient at index location (i,j) is scaled by
 *one of the constants in the table gu2_forward_quant_scalar_4x4 and then right
 *shift the result by (QP_BITS_h264_4x4 + floor(qp/6)). Before right shifting a
 *round factor is added. The round factor can be any value [a * (1 <<
 *(QP_BITS_h264_4x4 + floor(qp/6)))] for 'a' lies in the range 0-0.5. Here qp is
 *the quantization parameter used to quantize the mb.
 *
 * input   : qp/6
 * output  : round factor.
 *
 * @remarks The round factor is constructed by setting a = 1/3
 ******************************************************************************
 */
extern const UWORD32 gu4_forward_quant_round_factor_4x4[9];

/**
 ******************************************************************************
 * @brief  Threshold Table. Quantizing the given DCT coefficient is done only if
 * it exceeds the threshold value presented in this table.
 *
 * input   : qp/6, qp%6, index location (i,j)
 * output  : Threshold constant.
 *
 * @remarks 16 constants for each index position of the subblock and 6 for each
 * qp%6 in the range 0-5 inclusive and 9 for each qp/6 in the range 0-51.
 ******************************************************************************
 */
extern const UWORD16 gu2_forward_quant_threshold_4x4[96];

/**
 ******************************************************************************
 * @brief  Scale Table for quantizing 8x8 subblock. To quantize a given 8x8 DCT
 * transformed block, the coefficient at index location (i,j) is scaled by one
 *of the constants in this table and right shift the result by (QP_BITS_h264_8x8
 *+ floor(qp/6)), here qp is the quantization parameter used to quantize the mb.
 *
 * input   : qp%6, index location (i,j)
 * output  : scale constant.
 *
 * @remarks 64 constants for each index position of the subblock and 6 for each
 * qp%6 in the range 0-5 inclusive.
 ******************************************************************************
 */
extern const UWORD16 gu2_quant_scale_matrix_8x8[384];

/**
 ******************************************************************************
 * @brief  Specification of QPc as a function of qPi
 *
 * input   : qp luma
 * output  : qp chroma.
 *
 * @remarks Refer Table 8-15 of h264 specification.
 ******************************************************************************
 */
extern const UWORD8 gu1_qpc_fqpi[52];

#endif /* IH264_GLOBAL_DATA_H_ */
