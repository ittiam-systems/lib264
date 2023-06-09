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
*  ih264_padding.h
*
* @brief
*  Declarations for padding functions
*
* @author
*  Ittiam
*
* @remarks
*  None
*
*******************************************************************************
*/
#ifndef _IH264_PADDING_H_
#define _IH264_PADDING_H_

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/

typedef void ih264_pad(UWORD8 *, WORD32, WORD32, WORD32);

/* C function declarations */
ih264_pad ih264_pad_top;
ih264_pad ih264_pad_bottom;
ih264_pad ih264_pad_left_luma;
ih264_pad ih264_pad_left_chroma;
ih264_pad ih264_pad_right_luma;
ih264_pad ih264_pad_right_chroma;

/* A9 Q function declarations */
ih264_pad ih264_pad_top_a9q;
ih264_pad ih264_pad_left_luma_a9q;
ih264_pad ih264_pad_left_chroma_a9q;
ih264_pad ih264_pad_right_luma_a9q;
ih264_pad ih264_pad_right_chroma_a9q;

/* AV8 function declarations */
ih264_pad ih264_pad_top_av8;
ih264_pad ih264_pad_left_luma_av8;
ih264_pad ih264_pad_left_chroma_av8;
ih264_pad ih264_pad_right_luma_av8;
ih264_pad ih264_pad_right_chroma_av8;

ih264_pad ih264_pad_left_luma_ssse3;
ih264_pad ih264_pad_left_chroma_ssse3;
ih264_pad ih264_pad_right_luma_ssse3;
ih264_pad ih264_pad_right_chroma_ssse3;

#endif /*_IH264_PADDING_H_*/
