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
 *  ih264_size_defs.h
 *
 * @brief
 *  Contains declaration of global variables for H264 transform , quant and
 *inverse quant
 *
 * @author
 *  Ittiam
 *
 * @remarks
 *
 ********************************************************************************/

#ifndef IH264_SIZE_DEFS_H_
#define IH264_SIZE_DEFS_H_

/*****************************************************************************/
/* Constant Macros                                                           */
/*****************************************************************************/

/*-----------------------Primary defs--------------------------*/

/*Width of a 4x4 block*/
#define SUB_BLK_WIDTH_4x4 4

/*Width of an 8x8 block*/
#define SUB_BLK_WIDTH_8x8 8

/*Number of chroma blocks in a row of coffs*/
#define SUB_BLK_COUNT_CHROMA_4x4_420 2

/*Number of luma blocks in a row of coffs*/
#define SUB_BLK_COUNT_LUMA_4x4 4

/*Numbr of chroma planes*/
#define NUM_CHROMA_PLANES 2

/*Constant bit shifts*/
#define QP_BITS_h264_4x4 15
#define QP_BITS_h264_8x8 16

/*---------------------------Derived defs------------------------*/

/*Number of coefficients ina 4x4 block*/
#define COFF_CNT_SUB_BLK_4x4 SUB_BLK_WIDTH_4x4* SUB_BLK_WIDTH_4x4;

/*Number of luma blocks in a row of coffs*/
#define SUB_BLK_LUMA_4X4_CNT_MB SUB_BLK_COUNT_LUMA_4x4* SUB_BLK_COUNT_LUMA_4x4

/*Number of chroma coffs in an MB*/
#define SUB_BLK_CHROMA_4X4_CNT_MB \
  SUB_BLK_COUNT_CHROMA_4x4_420* SUB_BLK_COUNT_CHROMA_4x4_420
#define SUB_BLK_CHROMA_4X4_CNT_MB_BIPLANE \
  SUB_BLK_CHROMA_4X4_CNT_MB* NUM_CHROMA_PLANES

/*Size of trans buff = 4x4 for DC block +  4x4 * coffs for 4x4 ac blocks*/
#define SIZE_TRANS_BUFF                                         \
  (SUB_BLK_WIDTH_4x4 * SUB_BLK_WIDTH_4x4 * +SUB_BLK_WIDTH_4x4 * \
   SUB_BLK_WIDTH_4x4 * SUB_BLK_COUNT_LUMA_4x4 * SUB_BLK_COUNT_LUMA_4x4)

/*memory size = memory size of 4x4 block of resi coff + 4x4 for DC coff block */
#define SIZE_TMP_BUFF_ITRANS                 \
  ((SUB_BLK_WIDTH_4x4 * SUB_BLK_WIDTH_4x4) + \
   (SUB_BLK_WIDTH_4x4 * SUB_BLK_WIDTH_4x4))

#endif /* IH264_DEFS_H_ */
