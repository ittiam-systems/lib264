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
*  iv.h
*
* @brief
*  This file contains all the necessary structure and  enumeration
* definitions needed for the Application  Program Interface(API) of the
* Ittiam Video and Image  codecs
*
* @author
*  100239(RCY)
*
* @par List of Functions:
*
* @remarks
*  None
*
*******************************************************************************
*/

#ifndef _IV_H
#define _IV_H

/*****************************************************************************/
/* Constant Macros                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Typedefs                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* Enums                                                                     */
/*****************************************************************************/

/* IV_API_CALL_STATUS_T:This is only to return the FAIL/PASS status to the  */
/* application for the current API call                                     */

typedef enum {
  IV_STATUS_NA = 0x7FFFFFFF,
  IV_SUCCESS = 0x0,
  IV_FAIL = 0x1,
} IV_API_CALL_STATUS_T;

/* IV_MEM_TYPE_T: This Enumeration defines the type of memory (Internal/Ext */
/* -ernal) along with the cacheable/non-cacheable attributes                */

typedef enum {
  IV_NA_MEM_TYPE = 0x7FFFFFFF,
  IV_INTERNAL_CACHEABLE_PERSISTENT_MEM = 0x1,
  IV_INTERNAL_CACHEABLE_SCRATCH_MEM = 0x2,
  IV_EXTERNAL_CACHEABLE_PERSISTENT_MEM = 0x3,
  IV_EXTERNAL_CACHEABLE_SCRATCH_MEM = 0x4,
  IV_INTERNAL_NONCACHEABLE_PERSISTENT_MEM = 0x5,
  IV_INTERNAL_NONCACHEABLE_SCRATCH_MEM = 0x6,
  IV_EXTERNAL_NONCACHEABLE_PERSISTENT_MEM = 0x7,
  IV_EXTERNAL_NONCACHEABLE_SCRATCH_MEM = 0x8
} IV_MEM_TYPE_T;

/* IV_COLOR_FORMAT_T: This enumeration lists all the color formats which    */
/* finds usage in video/image codecs                                        */

typedef enum {
  IV_CHROMA_NA = 0x7FFFFFFF,
  IV_YUV_420P = 0x1,
  IV_YUV_422P = 0x2,
  IV_420_UV_INTL = 0x3,
  IV_YUV_422IBE = 0x4,
  IV_YUV_422ILE = 0x5,
  IV_YUV_444P = 0x6,
  IV_YUV_411P = 0x7,
  IV_GRAY = 0x8,
  IV_RGB_565 = 0x9,
  IV_RGB_24 = 0xa,
  IV_YUV_420SP_UV = 0xb,
  IV_YUV_420SP_VU = 0xc,
  IV_RGBA_8888 = 0xd
} IV_COLOR_FORMAT_T;

/* IV_PICTURE_CODING_TYPE_T: VOP/Frame coding type Enumeration              */

typedef enum {
  IV_NA_FRAME = 0x7FFFFFFF,
  IV_I_FRAME = 0x0,
  IV_P_FRAME = 0x1,
  IV_B_FRAME = 0x2,
  IV_IDR_FRAME = 0x3,
  IV_II_FRAME = 0x4,
  IV_IP_FRAME = 0x5,
  IV_IB_FRAME = 0x6,
  IV_PI_FRAME = 0x7,
  IV_PP_FRAME = 0x8,
  IV_PB_FRAME = 0x9,
  IV_BI_FRAME = 0xa,
  IV_BP_FRAME = 0xb,
  IV_BB_FRAME = 0xc,
  IV_MBAFF_I_FRAME = 0xd,
  IV_MBAFF_P_FRAME = 0xe,
  IV_MBAFF_B_FRAME = 0xf,
  IV_MBAFF_IDR_FRAME = 0x10,
  IV_NOT_CODED_FRAME = 0x11,
  IV_FRAMETYPE_DEFAULT = IV_I_FRAME
} IV_PICTURE_CODING_TYPE_T;

/* IV_FLD_TYPE_T: field type Enumeration                                    */

typedef enum {
  IV_NA_FLD = 0x7FFFFFFF,
  IV_TOP_FLD = 0x0,
  IV_BOT_FLD = 0x1,
  IV_FLD_TYPE_DEFAULT = IV_TOP_FLD
} IV_FLD_TYPE_T;

/* IV_CONTENT_TYPE_T: Video content type                                     */

typedef enum {
  IV_CONTENTTYPE_NA = 0x7FFFFFFF,
  IV_PROGRESSIVE = 0x0,
  IV_INTERLACED = 0x1,
  IV_PROGRESSIVE_FRAME = 0x2,
  IV_INTERLACED_FRAME = 0x3,
  IV_INTERLACED_TOPFIELD = 0x4,
  IV_INTERLACED_BOTTOMFIELD = 0x5,
  IV_CONTENTTYPE_DEFAULT = IV_PROGRESSIVE,
} IV_CONTENT_TYPE_T;

/* IV_API_COMMAND_TYPE_T:API command type                                   */
typedef enum {
  IV_CMD_NA = 0x7FFFFFFF,
  IV_CMD_GET_NUM_MEM_REC = 0x0,
  IV_CMD_FILL_NUM_MEM_REC = 0x1,
  IV_CMD_RETRIEVE_MEMREC = 0x2,
  IV_CMD_INIT = 0x3,
  IV_CMD_DUMMY_ELEMENT = 0x4,
} IV_API_COMMAND_TYPE_T;

/*****************************************************************************/
/* Structure                                                                 */
/*****************************************************************************/

/* IV_OBJ_T: This structure defines the handle for the codec instance        */

typedef struct {
  /**
   * u4_size of the structure
   */
  UWORD32 u4_size;

  /**
   * Pointer to the API function pointer table of the codec
   */
  void *pv_fxns;

  /**
   * Pointer to the handle of the codec
   */
  void *pv_codec_handle;
} iv_obj_t;

/* iv_mem_rec_t: This structure defines the memory record holder which will  */
/* be used by the codec to communicate its memory requirements to the        */
/* application through appropriate API functions                             */

typedef struct {
  /**
   * u4_size of the structure
   */
  UWORD32 u4_size;

  /**
   * Pointer to the memory allocated by the application
   */
  void *pv_base;

  /**
   * u4_size of the memory to be allocated
   */
  UWORD32 u4_mem_size;

  /**
   * Alignment of the memory pointer
   */
  UWORD32 u4_mem_alignment;
  /**
   * Nature of the memory to be allocated
   */
  IV_MEM_TYPE_T e_mem_type;
} iv_mem_rec_t;

/* IV_YUV_BUF_T: This structure defines attributes for the yuv buffer        */

typedef struct {
  /**
   * u4_size of the structure
   */
  UWORD32 u4_size;

  /**
   * Pointer to Luma (Y) Buffer
   */

  void *pv_y_buf;
  /**
   * Pointer to Chroma (Cb) Buffer
   */
  void *pv_u_buf;

  /**
   * Pointer to Chroma (Cr) Buffer
   */
  void *pv_v_buf;

  /**
   * Width of the Luma (Y) Buffer
   */
  UWORD32 u4_y_wd;

  /**
   * Height of the Luma (Y) Buffer
   */
  UWORD32 u4_y_ht;

  /**
   * Stride/Pitch of the Luma (Y) Buffer
   */
  UWORD32 u4_y_strd;

  /**
   * Width of the Chroma (Cb) Buffer
   */
  UWORD32 u4_u_wd;

  /**
   * Height of the Chroma (Cb) Buffer
   */
  UWORD32 u4_u_ht;

  /**
   * Stride/Pitch of the Chroma (Cb) Buffer
   */
  UWORD32 u4_u_strd;

  /**
   * Width of the Chroma (Cr) Buffer
   */
  UWORD32 u4_v_wd;

  /**
   * Height of the Chroma (Cr) Buffer
   */
  UWORD32 u4_v_ht;

  /**
   * Stride/Pitch of the Chroma (Cr) Buffer
   */
  UWORD32 u4_v_strd;
} iv_yuv_buf_t;

/*****************************************************************************/
/*  Get Number of Memory Records                                             */
/*****************************************************************************/

/* IV_API_COMMAND_TYPE_T::e_cmd = IV_CMD_GET_NUM_MEM_REC                     */

typedef struct {
  /**
   * u4_size of the structure
   */
  UWORD32 u4_size;

  /**
   * cmd
   */
  IV_API_COMMAND_TYPE_T e_cmd;
} iv_num_mem_rec_ip_t;

typedef struct {
  /**
   * u4_size of the structure
   */
  UWORD32 u4_size;

  /**
   * error code
   */
  UWORD32 u4_error_code;

  /**
   * num_mem_rec
   */
  UWORD32 u4_num_mem_rec;
} iv_num_mem_rec_op_t;

/*****************************************************************************/
/*  Fill Memory Records                                                      */
/*****************************************************************************/

/* IV_API_COMMAND_TYPE_T::e_cmd = IV_CMD_FILL_NUM_MEM_REC                    */

typedef struct {
  /**
   * u4_size of the structure
   */
  UWORD32 u4_size;

  /**
   * cmd
   */
  IV_API_COMMAND_TYPE_T e_cmd;

  /**
   * pointer to array of memrecords structures should be filled by codec
  with details of memory resource requirements
   */
  iv_mem_rec_t *pv_mem_rec_location;

  /**
   * maximum width for which codec should request memory requirements
   */
  UWORD32 u4_max_frm_wd;

  /**
   * maximum height for which codec should request memory requirements
   */
  UWORD32 u4_max_frm_ht;
} iv_fill_mem_rec_ip_t;

typedef struct {
  /**
   * u4_size of the structure
   */
  UWORD32 u4_size;

  /**
   * error_code
   */
  UWORD32 u4_error_code;

  /**
   * no of memory record structures which are filled by codec
   */
  UWORD32 u4_num_mem_rec_filled;
} iv_fill_mem_rec_op_t;

/*****************************************************************************/
/*  Retrieve Memory Records                                                  */
/*****************************************************************************/

/* IV_API_COMMAND_TYPE_T::e_cmd = IV_CMD_RETRIEVE_MEMREC                     */

typedef struct {
  /**
   * u4_size of the structure
   */
  UWORD32 u4_size;

  /**
   * cmd
   */
  IV_API_COMMAND_TYPE_T e_cmd;

  /**
   * array of structures where codec should fill with all resources(memory) with
   * it
   */
  iv_mem_rec_t *pv_mem_rec_location;
} iv_retrieve_mem_rec_ip_t;

typedef struct {
  /**
   * u4_size of the structure
   */
  UWORD32 u4_size;

  /**
   * error_code
   */
  UWORD32 u4_error_code;

  /**
   * no of memory records filled by codec
   */
  UWORD32 u4_num_mem_rec_filled;
} iv_retrieve_mem_rec_op_t;

#endif /* _IV_H */
