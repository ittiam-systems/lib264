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
*  ih264_common_tables.h
*
* @brief
*  Common tables
*
* @author
*  Harish
*
* @par List of Functions:
*
* @remarks
*  None
*
*******************************************************************************
*/

#ifndef _IH264_COMMON_TABLES_H_
#define _IH264_COMMON_TABLES_H_

/*****************************************************************************/
/* Structures                                                                */
/*****************************************************************************/

/**
******************************************************************************
*  @brief      level tables
******************************************************************************
*/
typedef struct {
  /* level */
  IH264_LEVEL_T u4_level_idc;

  /* max macroblock processing rate */
  UWORD32 u4_max_mbps;

  /* max frame size in mbs */
  UWORD32 u4_max_fs;

  /* max dpb size / 768 */
  UWORD32 u4_max_dpb_size;

  /* max bit rate */
  UWORD32 u4_max_br;

  /* max cpb size */
  UWORD32 u4_max_cpb_size;

  /* max vertical MV component range */
  UWORD32 u4_max_mv_y;

} level_tables_t;

/*****************************************************************************/
/* Extern global declarations                                                */
/*****************************************************************************/

/**
 ******************************************************************************
 * @brief  while encoding, basing on the input configuration parameters, the
 * the level of the bitstream is computed basing on the table below.
 * input  : table_idx
 * output : level_idc or cpb size
 * @remarks Table A-1 � level table limits
 ******************************************************************************
 */
extern const level_tables_t gas_ih264_lvl_tbl[16];

extern const WORD32 gai4_ih264_levels[];
extern const WORD32 gai4_ih264_max_luma_pic_size[];
extern const WORD32 gai4_ih264_max_wd_ht[];
extern const WORD32 gai4_ih264_min_wd_ht[];

extern intra_mbtype_info_t gas_ih264_i_mbtype_info[];
extern inter_mbtype_info_t gas_ih264_p_mbtype_info[];
extern inter_mbtype_info_t gas_ih264_b_mbtype_info[];
extern submbtype_info_t gas_ih264_p_submbtype_info[];
extern submbtype_info_t gas_ih264_b_submbtype_info[];

extern const UWORD8 gau1_ih264_inv_scan_prog4x4[];
extern const UWORD8 gau1_ih264_inv_scan_int4x4[];
extern const UWORD8 gau1_ih264_inv_scan_prog8x8_cavlc[64];
extern const UWORD8 gau1_ih264_inv_scan_int8x8_cavlc[64];
extern const UWORD8 gau1_ih264_inv_scan_prog8x8_cabac[64];
extern const UWORD8 gau1_ih264_inv_scan_int8x8_cabac[64];

extern const UWORD8 *gpau1_ih264_inv_scan8x8[];
extern const UWORD8 *gpau1_ih264_inv_scan4x4[];

extern const UWORD8 gau1_ih264_8x8_subblk_idx[];

extern const UWORD8 gau1_ih264_chroma_qp[];

extern const UWORD8 gau1_ih264_4x4_ngbr_avbl[16][16];
extern const UWORD8 gau1_ih264_8x8_ngbr_avbl[16][4];

extern const UWORD16 gau2_ih264_default_inter4x4_weight_scale[];
extern const UWORD16 gau2_ih264_default_intra4x4_weight_scale[];
extern const UWORD16 gau2_ih264_default_intra4x4_scaling_list[];
extern const UWORD16 gau2_ih264_default_inter4x4_scaling_list[];
extern const UWORD16 gau2_ih264_default_intra8x8_scaling_list[];
extern const UWORD16 gau2_ih264_default_inter8x8_scaling_list[];
extern const UWORD16 gau2_ih264_default_intra8x8_weight_scale[];
extern const UWORD16 gau2_ih264_default_inter8x8_weight_scale[];
extern const UWORD16 gau2_ih264_flat_4x4_weight_scale[];
extern const UWORD16 gau2_ih264_flat_8x8_weight_scale[];

extern const UWORD16 gau2_ih264_iquant_scale_matrix_4x4[96];
extern const UWORD16 gau2_ih264_iquant_scale_matrix_8x8[384];

#endif /*_IH264_COMMON_TABLES_H_*/
