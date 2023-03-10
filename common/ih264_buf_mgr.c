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
*  ih264_buf_mgr.c
*
* @brief
*  Contains function definitions for buffer management
*
* @author
*  Srinivas T
*
* @par List of Functions:
*   - ih264_buf_mgr_size()
*   - ih264_buf_mgr_lock()
*   - ih264_buf_mgr_unlock()
*   - ih264_buf_mgr_yield()
*   - ih264_buf_mgr_free()
*   - ih264_buf_mgr_init()
*   - ih264_buf_mgr_add()
*   - ih264_buf_mgr_get_next_free()
*   - ih264_buf_mgr_check_free()
*   - ih264_buf_mgr_set_status()
*   - ih264_buf_mgr_get_status()
*   - ih264_buf_mgr_get_buf()
*   - ih264_buf_mgr_get_bufid()
*   - ih264_buf_mgr_get_num_active_buf()
*
* @remarks
*  None
*
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_defs.h"
#include "ih264_error.h"
#include "ih264_buf_mgr.h"

#include "ithread.h"

/**
*******************************************************************************
*
* @brief Returns size for buf queue context. Does not include buf queue buffer
* requirements
*
* @par   Description
* Returns size for buf queue context. Does not include buf queue buffer
* requirements. Buffer size required to store the bufs should be allocated in
* addition to the value returned here.
*
* @returns Size of the buf queue context
*
* @remarks
*
*******************************************************************************
*/
WORD32 ih264_buf_mgr_size(void) {
  WORD32 size;

  size = sizeof(buf_mgr_t);
  size += ithread_get_mutex_lock_size();

  return size;
}

/**
*******************************************************************************
*
* @brief
*   Locks the buf_mgr context
*
* @par   Description
*   Locks the buf_mgr context by calling ithread_mutex_lock()
*
* @param[in] ps_buf_mgr
*   Job Queue context
*
* @returns IH264_FAIL if mutex lock fails else IH264_SUCCESS
*
* @remarks
*
*******************************************************************************
*/
IH264_ERROR_T ih264_buf_mgr_lock(buf_mgr_t *ps_buf_mgr) {
  WORD32 retval;
  retval = ithread_mutex_lock(ps_buf_mgr->pv_mutex);
  if (retval) {
    return IH264_FAIL;
  }
  return IH264_SUCCESS;
}

/**
*******************************************************************************
*
* @brief
*   Unlocks the buf_mgr context
*
* @par   Description
*   Unlocks the buf_mgr context by calling ithread_mutex_unlock()
*
* @param[in] ps_buf_mgr
*   Job Queue context
*
* @returns IH264_FAIL if mutex unlock fails else IH264_SUCCESS
*
* @remarks
*
*******************************************************************************
*/

IH264_ERROR_T ih264_buf_mgr_unlock(buf_mgr_t *ps_buf_mgr) {
  WORD32 retval;
  retval = ithread_mutex_unlock(ps_buf_mgr->pv_mutex);
  if (retval) {
    return IH264_FAIL;
  }
  return IH264_SUCCESS;
}
/**
*******************************************************************************
*
* @brief
*   Yeilds the thread
*
* @par   Description
*   Unlocks the buf_mgr context by calling
* ih264_buf_mgr_unlock(), ithread_yield() and then ih264_buf_mgr_lock()
* buf_mgr is unlocked before to ensure the buf_mgr can be accessed by other
*threads If unlock is not done before calling yield then no other thread can
*access the buf_mgr functions and update buf_mgr.
*
* @param[in] ps_buf_mgr
*   Job Queue context
*
* @returns IH264_FAIL if mutex lock unlock or yield fails else IH264_SUCCESS
*
* @remarks
*
*******************************************************************************
*/
IH264_ERROR_T ih264_buf_mgr_yield(buf_mgr_t *ps_buf_mgr) {
  IH264_ERROR_T ret = IH264_SUCCESS;

  IH264_ERROR_T rettmp;
  rettmp = ih264_buf_mgr_unlock(ps_buf_mgr);
  RETURN_IF((rettmp != IH264_SUCCESS), rettmp);

  // ithread_usleep(10);
  ithread_yield();

  rettmp = ih264_buf_mgr_lock(ps_buf_mgr);
  RETURN_IF((rettmp != IH264_SUCCESS), rettmp);
  return ret;
}

/**
*******************************************************************************
*
* @brief free the buf queue pointers
*
* @par   Description
* Frees the buf_mgr context
*
* @param[in] pv_buf
* Memoy for buf queue buffer and buf queue context
*
* @returns Pointer to buf queue context
*
* @remarks
* Since it will be called only once by master thread this is not thread safe.
*
*******************************************************************************
*/
IH264_ERROR_T ih264_buf_mgr_free(buf_mgr_t *ps_buf_mgr) {
  WORD32 ret;
  ret = ithread_mutex_destroy(ps_buf_mgr->pv_mutex);

  if (0 == ret)
    return IH264_SUCCESS;
  else
    return IH264_FAIL;
}
/**
*******************************************************************************
*
* @brief
*      Buffer manager initialization function.
*
* @par Description:
*    Initializes the buffer manager structure
*
* @param[in] ps_buf_mgr
*  Pointer to the buffer manager
*
* @returns
*
* @remarks
*  None
*
*******************************************************************************
*/

void *ih264_buf_mgr_init(void *pv_buf) {
  WORD32 id;
  UWORD8 *pu1_buf;
  buf_mgr_t *ps_buf_mgr;
  pu1_buf = (UWORD8 *) pv_buf;

  ps_buf_mgr = (buf_mgr_t *) pu1_buf;
  pu1_buf += sizeof(buf_mgr_t);

  ps_buf_mgr->pv_mutex = pu1_buf;
  pu1_buf += ithread_get_mutex_lock_size();

  ithread_mutex_init(ps_buf_mgr->pv_mutex);

  ps_buf_mgr->i4_max_buf_cnt = BUF_MGR_MAX_CNT;
  ps_buf_mgr->i4_active_buf_cnt = 0;

  for (id = 0; id < BUF_MGR_MAX_CNT; id++) {
    ps_buf_mgr->au4_status[id] = 0;
    ps_buf_mgr->apv_ptr[id] = NULL;
  }

  return ps_buf_mgr;
}

/**
*******************************************************************************
*
* @brief
*       Adds and increments the buffer and buffer count.
*
* @par Description:
*     Adds a buffer to the buffer manager if it is not already  present and
*   increments the  active buffer count
*
* @param[in] ps_buf_mgr
*  Pointer to the buffer manager
*
* @param[in] pv_ptr
*  Pointer to the buffer to be added
*
* @returns  Returns 0 on success, -1 otherwise
*
* @remarks
*  None
*
*******************************************************************************
*/
IH264_ERROR_T ih264_buf_mgr_add(buf_mgr_t *ps_buf_mgr, void *pv_ptr,
                                WORD32 buf_id) {
  IH264_ERROR_T ret = IH264_SUCCESS;
  ret = ih264_buf_mgr_lock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  /* Check if buffer ID is within allowed range */
  if (buf_id >= ps_buf_mgr->i4_max_buf_cnt) {
    ret = ih264_buf_mgr_unlock(ps_buf_mgr);
    RETURN_IF((ret != IH264_SUCCESS), ret);

    return IH264_FAIL;
  }

  /* Check if the current ID is being used to hold some other buffer */
  if ((ps_buf_mgr->apv_ptr[buf_id] != NULL) &&
      (ps_buf_mgr->apv_ptr[buf_id] != pv_ptr)) {
    ret = ih264_buf_mgr_unlock(ps_buf_mgr);
    RETURN_IF((ret != IH264_SUCCESS), ret);

    return IH264_FAIL;
  }
  ps_buf_mgr->apv_ptr[buf_id] = pv_ptr;
  ps_buf_mgr->i4_active_buf_cnt++;

  ret = ih264_buf_mgr_unlock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  return ret;
}

/**
*******************************************************************************
*
* @brief
*   Gets the next free buffer.
*
* @par Description:
*     Returns the next free buffer available and sets the  corresponding status
*   to DEC
*
* @param[in] ps_buf_mgr
*  Pointer to the buffer manager
*
* @param[in] pi4_buf_id
*  Pointer to the id of the free buffer
*
* @returns  Pointer to the free buffer
*
* @remarks
*  None
*
*******************************************************************************
*/
void *ih264_buf_mgr_get_next_free(buf_mgr_t *ps_buf_mgr, WORD32 *pi4_buf_id) {
  WORD32 id;
  void *pv_ret_ptr;
  IH264_ERROR_T ret = IH264_SUCCESS;
  ret = ih264_buf_mgr_lock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), NULL);

  pv_ret_ptr = NULL;
  for (id = 0; id < ps_buf_mgr->i4_active_buf_cnt; id++) {
    /* Check if the buffer is non-null and status is zero */
    if ((ps_buf_mgr->au4_status[id] == 0) && (ps_buf_mgr->apv_ptr[id])) {
      *pi4_buf_id = id;
      /* DEC is set to 1 */
      ps_buf_mgr->au4_status[id] = 1;
      pv_ret_ptr = ps_buf_mgr->apv_ptr[id];
      break;
    }
  }
  ret = ih264_buf_mgr_unlock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), NULL);

  return pv_ret_ptr;
}

/**
*******************************************************************************
*
* @brief
*      Checks the buffer manager for free buffers available.
*
* @par Description:
*  Checks if there are any free buffers available
*
* @param[in] ps_buf_mgr
*  Pointer to the buffer manager
*
* @returns  Returns 0 if available, -1 otherwise
*
* @remarks
*  None
*
*******************************************************************************
*/
IH264_ERROR_T ih264_buf_mgr_check_free(buf_mgr_t *ps_buf_mgr) {
  WORD32 id;
  IH264_ERROR_T ret = IH264_SUCCESS;
  IH264_ERROR_T rettmp = IH264_SUCCESS;
  rettmp = ih264_buf_mgr_lock(ps_buf_mgr);
  RETURN_IF((rettmp != IH264_SUCCESS), ret);

  ret = IH264_FAIL;
  for (id = 0; id < ps_buf_mgr->i4_active_buf_cnt; id++) {
    if ((ps_buf_mgr->au4_status[id] == 0) && (ps_buf_mgr->apv_ptr[id])) {
      ret = IH264_SUCCESS;
      break;
    }
  }
  rettmp = ih264_buf_mgr_unlock(ps_buf_mgr);
  RETURN_IF((rettmp != IH264_SUCCESS), ret);

  return ret;
}

/**
*******************************************************************************
*
* @brief
*       Resets the status bits.
*
* @par Description:
*     resets the status bits that the mask contains (status  corresponding to
*    the id)
*
* @param[in] ps_buf_mgr
*  Pointer to the buffer manager
*
* @param[in] buf_id
*  ID of the buffer status to be released
*
* @param[in] mask
*  Contains the bits that are to be reset
*
* @returns  0 if success, -1 otherwise
*
* @remarks
*  None
*
*******************************************************************************
*/
IH264_ERROR_T ih264_buf_mgr_release(buf_mgr_t *ps_buf_mgr, WORD32 buf_id,
                                    UWORD32 mask) {
  IH264_ERROR_T ret = IH264_SUCCESS;
  ret = ih264_buf_mgr_lock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  /* If the given id is pointing to an id which is not yet added */
  if (buf_id >= ps_buf_mgr->i4_active_buf_cnt) {
    ret = ih264_buf_mgr_unlock(ps_buf_mgr);
    RETURN_IF((ret != IH264_SUCCESS), ret);
    return IH264_FAIL;
  }

  ps_buf_mgr->au4_status[buf_id] &= ~mask;

  /*     If both the REF and DISP are zero, DEC is set to zero */
  if (ps_buf_mgr->au4_status[buf_id] == 1) {
    ps_buf_mgr->au4_status[buf_id] = 0;
  }

  ret = ih264_buf_mgr_unlock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  return ret;
}

/**
*******************************************************************************
*
* @brief
*      Sets the status bit.
*
* @par Description:
*     sets the status bits that the mask contains (status  corresponding to the
*    id)
*
*
* @param[in] ps_buf_mgr
*  Pointer to the buffer manager
*
* @param[in] buf_id
*  ID of the buffer whose status needs to be modified
*
*
* @param[in] mask
*  Contains the bits that are to be set
*
* @returns  0 if success, -1 otherwise
*
* @remarks
*  None
*
*******************************************************************************
*/
IH264_ERROR_T ih264_buf_mgr_set_status(buf_mgr_t *ps_buf_mgr, WORD32 buf_id,
                                       UWORD32 mask) {
  IH264_ERROR_T ret = IH264_SUCCESS;
  ret = ih264_buf_mgr_lock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  if (buf_id >= ps_buf_mgr->i4_active_buf_cnt) {
    ret = ih264_buf_mgr_unlock(ps_buf_mgr);
    RETURN_IF((ret != IH264_SUCCESS), ret);
    return IH264_FAIL;
  }

  if ((ps_buf_mgr->au4_status[buf_id] & mask) != 0) {
    ret = ih264_buf_mgr_unlock(ps_buf_mgr);
    RETURN_IF((ret != IH264_SUCCESS), ret);
    return IH264_FAIL;
  }

  ps_buf_mgr->au4_status[buf_id] |= mask;
  ret = ih264_buf_mgr_unlock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  return ret;
}

/**
*******************************************************************************
*
* @brief
*   Returns the status of the buffer.
*
* @par Description:
*  Returns the status of the buffer corresponding to the id
*
* @param[in] ps_buf_mgr
*  Pointer to the buffer manager
*
* @param[in] buf_id
*  ID of the buffer status required
*
* @returns  Status of the buffer corresponding to the id
*
* @remarks
*  None
*
*******************************************************************************
*/
WORD32 ih264_buf_mgr_get_status(buf_mgr_t *ps_buf_mgr, WORD32 buf_id) {
  IH264_ERROR_T ret = IH264_SUCCESS;
  UWORD32 status;

  ret = ih264_buf_mgr_lock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  status = ps_buf_mgr->au4_status[buf_id];

  ret = ih264_buf_mgr_unlock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  return status;
}

/**
*******************************************************************************
*
* @brief
*      Gets the buffer from the buffer manager
*
* @par Description:
*        Returns the pointer to the buffer corresponding to the id
*
* @param[in] ps_buf_mgr
*  Pointer to the buffer manager
*
* @param[in] buf_id
*  ID of the buffer required
*
* @returns  Pointer to the buffer required
*
* @remarks
*  None
*
*******************************************************************************
*/
void *ih264_buf_mgr_get_buf(buf_mgr_t *ps_buf_mgr, WORD32 buf_id) {
  IH264_ERROR_T ret = IH264_SUCCESS;
  void *pv_buf;
  ret = ih264_buf_mgr_lock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), NULL);

  pv_buf = ps_buf_mgr->apv_ptr[buf_id];

  ret = ih264_buf_mgr_unlock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), NULL);

  return pv_buf;
}

/**
*******************************************************************************
*
* @brief
*  Gets the buffer id from the buffer manager if the buffer is added to the
*  buffer manager
*
* @par Description:
*  Returns the buffer id corresponding to the given buffer if it exists
*
* @param[in] ps_buf_mgr
*  Pointer to the buffer manager
*
* @param[in] pv_buf
*  Pointer to the buffer
*
* @returns  Buffer id if exists, else -1
*
* @remarks
*  None
*
*******************************************************************************
*/
WORD32 ih264_buf_mgr_get_bufid(buf_mgr_t *ps_buf_mgr, void *pv_buf) {
  WORD32 id;
  WORD32 buf_id = -1;
  IH264_ERROR_T ret = IH264_SUCCESS;
  ret = ih264_buf_mgr_lock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  for (id = 0; id < ps_buf_mgr->i4_active_buf_cnt; id++) {
    if (ps_buf_mgr->apv_ptr[id] == pv_buf) {
      buf_id = id;
      break;
    }
  }
  ret = ih264_buf_mgr_unlock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  return buf_id;
}

/**
*******************************************************************************
*
* @brief
*        Gets the no.of active buffer
*
* @par Description:
*      Return the number of active buffers in the buffer manager
*
* @param[in] ps_buf_mgr
*  Pointer to the buffer manager
*
* @returns  number of active buffers
*
* @remarks
*  None
*
*******************************************************************************
*/
UWORD32 ih264_buf_mgr_get_num_active_buf(buf_mgr_t *ps_buf_mgr) {
  UWORD32 u4_buf_cnt;
  IH264_ERROR_T ret = IH264_SUCCESS;

  u4_buf_cnt = 0;

  ret = ih264_buf_mgr_lock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), ret);
  u4_buf_cnt = ps_buf_mgr->i4_active_buf_cnt;

  ret = ih264_buf_mgr_unlock(ps_buf_mgr);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  return u4_buf_cnt;
}
