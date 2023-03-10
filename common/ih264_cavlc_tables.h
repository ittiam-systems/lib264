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
* @file ih264_cavlc_tables.h
*
* @brief
*  This file contains enumerations, macros and extern declarations of H264
*  cavlc tables
*
* @author
*  Ittiam
*
*  @remarks
*   none
******************************************************************************
*/

#ifndef IH264_CAVLC_TABLES_H_
#define IH264_CAVLC_TABLES_H_

/*****************************************************************************/
/* Constant Macros                                                           */
/*****************************************************************************/
/**
******************************************************************************
*  @brief  maximum zeros left
******************************************************************************
*/
#define MAX_ZERO_LEFT 6

/*****************************************************************************/
/* Extern global declarations                                                */
/*****************************************************************************/

/**
 ******************************************************************************
 * @brief  Assignment of cbp to a codenum for intra and inter prediction modes
 * chroma format idc != 0
 * input  : cbp, intra - 0/inter - 1
 * output : codenum
 * @remarks Table 9-4 � Assignment of codeNum to values of coded_block_pattern
 * for macroblock prediction modes in H264 spec
 ******************************************************************************
 */
extern const UWORD8 gu1_cbp_map_tables[48][2];

/**
 ******************************************************************************
 * @brief  total non-zero coefficients and numbers of trailing ones of a
 *residual block are mapped to coefftoken using the tables given below. input  :
 *VLC-Num  | Trailing ones | Total coeffs output : coeff_token (code word, size
 *of the code word)
 * @remarks Table-9-5 coeff_token mapping to TotalCoeff( coeff_token )
 * and TrailingOnes( coeff_token ) in H264 spec
 ******************************************************************************
 */
extern const UWORD8 gu1_code_coeff_token_table[3][4][16];
extern const UWORD8 gu1_size_coeff_token_table[3][4][16];
extern const UWORD8 gu1_code_coeff_token_table_chroma[4][4];
extern const UWORD8 gu1_size_coeff_token_table_chroma[4][4];

/**
 ******************************************************************************
 * @brief  Thresholds for determining whether to increment Level table number.
 * input  : suffix_length
 * output : threshold
 ******************************************************************************
 */
extern const UWORD8 gu1_threshold_vlc_level[6];

/**
 ******************************************************************************
 * @brief  table for encoding total number of zeros
 * input  : coeff_token, total zeros
 * output : code word, size of the code word
 * @remarks Table-9-7, 9-8  total_zeros tables for 4x4 blocks with
 * TotalCoeff( coeff_token ) in H264 spec
 ******************************************************************************
 */
extern const UWORD8 gu1_size_zero_table[135];
extern const UWORD8 gu1_code_zero_table[135];
extern const UWORD8 gu1_size_zero_table_chroma[9];
extern const UWORD8 gu1_code_zero_table_chroma[9];

/**
 ******************************************************************************
 * @brief  index to access zero table (for speed)
 * input  : TotalCoeff( coeff_token )
 * output : index to access zero table
 ******************************************************************************
 */
extern const UWORD8 gu1_index_zero_table[15];

/**
 ******************************************************************************
 * @brief  table for encoding runs of zeros before
 * input  : zeros left, runs of zeros before
 * output : code word, size of the code word
 * @remarks Table-9-10  table for run_before in H264 spec
 ******************************************************************************
 */
extern const UWORD8 gu1_size_run_table[42];
extern const UWORD8 gu1_code_run_table[42];

/**
 ******************************************************************************
 * @brief  index to access run table (look up)
 * input  : zeros left
 * output : index to access run table
 ******************************************************************************
 */
extern const UWORD8 gu1_index_run_table[7];

#endif /* IH264_CAVLC_TABLES_H_ */
