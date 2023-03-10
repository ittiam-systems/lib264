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
*  ih264_disp_mgr.c
*
* @brief
*  Contains function definitions for display management
*
* @author
*  Srinivas T
*
* @par List of Functions:
*   - ih264_disp_mgr_init()
*   - ih264_disp_mgr_add()
*   - ih264_disp_mgr_get()
*
* @remarks
*  None
*
*******************************************************************************
*/
#include <stdlib.h>
#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_disp_mgr.h"

/**
*******************************************************************************
*
* @brief
*    Initialization function for display buffer manager
*
* @par Description:
*    Initializes the display buffer management structure
*
* @param[in] ps_disp_mgr
*  Pointer to the display buffer management structure
*
* @returns none
*
* @remarks
*  None
*
*******************************************************************************
*/
void ih264_disp_mgr_init(disp_mgr_t *ps_disp_mgr) {
  WORD32 id;

  ps_disp_mgr->u4_last_abs_poc = DEFAULT_POC;

  for (id = 0; id < DISP_MGR_MAX_CNT; id++) {
    ps_disp_mgr->ai4_abs_poc[id] = DEFAULT_POC;
    ps_disp_mgr->apv_ptr[id] = NULL;
  }
}

/**
*******************************************************************************
*
* @brief
*     Adds a buffer to the display manager
*
* @par Description:
*      Adds a buffer to the display buffer manager
*
* @param[in] ps_disp_mgr
*  Pointer to the display buffer management structure
*
* @param[in] buf_id
*  ID of the display buffer
*
* @param[in] abs_poc
*  Absolute POC of the display buffer
*
* @param[in] pv_ptr
*  Pointer to the display buffer
*
* @returns  0 if success, -1 otherwise
*
* @remarks
*  None
*
*******************************************************************************
*/
WORD32 ih264_disp_mgr_add(disp_mgr_t *ps_disp_mgr, WORD32 buf_id,
                          WORD32 abs_poc, void *pv_ptr) {
  if (buf_id >= DISP_MGR_MAX_CNT) {
    return (-1);
  }

  if (ps_disp_mgr->apv_ptr[buf_id] != NULL) {
    return (-1);
  }

  ps_disp_mgr->apv_ptr[buf_id] = pv_ptr;
  ps_disp_mgr->ai4_abs_poc[buf_id] = abs_poc;
  return 0;
}

/**
*******************************************************************************
*
* @brief
*  Gets the next buffer
*
* @par Description:
*  Gets the next display buffer
*
* @param[in] ps_disp_mgr
*  Pointer to the display buffer structure
*
* @param[out]  pi4_buf_id
*  Pointer to hold buffer id of the display buffer being returned
*
* @returns  Pointer to the next display buffer
*
* @remarks
*  None
*
*******************************************************************************
*/
void *ih264_disp_mgr_get(disp_mgr_t *ps_disp_mgr, WORD32 *pi4_buf_id) {
  WORD32 id;
  void *pv_ret_ptr;
  WORD32 i4_min_poc;
  WORD32 min_poc_id;

  pv_ret_ptr = NULL;
  i4_min_poc = 0x7FFFFFFF;
  min_poc_id = -1;

  /* Find minimum POC */
  for (id = 0; id < DISP_MGR_MAX_CNT; id++) {
    if ((DEFAULT_POC != ps_disp_mgr->ai4_abs_poc[id]) &&
        (ps_disp_mgr->ai4_abs_poc[id] <= i4_min_poc)) {
      i4_min_poc = ps_disp_mgr->ai4_abs_poc[id];
      min_poc_id = id;
    }
  }
  *pi4_buf_id = min_poc_id;
  /* If all pocs are still default_poc then return NULL */
  if (-1 == min_poc_id) {
    return NULL;
  }

  pv_ret_ptr = ps_disp_mgr->apv_ptr[min_poc_id];

  /* Set abs poc to default and apv_ptr to null so that the buffer is not
   * returned again */
  ps_disp_mgr->apv_ptr[min_poc_id] = NULL;
  ps_disp_mgr->ai4_abs_poc[min_poc_id] = DEFAULT_POC;
  return pv_ret_ptr;
}
