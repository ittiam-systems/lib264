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
*  ih264_trans_macros.h
*
* @brief
*  The file contains definitions of macros that perform forward and inverse
*  quantization
*
* @author
*  Ittiam
*
* @remark
*  None
*
*******************************************************************************
*/

#ifndef IH264_TRANS_MACROS_H_
#define IH264_TRANS_MACROS_H_

/*****************************************************************************/
/* Function Macros                                                           */
/*****************************************************************************/

/**
******************************************************************************
*  @brief   Macro to perform forward quantization.
*  @description The value to be quantized is first compared with a threshold.
*  If the value is less than the threshold, the quantization value is returned
*  as zero else the value is quantized traditionally as per the rules of
*  h264 specification
******************************************************************************
*/
#define FWD_QUANT(i4_value, u4_abs_value, i4_sign, threshold, scale, \
                  rndfactor, qbits, u4_nnz)                          \
  {                                                                  \
    if (i4_value < 0) {                                              \
      u4_abs_value = -i4_value;                                      \
      i4_sign = -1;                                                  \
    } else {                                                         \
      u4_abs_value = i4_value;                                       \
      i4_sign = 1;                                                   \
    }                                                                \
    if (u4_abs_value < threshold) {                                  \
      i4_value = 0;                                                  \
    } else {                                                         \
      u4_abs_value *= scale;                                         \
      u4_abs_value += rndfactor;                                     \
      u4_abs_value >>= qbits;                                        \
      i4_value = u4_abs_value * i4_sign;                             \
      if (i4_value) {                                                \
        u4_nnz++;                                                    \
      }                                                              \
    }                                                                \
  }

/**
******************************************************************************
*  @brief   Macro to perform inverse quantization.
*  @remarks The value can also be de-quantized as
*  if (u4_qp_div_6 < 4)
*  {
*      i4_value = (quant_scale * weight_scale * i4_value + (1 <<
*(3-u4_qp_div_6))) i4_value >>= (4 - u4_qp_div_6)
*  }
*  else
*  {
*      i4_value = (quant_scale * weight_scale * i4_value) << (u4_qp_div_6 -4)
*  }
******************************************************************************
*/
#define INV_QUANT(i4_value, quant_scale, weight_scale, u4_qp_div_6, rndfactor, \
                  qbits)                                                       \
  {                                                                            \
    i4_value *= quant_scale;                                                   \
    i4_value *= weight_scale;                                                  \
    i4_value += rndfactor;                                                     \
    i4_value <<= u4_qp_div_6;                                                  \
    i4_value >>= qbits;                                                        \
  }

#define QUANT_H264(x, y, w, z, shft)                      \
  (shft = ABS(x), shft *= y, shft += z, shft = shft >> w, \
   shft = SIGNXY(shft, x))

#define IQUANT_H264(x, y, wscal, w, shft) \
  (shft = x, shft *= y, shft *= wscal, shft = shft << w)

#define IQUANT_lev_H264(x, y, wscal, add_f, w, shft) \
  (shft = x, shft *= y, shft *= wscal, shft += add_f, shft = shft >> w)

#endif /* IH264_TRANS_MACROS_H_ */
