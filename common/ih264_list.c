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
*  ih264_list.c
*
* @brief
*  Contains functions for buf queue
*
* @author
*  Harish
*
* @par List of Functions:
*  ih264_list_size()
*  ih264_list_lock()
*  ih264_list_unlock()
*  ih264_list_yield()
*  ih264_list_free()
*  ih264_list_init()
*  ih264_list_reset()
*  ih264_list_deinit()
*  ih264_list_terminate()
*  ih264_list_queue()
*  ih264_list_dequeue()
*
* @remarks
*  None
*
*******************************************************************************
*/
/*****************************************************************************/
/* File Includes                                                             */
/*****************************************************************************/
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ih264_typedefs.h"
#include "ithread.h"
#include "ih264_platform_macros.h"
#include "ih264_macros.h"
#include "ih264_debug.h"
#include "ih264_error.h"
#include "ih264_list.h"

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
WORD32 ih264_list_size(WORD32 num_entries, WORD32 entry_size) {
  WORD32 size;
  WORD32 clz;
  size = sizeof(list_t);
  size += ithread_get_mutex_lock_size();

  /* Use next power of two number of entries*/
  clz = CLZ(num_entries);
  num_entries = 1 << (32 - clz);

  size += num_entries * entry_size;
  return size;
}

/**
*******************************************************************************
*
* @brief
*   Locks the list context
*
* @par   Description
*   Locks the list context by calling ithread_mutex_lock()
*
* @param[in] ps_list
*   Job Queue context
*
* @returns IH264_FAIL if mutex lock fails else IH264_SUCCESS
*
* @remarks
*
*******************************************************************************
*/
IH264_ERROR_T ih264_list_lock(list_t *ps_list) {
  WORD32 retval;
  retval = ithread_mutex_lock(ps_list->pv_mutex);
  if (retval) {
    return IH264_FAIL;
  }
  return IH264_SUCCESS;
}

/**
*******************************************************************************
*
* @brief
*   Unlocks the list context
*
* @par   Description
*   Unlocks the list context by calling ithread_mutex_unlock()
*
* @param[in] ps_list
*   Job Queue context
*
* @returns IH264_FAIL if mutex unlock fails else IH264_SUCCESS
*
* @remarks
*
*******************************************************************************
*/

IH264_ERROR_T ih264_list_unlock(list_t *ps_list) {
  WORD32 retval;
  retval = ithread_mutex_unlock(ps_list->pv_mutex);
  if (retval) {
    return IH264_FAIL;
  }
  return IH264_SUCCESS;
}
/**
*******************************************************************************
*
* @brief
*   Yields the thread
*
* @par   Description
*   Unlocks the list context by calling
* ih264_list_unlock(), ithread_yield() and then ih264_list_lock()
* list is unlocked before to ensure the list can be accessed by other threads
* If unlock is not done before calling yield then no other thread can access
* the list functions and update list.
*
* @param[in] ps_list
*   Job Queue context
*
* @returns IH264_FAIL if mutex lock unlock or yield fails else IH264_SUCCESS
*
* @remarks
*
*******************************************************************************
*/
IH264_ERROR_T ih264_list_yield(list_t *ps_list) {
  IH264_ERROR_T ret = IH264_SUCCESS;

  IH264_ERROR_T rettmp;
  rettmp = ih264_list_unlock(ps_list);
  RETURN_IF((rettmp != IH264_SUCCESS), rettmp);

  ithread_yield();

  if (ps_list->i4_yeild_interval_us > 0)
    ithread_usleep(ps_list->i4_yeild_interval_us);

  rettmp = ih264_list_lock(ps_list);
  RETURN_IF((rettmp != IH264_SUCCESS), rettmp);
  return ret;
}

/**
*******************************************************************************
*
* @brief free the buf queue pointers
*
* @par   Description
* Frees the list context
*
* @param[in] pv_buf
* Memory for buf queue buffer and buf queue context
*
* @returns Pointer to buf queue context
*
* @remarks
* Since it will be called only once by master thread this is not thread safe.
*
*******************************************************************************
*/
IH264_ERROR_T ih264_list_free(list_t *ps_list) {
  WORD32 ret;
  ret = ithread_mutex_destroy(ps_list->pv_mutex);

  if (0 == ret)
    return IH264_SUCCESS;
  else
    return IH264_FAIL;
}

/**
*******************************************************************************
*
* @brief Initialize the buf queue
*
* @par   Description
* Initializes the list context and sets write and read pointers to start of
* buf queue buffer
*
* @param[in] pv_buf
* Memoy for buf queue buffer and buf queue context
*
* @param[in] buf_size
* Size of the total memory allocated
*
* @returns Pointer to buf queue context
*
* @remarks
* Since it will be called only once by master thread this is not thread safe.
*
*******************************************************************************
*/
void *ih264_list_init(void *pv_buf, WORD32 buf_size, WORD32 num_entries,
                      WORD32 entry_size, WORD32 yeild_interval_us) {
  list_t *ps_list;
  UWORD8 *pu1_buf;

  pu1_buf = (UWORD8 *) pv_buf;

  ps_list = (list_t *) pu1_buf;
  pu1_buf += sizeof(list_t);
  buf_size -= sizeof(list_t);

  ps_list->pv_mutex = pu1_buf;
  pu1_buf += ithread_get_mutex_lock_size();
  buf_size -= ithread_get_mutex_lock_size();

  if (buf_size <= 0) return NULL;

  ithread_mutex_init(ps_list->pv_mutex);

  /* Ensure num_entries is power of two */
  ASSERT(0 == (num_entries & (num_entries - 1)));

  /* Ensure remaining buffer is large enough to hold given number of entries */
  ASSERT((num_entries * entry_size) <= buf_size);

  ps_list->pv_buf_base = pu1_buf;
  ps_list->i4_terminate = 0;
  ps_list->i4_entry_size = entry_size;
  ps_list->i4_buf_rd_idx = 0;
  ps_list->i4_buf_wr_idx = 0;
  ps_list->i4_log2_buf_max_idx = 32 - CLZ(num_entries);
  ps_list->i4_buf_max_idx = num_entries;
  ps_list->i4_yeild_interval_us = yeild_interval_us;

  return ps_list;
}
/**
*******************************************************************************
*
* @brief
*   Resets the list context
*
* @par   Description
*   Resets the list context by initializing buf queue context elements
*
* @param[in] ps_list
*   Job Queue context
*
* @returns IH264_FAIL if lock unlock fails else IH264_SUCCESS
*
* @remarks
*
*******************************************************************************
*/
IH264_ERROR_T ih264_list_reset(list_t *ps_list) {
  IH264_ERROR_T ret = IH264_SUCCESS;
  ret = ih264_list_lock(ps_list);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  ps_list->i4_terminate = 0;
  ps_list->i4_buf_rd_idx = 0;
  ps_list->i4_buf_wr_idx = 0;

  ret = ih264_list_unlock(ps_list);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  return ret;
}

/**
*******************************************************************************
*
* @brief
*   Deinitializes the list context
*
* @par   Description
*   Deinitializes the list context by calling ih264_list_reset()
* and then destrying the mutex created
*
* @param[in] ps_list
*   Job Queue context
*
* @returns IH264_FAIL if lock unlock fails else IH264_SUCCESS
*
* @remarks
*
*******************************************************************************
*/
IH264_ERROR_T ih264_list_deinit(list_t *ps_list) {
  WORD32 retval;
  IH264_ERROR_T ret = IH264_SUCCESS;

  ret = ih264_list_reset(ps_list);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  retval = ithread_mutex_destroy(ps_list->pv_mutex);
  if (retval) {
    return IH264_FAIL;
  }

  return IH264_SUCCESS;
}

/**
*******************************************************************************
*
* @brief
*   Terminates the list
*
* @par   Description
*   Terminates the list by setting a flag in context.
*
* @param[in] ps_list
*   Job Queue context
*
* @returns IH264_FAIL if lock unlock fails else IH264_SUCCESS
*
* @remarks
*
*******************************************************************************
*/

IH264_ERROR_T ih264_list_terminate(list_t *ps_list) {
  IH264_ERROR_T ret = IH264_SUCCESS;
  ret = ih264_list_lock(ps_list);
  RETURN_IF((ret != IH264_SUCCESS), ret);

  ps_list->i4_terminate = 1;

  ret = ih264_list_unlock(ps_list);
  RETURN_IF((ret != IH264_SUCCESS), ret);
  return ret;
}

/**
*******************************************************************************
*
* @brief Adds a buf to the queue
*
* @par   Description
* Adds a buf to the queue and updates wr address to next location.
* Format/content of the buf structure is abstracted and hence size of the buf
* buffer is being passed.
*
* @param[in] ps_list
*   Job Queue context
*
* @param[in] pv_buf
*   Pointer to the location that contains details of the buf to be added
*
* @param[in] buf_size
*   Size of the buf buffer
*
* @param[in] blocking
*   To signal if the write is blocking or non-blocking.
*
* @returns
*
* @remarks
* Job Queue buffer is assumed to be allocated to handle worst case number of
*bufs Wrap around is not supported
*
*******************************************************************************
*/
IH264_ERROR_T ih264_list_queue(list_t *ps_list, void *pv_buf, WORD32 blocking) {
  IH264_ERROR_T ret = IH264_SUCCESS;
  IH264_ERROR_T rettmp;

  WORD32 diff;
  void *pv_buf_wr;

  volatile WORD32 *pi4_wr_idx, *pi4_rd_idx;
  WORD32 buf_size = ps_list->i4_entry_size;

  rettmp = ih264_list_lock(ps_list);
  RETURN_IF((rettmp != IH264_SUCCESS), rettmp);

  while (1) {
    /* Ensure wr idx does not go beyond rd idx by more than number of entries
     */
    pi4_wr_idx = &ps_list->i4_buf_wr_idx;
    pi4_rd_idx = &ps_list->i4_buf_rd_idx;
    diff = *pi4_wr_idx - *pi4_rd_idx;

    if (diff < ps_list->i4_buf_max_idx) {
      WORD32 wr_idx;
      wr_idx = ps_list->i4_buf_wr_idx & (ps_list->i4_buf_max_idx - 1);
      pv_buf_wr = (UWORD8 *) ps_list->pv_buf_base + wr_idx * buf_size;

      memcpy(pv_buf_wr, pv_buf, buf_size);
      ps_list->i4_buf_wr_idx++;
      break;
    } else {
      /* wr is ahead, so wait for rd to consume */
      if (blocking) {
        ih264_list_yield(ps_list);
      } else {
        ret = IH264_FAIL;
        break;
      }
    }
  }
  ps_list->i4_terminate = 0;

  rettmp = ih264_list_unlock(ps_list);
  RETURN_IF((rettmp != IH264_SUCCESS), rettmp);

  return ret;
}
/**
*******************************************************************************
*
* @brief Gets next from the Job queue
*
* @par   Description
* Gets next buf from the buf queue and updates rd address to next location.
* Format/content of the buf structure is abstracted and hence size of the buf
* buffer is being passed. If it is a blocking call and if there is no new buf
* then this functions unlocks the mutex and calls yield and then locks it back.
* and continues till a buf is available or terminate is set
*
* @param[in] ps_list
*   Job Queue context
*
* @param[out] pv_buf
*   Pointer to the location that contains details of the buf to be written
*
* @param[in] buf_size
*   Size of the buf buffer
*
* @param[in] blocking
*   To signal if the read is blocking or non-blocking.
*
* @returns
*
* @remarks
* Job Queue buffer is assumed to be allocated to handle worst case number of
*bufs Wrap around is not supported
*
*******************************************************************************
*/
IH264_ERROR_T ih264_list_dequeue(list_t *ps_list, void *pv_buf,
                                 WORD32 blocking) {
  IH264_ERROR_T ret = IH264_SUCCESS;
  IH264_ERROR_T rettmp;
  WORD32 buf_size = ps_list->i4_entry_size;
  WORD32 diff;

  void *pv_buf_rd;
  volatile WORD32 *pi4_wr_idx, *pi4_rd_idx;

  rettmp = ih264_list_lock(ps_list);
  RETURN_IF((rettmp != IH264_SUCCESS), rettmp);

  while (1) {
    /* Ensure wr idx is ahead of rd idx and
     * wr idx does not go beyond rd idx by more than number of entries
     */
    pi4_wr_idx = &ps_list->i4_buf_wr_idx;
    pi4_rd_idx = &ps_list->i4_buf_rd_idx;
    diff = *pi4_wr_idx - *pi4_rd_idx;

    if (diff > 0) {
      WORD32 rd_idx;
      rd_idx = ps_list->i4_buf_rd_idx & (ps_list->i4_buf_max_idx - 1);
      pv_buf_rd = (UWORD8 *) ps_list->pv_buf_base + rd_idx * buf_size;

      memcpy(pv_buf, pv_buf_rd, buf_size);
      ps_list->i4_buf_rd_idx++;
      break;
    } else {
      /* If terminate is signaled then break */
      if (ps_list->i4_terminate) {
        ret = IH264_FAIL;
        break;
      }
      /* wr is ahead, so wait for rd to consume */
      if (blocking) {
        ih264_list_yield(ps_list);
      } else {
        ret = IH264_FAIL;
        break;
      }
    }
  }

  rettmp = ih264_list_unlock(ps_list);
  RETURN_IF((rettmp != IH264_SUCCESS), rettmp);

  return ret;
}
