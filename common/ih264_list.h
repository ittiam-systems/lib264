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
*  ih264_list.h
*
* @brief
*  Contains functions for buf queue
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

#ifndef _IH264_LIST_H_
#define _IH264_LIST_H_

typedef struct {
  /** Pointer to buffer base which contains the bufs */
  void *pv_buf_base;

  /** Mutex used to keep the functions thread-safe */
  void *pv_mutex;

  /** Current write index */
  volatile WORD32 i4_buf_wr_idx;

  /** Current read index */
  volatile WORD32 i4_buf_rd_idx;

  /** Maximum index */
  WORD32 i4_buf_max_idx;

  /** Log2(buf_max_idx) -
   * To ensure number of entries is power of two
   * This makes it easier to wrap around by using AND with buf_max_idx - 1
   * */
  WORD32 i4_log2_buf_max_idx;

  /** Flag to indicate list has to be terminated */
  WORD32 i4_terminate;

  /** Size of each entry */
  WORD32 i4_entry_size;

  /** If the list is to be used frequently send this as zero, else send a large
   * value to ensure cores are not loaded unnecessarily. For eg: For picture
   * level queues this can be a large value like 100us but for jobq this will be
   * zero.
   */
  WORD32 i4_yeild_interval_us;

} list_t;

WORD32 ih264_list_size(WORD32 num_entries, WORD32 entry_size);
void *ih264_list_init(void *pv_buf, WORD32 buf_size, WORD32 num_entries,
                      WORD32 entry_size, WORD32 yeild_interval_us);
IH264_ERROR_T ih264_list_free(list_t *ps_list);
IH264_ERROR_T ih264_list_reset(list_t *ps_list);
IH264_ERROR_T ih264_list_deinit(list_t *ps_list);
IH264_ERROR_T ih264_list_terminate(list_t *ps_list);
IH264_ERROR_T ih264_list_queue(list_t *ps_list, void *pv_buf, WORD32 blocking);
IH264_ERROR_T ih264_list_dequeue(list_t *ps_list, void *pv_buf,
                                 WORD32 blocking);

#endif /* _IH264_PROCESS_SLICE_H_ */
