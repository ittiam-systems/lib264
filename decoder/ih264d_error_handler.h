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

#ifndef _IH264D_ERROR_HANDLER_H_
#define _IH264D_ERROR_HANDLER_H_

/*!
 *************************************************************************
 * \file ih264d_error_handler.h
 *
 * \brief
 *    Contains declaration of ih264d_global_error_handler function
 *
 * \date
 *    21/11/2002
 *
 * \author  AI
 *************************************************************************
 */

#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"

typedef enum {

  ERROR_MEM_ALLOC_ISRAM_T = 0x50,
  ERROR_MEM_ALLOC_SDRAM_T = 0x51,
  ERROR_BUF_MGR = 0x52,
  ERROR_DBP_MANAGER_T = 0x53,
  ERROR_GAPS_IN_FRM_NUM = 0x54,
  ERROR_UNKNOWN_NAL = 0x55,
  ERROR_INV_MB_SLC_GRP_T = 0x56,
  ERROR_MULTIPLE_SLC_GRP_T = 0x57,
  ERROR_UNKNOWN_LEVEL = 0x58,
  ERROR_FEATURE_UNAVAIL = 0x59,
  ERROR_NOT_SUPP_RESOLUTION = 0x5A,
  ERROR_INVALID_PIC_PARAM = 0x5B,
  ERROR_INVALID_SEQ_PARAM = 0x5C,
  ERROR_EGC_EXCEED_32_1_T = 0x5D,
  ERROR_EGC_EXCEED_32_2_T = 0x5E,
  ERROR_INV_RANGE_TEV_T = 0x5F,
  ERROR_INV_SLC_TYPE_T = 0x60,
  ERROR_UNAVAIL_PICBUF_T = 0x61,
  ERROR_UNAVAIL_MVBUF_T = 0x62,
  ERROR_UNAVAIL_DISPBUF_T = 0x63,
  ERROR_INV_POC_TYPE_T = 0x64,
  ERROR_PIC1_NOT_FOUND_T = 0x65,
  ERROR_PIC0_NOT_FOUND_T = 0x66,
  ERROR_NUM_REF = 0x67,
  ERROR_REFIDX_ORDER_T = 0x68,
  ERROR_EOB_FLUSHBITS_T = 0x69,
  ERROR_EOB_GETBITS_T = 0x6A,
  ERROR_EOB_GETBIT_T = 0x6B,
  ERROR_EOB_BYPASS_T = 0x6C,
  ERROR_EOB_DECISION_T = 0x6D,
  ERROR_EOB_TERMINATE_T = 0x6E,
  ERROR_EOB_READCOEFF4X4CAB_T = 0x6F,
  ERROR_INV_RANGE_QP_T = 0x70,
  ERROR_END_OF_FRAME_EXPECTED_T = 0x71,
  ERROR_MB_TYPE = 0x72,
  ERROR_SUB_MB_TYPE = 0x73,
  ERROR_CBP = 0x74,
  ERROR_REF_IDX = 0x75,
  ERROR_NUM_MV = 0x76,
  ERROR_CHROMA_PRED_MODE = 0x77,
  ERROR_INTRAPRED = 0x78,
  ERROR_NEXT_MB_ADDRESS_T = 0x79,
  ERROR_MB_ADDRESS_T = 0x7A,
  ERROR_MB_GROUP_ASSGN_T = 0x7B,
  ERROR_CAVLC_NUM_COEFF_T = 0x7C,
  ERROR_CAVLC_SCAN_POS_T = 0x7D,
  ERROR_CABAC_RENORM_T = 0x7E,
  ERROR_CABAC_SIG_COEFF1_T = 0x7F,
  ERROR_CABAC_SIG_COEFF2_T = 0x80,
  ERROR_CABAC_ENCODE_COEFF_T = 0x81,
  ERROR_INV_SPS_PPS_T = 0x82,
  ERROR_INV_SLICE_HDR_T = 0x83,
  ERROR_PRED_WEIGHT_TABLE_T = 0x84,
  IH264D_VERS_BUF_INSUFFICIENT = 0x85,
  ERROR_ACTUAL_LEVEL_GREATER_THAN_INIT = 0x86,
  ERROR_CORRUPTED_SLICE = 0x87,
  ERROR_FRAME_LIMIT_OVER = 0x88,
  ERROR_ACTUAL_RESOLUTION_GREATER_THAN_INIT = 0x89,
  ERROR_PROFILE_NOT_SUPPORTED = 0x8A,
  ERROR_DISP_WIDTH_RESET_TO_PIC_WIDTH = 0x8B,
  ERROR_DISP_WIDTH_INVALID = 0x8C,
  ERROR_DANGLING_FIELD_IN_PIC = 0x8D,
  ERROR_DYNAMIC_RESOLUTION_NOT_SUPPORTED = 0x8E,
  ERROR_INIT_NOT_DONE = 0x8F,
  ERROR_LEVEL_UNSUPPORTED = 0x90,
  ERROR_START_CODE_NOT_FOUND = 0x91,
  ERROR_PIC_NUM_IS_REPEATED = 0x92,
  ERROR_SEI_MDCV_PARAMS_NOT_FOUND = 0x98,
  ERROR_SEI_CLLI_PARAMS_NOT_FOUND = 0x99,
  ERROR_INV_SEI_MDCV_PARAMS = 0x9A,
  ERROR_INV_SEI_CLLI_PARAMS = 0x9B,

} h264_decoder_error_code_t;

#endif /* _IH264D_ERROR_HANDLER_H_ */
