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

#ifndef _IH264D_MEM_REQUEST_H_
#define _IH264D_MEM_REQUEST_H_
/*!
 ***************************************************************************
 * \file ih264d_mem_request.h
 *
 * \brief
 *    This file contains declarations and data structures of the API's which
 *    required to interact with Picture Buffer.
 *
 *
 * \date
 *    11/12/2002
 *
 * \author  NS
 ***************************************************************************/
#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264d_defs.h"
#include "ih264d_structs.h"

#define MAX_MEM_BLOCKS 64 + 8

struct MemBlock {
  void **v_memLocation; /** memory location where address of allocated memory
                           should be stored*/
  UWORD32 u4_mem_size;  /** Size of the memory block */
};

struct MemReq {
  UWORD32 u4_num_memBlocks; /** Number of memory blocks */
  struct MemBlock
      s_memBlock[MAX_MEM_BLOCKS]; /** Pointer to the first memory block */
};

struct PicMemBlock {
  void *buf1; /** memory location for buf1 */
  void *buf2; /** memory location for buf2 */
  void *buf3; /** memory location for buf3 */
};

struct PicMemReq {
  WORD32 i4_num_pic_memBlocks; /** Number of memory blocks */
  UWORD32 u4_size1;            /** Size of the buf1 in PicMemBlock */
  UWORD32 u4_size2;            /** Size of the buf2 in PicMemBlock */
  UWORD32 u4_size3;            /** Size of the buf3 in PicMemBlock */
  struct PicMemBlock s_PicMemBlock[MAX_DISP_BUFS_NEW];
};

WORD32 ih264d_create_pic_buffers(UWORD8 u1_num_of_buf, dec_struct_t *ps_dec);

WORD32 ih264d_create_mv_bank(void *pv_codec_handle, UWORD32 u4_wd,
                             UWORD32 u4_ht);
WORD16 ih264d_get_memory_dec_params(dec_struct_t *ps_dec);

#endif /* _IH264D_MEM_REQUEST_H_ */
