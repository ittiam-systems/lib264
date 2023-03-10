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
 *  ih264_dpb_mgr.h
 *
 * @brief
 *  Function declarations used for decoded picture buffer management
 *
 * @author
 *  Srinivas T
 *
 *
 * @remarks
 *  None
 *
 *******************************************************************************
 */
#ifndef _IH264_DPB_MGR_H_
#define _IH264_DPB_MGR_H_

/* Temporary definitions. Have to be defined later */

#define MAX_DPB_BUFS (MAX_DPB_SIZE * 4)

#define MARK_ST_PICNUM_AS_NONREF 1
#define MARK_LT_INDEX_AS_NONREF 2
#define MARK_ST_PICNUM_AS_LT_INDEX 3
#define RESET_REF_PICTURES 5

typedef struct dpb_info_t dpb_info_t;

enum {
  INVALID = -1,
  UNUSED_FOR_REF = 0,
  LONG_TERM_REF,
  SHORT_TERM_REF,
};
struct dpb_info_t {
  /**
   * Pointer to picture buffer structure
   */
  pic_buf_t *ps_pic_buf;

  /**
   * Link to the DPB buffer with previous link
   */
  dpb_info_t *ps_prev_dpb;
};

typedef struct {
  /**
   * Pointer to the most recent pic Num
   */
  dpb_info_t *ps_dpb_short_term_head;

  /**
   * Pointer to the most recent pic Num
   */
  dpb_info_t *ps_dpb_long_term_head;

  /**
   * Physical storage for dpbInfo for ref bufs
   */
  dpb_info_t as_dpb_info[MAX_DPB_BUFS];

  /**
   * Array of structures for bottom field.
   */
  pic_buf_t as_top_field_pics[MAX_DPB_BUFS];

  /**
   * Array of structures for bottom field.
   */
  pic_buf_t as_bottom_field_pics[MAX_DPB_BUFS];

  /**
   * Number of short-term reference buffers
   */
  UWORD8 u1_num_short_term_ref_bufs;

  /**
   * Number of long-term reference buffers
   */
  UWORD8 u1_num_long_term_ref_bufs;

  /**
   * buffer ID current frame
   */
  WORD32 i4_cur_frame_buf_id;

} dpb_mgr_t;

void ih264_dpb_mgr_init(dpb_mgr_t *ps_dpb_mgr);

WORD32 ih264_dpb_mgr_insert_ref_frame(dpb_mgr_t *ps_dpb_mgr,
                                      pic_buf_t *ps_pic_buf,
                                      WORD32 reference_type, UWORD32 frame_num,
                                      WORD32 long_term_frame_idx);

WORD32 ih264_dpb_mgr_delete_ref_frame(dpb_mgr_t *ps_dpb_mgr,
                                      WORD32 reference_type);

WORD32 ih264_dpb_mgr_delete_all_ref_frames(dpb_mgr_t *ps_dpb_mgr);

WORD32 ih264_dpb_mgr_count_ref_frames(dpb_mgr_t *ps_dpb_mgr,
                                      WORD32 curr_frame_num,
                                      WORD32 max_frame_num);

WORD32 ih264_dpb_mgr_delete_short_ref_frame(dpb_mgr_t *ps_dpb_mgr,
                                            WORD32 curr_frame_num,
                                            WORD32 max_frame_num);

WORD32 ih264_dpb_mgr_insert_ref_field(dpb_mgr_t *ps_dpb_mgr,
                                      pic_buf_t *ps_pic_buf,
                                      WORD32 reference_type, UWORD32 frame_num,
                                      WORD32 long_term_frame_idx);

WORD32 ih264_dpb_mgr_delete_ref_field(dpb_mgr_t *ps_dpb_mgr,
                                      WORD32 reference_type);

WORD32 ih264_dpb_mgr_alternate_ref_fields(dpb_mgr_t *ps_dpb_mgr,
                                          WORD32 reference_type,
                                          WORD32 first_field_type);

WORD32 ih264_dpb_mgr_sort_short_term_fields_by_frame_num(
    dpb_mgr_t *ps_dpb_mgr, WORD32 curr_frame_num, WORD32 first_field_type,
    WORD32 max_frame_num);

WORD32 ih264_dpb_mgr_sort_short_term_fields_by_poc_l0(dpb_mgr_t *ps_dpb_mgr,
                                                      WORD32 curr_poc,
                                                      WORD32 first_field_type);

WORD32 ih264_dpb_mgr_sort_short_term_fields_by_poc_l1(dpb_mgr_t *ps_dpb_mgr,
                                                      WORD32 curr_poc,
                                                      WORD32 first_field_type);

WORD32 ih264_dpb_mgr_sort_long_term_fields_by_frame_idx(
    dpb_mgr_t *ps_dpb_mgr, WORD32 first_field_type);

WORD32 ih264_dpb_mgr_delete_long_ref_fields_max_frame_idx(dpb_mgr_t *ps_dpb_mgr,
                                                          WORD32 max_frame_idx);

void ih264_dpb_mgr_del_ref(dpb_mgr_t *ps_dpb_mgr, buf_mgr_t *ps_buf_mgr,
                           WORD32 u4_abs_poc);

pic_buf_t *ih264_dpb_mgr_get_ref_by_nearest_poc(dpb_mgr_t *ps_dpb_mgr,
                                                WORD32 cur_abs_poc);

pic_buf_t *ih264_dpb_mgr_get_ref_by_poc(dpb_mgr_t *ps_dpb_mgr, WORD32 abs_poc);

pic_buf_t *ih264_dpb_mgr_get_ref_by_poc_lsb(dpb_mgr_t *ps_dpb_mgr,
                                            WORD32 poc_lsb);

void ih264_dpb_mgr_reset(dpb_mgr_t *ps_dpb_mgr, buf_mgr_t *ps_buf_mgr);

void ih264_dpb_mgr_release_pics(buf_mgr_t *ps_buf_mgr, UWORD8 u1_disp_bufs);

#endif /*  _IH264_DPB_MGR_H_ */
