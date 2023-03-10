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
*  ih264_buf_mgr.h
*
* @brief
*  Function declarations used for buffer management
*
* @remarks
*  None
*
*******************************************************************************
*/
#ifndef _IH264_BUF_MGR_H_
#define _IH264_BUF_MGR_H_

#define BUF_MGR_MAX_CNT 64

/** Flag for current encoding decoder */
#define BUF_MGR_CODEC (1 << 1)

/** Flag for reference status */
#define BUF_MGR_REF (1 << 2)

/** Flag for I/O - Display/output in case of decoder, capture/input in case of
 * encoder */
#define BUF_MGR_IO (1 << 3)

typedef struct {
  /**
   * Mutex used to keep the functions thread-safe
   */
  void *pv_mutex;

  /**
   * max_buf_cnt
   */
  WORD32 i4_max_buf_cnt;

  /**
   * active_buf_cnt
   */
  WORD32 i4_active_buf_cnt;

  /**
   *  au4_status[BUF_MGR_MAX_CNT]
   */
  UWORD32 au4_status[BUF_MGR_MAX_CNT];

  /* The last three bit of status are:    */

  /* Bit 0 - IN USE                       */
  /* Bit 1 - CODEC                        */
  /* Bit 2 - REF                          */
  /* Bit 3 - DISP/IO/RECON                */
  void *apv_ptr[BUF_MGR_MAX_CNT];

} buf_mgr_t;

// Returns size of the buffer manager context
WORD32 ih264_buf_mgr_size(void);

// Free buffer manager
IH264_ERROR_T ih264_buf_mgr_free(buf_mgr_t *ps_buf_mgr);

// Initializes the buffer API structure
void *ih264_buf_mgr_init(void *pv_buf);

// Add buffer to buffer manager. 0: success, -1: fail (u4_active_buf_cnt has
// reached u4_max_buf_cnt)
IH264_ERROR_T ih264_buf_mgr_add(buf_mgr_t *ps_buf_mgr, void *pv_ptr,
                                WORD32 buf_id);

// this function will set the buffer status to DEC
void *ih264_buf_mgr_get_next_free(buf_mgr_t *ps_buf_mgr, WORD32 *pi4_id);

// this function will check if there are any free buffers
IH264_ERROR_T ih264_buf_mgr_check_free(buf_mgr_t *ps_buf_mgr);

// mask will have who released it: DISP:REF:DEC
IH264_ERROR_T ih264_buf_mgr_release(buf_mgr_t *ps_buf_mgr, WORD32 id,
                                    UWORD32 mask);

// sets the status to one or all of DISP:REF:DEC
IH264_ERROR_T ih264_buf_mgr_set_status(buf_mgr_t *ps_buf_mgr, WORD32 id,
                                       UWORD32 mask);

// Gets status of the buffer
WORD32 ih264_buf_mgr_get_status(buf_mgr_t *ps_buf_mgr, WORD32 id);

// pass the ID - buffer will be returned
void *ih264_buf_mgr_get_buf(buf_mgr_t *ps_buf_mgr, WORD32 id);
// Pass buffer to get ID
WORD32 ih264_buf_mgr_get_bufid(buf_mgr_t *ps_buf_mgr, void *pv_buf);

// will return number of active buffers
UWORD32 ih264_buf_mgr_get_num_active_buf(buf_mgr_t *ps_buf_mgr);

#endif /* _IH264_BUF_MGR_H_ */
