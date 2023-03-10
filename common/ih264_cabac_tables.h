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
******************************************************************************
* @file ih264_cabac_tables.h
*
* @brief
*  This file contains enumerations, macros and extern declarations of H264
*  cabac tables
*
* @author
*  Ittiam
*
* @remarks
*  none
******************************************************************************
*/

#ifndef IH264_CABAC_TABLES_H_
#define IH264_CABAC_TABLES_H_

/*****************************************************************************/
/* Constant Macros                                                           */
/*****************************************************************************/

/**
******************************************************************************
*  @brief  maximum range of cabac_init_idc (0-2)
******************************************************************************
*/
#define IH264_NUM_CABAC_INIT_IDC_PLUS_ONE 4

/**
******************************************************************************
*  @brief  max range of qps in H264 (0-51)
******************************************************************************
*/
#define IH264_MAX_QP 52

/**
******************************************************************************
*  @brief  max range of cabac contexts in H264 (0-459)
******************************************************************************
*/
#define IH264_NUM_CABAC_CTXTS 460

/*****************************************************************************/
/* Extern global declarations                                                */
/*****************************************************************************/

/**
 ******************************************************************************
 * @breif  Table for rangeTabLPS depending on pStateIdx and qCodIRangeIdx
 * input   : pStateIdx(0-63) and qCodIRangeIdx(0-3) [(Range >> 6) & 0x3]
 * output  : RLps
 *
 * @remarks See Table 9-35 of H264 spec for rangeTabLPS
 *******************************************************************************
 */
extern const UWORD8 gau1_ih264_cabac_rlps[64][4];

/**
 ******************************************************************************
 * @breif  probability+MPS state transition tables based on cur State and bin
 * input  : curpState[bits7-2]  | curMPS[bit1] | decodedBin[bit0]
 * output : nextpState[bits6-1] | nextMPS[bit0]
 * @remarks Modified form of Table-9-36 State Transition table in H264 spec
 ******************************************************************************
 */
extern const UWORD8 gau1_ih264_next_state[128 * 2];

/**
 ******************************************************************************
 * @brief  Init context tables for all combinations of qp and cabac_init_idc
 * @remarks Packing format MPS in lsb and pState in bits[1-6]
 ******************************************************************************
 */
extern const UWORD8 gau1_ih264_cab_ctxts[IH264_NUM_CABAC_INIT_IDC_PLUS_ONE]
                                        [IH264_MAX_QP][IH264_NUM_CABAC_CTXTS];

#endif /* IH264_CABAC_TABLES_H_ */
