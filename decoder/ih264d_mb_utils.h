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
#ifndef _IH264D_MB_UTILS_H_
#define _IH264D_MB_UTILS_H_
/*!
 **************************************************************************
 * \file ih264d_mb_utils.h
 *
 * \brief
 *    Contains declarations of the utility functions needed to decode MB
 *
 * \date
 *    18/12/2002
 *
 * \author  AI
 **************************************************************************
 */
#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264d_structs.h"

/*--------------------------------------------------------------------*/
/* Macros to get raster scan position of a block[8x8] / sub block[4x4]*/
/*--------------------------------------------------------------------*/

#define GET_BLK_RASTER_POS_X(x) ((x & 0x01) << 1)
#define GET_BLK_RASTER_POS_Y(y) ((y >> 1) << 1)
#define GET_SUB_BLK_RASTER_POS_X(x) ((x & 0x01))
#define GET_SUB_BLK_RASTER_POS_Y(y) ((y >> 1))

/*--------------------------------------------------------------------*/
/* Masks used in decoding of Macroblock                               */
/*--------------------------------------------------------------------*/

#define LEFT_MB_AVAILABLE_MASK 0x01
#define TOP_LEFT_MB_AVAILABLE_MASK 0x02
#define TOP_MB_AVAILABLE_MASK 0x04
#define TOP_RIGHT_MB_AVAILABLE_MASK 0x08

#define TOP_RT_SUBBLOCK_MASK_MOD 0xFFF7

#define TOP_RIGHT_DEFAULT_AVAILABLE 0x5750
#define TOP_RIGHT_TOPR_AVAILABLE 0x0008
#define TOP_RIGHT_TOP_AVAILABLE 0x0007

#define TOP_LEFT_DEFAULT_AVAILABLE 0xEEE0
#define TOP_LEFT_TOPL_AVAILABLE 0x0001
#define TOP_LEFT_TOP_AVAILABLE 0x000E
#define TOP_LEFT_LEFT_AVAILABLE 0x1110

#define CHECK_MB_MAP(u4_mb_num, mb_map, u4_cond)        \
  {                                                     \
    UWORD32 u4_bit_number;                              \
    volatile UWORD8 *pu1_mb_flag;                       \
                                                        \
    u4_bit_number = u4_mb_num & 0x07;                   \
    pu1_mb_flag = (UWORD8 *) mb_map + (u4_mb_num >> 3); \
                                                        \
    u4_cond = CHECKBIT((*pu1_mb_flag), u4_bit_number);  \
  }

#define CHECK_MB_MAP_BYTE(u4_mb_num, mb_map, u4_cond) \
  {                                                   \
    volatile UWORD8 *pu1_mb_flag;                     \
                                                      \
    pu1_mb_flag = (UWORD8 *) mb_map + (u4_mb_num);    \
                                                      \
    u4_cond = (*pu1_mb_flag);                         \
  }

#define UPDATE_MB_MAP(u2_frm_wd_in_mbs, u2_mbx, u2_mby, mb_map, mb_count)                       \
  {                                                                                             \
    UWORD32 u4_bit_number;                                                                      \
    UWORD32 u4_mb_number;                                                                       \
                                                                                                \
    u4_mb_number = u2_frm_wd_in_mbs * (u2_mby >> u1_mbaff) + u2_mbx;                            \
                                                                                                \
    u4_bit_number = u4_mb_number & 0x07;                                                        \
    /*                                                                                          \
     * In case of MbAff, update the mb_map only if the entire MB is done. We                    \
     * can check that by checking if Y is odd, implying that this is the                        \
     * second row in the MbAff MB                                                               \
     */                                                                                         \
    SET_BIT(mb_map[u4_mb_number >> 3], u4_bit_number);                                          \
                                                                                                \
    if (1 == u1_mbaff) {                                                                        \
      /*                                                                                        \
       * If MBAFF u4_flag is set, set this MB and the MB just below this.                       \
       * So, add frame width to the MB number and set that bit.                                 \
       */                                                                                       \
      /*                                                                                        \
      u4_mb_number    += u2_frm_wd_in_mbs;                                                      \
                                                                                              \ \
      u4_bit_number = u4_mb_number & 0x07;                                                      \
                                                                                              \ \
      SET_BIT(mb_map[u4_mb_number >> 3], u4_bit_number);                                        \
      */                                                                                        \
    }                                                                                           \
                                                                                                \
    /*H264_DEC_DEBUG_PRINT("SETBIT: %d\n", u4_mb_number);*/                                     \
    mb_count++;                                                                                 \
  }

#define UPDATE_MB_MAP_MBNUM(mb_map, u4_mb_number)                            \
  {                                                                          \
    UWORD32 u4_bit_number;                                                   \
    volatile UWORD8 *pu1_mb_flag;                                            \
                                                                             \
    u4_bit_number = u4_mb_number & 0x07;                                     \
    pu1_mb_flag = (UWORD8 *) mb_map + (u4_mb_number >> 3);                   \
    /*                                                                       \
     * In case of MbAff, update the mb_map only if the entire MB is done. We \
     * can check that by checking if Y is odd, implying that this is the     \
     * second row in the MbAff MB                                            \
     */                                                                      \
    SET_BIT((*pu1_mb_flag), u4_bit_number);                                  \
  }

#define UPDATE_MB_MAP_MBNUM_BYTE(mb_map, u4_mb_number)                       \
  {                                                                          \
    volatile UWORD8 *pu1_mb_flag;                                            \
                                                                             \
    pu1_mb_flag = (UWORD8 *) mb_map + (u4_mb_number);                        \
    /*                                                                       \
     * In case of MbAff, update the mb_map only if the entire MB is done. We \
     * can check that by checking if Y is odd, implying that this is the     \
     * second row in the MbAff MB                                            \
     */                                                                      \
    (*pu1_mb_flag) = 1;                                                      \
  }

#define UPDATE_SLICE_NUM_MAP(slice_map, u4_mb_number, u2_slice_num) \
  {                                                                 \
    volatile UWORD16 *pu2_slice_map;                                \
                                                                    \
    pu2_slice_map = (UWORD16 *) slice_map + (u4_mb_number);         \
    (*pu2_slice_map) = u2_slice_num;                                \
  }

#define GET_SLICE_NUM_MAP(slice_map, mb_number, u2_slice_num) \
  {                                                           \
    volatile UWORD16 *pu2_slice_map;                          \
                                                              \
    pu2_slice_map = (UWORD16 *) slice_map + (mb_number);      \
    u2_slice_num = (*pu2_slice_map);                          \
  }

#define GET_XPOS_PRED(u1_out, pkd_info) \
  {                                     \
    WORD32 bit_field;                   \
    bit_field = pkd_info & 0x3;         \
    u1_out = bit_field;                 \
  }

#define GET_YPOS_PRED(u1_out, pkd_info) \
  {                                     \
    WORD32 bit_field;                   \
    bit_field = pkd_info >> 2;          \
    u1_out = bit_field & 0x3;           \
  }

#define GET_WIDTH_PRED(u1_out, pkd_info)       \
  {                                            \
    WORD32 bit_field;                          \
    bit_field = pkd_info >> 4;                 \
    bit_field = (bit_field & 0x3) << 1;        \
    u1_out = (bit_field == 0) ? 1 : bit_field; \
  }

#define GET_HEIGHT_PRED(u1_out, pkd_info)      \
  {                                            \
    WORD32 bit_field;                          \
    bit_field = pkd_info >> 6;                 \
    bit_field = (bit_field & 0x3) << 1;        \
    u1_out = (bit_field == 0) ? 1 : bit_field; \
  }

/*!
 **************************************************************************
 *   \brief   Masks for elements present in the first column but not on the
 *   first row.
 **************************************************************************
 */
#define FIRST_COL_NOT_FIRST_ROW 0xFAFB
#define FIRST_ROW_MASK 0xFFCC
/*!
 **************************************************************************
 *   \brief   Mask for elements presen in the first row but not in the
 *   last column.
 **************************************************************************
 */
#define FIRST_ROW_NOT_LAST_COL 0xFFEC
/*!
 **************************************************************************
 *   \brief   Mask for elements presen in the first row but not in the
 *   first column.
 **************************************************************************
 */
#define FIRST_ROW_NOT_FIRST_COL 0xFFCD
/*!
 **************************************************************************
 *   \brief   Masks for the top right subMB of a 4x4 block
 **************************************************************************
 */
#define TOP_RT_SUBBLOCK_MASK 0xFFDF
/*!
 **************************************************************************
 *   \brief   Masks for the top left subMB of a 4x4 block
 **************************************************************************
 */
#define TOP_LT_SUBBLOCK_MASK 0xFFFE
/*!
 **************************************************************************
 *   \brief   Indicates if a subMB has a top right subMB available
 **************************************************************************
 */
#define TOP_RT_SUBBLOCK_MB_MASK 0x5F4C

#define FIRST_COL_MASK 0xFAFA

/*--------------------------------------------------------------------*/
/* Macros to calculate the current position of a MB wrt picture       */
/*--------------------------------------------------------------------*/
#define MB_LUMA_PIC_OFFSET(mb_x, mb_y, frmWidthY) \
  (((mb_y) * (frmWidthY) + (mb_x)) << 4)
#define MB_CHROMA_PIC_OFFSET(mb_x, mb_y, frmWidthUV) \
  (((mb_y) * (frmWidthUV) + (mb_x)) << 3)

/*--------------------------------------------------------------------*/
/* Macros to calculate the current position of a MB wrt N[ Num coeff] Array */
/*--------------------------------------------------------------------*/
#define MB_PARAM_OFFSET(mb_x, mb_y, frmWidthInMbs, u1_mbaff, u1_topmb) \
  ((mb_x << u1_mbaff) + (1 - u1_topmb) + (mb_y * frmWidthInMbs))

UWORD32 ih264d_get_mb_info_cavlc_mbaff(dec_struct_t *ps_dec,
                                       const UWORD16 ui16_curMbAddress,
                                       dec_mb_info_t *ps_cur_mb_info,
                                       UWORD32 u4_mbskip_run);
UWORD32 ih264d_get_mb_info_cavlc_nonmbaff(dec_struct_t *ps_dec,
                                          const UWORD16 ui16_curMbAddress,
                                          dec_mb_info_t *ps_cur_mb_info,
                                          UWORD32 u4_mbskip_run);

UWORD32 ih264d_get_mb_info_cabac_mbaff(dec_struct_t *ps_dec,
                                       const UWORD16 ui16_curMbAddress,
                                       dec_mb_info_t *ps_cur_mb_info,
                                       UWORD32 u4_mbskip_run);

UWORD32 ih264d_get_mb_info_cabac_nonmbaff(dec_struct_t *ps_dec,
                                          const UWORD16 ui16_curMbAddress,
                                          dec_mb_info_t *ps_cur_mb_info,
                                          UWORD32 u4_mbskip_run);

UWORD8 get_cabac_context_non_mbaff(dec_struct_t *ps_dec, UWORD16 u2_mbskip);

UWORD32 ih264d_get_cabac_context_mbaff(dec_struct_t *ps_dec,
                                       dec_mb_info_t *ps_cur_mb_info,
                                       UWORD32 u4_mbskip);

WORD32 PutMbToFrame(dec_struct_t *ps_dec);
void ih264d_get_mbaff_neighbours(dec_struct_t *ps_dec,
                                 dec_mb_info_t *ps_cur_mb_info,
                                 UWORD8 uc_curMbFldDecFlag);

void ih264d_update_mbaff_left_nnz(dec_struct_t *ps_dec,
                                  dec_mb_info_t *ps_cur_mb_info);
void ih264d_transfer_mb_group_data(
    dec_struct_t *ps_dec, const WORD8 c_numMbs,
    const UWORD8 u1_end_of_row,     /* Cur n-Mb End of Row Flag */
    const UWORD8 u1_end_of_row_next /* Next n-Mb End of Row Flag */
);

// void FillRandomData(UWORD8 *pu1_buf, WORD32 u4_bufSize);

#endif /* _MB_UTILS_H_ */
