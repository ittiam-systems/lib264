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

#include "../common/ih264_typedefs.h"
#include "../decoder/api/iv.h"
#include "../decoder/api/ivd.h"
#include "../decoder/api/ih264d.h"
#include <stdbool.h>

typedef struct AVC_Decoder      AVC_Decoder;
typedef struct AVC_Video_Frame  AVC_Video_Frame;
typedef struct AVC_Video_Init_Params AVC_Video_Init_Params;
typedef struct FilmGrainCharacteristicsStruct_t FilmGrainCharacteristicsStruct;

typedef struct Buffer_Handler Buffer_Handler;

#define NUM_FRAMES_BUFFERED     10

/** Used to remove warnings about unused parameters */
#define UNUSED(x) ((void)(x))

struct AVC_Decoder {

    iv_obj_t *codec_obj;         // Codec context

    bool mIsInFlush;        // codec is flush mode

    bool mReceivedEOS;      // EOS is receieved on input port

    /*to handle header decode, to get color format*/
    int is_header_decoded;

    /*to hold the buf address*/
    void *pv_mem_rec_location;

    Buffer_Handler *ad_Buffer;     /**< Hangs on to the video stream   */

    AVC_Video_Frame     *ad_Frames[NUM_FRAMES_BUFFERED];

    AVC_Video_Frame     *ad_LastFrame;  /**< Last returned one, for freeing */

    int                 ad_NumBuffered;

    UWORD8             *ad_InputBuffer;

    size_t              ad_InputBufferSize;

    size_t              ad_FrameSize;

    int                 ad_IsInitialized;

    UWORD32             total_bytes_comsumed;

    UWORD32             file_pos;

    int                 frame_width;

    int                 frame_height;

    UWORD64 u8_ip_frm_ts;

    UWORD8 *pBuf;

    UWORD8 *yBuf;
    UWORD8 *uBuf;
    UWORD8 *vBuf;

    UWORD32 u4_num_cores;

    UWORD32 current_time;

    UWORD32 expected_time;

    UWORD32 first_frame_displayed;

    UWORD32 output_present;
};

/**
 *  Instantiate an instance of decoder implementation
 *
 * @return
 *      An instance of the Ittiam decoder, NULL on error.
 */
int AVC_initDecoder(AVC_Decoder *ad, AVC_Video_Init_Params *avip);

/**
 *  De-instantiate an instance of decoder implementation
 *
 * @return
 *      An instance of the Ittiam decoder, NULL on error.
 */
int AVC_deInitDecoder(AVC_Decoder *ad);

/**
 *  API to set the decoder parameter runtime
 *
 * @return
 *      Success or Error.
 */
int setParams(AVC_Decoder *ad, size_t stride);

/**
 *  API to get the decoder version
 *
 * @return
 *      Void.
 */
void get_version(AVC_Decoder *ad);

/**
 *  API used for configuring the number of cores to be used by Decoder
 *
 * @return
 *      Success or Error.
 */
int setNumCores(AVC_Decoder *ad);

/**
 *  API used for configuring the Architecture type to the Decoder
 *
 * @return
 *      Success or Error.
 */
int setProcessor(AVC_Decoder *ad);

/**
 *  API used for resetting the Decoder instance
 *
 * @return
 *      Success or Error.
 */
int resetDecoder(AVC_Decoder *ad);

/**
 *  API used for resetting the decoder plugin
 *
 * @return
 *      Success or Error.
 */
int resetPlugin(AVC_Decoder *ad);

/**
 *  to decode header and get the input stream params
 *
 * @return
 *      Success or Error.
 */
int decodeHeader(AVC_Decoder *ad, size_t timeStampIx);

/**
 *  to decode the input stream
 *
 * @return
 *      None.
 */
void AVC_Decoder_run(AVC_Decoder *ad, int multi_frame);

/**
 *  to flush the decoder queue
 *
 * @return
 *      None.
 */
int setFlushMode(AVC_Decoder *ad);

/*utility function calls to get the decoded params*/
AVC_Decoder *AVC_Decoder_new(void);

AVC_Video_Init_Params *AVC_Decoder_get_init_params(void);

void AVC_Decoder_destroy(AVC_Decoder *ad, AVC_Video_Init_Params *avip);

int AVC_Decoder_video_finished(AVC_Decoder *ad);

int AVC_Decoder_get_width(AVC_Decoder *ad);

int AVC_Decoder_get_height(AVC_Decoder *ad);

float AVC_Video_Frame_get_time(AVC_Video_Frame *avf);

void *AVC_Video_Frame_get_buffer(AVC_Video_Frame *avf);

size_t AVC_Video_Frame_get_size(AVC_Video_Frame *avf);

AVC_Video_Frame *AVC_Decoder_get_frame(AVC_Decoder *ad);

void AVC_Decoder_set_source(AVC_Decoder *ad, Buffer_Handler *handle);

void AVC_Decoder_set_fgs(AVC_Video_Init_Params *avip, int fgs_enable);

void AVC_Decoder_set_fgs_transform(AVC_Video_Init_Params *avip, int fgs_transform);

void AVC_Decoder_set_fgs_blk_size(AVC_Video_Init_Params *avip, int fgs_blk_size);

void AVC_Decoder_set_fgs_chroma(AVC_Video_Init_Params *avip, int fgs_chroma);

void AVC_Decoder_set_num_cores(AVC_Video_Init_Params *avip, int num_cores);

void AVC_Decoder_set_fps(AVC_Video_Init_Params *avip, int playback_fps);

void AVC_Decoder_video_reset(AVC_Decoder *ad);

int AVC_Decoder_video_finished(AVC_Decoder *ad);

int AVC_Decoder_get_width(AVC_Decoder *ad);

int AVC_Decoder_get_height(AVC_Decoder *ad);

float AVC_Video_Frame_get_time(AVC_Video_Frame *avf);

unsigned int AVC_Decoder_get_y_strd(AVC_Video_Frame *avf);

unsigned int AVC_Decoder_get_y_wd(AVC_Video_Frame *avf);

unsigned int AVC_Decoder_get_y_ht(AVC_Video_Frame *avf);

unsigned int AVC_Decoder_get_u_strd(AVC_Video_Frame *avf);

unsigned int AVC_Decoder_get_u_wd(AVC_Video_Frame *avf);

unsigned int AVC_Decoder_get_u_ht(AVC_Video_Frame *avf);

unsigned int AVC_Decoder_get_v_strd(AVC_Video_Frame *avf);

unsigned int AVC_Decoder_get_v_wd(AVC_Video_Frame *avf);

unsigned int AVC_Decoder_get_v_ht(AVC_Video_Frame *avf);

void *AVC_Video_Frame_get_buffer(AVC_Video_Frame *avf);

void *AVC_Video_Frame_get_y_buffer(AVC_Video_Frame *avf);

void *AVC_Video_Frame_get_u_buffer(AVC_Video_Frame *avf);

void *AVC_Video_Frame_get_v_buffer(AVC_Video_Frame *avf);

size_t AVC_Video_Frame_get_size(AVC_Video_Frame *avf);

AVC_Video_Frame *AVC_Decoder_get_frame(AVC_Decoder *ad);

void set_fgc_sei_params(ih264d_ctl_get_sei_fgc_params_op_t *sei, FilmGrainCharacteristicsStruct *fgc_sei);

Buffer_Handler *Buffer_Handler_open();

unsigned int Buffer_Handler_read(Buffer_Handler *handle, unsigned char *buffer, unsigned int num_bytes);

int Buffer_Handler_empty(Buffer_Handler *handle);

void Buffer_Handler_close(Buffer_Handler *handle);

void Buffer_Handler_set_buffer(Buffer_Handler *handle, void *buf, unsigned int len);

void Buffer_Handler_update_pos(Buffer_Handler *handle, unsigned int pos);
