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
 **************************************************************************
 * \file ih264d_tables.c
 *
 * \brief
 *    Defination of all tables used by h264 decoder
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
#include "ih264d_defs.h"

const UWORD8 gau1_ih264d_qp_scale_cr[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5,  6,
    7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    26, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 34, 35, 35, 36, 36, 37, 37, 37,
    38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39};
const UWORD8 gau1_ih264d_alpha_table[] = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   4,   4,   5,   6,   7,   8,   9,   10,  12,  13,  15,
    17,  20,  22,  25,  28,  32,  36,  40,  45,  50,  56,  63,  71,
    80,  90,  101, 113, 127, 144, 162, 182, 203, 226, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
const UWORD8 gau1_ih264d_beta_table[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  2,  3,  3,  3,  3,  4,  4,  4,
    6,  6,  7,  7,  8,  8,  9,  9,  10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15,
    15, 16, 16, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18};

const UWORD8 gau1_ih264d_clip_table[][4] = {{0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},

                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 1},
                                            {0, 0, 0, 1},
                                            {0, 0, 0, 1},
                                            {0, 0, 0, 1},
                                            {0, 0, 1, 1},
                                            {0, 0, 1, 1},
                                            {0, 1, 1, 1},
                                            {0, 1, 1, 1},
                                            {0, 1, 1, 1},
                                            {0, 1, 1, 1},
                                            {0, 1, 1, 2},
                                            {0, 1, 1, 2},
                                            {0, 1, 1, 2},
                                            {0, 1, 1, 2},
                                            {0, 1, 2, 3},
                                            {0, 1, 2, 3},
                                            {0, 2, 2, 3},
                                            {0, 2, 2, 4},
                                            {0, 2, 3, 4},
                                            {0, 2, 3, 4},
                                            {0, 3, 3, 5},
                                            {0, 3, 4, 6},
                                            {0, 3, 4, 6},
                                            {0, 4, 5, 7},
                                            {0, 4, 5, 8},
                                            {0, 4, 6, 9},
                                            {0, 5, 7, 10},
                                            {0, 6, 8, 11},
                                            {0, 6, 8, 13},
                                            {0, 7, 10, 14},
                                            {0, 8, 11, 16},
                                            {0, 9, 12, 18},
                                            {0, 10, 13, 20},
                                            {0, 11, 15, 23},
                                            {0, 13, 17, 25},

                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25},
                                            {0, 13, 17, 25}

};
const UWORD8 gau1_ih264d_clip_table_deblock[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5,  6,
    7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
    45, 46, 47, 48, 49, 50, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51};

/****************DEBLOCKING TABLES ENDS*******************/

/*************************************************************/
/* BS CALCULATION TABLES                                     */
/*************************************************************/
UWORD32 const gau4_ih264d_packed_bs2[32] = {
    /*************************************************************/
    /* BS TABLES FOR NORMAL EDGES                                */
    /*************************************************************/
    0x00000000,
    0x02000000,
    0x00020000,
    0x02020000,
    0x00000200,
    0x02000200,
    0x00020200,
    0x02020200,
    0x00000002,
    0x02000002,
    0x00020002,
    0x02020002,
    0x00000202,
    0x02000202,
    0x00020202,
    0x02020202,

    /*************************************************************/
    /* BS TABLES FOR XTRA LEFT MB EDGES IN MBAFF CASE            */
    /*************************************************************/
    0x01010101,
    0x02010101,
    0x01020101,
    0x02020101,
    0x01010201,
    0x02010201,
    0x01020201,
    0x02020201,
    0x01010102,
    0x02010102,
    0x01020102,
    0x02020102,
    0x01010202,
    0x02010202,
    0x01020202,
    0x02020202,
};

UWORD16 const gau2_ih264d_4x4_v2h_reorder[16] = {
    0x0000, 0x0001, 0x0010, 0x0011, 0x0100, 0x0101, 0x0110, 0x0111,
    0x1000, 0x1001, 0x1010, 0x1011, 0x1100, 0x1101, 0x1110, 0x1111};

/****************SCALING TABLES STARTS *****************/
const WORD16 gai2_ih264d_default_intra4x4[16] = {
    6, 13, 13, 20, 20, 20, 28, 28, 28, 28, 32, 32, 32, 37, 37, 42};

const WORD16 gai2_ih264d_default_inter4x4[16] = {
    10, 14, 14, 20, 20, 20, 24, 24, 24, 24, 27, 27, 27, 30, 30, 34};

const WORD16 gai2_ih264d_default_intra8x8[64] = {
    6,  10, 10, 13, 11, 13, 16, 16, 16, 16, 18, 18, 18, 18, 18, 23,
    23, 23, 23, 23, 23, 25, 25, 25, 25, 25, 25, 25, 27, 27, 27, 27,
    27, 27, 27, 27, 29, 29, 29, 29, 29, 29, 29, 31, 31, 31, 31, 31,
    31, 33, 33, 33, 33, 33, 36, 36, 36, 36, 38, 38, 38, 40, 40, 42};

const WORD16 gai2_ih264d_default_inter8x8[64] = {
    9,  13, 13, 15, 13, 15, 17, 17, 17, 17, 19, 19, 19, 19, 19, 21,
    21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 24, 24, 24, 24,
    24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 27, 27, 27, 27, 27,
    27, 28, 28, 28, 28, 28, 30, 30, 30, 30, 32, 32, 32, 33, 33, 35};

const WORD16 gai2_ih264d_flat_4x4[16] = {16, 16, 16, 16, 16, 16, 16, 16,
                                         16, 16, 16, 16, 16, 16, 16, 16};

const WORD16 gai2_ih264d_flat_8x8[64] = {
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};

/****************SCALING TABLES ENDS *****************/

/*Inverse scan tables for individual 4x4 blocks of 8x8 transform coeffs of CAVLC
 */

/* progressive */

const UWORD8 gau1_ih264d_inv_scan_prog8x8_cavlc[4][16] = {
    {0, 9, 17, 18, 12, 40, 27, 7, 35, 57, 29, 30, 58, 38, 53,
     47}, /* for First subblock  */
    {1, 2, 24, 11, 19, 48, 20, 14, 42, 50, 22, 37, 59, 31, 60,
     55}, /* for second subblock */
    {8, 3, 32, 4, 26, 41, 13, 21, 49, 43, 15, 44, 52, 39, 61,
     62}, /* for third subblock  */
    {16, 10, 25, 5, 33, 34, 6, 28, 56, 36, 23, 51, 45, 46, 54,
     63} /* for fourth subblock */
};

const UWORD8 gau1_ih264d_inv_scan_int8x8_cavlc[4][16] = {
    {0, 9, 2, 56, 18, 26, 34, 27, 35, 28, 36, 29, 45, 7, 54,
     39}, /* for First subblock  */
    {8, 24, 25, 33, 41, 11, 42, 12, 43, 13, 44, 14, 53, 15, 62,
     47}, /* for second subblock */
    {16, 32, 40, 10, 49, 4, 50, 5, 51, 6, 52, 22, 61, 38, 23,
     55}, /* for third subblock  */
    {1, 17, 48, 3, 57, 19, 58, 20, 59, 21, 60, 37, 30, 46, 31,
     63} /* for fourth subblock */
};

/*Inverse scan tables for individual 8x8 blocks of 8x8 transform coeffs of CABAC
 */
/* progressive */

const UWORD8 gau1_ih264d_inv_scan_prog8x8_cabac[64] = {
    0,  1,  8,  16, 9,  2,  3,  10, 17, 24, 32, 25, 18, 11, 4,  5,
    12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13, 6,  7,  14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63};

/* interlace */

const UWORD8 gau1_ih264d_inv_scan_int8x8_cabac[64] = {
    0,  8,  16, 1,  9,  24, 32, 17, 2,  25, 40, 48, 56, 33, 10, 3,
    18, 41, 49, 57, 26, 11, 4,  19, 34, 42, 50, 58, 27, 12, 5,  20,
    35, 43, 51, 59, 28, 13, 6,  21, 36, 44, 52, 60, 29, 14, 22, 37,
    45, 53, 61, 30, 7,  15, 38, 46, 54, 62, 23, 31, 39, 47, 55, 63};

/****************PARSING TABLES *******************/
UWORD8 const gau1_ih264d_subblk_offset[16] = {8,  9,  12, 13, 10, 11, 14, 15,
                                              16, 17, 20, 21, 18, 19, 22, 23};

const UWORD8 gau1_ih264d_cbp_tab[6] = {0, 16, 32, 15, 31, 47};

/** gives CBP value from codeword number, both for intra and inter */

const UWORD8 gau1_ih264d_cbp_table[48][2] = {
    {47, 0},  {31, 16}, {15, 1},  {0, 2},   {23, 4},  {27, 8},  {29, 32},
    {30, 3},  {7, 5},   {11, 10}, {13, 12}, {14, 15}, {39, 47}, {43, 7},
    {45, 11}, {46, 13}, {16, 14}, {3, 6},   {5, 9},   {10, 31}, {12, 35},
    {19, 37}, {21, 42}, {26, 44}, {28, 33}, {35, 34}, {37, 36}, {42, 40},
    {44, 39}, {1, 43},  {2, 45},  {4, 46},  {8, 17},  {17, 18}, {18, 20},
    {20, 24}, {24, 19}, {6, 21},  {9, 26},  {22, 28}, {25, 23}, {32, 27},
    {33, 29}, {34, 30}, {36, 22}, {40, 25}, {38, 38}, {41, 41},
};
/****************PARSING TABLES ENDS *******************/

/****************DECODE SLICE TABLES STARTS *******************/
/*Definition of Tables needed by functions of this file */
const UWORD8 gau1_ih264d_inv_scan[16] = {0, 1,  4,  8,  5, 2,  3,  6,
                                         9, 12, 13, 10, 7, 11, 14, 15};

const UWORD8 gau1_ih264d_inv_scan_fld[16] = {0, 4, 1,  8,  12, 5, 9,  13,
                                             2, 6, 10, 14, 3,  7, 11, 15};

const UWORD8 gau1_ih264d_dequant_matrix[6][16] = {
    {10, 13, 10, 13, 13, 16, 13, 16, 10, 13, 10, 13, 13, 16, 13, 16},
    {11, 14, 11, 14, 14, 18, 14, 18, 11, 14, 11, 14, 14, 18, 14, 18},
    {13, 16, 13, 16, 16, 20, 16, 20, 13, 16, 13, 16, 16, 20, 16, 20},
    {14, 18, 14, 18, 18, 23, 18, 23, 14, 18, 14, 18, 18, 23, 18, 23},
    {16, 20, 16, 20, 20, 25, 20, 25, 16, 20, 16, 20, 20, 25, 20, 25},
    {18, 23, 18, 23, 23, 29, 23, 29, 18, 23, 18, 23, 23, 29, 23, 29}};

const UWORD16 gau2_ih264_iquant_scale_4x4[6][16] = {
    {10, 13, 10, 13, 13, 16, 13, 16, 10, 13, 10, 13, 13, 16, 13, 16},
    {11, 14, 11, 14, 14, 18, 14, 18, 11, 14, 11, 14, 14, 18, 14, 18},
    {13, 16, 13, 16, 16, 20, 16, 20, 13, 16, 13, 16, 16, 20, 16, 20},
    {14, 18, 14, 18, 18, 23, 18, 23, 14, 18, 14, 18, 18, 23, 18, 23},
    {16, 20, 16, 20, 20, 25, 20, 25, 16, 20, 16, 20, 20, 25, 20, 25},
    {18, 23, 18, 23, 23, 29, 23, 29, 18, 23, 18, 23, 23, 29, 23, 29}};

const UWORD8 gau1_ih264d_dequant8x8_zigzag_cavlc[4][6][16] = {
    {{20, 18, 24, 32, 19, 19, 18, 19, 19, 18, 18, 24, 24, 25, 24,
      18}, /* for First subblock  */
     {22, 19, 26, 35, 21, 21, 19, 21, 21, 19, 19, 26, 26, 28, 26, 19},
     {26, 23, 31, 42, 24, 24, 23, 24, 24, 23, 23, 31, 31, 33, 31, 23},
     {28, 25, 33, 45, 26, 26, 25, 26, 26, 25, 25, 33, 33, 35, 33, 25},
     {32, 28, 38, 51, 30, 30, 28, 30, 30, 28, 28, 38, 38, 40, 38, 28},
     {36, 32, 43, 58, 34, 34, 32, 34, 34, 32, 32, 43, 43, 46, 43, 32}},
    {{19, 25, 19, 18, 24, 25, 25, 24, 24, 32, 32, 19, 18, 18, 19,
      24}, /* for second subblock */
     {21, 28, 21, 19, 26, 28, 28, 26, 26, 35, 35, 21, 19, 19, 21, 26},
     {24, 33, 24, 23, 31, 33, 33, 31, 31, 42, 42, 24, 23, 23, 24, 31},
     {26, 35, 26, 25, 33, 35, 35, 33, 33, 45, 45, 26, 25, 25, 26, 33},
     {30, 40, 30, 28, 38, 40, 40, 38, 38, 51, 51, 30, 28, 28, 30, 38},
     {34, 46, 34, 32, 43, 46, 46, 43, 43, 58, 58, 34, 32, 32, 34, 43}},
    {{19, 19, 20, 20, 24, 18, 18, 24, 24, 18, 18, 19, 25, 19, 18,
      24}, /* for third subblock  */
     {21, 21, 22, 22, 26, 19, 19, 26, 26, 19, 19, 21, 28, 21, 19, 26},
     {24, 24, 26, 26, 31, 23, 23, 31, 31, 23, 23, 24, 33, 24, 23, 31},
     {26, 26, 28, 28, 33, 25, 25, 33, 33, 25, 25, 26, 35, 26, 25, 33},
     {30, 30, 32, 32, 38, 28, 28, 38, 38, 28, 28, 30, 40, 30, 28, 38},
     {34, 34, 36, 36, 43, 32, 32, 43, 43, 32, 32, 34, 46, 34, 32, 43}},
    {{25, 24, 18, 19, 19, 25, 25, 19, 19, 20, 24, 24, 18, 24, 32,
      18}, /* for fourth subblock */
     {28, 26, 19, 21, 21, 28, 28, 21, 21, 22, 26, 26, 19, 26, 35, 19},
     {33, 31, 23, 24, 24, 33, 33, 24, 24, 26, 31, 31, 23, 31, 42, 23},
     {35, 33, 25, 26, 26, 35, 35, 26, 26, 28, 33, 33, 25, 33, 45, 25},
     {40, 38, 28, 30, 30, 40, 40, 30, 30, 32, 38, 38, 28, 38, 51, 28},
     {46, 43, 32, 34, 34, 46, 46, 34, 34, 36, 43, 43, 32, 43, 58, 32}}

};

const UWORD16 gau1_ih264d_dequant8x8_cavlc[6][64] = {
    {20, 19, 25, 19, 20, 19, 25, 19, 19, 18, 24, 18, 19, 18, 24, 18,
     25, 24, 32, 24, 25, 24, 32, 24, 19, 18, 24, 18, 19, 18, 24, 18,
     20, 19, 25, 19, 20, 19, 25, 19, 19, 18, 24, 18, 19, 18, 24, 18,
     25, 24, 32, 24, 25, 24, 32, 24, 19, 18, 24, 18, 19, 18, 24, 18},
    {22, 21, 28, 21, 22, 21, 28, 21, 21, 19, 26, 19, 21, 19, 26, 19,
     28, 26, 35, 26, 28, 26, 35, 26, 21, 19, 26, 19, 21, 19, 26, 19,
     22, 21, 28, 21, 22, 21, 28, 21, 21, 19, 26, 19, 21, 19, 26, 19,
     28, 26, 35, 26, 28, 26, 35, 26, 21, 19, 26, 19, 21, 19, 26, 19},
    {26, 24, 33, 24, 26, 24, 33, 24, 24, 23, 31, 23, 24, 23, 31, 23,
     33, 31, 42, 31, 33, 31, 42, 31, 24, 23, 31, 23, 24, 23, 31, 23,
     26, 24, 33, 24, 26, 24, 33, 24, 24, 23, 31, 23, 24, 23, 31, 23,
     33, 31, 42, 31, 33, 31, 42, 31, 24, 23, 31, 23, 24, 23, 31, 23},
    {28, 26, 35, 26, 28, 26, 35, 26, 26, 25, 33, 25, 26, 25, 33, 25,
     35, 33, 45, 33, 35, 33, 45, 33, 26, 25, 33, 25, 26, 25, 33, 25,
     28, 26, 35, 26, 28, 26, 35, 26, 26, 25, 33, 25, 26, 25, 33, 25,
     35, 33, 45, 33, 35, 33, 45, 33, 26, 25, 33, 25, 26, 25, 33, 25},
    {32, 30, 40, 30, 32, 30, 40, 30, 30, 28, 38, 28, 30, 28, 38, 28,
     40, 38, 51, 38, 40, 38, 51, 38, 30, 28, 38, 28, 30, 28, 38, 28,
     32, 30, 40, 30, 32, 30, 40, 30, 30, 28, 38, 28, 30, 28, 38, 28,
     40, 38, 51, 38, 40, 38, 51, 38, 30, 28, 38, 28, 30, 28, 38, 28},
    {36, 34, 46, 34, 36, 34, 46, 34, 34, 32, 43, 32, 34, 32, 43, 32,
     46, 43, 58, 43, 46, 43, 58, 43, 34, 32, 43, 32, 34, 32, 43, 32,
     36, 34, 46, 34, 36, 34, 46, 34, 34, 32, 43, 32, 34, 32, 43, 32,
     46, 43, 58, 43, 46, 43, 58, 43, 34, 32, 43, 32, 34, 32, 43, 32},
};

/****************DECODE SLICE TABLES ENDS *******************/

/****************MOTION VECTOR DECODING TABLES STARTS *******************/

/**
 **************************************************************************
 *   \brief   This array is used to evaluate the condition when only one of
 *   predictor subMbs has a reference frame equal to that of E subMb.
 **************************************************************************
 */

const WORD8 gau1_ih264d_mv_pred_condition[] = {-1, 0, 1, -1, 2, -1, -1, -1};

/** Number of subMbs for the 8x8 prediction mode */
const UWORD8 gau1_ih264d_num_submb_part[] = {1, 2, 2, 4};

/** Width of the 8x8 prediction mode in terms of subMbs */
const UWORD8 gau1_ih264d_submb_partw[] = {2, 2, 1, 1};

/** Height of the 8x8 prediction mode in terms of subMbs */
const UWORD8 gau1_ih264d_submb_parth[] = {2, 1, 2, 1};

/** Number of MB partitions for the MB prediction mode */
const UWORD8 gau1_ih264d_num_mb_part[] = {1, 2, 2, 4};

/** Width of the MB partition in terms of subMbs */
const UWORD8 gau1_ih264d_mb_partw[] = {4, 4, 2, 2, 2};

/** Height of the MB partition in terms of subMbs */
const UWORD8 gau1_ih264d_mb_parth[] = {4, 2, 4, 2, 2};

/** MB partition information is packed into a UWORD32 {0,number,width,height} */
const UWORD32 gau4_ih264d_submb_part[] = {0x00010202, 0x00020201, 0x00020102,
                                          0x00040101};

const UWORD8 gau1_ih264d_submb_indx_mod[] = {
    0, 0,      /* 16x16 */
    0, 8,      /* 16x8 */
    0, 2,      /* 8x16 */
    0, 0,      /* 8x8 */
    0, 4,      /* 8x4 */
    0, 1,      /* 4x8 */
    0, 1, 3, 1 /* 4x4 */
};

/** This table is used to assign CBPs to Inter MBs. */
const UWORD8 gau1_ih264d_cbp_inter[] = {
    0,  16, 1,  2,  4,  8,  32, 3,  5,  10, 12, 15, 47, 7,  11, 13,
    14, 6,  9,  31, 35, 37, 42, 44, 33, 34, 36, 40, 39, 43, 45, 46,
    17, 18, 20, 24, 19, 21, 26, 28, 23, 27, 29, 30, 22, 25, 38, 41};

/** Motion comp modes for P followed by B,
 0 to 4   : P Mbs
 5 to 27  : B Mbs
 28 to 30 : DIRECT */
const UWORD8 gau1_ih264d_mb_mc_mode[] = {
    PRED_16x16, PRED_16x8, PRED_8x16, PRED_8x8, PRED_8x8R0, PRED_16x16,
    PRED_16x16, PRED_16x16, PRED_16x16, PRED_16x8, PRED_8x16, PRED_16x8,
    PRED_8x16, PRED_16x8, PRED_8x16, PRED_16x8, PRED_8x16, PRED_16x8, PRED_8x16,
    PRED_16x8, PRED_8x16, PRED_16x8, PRED_8x16, PRED_16x8, PRED_8x16, PRED_16x8,
    PRED_8x16, PRED_8x8,
    /* Self defined modes for B_SKIP and DIRECT16x16 */
    PRED_8x8, PRED_8x8, PRED_8x8};

const UWORD8 gau1_ih264d_submb_mc_mode[] = {
    SUBMB_8x8, SUBMB_8x4, SUBMB_4x8, SUBMB_4x4, SUBMB_8x8, SUBMB_8x8, SUBMB_8x8,
    SUBMB_8x8, SUBMB_8x4, SUBMB_4x8, SUBMB_8x4, SUBMB_4x8, SUBMB_8x4, SUBMB_4x8,
    SUBMB_4x4, SUBMB_4x4, SUBMB_4x4,
    /* Self defined modes B DIRECT8x8 */
    SUBMB_4x4, SUBMB_4x4, SUBMB_4x4};

/** Sub MB pred modes for B slice */
const UWORD8 gau1_ih264d_submb_pred_modes[] = {
    PRED_L0,
    PRED_L0,
    PRED_L0,
    PRED_L0,
    B_DIRECT,
    PRED_L0,
    PRED_L1,
    BI_PRED,
    PRED_L0,
    PRED_L0,
    PRED_L1,
    PRED_L1,
    BI_PRED,
    BI_PRED,
    PRED_L0,
    PRED_L1,
    BI_PRED,
    /* Self defined modes for B DIRECT8x8 */
    BI_PRED,
    PRED_L0,
    PRED_L1,
};

/** MB pred modes for P and B slice */
const WORD8 gau1_ih264d_mb_pred_modes[2][32] = {
    {
        PRED_L0,
        PRED_L0,
        PRED_L0,
        PRED_INVALID,
        PRED_INVALID,
        B_DIRECT,
        PRED_L0,
        PRED_L1,
        BI_PRED,
        PRED_L0,
        PRED_L0,
        PRED_L1,
        PRED_L1,
        PRED_L0,
        PRED_L0,
        PRED_L1,
        PRED_L1,
        PRED_L0,
        PRED_L0,
        PRED_L1,
        PRED_L1,
        BI_PRED,
        BI_PRED,
        BI_PRED,
        BI_PRED,
        BI_PRED,
        BI_PRED,
        PRED_INVALID,
        /* Self defined modes for B_SKIP and DIRECT16x16 */
        BI_PRED,
        PRED_L0,
        PRED_L1,
    },
    {PRED_INVALID, PRED_L0, PRED_L0, PRED_INVALID, PRED_INVALID, PRED_INVALID,
     PRED_INVALID, PRED_INVALID, PRED_INVALID, PRED_L0, PRED_L0, PRED_L1,
     PRED_L1, PRED_L1, PRED_L1, PRED_L0, PRED_L0, BI_PRED, BI_PRED, BI_PRED,
     BI_PRED, PRED_L0, PRED_L0, PRED_L1, PRED_L1, BI_PRED, BI_PRED,
     PRED_INVALID,
     /* Self defined modes for B_SKIP and DIRECT16x16 */
     PRED_INVALID, PRED_INVALID, PRED_INVALID}};

/****************MOTION VECTOR DECODING TABLES ENDS *******************/

/****************CAVLC DECODING TABLES STARTS *******************/

/*****************************************************************************/
/* 6 Bit table look for total zeros (totalcoeff = 2to10) as in Table 9.7     */
/* of H264 standard. In each table entry, lower 4 bits represent total zeros */
/* decoded while upper 4 bit represent the bits to be flushed from ps_bitstrm */
/*****************************************************************************/
const UWORD8 gau1_ih264d_table_total_zero_2to10[9][64] = {
    /* For total coeff = 2 */
    {
        0x6E, 0x6D, 0x6C, 0x6B, 0x5A, 0x5A, 0x59, 0x59, 0x48, 0x48, 0x48,
        0x48, 0x47, 0x47, 0x47, 0x47, 0x46, 0x46, 0x46, 0x46, 0x45, 0x45,
        0x45, 0x45, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x33,
        0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x32, 0x32, 0x32, 0x32,
        0x32, 0x32, 0x32, 0x32, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31,
        0x31, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    },

    /* For total coeff = 3 */
    {
        0x6D, 0x6B, 0x5C, 0x5C, 0x5A, 0x5A, 0x59, 0x59, 0x48, 0x48, 0x48,
        0x48, 0x45, 0x45, 0x45, 0x45, 0x44, 0x44, 0x44, 0x44, 0x40, 0x40,
        0x40, 0x40, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x36,
        0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x33, 0x33, 0x33, 0x33,
        0x33, 0x33, 0x33, 0x33, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32,
        0x32, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31,
    },

    /* For total coeff = 4 */
    {
        0x5C, 0x5C, 0x5B, 0x5B, 0x5A, 0x5A, 0x50, 0x50, 0x49, 0x49, 0x49,
        0x49, 0x47, 0x47, 0x47, 0x47, 0x43, 0x43, 0x43, 0x43, 0x42, 0x42,
        0x42, 0x42, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x36,
        0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x35, 0x35, 0x35, 0x35,
        0x35, 0x35, 0x35, 0x35, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
        0x34, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31,
    },

    /* For total coeff = 5 */
    {
        0x5B, 0x5B, 0x59, 0x59, 0x4A, 0x4A, 0x4A, 0x4A, 0x48, 0x48, 0x48,
        0x48, 0x42, 0x42, 0x42, 0x42, 0x41, 0x41, 0x41, 0x41, 0x40, 0x40,
        0x40, 0x40, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x36,
        0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x35, 0x35, 0x35, 0x35,
        0x35, 0x35, 0x35, 0x35, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
        0x34, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
    },

    /* For total coeff = 6 */
    {
        0x6A, 0x60, 0x51, 0x51, 0x48, 0x48, 0x48, 0x48, 0x39, 0x39, 0x39,
        0x39, 0x39, 0x39, 0x39, 0x39, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37,
        0x37, 0x37, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x35,
        0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x34, 0x34, 0x34, 0x34,
        0x34, 0x34, 0x34, 0x34, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
        0x33, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32,
    },

    /* For total coeff = 7 */
    {
        0x69, 0x60, 0x51, 0x51, 0x47, 0x47, 0x47, 0x47, 0x38, 0x38, 0x38,
        0x38, 0x38, 0x38, 0x38, 0x38, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
        0x36, 0x36, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x33,
        0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x32, 0x32, 0x32, 0x32,
        0x32, 0x32, 0x32, 0x32, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
        0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    },

    /* For total coeff = 8 */
    {
        0x68, 0x60, 0x52, 0x52, 0x41, 0x41, 0x41, 0x41, 0x37, 0x37, 0x37,
        0x37, 0x37, 0x37, 0x37, 0x37, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
        0x36, 0x36, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x25,
        0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
        0x25, 0x25, 0x25, 0x25, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24,
        0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24,
    },

    /* For total coeff = 9 */
    {
        0x61, 0x60, 0x57, 0x57, 0x42, 0x42, 0x42, 0x42, 0x35, 0x35, 0x35,
        0x35, 0x35, 0x35, 0x35, 0x35, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26,
        0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x24,
        0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24,
        0x24, 0x24, 0x24, 0x24, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23,
        0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23,
    },

    /* For total coeff = 10 */
    {
        0x51, 0x51, 0x50, 0x50, 0x46, 0x46, 0x46, 0x46, 0x32, 0x32, 0x32,
        0x32, 0x32, 0x32, 0x32, 0x32, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
        0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x24,
        0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24,
        0x24, 0x24, 0x24, 0x24, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23,
        0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23,
    }

};

/*****************************************************************************/
/* 4 Bit table look for total zeros (totalcoeff = 11to15) as in Table 9.7    */
/* of H264 standard. In each table entry, lower 4 bits represent total zeros */
/* decoded while upper 4 bit represent the bits to be flushed from ps_bitstrm */
/*****************************************************************************/
const UWORD8 gau1_ih264d_table_total_zero_11to15[5][16] = {
    /* For total coeff = 11 */
    {
        0x40,
        0x41,
        0x32,
        0x32,
        0x33,
        0x33,
        0x35,
        0x35,
        0x14,
        0x14,
        0x14,
        0x14,
        0x14,
        0x14,
        0x14,
        0x14,
    },

    /* For total coeff = 12 */
    {
        0x40,
        0x41,
        0x34,
        0x34,
        0x22,
        0x22,
        0x22,
        0x22,
        0x13,
        0x13,
        0x13,
        0x13,
        0x13,
        0x13,
        0x13,
        0x13,
    },

    /* For total coeff = 13 */
    {
        0x30,
        0x30,
        0x31,
        0x31,
        0x23,
        0x23,
        0x23,
        0x23,
        0x12,
        0x12,
        0x12,
        0x12,
        0x12,
        0x12,
        0x12,
        0x12,
    },

    /* For total coeff = 14 */
    {
        0x20,
        0x20,
        0x20,
        0x20,
        0x21,
        0x21,
        0x21,
        0x21,
        0x12,
        0x12,
        0x12,
        0x12,
        0x12,
        0x12,
        0x12,
        0x12,
    },

    /* For total coeff = 15 */
    {
        0x10,
        0x10,
        0x10,
        0x10,
        0x10,
        0x10,
        0x10,
        0x10,
        0x11,
        0x11,
        0x11,
        0x11,
        0x11,
        0x11,
        0x11,
        0x11,
    },
};

/** Tables used to read "Run Before", Below tables are packed to reduce lookups
 */
/** (Base addess of Gx << 2)  + (Max code length for that Gx) */
const UWORD8 gau1_ih264d_table_run_before[64] = {
    0,  0,  0,  0,  0,  0,  0, 0, 5,  5,  5,  5,  1,  1,  1, 1,
    10, 10, 6,  6,  1,  1,  1, 1, 14, 14, 10, 10, 6,  6,  2, 2,
    19, 15, 10, 10, 6,  6,  2, 2, 23, 19, 15, 11, 6,  6,  2, 2,
    7,  11, 19, 15, 27, 23, 2, 2, 27, 27, 23, 19, 15, 11, 7, 3};

/*****************************************************************************/
/* Lookup table for CAVLC 4x4  total_coeff,trailing_ones as pers Table 9-5   */
/* in the standard. Starting form lsb first 2 bits=flushbits, next 2bits=    */
/* trailing ones, next 5 bits=total_coeff. Total bits used = 9 out of 16     */
/*****************************************************************************/
const UWORD16 gau2_ih264d_code_gx[304] = {
    /* Lookup for 0 <= nC < 2 */
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0014,
    0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0026, 0x0026, 0x0012,
    0x0012, 0x003D, 0x003D, 0x003D, 0x003D, 0x005E, 0x005E, 0x003A, 0x003A,
    0x004D, 0x004D, 0x004D, 0x004D, 0x006E, 0x006E, 0x004A, 0x004A, 0x0036,
    0x0036, 0x0022, 0x0022, 0x007E, 0x007E, 0x005A, 0x005A, 0x0046, 0x0046,
    0x0032, 0x0032, 0x008E, 0x008E, 0x006A, 0x006A, 0x0056, 0x0056, 0x0042,
    0x0042, 0x009E, 0x009E, 0x007A, 0x007A, 0x0066, 0x0066, 0x0052, 0x0052,
    0x0083, 0x009B, 0x0087, 0x0073, 0x00AF, 0x008B, 0x0077, 0x0063, 0x00CF,
    0x00BB, 0x00A7, 0x00A3, 0x00BF, 0x00AB, 0x0097, 0x0093, 0x00EF, 0x00DB,
    0x00C7, 0x00C3, 0x00DF, 0x00CB, 0x00B7, 0x00B3, 0x010F, 0x00FB, 0x00F7,
    0x00E3, 0x00FF, 0x00EB, 0x00E7, 0x00D3, 0x0102, 0x0102, 0x010A, 0x010A,
    0x0106, 0x0106, 0x00F2, 0x00F2, 0x00D4, 0x00D4, 0x00D4, 0x00D4, 0x00D4,
    0x00D4, 0x00D4, 0x00D4,

    /* Lookup for 2 <= nC < 4 */
    0x0015, 0x0015, 0x0015, 0x0015, 0x0001, 0x0001, 0x0001, 0x0001, 0x004E,
    0x004E, 0x003E, 0x003E, 0x0029, 0x0029, 0x0029, 0x0029, 0x006F, 0x003B,
    0x0037, 0x0013, 0x005E, 0x005E, 0x0026, 0x0026, 0x007E, 0x007E, 0x004A,
    0x004A, 0x0046, 0x0046, 0x0022, 0x0022, 0x008E, 0x008E, 0x005A, 0x005A,
    0x0056, 0x0056, 0x0032, 0x0032, 0x0052, 0x0052, 0x006A, 0x006A, 0x0066,
    0x0066, 0x0042, 0x0042, 0x009E, 0x009E, 0x007A, 0x007A, 0x0076, 0x0076,
    0x0062, 0x0062, 0x00BF, 0x009B, 0x0097, 0x0083, 0x00AF, 0x008B, 0x0087,
    0x0073, 0x00B3, 0x00BB, 0x00B7, 0x00A3, 0x00CF, 0x00AB, 0x00A7, 0x0093,
    0x00EF, 0x00DB, 0x00D7, 0x00D3, 0x00DF, 0x00CB, 0x00C7, 0x00C3, 0x00F7,
    0x00F3, 0x00FB, 0x00E7, 0x00EA, 0x00EA, 0x00E2, 0x00E2, 0x010E, 0x010E,
    0x010A, 0x010A, 0x0106, 0x0106, 0x0102, 0x0102, 0x00FC, 0x00FC, 0x00FC,
    0x00FC, 0x00FC, 0x00FC, 0x00FC, 0x00FC,

    /* Lookup for 4 <= nC < 8 */
    0x007F, 0x006F, 0x005F, 0x004F, 0x003F, 0x002B, 0x0017, 0x0003, 0x0057,
    0x005B, 0x0047, 0x004B, 0x0037, 0x008F, 0x003B, 0x0027, 0x0033, 0x007B,
    0x0077, 0x0023, 0x009F, 0x006B, 0x0067, 0x0013, 0x0073, 0x0063, 0x009B,
    0x0053, 0x00AF, 0x008B, 0x0087, 0x0043, 0x00CF, 0x00BB, 0x00A7, 0x0093,
    0x00BF, 0x00AB, 0x0097, 0x0083, 0x00C3, 0x00DB, 0x00C7, 0x00B3, 0x00DF,
    0x00CB, 0x00B7, 0x00A3, 0x00F7, 0x00E3, 0x00EF, 0x00EB, 0x00E7, 0x00D3,
    0x00D6, 0x00D6, 0x0106, 0x0106, 0x00F2, 0x00F2, 0x00FE, 0x00FE, 0x00FA,
    0x00FA, 0x010D, 0x010D, 0x010D, 0x010D, 0x0109, 0x0109, 0x0109, 0x0109,
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100};

/*****************************************************************************/
/* Lookup table for CAVLC ChromaDC total_coeff,trailing_ones parsing as per  */
/* Table 9-5 in the standard. Starting from msb, First 4bits=total_coeff,    */
/* next 2bits=trailing_ones and last 2bits=flushbits-1                       */
/*****************************************************************************/
const UWORD8 gau1_ih264d_cav_chromdc_vld[256] = {
    0x9E, 0x9E, 0x97, 0x8F, 0x76, 0x76, 0x6E, 0x6E, 0x85, 0x85, 0x85, 0x85,
    0x65, 0x65, 0x65, 0x65, 0x45, 0x45, 0x45, 0x45, 0x7D, 0x7D, 0x7D, 0x7D,
    0x4D, 0x4D, 0x4D, 0x4D, 0x25, 0x25, 0x25, 0x25,

    0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52,
    0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52,
    0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52,

    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01,

    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
};

const UWORD16 gau2_ih264d_offset_num_vlc_tab[9] = {0,   0,   120, 120, 224,
                                                   224, 224, 224, 224};

/*****************************************************************************/
/* Function pointer u4_ofst table lookup for parsing 4x4 residual blocks in   */
/* CAVLC. The u4_ofst is dependent on total coeffs coded                      */
/*****************************************************************************/
const UWORD8 gau1_ih264d_total_coeff_fn_ptr_offset[16] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2};

/****************************************************************************/
/*  gai2_ih264d_trailing_one_level lookup tables based on trailing one bits */
/*  All zeroes are u2_dummy in the table are u2_dummy to keep 3 uniform elements
 */
/****************************************************************************/
const WORD16 gai2_ih264d_trailing_one_level[14][3] = {
    /* All zeroes are u2_dummy */
    /**********************************************************************/
    /* Levels for trailing ones = 1, bits read can be 0 or 1              */
    /**********************************************************************/
    {1, 0, 0},  /* 0 */
    {-1, 0, 0}, /* 1 */

    /**********************************************************************/
    /* Levels for trailing ones = 2, bits read can be 00, 01, 10 ,11      */
    /**********************************************************************/
    {1, 1, 0},   /* 00 */
    {1, -1, 0},  /* 01 */
    {-1, 1, 0},  /* 10 */
    {-1, -1, 0}, /* 11 */

    /**********************************************************************/
    /* Levels for trailing ones = 3, bits read can be 000 - 111           */
    /**********************************************************************/
    {1, 1, 1},    /* 000 */
    {1, 1, -1},   /* 001 */
    {1, -1, 1},   /* 010 */
    {1, -1, -1},  /* 011 */
    {-1, 1, 1},   /* 100 */
    {-1, 1, -1},  /* 101 */
    {-1, -1, 1},  /* 110 */
    {-1, -1, -1}, /* 111 */
};
/****************CAVLC DECODING TABLES ENDS *******************/

/****************************************************************************/
/* These are the codes used for error detection in intra pred4x4 modes      */
/****************************************************************************/
const UWORD8 gau1_ih264d_intra_pred_err_code[9] = {2, 1, 0, 2, 3, 3, 3, 2, 1};

/* Number of users for top field , bottom field, which field needs to be     */
/* displayed first                                                           */
const UWORD8 gau1_ih264d_sei_fld_usage[9][3] = {
    {1, 1, DISP_FLD_FIRST_UNDEF}, {1, 0, DISP_TOP_FLD_FIRST},
    {0, 1, DISP_BOT_FLD_FIRST},   {1, 1, DISP_TOP_FLD_FIRST},
    {1, 1, DISP_BOT_FLD_FIRST},   {2, 1, DISP_TOP_FLD_FIRST},
    {1, 2, DISP_BOT_FLD_FIRST},   {2, 2, DISP_FLD_FIRST_UNDEF},
    {3, 3, DISP_FLD_FIRST_UNDEF}};

/*****************************************************************/
/* Context increment for significant coefficient(CABAC)          */
/* Requires only 63 elements. But the last element with value -1 */
/* is kept to make it 64                                         */
/*****************************************************************/
const UWORD8 gau1_ih264d_sigcoeff_context_inc_frame[64] = {
    0,  1,  2,  3,  4,  5,  5,  4, 4,  3,  3,  4,  4,  4,  5,  5,
    4,  4,  4,  4,  3,  3,  6,  7, 7,  7,  8,  9,  10, 9,  8,  7,
    7,  6,  11, 12, 13, 11, 6,  7, 8,  9,  14, 10, 9,  8,  6,  11,
    12, 13, 11, 6,  9,  14, 10, 9, 11, 12, 13, 11, 14, 10, 12, -1};

const UWORD8 gau1_ih264d_sigcoeff_context_inc_field[64] = {
    0, 1,  1,  2,  2,  3,  3,  4,  5,  6,  7,  7,  7,  8,  4,  5,
    6, 9,  10, 10, 8,  11, 12, 11, 9,  9,  10, 10, 8,  11, 12, 11,
    9, 9,  10, 10, 8,  11, 12, 11, 9,  9,  10, 10, 8,  13, 13, 9,
    9, 10, 10, 8,  13, 13, 9,  9,  10, 10, 14, 14, 14, 14, 14, -1};

const UWORD8 gau1_ih264d_lastcoeff_context_inc[64] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4,
    4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, -1};

/*!
 **************************************************************************
 *   \brief   gau1_ih264d_top_left_mb_part_indx_mod
 *
 *   SubBlk number of the top left subBlk in each of the MB partition
 *   (16x16, 16x8, 8x16, 8x8)
 **************************************************************************
 */
const UWORD8 gau1_ih264d_top_left_mb_part_indx_mod[] = {
    0, 0 /* Junk */, /* 16x16 */
    0, 8,            /* 16x8 */
    0, 2,            /* 8x16 */
    0, 2,
    8, 10 /* 8x8 */
};

/*!
 **************************************************************************
 *   \brief   gau1_ih264d_submb_indx_mod_sp_drct
 *
 *   Contains increments to the subBlk num in a given subMb partition.
 **************************************************************************
 */
const UWORD8 gau1_ih264d_submb_indx_mod_sp_drct[] = {
    0, 0 /* Junk */, /* 8x8 */
    0, 4,            /* 8x4 */
    0, 1,            /* 4x8 */
    0, 1,
    3, 1 /* 4x4 */
};