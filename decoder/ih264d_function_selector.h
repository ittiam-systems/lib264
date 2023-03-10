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
 *  ih264d_function_selector.h
 *
 * @brief
 *  Structure definitions used in the decoder
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

#ifndef _IH264D_FUNCTION_SELECTOR_H_
#define _IH264D_FUNCTION_SELECTOR_H_

#define D_ARCH_NA 1
#define D_ARCH_ARM_NONEON 2
#define D_ARCH_ARM_A9Q 3
#define D_ARCH_ARM_A9A 4
#define D_ARCH_ARM_A9 5
#define D_ARCH_ARM_A7 6
#define D_ARCH_ARM_A5 7
#define D_ARCH_ARM_A15 8
#define D_ARCH_ARM_NEONINTR 9
#define D_ARCH_ARMV8_GENERIC 10
#define D_ARCH_X86_GENERIC 11
#define D_ARCH_X86_SSSE3 12
#define D_ARCH_X86_SSE42 13
#define D_ARCH_X86_AVX2 14
#define D_ARCH_MIPS_GENERIC 15
#define D_ARCH_MIPS_32 16

void ih264d_init_arch(dec_struct_t *ps_codec);

void ih264d_init_function_ptr(dec_struct_t *ps_codec);

void ih264d_init_function_ptr_generic(dec_struct_t *ps_codec);
void ih264d_init_function_ptr_ssse3(dec_struct_t *ps_codec);
void ih264d_init_function_ptr_sse42(dec_struct_t *ps_codec);

#ifndef DISABLE_AVX2
void ih264d_init_function_ptr_avx2(dec_struct_t *ps_codec);
#endif

void ih264d_init_function_ptr_a9q(dec_struct_t *ps_codec);
void ih264d_init_function_ptr_av8(dec_struct_t *ps_codec);

#endif /* _IH264D_FUNCTION_SELECTOR_H_ */
