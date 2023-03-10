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

#ifndef _IH264D_TABLES_H_
#define _IH264D_TABLES_H_

/**
 **************************************************************************
 * \file ih264d_tables.h
 *
 * \brief
 *    Declaration of all tables used by h264 decoder
 *
 * \date
 *    17/09/2004
 *
 * \author  MA
 **************************************************************************
 */
#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264d_cabac.h"

/*Deblocking Table declaration*/
extern const UWORD8 gau1_ih264d_qp_scale_cr[];
extern const UWORD8 gau1_ih264d_alpha_table[];
extern const UWORD8 gau1_ih264d_clip_table_deblock[];
extern const UWORD8 gau1_ih264d_beta_table[];
extern const UWORD8 gau1_ih264d_clip_table[][4];

/*Parsing Table declaration*/
extern const UWORD8 gau1_ih264d_cbp_tab[6];
extern const UWORD32 gau4_ih264d_packed_bs2[16];
extern const UWORD16 gau2_ih264d_4x4_v2h_reorder[16];
extern const UWORD8 gau1_ih264d_subblk_offset[16];
extern const UWORD8 gau1_ih264d_cbp_table[48][2];

/*Decode Slice Table declaration*/
extern const UWORD8 gau1_ih264d_inv_scan[16];
extern const UWORD8 gau1_ih264d_inv_scan_fld[16];
extern const UWORD8 gau1_ih264d_dequant_matrix[6][16];
extern const UWORD16 gau2_ih264_iquant_scale_4x4[6][16];
extern const UWORD8 gau1_ih264d_dequant8x8_zigzag_cavlc[4][6][16];
extern const UWORD16 gau1_ih264d_dequant8x8_cavlc[6][64];

extern const UWORD8 gau1_ih264d_inv_scan_prog8x8_cavlc[4][16];
extern const UWORD8 gau1_ih264d_inv_scan_int8x8_cavlc[4][16];
extern const UWORD8 gau1_ih264d_inv_scan_prog8x8_cabac[64];
extern const UWORD8 gau1_ih264d_inv_scan_int8x8_cabac[64];

extern const UWORD8 gau1_ih264d_lastcoeff_context_inc[64];
extern const UWORD8 gau1_ih264d_sigcoeff_context_inc_frame[64];
extern const UWORD8 gau1_ih264d_sigcoeff_context_inc_field[64];

/* scaling related table declaration */
extern const WORD16 gai2_ih264d_default_intra4x4[16];
extern const WORD16 gai2_ih264d_default_inter4x4[16];
extern const WORD16 gai2_ih264d_default_intra8x8[64];
extern const WORD16 gai2_ih264d_default_inter8x8[64];
extern const WORD16 gai2_ih264d_flat_4x4[16];
extern const WORD16 gai2_ih264d_flat_8x8[64];

/*Decode MV Table declaration*/
extern const WORD8 gau1_ih264d_mv_pred_condition[];

/** Number of subMbs for the 8x8 prediction mode */
extern const UWORD8 gau1_ih264d_num_submb_part[];

/** Width of the 8x8 prediction mode in terms of subMbs */
extern const UWORD8 gau1_ih264d_submb_partw[];

/** Height of the 8x8 prediction mode in terms of subMbs */
extern const UWORD8 gau1_ih264d_submb_parth[];

/** Number of MB partitions for the MB prediction mode */
extern const UWORD8 gau1_ih264d_num_mb_part[];

/** Width of the MB partition in terms of subMbs */
extern const UWORD8 gau1_ih264d_mb_partw[];

/** Height of the MB partition in terms of subMbs */
extern const UWORD8 gau1_ih264d_mb_parth[];

/** MB partition information is packed into a UWORD32 {0,number,width,height} */
extern const UWORD32 gau4_ih264d_submb_part[];

extern const UWORD8 gau1_ih264d_submb_indx_mod[];

/** This table is used to assign CBPs to Inter MBs. */
extern const UWORD8 gau1_ih264d_cbp_inter[];

/** Motion comp modes for P followed by B,
 0 to 4   : P Mbs
 5 to 27  : B Mbs
 28 to 30 : DIRECT */
extern const UWORD8 gau1_ih264d_mb_mc_mode[];

extern const UWORD8 gau1_ih264d_submb_mc_mode[];

/** Sub MB pred modes for B slice */
extern const UWORD8 gau1_ih264d_submb_pred_modes[];

/** MB pred modes for P and B slice */
extern const WORD8 gau1_ih264d_mb_pred_modes[2][32];

/*Decode CAVLC Table declaration*/
extern const UWORD8 gau1_ih264d_table_total_zero_2to10[9][64];
extern const UWORD8 gau1_ih264d_table_total_zero_11to15[5][16];
extern const UWORD8 gau1_ih264d_table_run_before[64];
extern const UWORD16 gau2_ih264d_code_gx[304];
extern const UWORD8 gau1_ih264d_cav_chromdc_vld[256];
extern const UWORD16 gau2_ih264d_offset_num_vlc_tab[9];
extern const UWORD8 gau1_ih264d_total_coeff_fn_ptr_offset[16];
extern const WORD16 gai2_ih264d_trailing_one_level[14][3];

/*Decode CABAC Table declaration*/
extern const UWORD32 gau4_ih264d_cabac_table[];

/****************************************************************************/
/*             For error detection in intra pred4x4 modes                   */
/****************************************************************************/
extern const UWORD8 gau1_ih264d_intra_pred_err_code[9];

/*****************************************************************************/
/* Cabac tables for context initialization depending upon type of Slice,     */
/* cabac init Idc value and Qp.                                              */
/*****************************************************************************/
extern const UWORD8 gau1_ih264d_cabac_ctxt_init_table[NUM_CAB_INIT_IDC_PLUS_ONE]
                                                     [QP_RANGE]
                                                     [NUM_CABAC_CTXTS];

/*****************************************************************************/
/* SEI tables for field usge and which field first                           */
/*****************************************************************************/
extern const UWORD8 gau1_ih264d_sei_fld_usage[9][3];

extern const UWORD8 gau1_ih264d_top_left_mb_part_indx_mod[];
extern const UWORD8 gau1_ih264d_submb_indx_mod_sp_drct[];

#endif /*TABLES_H*/
