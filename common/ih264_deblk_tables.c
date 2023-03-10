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
*  ih264_deblk_tables.c
*
* @brief
*  Contains tables used for deblocking
*
* @author
*  Ittiam
*
* @par List of Tables:
*  - guc_ih264_qp_scale_cr[]
*  - guc_ih264_alpha_table[]
*  - guc_ih264_beta_table[]
*  - guc_ih264_clip_table[][]
*
* @remarks
*  None
*
*******************************************************************************
*/

/*****************************************************************************/
/* File Includes                                                             */
/*****************************************************************************/

/* System include files */
#include <stdio.h>

/* User include files */
#include "ih264_typedefs.h"
#include "ih264_deblk_tables.h"

/*****************************************************************************/
/* Extern global definitions                                                 */
/*****************************************************************************/

/**
 ******************************************************************************
 * @brief  alpha & beta tables for deblocking
 * input   : indexA [0-51] & indexB [0-51]
 * output  : alpha & beta
 *
 * @remarks Table 8-16 � in H264 Specification,
 * Derivation of offset dependent threshold variables
 *  alpha and beta from indexA and indexB
 ******************************************************************************
 */
const UWORD8 gu1_ih264_alpha_table[52] = {
    /* indexA :: 0-51 inclusive */
    0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,  0,  0,  4,   4,   5,   6,   7,   8,   9,   10,  12,  13,
    15, 17, 20, 22,  25,  28,  32,  36,  40,  45,  50,  56,  63,
    71, 80, 90, 101, 113, 127, 144, 162, 182, 203, 226, 255, 255,
};

const UWORD8 gu1_ih264_beta_table[52] = {
    /* indexB :: 0-51 inclusive */
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,
    2,  3,  3,  3,  3,  4,  4,  4,  6,  6,  7,  7,  8,  8,  9,  9,  10, 10,
    11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18,
};

/**
 ******************************************************************************
 * @brief  t'C0 table for deblocking
 * input   : indexA [0-51] and bS [1,3]
 * output  : t'C0
 *
 * @remarks Table 8-17 � in H264 Specification,
 * Value of variable t'C0 as a function of indexA and bS
 ******************************************************************************
 */
const UWORD8 gu1_ih264_clip_table[52][4] = {
    /* indexA :: 0-51 inclusive */
    {0, 0, 0, 0},   {0, 0, 0, 0},    {0, 0, 0, 0},    {0, 0, 0, 0},
    {0, 0, 0, 0},   {0, 0, 0, 0},    {0, 0, 0, 0},    {0, 0, 0, 0},
    {0, 0, 0, 0},   {0, 0, 0, 0},    {0, 0, 0, 0},    {0, 0, 0, 0},
    {0, 0, 0, 0},   {0, 0, 0, 0},    {0, 0, 0, 0},    {0, 0, 0, 0},
    {0, 0, 0, 0},   {0, 0, 0, 1},    {0, 0, 0, 1},    {0, 0, 0, 1},
    {0, 0, 0, 1},   {0, 0, 1, 1},    {0, 0, 1, 1},    {0, 1, 1, 1},
    {0, 1, 1, 1},   {0, 1, 1, 1},    {0, 1, 1, 1},    {0, 1, 1, 2},
    {0, 1, 1, 2},   {0, 1, 1, 2},    {0, 1, 1, 2},    {0, 1, 2, 3},
    {0, 1, 2, 3},   {0, 2, 2, 3},    {0, 2, 2, 4},    {0, 2, 3, 4},
    {0, 2, 3, 4},   {0, 3, 3, 5},    {0, 3, 4, 6},    {0, 3, 4, 6},
    {0, 4, 5, 7},   {0, 4, 5, 8},    {0, 4, 6, 9},    {0, 5, 7, 10},
    {0, 6, 8, 11},  {0, 6, 8, 13},   {0, 7, 10, 14},  {0, 8, 11, 16},
    {0, 9, 12, 18}, {0, 10, 13, 20}, {0, 11, 15, 23}, {0, 13, 17, 25},
};
