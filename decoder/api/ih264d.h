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
/*  File Name         : ih264d.h                                             */
/*                                                                           */
/*  Description       : This file contains all the necessary structure and   */
/*                      enumeration definitions needed for the Application   */
/*                      Program Interface(API) of the Ittiam H264 ASP       */
/*                      Decoder on Cortex A8 - Neon platform                 */
/*                                                                           */
/*  List of Functions : ih264d_api_function                              */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         26 08 2010   100239(RCY)     Draft                                */
/*                                                                           */
/*****************************************************************************/

#ifndef _IH264D_H_
#define _IH264D_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "iv.h"
#include "ivd.h"

/*****************************************************************************/
/* Constant Macros                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Function Macros                                                           */
/*****************************************************************************/
#define IS_IVD_CONCEALMENT_APPLIED(x) (x & (1 << IVD_APPLIEDCONCEALMENT))
#define IS_IVD_INSUFFICIENTDATA_ERROR(x) (x & (1 << IVD_INSUFFICIENTDATA))
#define IS_IVD_CORRUPTEDDATA_ERROR(x) (x & (1 << IVD_CORRUPTEDDATA))
#define IS_IVD_CORRUPTEDHEADER_ERROR(x) (x & (1 << IVD_CORRUPTEDHEADER))
#define IS_IVD_UNSUPPORTEDINPUT_ERROR(x) (x & (1 << IVD_UNSUPPORTEDINPUT))
#define IS_IVD_UNSUPPORTEDPARAM_ERROR(x) (x & (1 << IVD_UNSUPPORTEDPARAM))
#define IS_IVD_FATAL_ERROR(x) (x & (1 << IVD_FATALERROR))
#define IS_IVD_INVALID_BITSTREAM_ERROR(x) (x & (1 << IVD_INVALID_BITSTREAM))
#define IS_IVD_INCOMPLETE_BITSTREAM_ERROR(x) \
  (x & (1 << IVD_INCOMPLETE_BITSTREAM))

/*****************************************************************************/
/* API Function Prototype                                                    */
/*****************************************************************************/
IV_API_CALL_STATUS_T ih264d_api_function(iv_obj_t *ps_handle, void *pv_api_ip,
                                         void *pv_api_op);

/*****************************************************************************/
/* Enums                                                                     */
/*****************************************************************************/
/* Codec Error codes for H264 ASP Decoder                                   */

typedef enum {

  IH264D_VID_HDR_DEC_NUM_FRM_BUF_NOT_SUFFICIENT =
      IVD_DUMMY_ELEMENT_FOR_CODEC_EXTENSIONS + 1,

} IH264D_ERROR_CODES_T;

/*****************************************************************************/
/* Extended Structures                                                       */
/*****************************************************************************/

/*****************************************************************************/
/*  Get Number of Memory Records                                             */
/*****************************************************************************/

typedef struct {
  iv_num_mem_rec_ip_t s_ivd_num_mem_rec_ip_t;
} ih264d_num_mem_rec_ip_t;

typedef struct {
  iv_num_mem_rec_op_t s_ivd_num_mem_rec_op_t;
} ih264d_num_mem_rec_op_t;

/*****************************************************************************/
/*  Fill Memory Records                                                      */
/*****************************************************************************/

typedef struct {
  iv_fill_mem_rec_ip_t s_ivd_fill_mem_rec_ip_t;
  WORD32 i4_level;
  UWORD32 u4_num_reorder_frames;
  UWORD32 u4_num_ref_frames;
  UWORD32 u4_share_disp_buf;

  /* format in which codec has to give out frame data for display */
  IV_COLOR_FORMAT_T e_output_format;

  /* Number of extra display buffers that will be allocated to handle display
   * pipeline depth */
  UWORD32 u4_num_extra_disp_buf;

} ih264d_fill_mem_rec_ip_t;

typedef struct {
  iv_fill_mem_rec_op_t s_ivd_fill_mem_rec_op_t;

} ih264d_fill_mem_rec_op_t;

/*****************************************************************************/
/*  Retrieve Memory Records                                                  */
/*****************************************************************************/

typedef struct {
  iv_retrieve_mem_rec_ip_t s_ivd_retrieve_mem_rec_ip_t;
} ih264d_retrieve_mem_rec_ip_t;

typedef struct {
  iv_retrieve_mem_rec_op_t s_ivd_retrieve_mem_rec_op_t;
} ih264d_retrieve_mem_rec_op_t;

/*****************************************************************************/
/*   Initialize decoder                                                      */
/*****************************************************************************/

typedef struct {
  ivd_init_ip_t s_ivd_init_ip_t;
  WORD32 i4_level;
  UWORD32 u4_num_reorder_frames;
  UWORD32 u4_num_ref_frames;
  UWORD32 u4_share_disp_buf;
  /* Number of extra display buffers that will be allocated to handle display
   * pipeline depth */
  UWORD32 u4_num_extra_disp_buf;

} ih264d_init_ip_t;

typedef struct {
  ivd_init_op_t s_ivd_init_op_t;
} ih264d_init_op_t;

/*****************************************************************************/
/*   Video Decode                                                            */
/*****************************************************************************/

typedef struct {
  ivd_video_decode_ip_t s_ivd_video_decode_ip_t;
} ih264d_video_decode_ip_t;

typedef struct {
  ivd_video_decode_op_t s_ivd_video_decode_op_t;
} ih264d_video_decode_op_t;

/*****************************************************************************/
/*   Get Display Frame                                                       */
/*****************************************************************************/

typedef struct {
  ivd_get_display_frame_ip_t s_ivd_get_display_frame_ip_t;
} ih264d_get_display_frame_ip_t;

typedef struct {
  ivd_get_display_frame_op_t s_ivd_get_display_frame_op_t;
} ih264d_get_display_frame_op_t;

/*****************************************************************************/
/*   Set Display Frame                                                       */
/*****************************************************************************/

typedef struct {
  ivd_set_display_frame_ip_t s_ivd_set_display_frame_ip_t;
} ih264d_set_display_frame_ip_t;

typedef struct {
  ivd_set_display_frame_op_t s_ivd_set_display_frame_op_t;
} ih264d_set_display_frame_op_t;

/*****************************************************************************/
/*   Release Display Buffers                                                 */
/*****************************************************************************/

typedef struct {
  ivd_rel_display_frame_ip_t s_ivd_rel_display_frame_ip_t;
} ih264d_rel_display_frame_ip_t;

typedef struct {
  ivd_rel_display_frame_op_t s_ivd_rel_display_frame_op_t;
} ih264d_rel_display_frame_op_t;

typedef enum {
  /** Set number of cores/threads to be used */
  IH264D_CMD_CTL_SET_NUM_CORES = IVD_CMD_CTL_CODEC_SUBCMD_START,

  /** Set processor details */
  IH264D_CMD_CTL_SET_PROCESSOR = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x001,

  /** Get display buffer dimensions */
  IH264D_CMD_CTL_GET_BUFFER_DIMENSIONS = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x100,

  /** Get VUI parameters */
  IH264D_CMD_CTL_GET_VUI_PARAMS = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x101,

  /** Enable/disable GPU, supported on select platforms */
  IH264D_CMD_CTL_GPU_ENABLE_DISABLE = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x200,

  /** Set degrade level */
  IH264D_CMD_CTL_DEGRADE = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x300,

  /** Get SEI MDCV parameters */
  IH264D_CMD_CTL_GET_SEI_MDCV_PARAMS = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x301,

  /** Get SEI CLLI parameters */
  IH264D_CMD_CTL_GET_SEI_CLLI_PARAMS = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x302,

  /** Get SEI FGC parameters */
  IH264D_CMD_CTL_GET_SEI_FGC_PARAMS = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x303

} IH264D_CMD_CTL_SUB_CMDS;
/*****************************************************************************/
/*   Video control  Flush                                                    */
/*****************************************************************************/

typedef struct {
  ivd_ctl_flush_ip_t s_ivd_ctl_flush_ip_t;
} ih264d_ctl_flush_ip_t;

typedef struct {
  ivd_ctl_flush_op_t s_ivd_ctl_flush_op_t;
} ih264d_ctl_flush_op_t;

/*****************************************************************************/
/*   Video control reset                                                     */
/*****************************************************************************/

typedef struct {
  ivd_ctl_reset_ip_t s_ivd_ctl_reset_ip_t;
} ih264d_ctl_reset_ip_t;

typedef struct {
  ivd_ctl_reset_op_t s_ivd_ctl_reset_op_t;
} ih264d_ctl_reset_op_t;

/*****************************************************************************/
/*   Video control  Set Params                                               */
/*****************************************************************************/

typedef struct {
  ivd_ctl_set_config_ip_t s_ivd_ctl_set_config_ip_t;
} ih264d_ctl_set_config_ip_t;

typedef struct {
  ivd_ctl_set_config_op_t s_ivd_ctl_set_config_op_t;
} ih264d_ctl_set_config_op_t;

/*****************************************************************************/
/*   Video control:Get Buf Info                                              */
/*****************************************************************************/

typedef struct {
  ivd_ctl_getbufinfo_ip_t s_ivd_ctl_getbufinfo_ip_t;
} ih264d_ctl_getbufinfo_ip_t;

typedef struct {
  ivd_ctl_getbufinfo_op_t s_ivd_ctl_getbufinfo_op_t;
} ih264d_ctl_getbufinfo_op_t;

/*****************************************************************************/
/*   Video control:Getstatus Call                                            */
/*****************************************************************************/

typedef struct {
  ivd_ctl_getstatus_ip_t s_ivd_ctl_getstatus_ip_t;
} ih264d_ctl_getstatus_ip_t;

typedef struct {
  ivd_ctl_getstatus_op_t s_ivd_ctl_getstatus_op_t;
} ih264d_ctl_getstatus_op_t;

/*****************************************************************************/
/*   Video control:Get Version Info                                          */
/*****************************************************************************/

typedef struct {
  ivd_ctl_getversioninfo_ip_t s_ivd_ctl_getversioninfo_ip_t;
} ih264d_ctl_getversioninfo_ip_t;

typedef struct {
  ivd_ctl_getversioninfo_op_t s_ivd_ctl_getversioninfo_op_t;
} ih264d_ctl_getversioninfo_op_t;

typedef struct {
  /**
   * u4_size
   */
  UWORD32 u4_size;

  /**
   * cmd
   */
  IVD_API_COMMAND_TYPE_T e_cmd;

  /**
   * sub_cmd
   */
  IVD_CONTROL_API_COMMAND_TYPE_T e_sub_cmd;

  /**
   * Pictures that are are degraded
   * 0 : No degrade
   * 1 : Only on non-reference frames
   * 2 : Use interval specified by u4_nondegrade_interval
   * 3 : All non-key frames
   * 4 : All frames
   */
  WORD32 i4_degrade_pics;

  /**
   * Interval for pictures which are completely decoded without any degradation
   */
  WORD32 i4_nondegrade_interval;

  /**
   * bit position (lsb is zero): Type of degradation
   * 1 : Disable deblocking
   * 2 : Faster inter prediction filters
   * 3 : Fastest inter prediction filters
   */
  WORD32 i4_degrade_type;

} ih264d_ctl_degrade_ip_t;

typedef struct {
  /**
   * u4_size
   */
  UWORD32 u4_size;

  /**
   * error_code
   */
  UWORD32 u4_error_code;
} ih264d_ctl_degrade_op_t;

typedef struct {
  UWORD32 u4_size;
  IVD_API_COMMAND_TYPE_T e_cmd;
  IVD_CONTROL_API_COMMAND_TYPE_T e_sub_cmd;
  UWORD32 u4_disable_deblk_level;
} ih264d_ctl_disable_deblock_ip_t;

typedef struct {
  UWORD32 u4_size;
  UWORD32 u4_error_code;
} ih264d_ctl_disable_deblock_op_t;

typedef struct {
  UWORD32 u4_size;
  IVD_API_COMMAND_TYPE_T e_cmd;
  IVD_CONTROL_API_COMMAND_TYPE_T e_sub_cmd;
  UWORD32 u4_num_cores;
} ih264d_ctl_set_num_cores_ip_t;

typedef struct {
  UWORD32 u4_size;
  UWORD32 u4_error_code;
} ih264d_ctl_set_num_cores_op_t;

typedef struct {
  /**
   * i4_size
   */
  UWORD32 u4_size;
  /**
   * cmd
   */
  IVD_API_COMMAND_TYPE_T e_cmd;
  /**
   * sub cmd
   */
  IVD_CONTROL_API_COMMAND_TYPE_T e_sub_cmd;
  /**
   * Processor type
   */
  UWORD32 u4_arch;
  /**
   * SOC type
   */
  UWORD32 u4_soc;

  /**
   * num_cores
   */
  UWORD32 u4_num_cores;

} ih264d_ctl_set_processor_ip_t;

typedef struct {
  /**
   * i4_size
   */
  UWORD32 u4_size;
  /**
   * error_code
   */
  UWORD32 u4_error_code;
} ih264d_ctl_set_processor_op_t;

typedef struct {
  UWORD32 u4_size;
  IVD_API_COMMAND_TYPE_T e_cmd;
  IVD_CONTROL_API_COMMAND_TYPE_T e_sub_cmd;
} ih264d_ctl_get_frame_dimensions_ip_t;

typedef struct {
  UWORD32 u4_size;
  UWORD32 u4_error_code;
  UWORD32 u4_x_offset[3];
  UWORD32 u4_y_offset[3];
  UWORD32 u4_disp_wd[3];
  UWORD32 u4_disp_ht[3];
  UWORD32 u4_buffer_wd[3];
  UWORD32 u4_buffer_ht[3];
} ih264d_ctl_get_frame_dimensions_op_t;

typedef struct {
  /**
   * u4_size
   */
  UWORD32 u4_size;

  /**
   * cmd
   */
  IVD_API_COMMAND_TYPE_T e_cmd;

  /**
   * sub_cmd
   */
  IVD_CONTROL_API_COMMAND_TYPE_T e_sub_cmd;
} ih264d_ctl_get_sei_mdcv_params_ip_t;

typedef struct {
  /**
   * u4_size
   */
  UWORD32 u4_size;

  /**
   * error_code
   */
  UWORD32 u4_error_code;

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
} ih264d_ctl_get_sei_mdcv_params_op_t;

typedef struct {
  /**
   * u4_size
   */
  UWORD32 u4_size;

  /**
   * cmd
   */
  IVD_API_COMMAND_TYPE_T e_cmd;

  /**
   * sub_cmd
   */
  IVD_CONTROL_API_COMMAND_TYPE_T e_sub_cmd;
} ih264d_ctl_get_sei_clli_params_ip_t;

typedef struct {
  /**
   * u4_size
   */
  UWORD32 u4_size;

  /**
   * error_code
   */
  UWORD32 u4_error_code;

  /**
   * The maximum pixel intensity of all samples
   */
  UWORD16 u2_max_content_light_level;

  /**
   * The average pixel intensity of all samples
   */
  UWORD16 u2_max_pic_average_light_level;
} ih264d_ctl_get_sei_clli_params_op_t;

typedef struct
{
  /**
   * u4_size
   */
  UWORD32 u4_size;

  /**
   * cmd
   */
  IVD_API_COMMAND_TYPE_T e_cmd;

  /**
   * sub_cmd
   */
  IVD_CONTROL_API_COMMAND_TYPE_T e_sub_cmd;

} ih264d_ctl_get_sei_fgc_params_ip_t;

typedef struct
{
  /**
   * u4_size
   */
  UWORD32 u4_size;

  /**
   * error_code
   */
  UWORD32 u4_error_code;

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
} ih264d_ctl_get_sei_fgc_params_op_t;

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif
#endif /* _IH264D_H_ */
