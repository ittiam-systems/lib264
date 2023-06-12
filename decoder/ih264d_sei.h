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

/*****************************************************************************/
/*                                                                           */
/*  File Name         : ih264d_sei.h */
/*                                                                           */
/*  Description       : This file contains routines to parse SEI NAL's       */
/*                                                                           */
/*  List of Functions : <List the functions defined in this file>            */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         25 05 2005   NS              Draft                                */
/*                                                                           */
/*****************************************************************************/

#ifndef _IH264D_SEI_H_
#define _IH264D_SEI_H_

#include "ih264_typedefs.h"
#include "ih264_macros.h"
#include "ih264_platform_macros.h"
#include "ih264d_bitstrm.h"
#include "ih264d.h"

#define SEI_BUF_PERIOD 0
#define SEI_PIC_TIMING 1
#define SEI_PAN_SCAN_RECT 2
#define SEI_FILLER 3
#define SEI_UD_REG_T35 4
#define SEI_UD_UN_REG 5
#define SEI_RECOVERY_PT 6
#define SEI_DEC_REF_MARK 7
#define SEI_SPARE_PIC 8
#define SEI_SCENE_INFO 9
#define SEI_SUB_SEQN_INFO 10
#define SEI_SUB_SEQN_LAY_CHAR 11
#define SEI_SUB_SEQN_CHAR 12
#define SEI_FULL_FRAME_FREEZE 13
#define SEI_FULL_FRAME_FREEZE_REL 14
#define SEI_FULL_FRAME_SNAP_SHOT 15
#define SEI_PROG_REF_SEGMENT_START 16
#define SEI_PROG_REF_SEGMENT_END 17
#define SEI_MOT_CON_SLICE_GRP_SET 18
#define SEI_FILM_GRAIN_CHARACTERISTICS 19

#define SEI_MASTERING_DISP_COL_VOL 137
#define SEI_CONTENT_LIGHT_LEVEL_INFORMATION_DATA 144
/* Declaration of dec_struct_t to avoid CCS compilation Error */
struct _DecStruct;
WORD32 ih264d_parse_sei_message(struct _DecStruct *ps_dec,
                                dec_bit_stream_t *ps_bitstrm);
typedef struct {
  UWORD8 u1_seq_parameter_set_id;
  UWORD32 u4_initial_cpb_removal_delay;
  UWORD32 u4_nitial_cpb_removal_delay_offset;

} buf_period_t;

/**
 * Structure to hold Mastering Display Color Volume SEI
 */
typedef struct {
  /**
   * Array to store the display_primaries_x values
   */
  UWORD16 au2_display_primaries_x[NUM_SEI_MDCV_PRIMARIES];

  /**
   * Array to store the display_primaries_y values
   */
  UWORD16 au2_display_primaries_y[NUM_SEI_MDCV_PRIMARIES];

  /**
   * Variable to store the white point x value
   */
  UWORD16 u2_white_point_x;

  /**
   * Variable to store the white point y value
   */
  UWORD16 u2_white_point_y;

  /**
   * Variable to store the max display mastering luminance value
   */
  UWORD32 u4_max_display_mastering_luminance;

  /**
   * Variable to store the min display mastering luminance value
   */
  UWORD32 u4_min_display_mastering_luminance;

} sei_mdcv_params_t;

/**
 * Structure for Content Light Level Information
 *
 */
typedef struct {
  /**
   * The maximum pixel intensity of all samples
   */
  UWORD16 u2_max_content_light_level;

  /**
   * The average pixel intensity of all samples
   */
  UWORD16 u2_max_pic_average_light_level;

} sei_clli_params_t;

typedef struct
{
  /**
   * Flag to control the presence of FGC SEI params
   */
  UWORD8 u1_film_grain_characteristics_cancel_flag;

  /**
   * Specifies the pic order count
   */
  WORD32 i4_poc;

  /**
   * Specifies IDR pic ID
   */
  UWORD32 u4_idr_pic_id;

  /**
   * Specifies film grain model for simulation
   */
  UWORD8 u1_film_grain_model_id;

  /**
   * Specifies separate color format for decoded samples and grain
   */
  UWORD8 u1_separate_colour_description_present_flag;

  /**
   * Specifies the bit depth used for the luma component
   */
  UWORD8 u1_film_grain_bit_depth_luma_minus8;

  /**
   * Specifies the bit depth used for the Cb and Cr components
   */
  UWORD8 u1_film_grain_bit_depth_chroma_minus8;

  /**
   * Specifies the colour space of the FGC in SEI
   */
  UWORD8 u1_film_grain_full_range_flag;

  /**
   * Specifies the colour space of the FGC in SEI
   */
  UWORD8 u1_film_grain_colour_primaries;

  /**
   * Specifies the colour space of the FGC in SEI
   */
  UWORD8 u1_film_grain_transfer_characteristics;

  /**
   * Specifies the colour space of the FGC in SEI
   */
  UWORD8 u1_film_grain_matrix_coefficients;

  /**
   * identifies the blending mode used to blend the simulated film grain with the decoded images
   */
  UWORD8 u1_blending_mode_id;

  /**
   * Specifies a scale factor used in the film grain characterization equations
   */
  UWORD8 u1_log2_scale_factor;

  /**
   * Indicates whether film grain is modelled or not on the colour component
   */
  UWORD8 au1_comp_model_present_flag[SEI_FGC_NUM_COLOUR_COMPONENTS];

  /**
   * Specifies the number of intensity intervals for which
   * a specific set of model values has been estimated
   */
  UWORD8 au1_num_intensity_intervals_minus1[SEI_FGC_NUM_COLOUR_COMPONENTS];

  /**
   * Specifies the number of model values present for each intensity interval in which
   * the film grain has been modelled
   */
  UWORD8 au1_num_model_values_minus1[SEI_FGC_NUM_COLOUR_COMPONENTS];

  /**
   * Specifies the lower bound of the interval of intensity levels for which
   * the set of model values applies
   */
  UWORD8 au1_intensity_interval_lower_bound[SEI_FGC_NUM_COLOUR_COMPONENTS]
                                           [SEI_FGC_MAX_NUM_INTENSITY_INTERVALS];

  /**
   * Specifies the upper bound of the interval of intensity levels for which
   * the set of model values applies
   */
  UWORD8 au1_intensity_interval_upper_bound[SEI_FGC_NUM_COLOUR_COMPONENTS]
                                           [SEI_FGC_MAX_NUM_INTENSITY_INTERVALS];

  /**
   * Represents each one of the model values present for
   * the colour component and intensity interval
   */
  WORD32 ai4_comp_model_value[SEI_FGC_NUM_COLOUR_COMPONENTS][SEI_FGC_MAX_NUM_INTENSITY_INTERVALS]
                             [SEI_FGC_MAX_NUM_MODEL_VALUES];

  /**
   * Specifies the persistence of the film grain characteristics SEI message
   */
  UWORD32 u4_film_grain_characteristics_repetition_period;

} sei_fgc_params_t;

struct _sei {
  UWORD8 u1_seq_param_set_id;
  buf_period_t s_buf_period;
  UWORD8 u1_pic_struct;
  UWORD16 u2_recovery_frame_cnt;
  UWORD8 u1_exact_match_flag;
  UWORD8 u1_broken_link_flag;
  UWORD8 u1_changing_slice_grp_idc;
  UWORD8 u1_is_valid;

  /**
   *  mastering display color volume info present flag
   */
  UWORD8 u1_sei_mdcv_params_present_flag;

  /*
   * MDCV parameters
   */
  sei_mdcv_params_t s_sei_mdcv_params;

  /**
   * content light level information present flag
   */
  UWORD8 u1_sei_clli_params_present_flag;

  /*
   * CLLI parameters
   */
  sei_clli_params_t s_sei_clli_params;

  /**
   * film grain params info present flag
   */
  UWORD8 u1_sei_fgc_params_present_flag;

  /*
   * film grain characteristics parameters
   */
  sei_fgc_params_t s_sei_fgc_params;
};
typedef struct _sei sei;

WORD32 ih264d_export_sei_mdcv_params(ivd_sei_decode_op_t *ps_sei_decode_op,
                                     sei *ps_sei, sei *ps_sei_export);

WORD32 ih264d_export_sei_clli_params(ivd_sei_decode_op_t *ps_sei_decode_op,
                                    sei *ps_sei, sei *ps_sei_export);

WORD32 ih264d_export_sei_fgc_params(ivd_sei_decode_op_t *ps_sei_decode_op,
                                     sei *ps_sei, sei *ps_sei_export);

#endif /* _IH264D_SEI_H_ */
