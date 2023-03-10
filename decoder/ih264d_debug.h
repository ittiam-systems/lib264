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
#ifndef _IH264D_DEBUG_H_
#define _IH264D_DEBUG_H_

/*!
 **************************************************************************
 * \file ih264d_debug.h
 *
 * \brief
 *    Contains declarations used for debugging
 *
 * \date
 *    2/12/2002
 *
 * \author  AI
 **************************************************************************
 */
#ifdef DEBUG_DEC
#define H264_DEC_DEBUG_PRINT(...)                            \
  printf("\n[H264_DEBUG] %s/%d:: ", __FUNCTION__, __LINE__); \
  printf(__VA_ARGS__)
#else  // DEBUG_DEC
#define H264_DEC_DEBUG_PRINT(...) \
  {}
#endif                         // DEBUG_DEC
#define STRENGTH_DEBLOCKING 0  // sanjeev
#define DEBUG_RECONSTRUCT_LUMA 0
#define DEBUG_RECONSTRUCT_CHROMA 0

#define DEBUG_IDCT 0
#define DEBUG_LUMA_IDCT 0
#define DEBUG_REF_IDCT 0

#define BIN_BIT_RATIO 0
#define MB_PART_HIST 0

#define MB_INTRA_PREDICTION 1

#ifdef WIN32
#define CHK_PURIFY 0
#else
#define CHK_PURIFY 0
#endif

#if MB_INTRA_PREDICTION
#define MB_INTRA_CHROMA_PREDICTION_ON 1
#define MB_INTRA_4x4_PREDICTION_ON 1
#define MB_INTRA_16x16_PREDICTION_ON 1
#endif

#define TRACE 0
#define DEBUG_CABAC 0
#define DEBUG_ABS_MVD 0
#define DEBUG_INTRA_PRED_MODES 0
#define DEBUG_DEBLOCKING 0

#define COPYTHECONTEXT(s, val)
#define PRINT_TRACE
#define PRINT_TRACE_CAB
#define SWITCHOFFTRACE
#define SWITCHONTRACE
#define SWITCHOFFTRACECABAC
#define SWITCHONTRACECABAC

#define INC_BIN_COUNT(ps_cab_env)
#define INC_DECISION_BINS(ps_cab_env)
#define INC_BYPASS_BINS(ps_cab_env)
#define INC_SYM_COUNT(ps_cab_env)
#define PRINT_BIN_BIT_RATIO(ps_dec)
#define RESET_BIN_COUNTS(ps_cab_env)

#ifdef PROFILE_DIS_DEBLK
#define PROFILE_DISABLE_DEBLK() return;
#else
#define PROFILE_DISABLE_DEBLK() ;
#endif

#ifdef PROFILE_DIS_IQ_IT_RECON
#define PROFILE_DISABLE_IQ_IT_RECON() if (0)
#define PROFILE_DISABLE_IQ_IT_RECON_RETURN() return;
#else
#define PROFILE_DISABLE_IQ_IT_RECON() ;
#define PROFILE_DISABLE_IQ_IT_RECON_RETURN() ;
#endif

#ifdef PROFILE_DIS_INTRA_PRED
#define PROFILE_DISABLE_INTRA_PRED() if (0)
#else
#define PROFILE_DISABLE_INTRA_PRED() ;
#endif

#ifdef PROFILE_DIS_UNPACK
#define PROFILE_DISABLE_UNPACK_LUMA() return 0;
#define PROFILE_DISABLE_UNPACK_CHROMA() return;
#else
#define PROFILE_DISABLE_UNPACK_LUMA() ;
#define PROFILE_DISABLE_UNPACK_CHROMA() ;
#endif

#ifdef PROFILE_DIS_INTER_PRED
#define PROFILE_DISABLE_INTER_PRED() return;
#else
#define PROFILE_DISABLE_INTER_PRED() ;
#endif

#ifdef PROFILE_DIS_BOUNDARY_STRENGTH
#define PROFILE_DISABLE_BOUNDARY_STRENGTH() return;
#else
#define PROFILE_DISABLE_BOUNDARY_STRENGTH() ;
#endif

#ifdef PROFILE_DIS_MB_PART_INFO
#define PROFILE_DISABLE_MB_PART_INFO() return 0;
#else
#define PROFILE_DISABLE_MB_PART_INFO() ;
#endif

#endif /* _IH264D_DEBUG_H_ */
