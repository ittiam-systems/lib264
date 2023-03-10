<H1><b>1. Application Program Interface</b></H1>

This chapter describes the Application Program Interfaces (APIs) of the lib264 video decoder. Application uses these APIs to interact with the codec library and to exchange the data with it. There is a single entry point to the decoder library via following API:

<table>
  <thead>
    <tr>
      <th colspan="3">Decoder API</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Name</td>
      <td colspan="2">&lt;DecoderName&gt;_api_function()</td>
    </tr>
    <tr>
      <td>Purpose</td>
      <td colspan="2">This is an API function of the decoder for the application, and is the only entry point to the decoder library.</td>
    </tr>
    <tr>
      <td>Prototype</td>
      <td colspan="2">void &lt;DecoderName&gt;_api_function()(iv_obj_t *dec_hdl, void *pv_api_ip, void *pv_api_op);</td>
    </tr>
    <tr>
      <td rowspan="4">Argument details</td>
      <td>Arguement</td>
      <td>Description</td>
    </tr>
    <tr>
      <td>iv_obj_t *dec_hdl</td>
      <td>Pointer to the codec instance called as decoder handle.</td>
    </tr>
    <tr>
      <td>void *pv_api_ip</td>
      <td>Pointer to the APIs input structure type-casted as void pointer.</td>
    </tr>
    <tr>
      <td>void *pv_api_op</td>
      <td>Pointer to the APIs output structure type-casted as void pointer.</td>
    </tr>
  </tbody>
</table>

<p align="center">Table: Decoder API Details</p>

The input structure passed depends on the purpose of the call. That is, for a control call to get the version information, the input structure will be ivd_ctl_getversioninfo_ip_t.

All the input structures have the e_cmd Enumeration data type as the second field. Application calls the API with a suitable value of e_cmd Enum. Decoder reads this command and performs the desired functionality. For example, if the application wants to initialize the lib264 decoder, it shall call the lib264_library with e_cmd set as IVD_CMD_INIT and the input structure will be ivd_init_ip_t .
Apart from e_cmd, the input structure contains the parameters necessary for codec configuration and other input parameters needed by the library interface to process the input bit stream. The output structure contains the status code and other parameters returned by the library based on the command passed to the decoder. Handle contains the pointer to memory records location and the data structure containing all the persistent state variables of the decoder.

The following sub-sections describe the various functionalities exported by the above API. Application should set the appropriate values of e_cmd parameter and the other fields in the appropriate input structure. Status of the API call and the other outputs are returned in the output structure. An application typecasts the input and the output structure pointers as void pointers before it makes a call to the API. On receiving the command via e_cmd parameter, the Decoder calls the suitable function to perform the functionality, corresponding to the current command. Decoder also type casts the input/output structures suitably according to the e_cmd.

NOTE: void pointer variable in the input and output structure for each API has been kept for extension purpose of the API and is an optional parameter.

<H3><b>Get Number of Memory Records</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Get Number of Memory Records API    </th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">Application uses this API functionality to find the number of memory records needed by the decoder library. The application then allocates sufficient memory to store all the memory records.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> IV_API_COMMAND_TYPE_T e_cmd;<br>} iv_num_mem_rec_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="3">Input Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This parameter defines the function to be performed by decoder library. For memory query, command should be IV_CMD_GET_NUM_MEM_REC;</td>
      </tr>
      <tr>
         <td>Output Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br>    UWORD32 u4_error_code;<br> UWORD32 u4_num_mem_rec;<br>} iv_num_mem_rec_op_t;</td>
      </tr>
      <tr>
         <td rowspan="4">Output Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>u4_error_code</td>
         <td>For the error and status codes refer Error/Status Codes</td>
      </tr>
      <tr>
         <td>u4_num_mem_rec</td>
         <td>Number of memory records neededby decoder.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Number of memory records API</p>

<H3><b>Fill Memory Records</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Fill Memory Records API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">Application asks the decoder to fill the details of all the memory records through this API call. Decoder fills the size, type of memory (scratch/persistent), alignment requirements of each memory record. The application uses these memory attributes to allocate memory in appropriate region of memory.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> IV_API_COMMAND_TYPE_T e_cmd;<br> iv_mem_rec_t *pv_mem_rec_location;<br> UWORD32 u4_max_frm_wd;<br> UWORD32 u4_max_frm_ht;<br>} iv_fill_mem_rec_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="6">Input Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This parameter defines the function to be performed by decoder library. For fill memory records query, command should be IV_CMD_FILL_NUM_MEM_REC</td>
      </tr>
      <tr>
         <td>pv_mem_rec_location</td>
         <td>Pointer pointing to the data structure containing the mem tabs.</td>
      </tr>
      <tr>
         <td>u4_max_frm_wd</td>
         <td>The parameter tells the width of current video sequence, this is either known through file container information, or application can also pass maximum width it supports. This information shall be used by the decoder to calculate the memory requirements.</td>
      </tr>
      <tr>
         <td>u4_max_frm_ht</td>
         <td>The parameter tells the height of current video sequence,this is either known through file container information, or application can also pass maximum height it supports. This information shall be used by the decoder to calculate the memory requirements.</td>
      </tr>
      <tr>
         <td>Output Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> UWORD32 u4_error_code;<br> UWORD32 u4_num_mem_rec_filled;<br>} iv_fill_mem_rec_op_t;</td>
      </tr>
      <tr>
         <td rowspan="4">Output Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>u4_error_code</td>
         <td>For error and status codes refer Error/Status Codes</td>
      </tr>
      <tr>
         <td>u2_num_mem_rec_filled</td>
         <td>This parameter specifies the number of memory records actually filled by decoder library.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Fill memory records API</p>

<H3><b>Retrieve Memory Records</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Retrieve Memory Records API </th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This is the API call to retrieve the memory records that were allocated to the decoder during initialization. This will be used in the deletion of the instance of the codec.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> IV_API_COMMAND_TYPE_T e_cmd;<br> iv_mem_rec_t *pv_mem_rec_location;<br>} iv_retrieve_mem_rec_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="4">Input Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This parameter defines the function to be performed by decoder library. For memory query, command should be IV_CMD_RETRIEVE_MEMREC</td>
      </tr>
      <tr>
         <td>pv_mem_rec_location</td>
         <td>This is the pointer in which the decoder fills the memory record attributes along with the memory pointer allocated by the application.</td>
      </tr>
      <tr>
         <td>Output Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> UWORD32 u4_error_code;<br> UWORD32 u4_num_mem_rec_filled;<br>} iv_retrieve_mem_rec_op_t;</td>
      </tr>
      <tr>
         <td rowspan="4">Output Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td colspan="2">u4_size</td>
      </tr>
      <tr>
         <td>u4_error_code</td>
         <td>For error and status codes refer Error/Status Codes</td>
      </tr>
      <tr>
         <td>u4_num_mem_rec_filled</td>
         <td>This parameter specifies the number of memory records actually filled by decoder library.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Retrieve Memory Records API</p>

<H3><b>Initialize decoder</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Initialize decoder API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">All the persistent state variables and the memory records are initialized internally in the decoder and a decoder object is returned as a codec Handle. Refer section 3.3 for the handle definition.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> IVD_API_COMMAND_TYPE_T e_cmd;<br> UWORD32 u4_num_mem_rec;<br> UWORD32 u4_frm_max_wd;<br> UWORD32 u4_frm_max_ht;<br> IV_COLOR_FORMAT_T e_output_format;<br> iv_mem_rec_t *pv_mem_rec_location;<br>} ivd_init_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="8">Input Structure Details</td>
         <td>   <br>API Parameter   </td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This parameter defines the function to be performed by decoder library. To initialize decoder, command should be IVD_CMD_INIT</td>
      </tr>
      <tr>
         <td>u4_num_mem_rec</td>
         <td>This parameter specifies the number of memory records for which memory is allocated. This shall be same as that returned during IV_CMD_GET_NUM_MEM_REC call</td>
      </tr>
      <tr>
         <td>u4_frm_max_wd</td>
         <td>The parameter tells the width of current video sequence, this is either known through file container information, or application can also pass maximum width it supports</td>
      </tr>
      <tr>
         <td>u4_frm_max_ht</td>
         <td>The parameter tells the height of current video sequence, this is either known through file container information, or application can also pass maximum height it supports</td>
      </tr>
      <tr>
         <td>e_output_format</td>
         <td>The parameter gives the output color format expected.</td>
      </tr>
      <tr>
         <td>pv_mem_rec_location</td>
         <td>This pointer holds the memory records that have been allocated by the application. The allocation has to be as per the decoder request (or at least compatible to the request) after the fill memory records API call. If any of the memory records is incompatible, the init call will fail.</td>
      </tr>
      <tr>
         <td>Output Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> UWORD32 u4_error_code;<br>} ivd_init_op_t;</td>
      </tr>
      <tr>
         <td rowspan="3">Output Structure Details</td>
         <td>   <br>API Parameter   </td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>u4_error_code</td>
         <td>For error and status codes refer Error/Status Codes</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: initialize decoder API</p>

<H3><b>Video Control API</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="5">Video Control API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="4">This API is used to make control calls to change run time parameters, query the status, flush decoder and to set the decoder in the required state before the frame decode call. For more details refer the Video Control API command type data structure. This varies depending upon the e_sub_cmd. For details refer the individual data structures corresponding to each control API command type. However common parameters are explained.</td>
      </tr>
      <tr>
         <td rowspan="9">Input Structure<br> </td>
         <td colspan="4">typedef struct {<br> UWORD32 u4_size;<br> IVD_API_COMMAND_TYPE_T e_cmd;<br> IVD_CONTROL_API_COMMAND_TYPE_T e_sub_cmd;<br> . . <br>}&lt;structure_name&gt;<br>The &lt;structure_name&gt; depends on the type of control call. The various structures available are:<br> </td>
      </tr>
      <tr>
         <td>Structure Name</td>
         <td colspan="2">e_sub_cmd</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>ivd_ctl_flush_ip_t</td>
         <td colspan="2">IVD_CMD_CTL_FLUSH</td>
         <td>Input structure for control call to flush.</td>
      </tr>
      <tr>
         <td>ivd_ctl_reset_ip_t</td>
         <td colspan="2">IVD_CMD_CTL_RESET</td>
         <td>Input structure for control call to reset.</td>
      </tr>
      <tr>
         <td rowspan="2">ivd_ctl_set_config_ip_t</td>
         <td colspan="2">IVD_CMD_CTL_SETPARAMS</td>
         <td>Input structure for control call to set the config parameters.</td>
      </tr>
      <tr>
         <td colspan="2">IVD_CMD_CTL_SETDEFAULT</td>
         <td>Input structure for control call to set the config parameters to default.</td>
      </tr>
      <tr>
         <td>ivd_ctl_getbufinfo_ip_t</td>
         <td colspan="2">IVD_CMD_CTL_GETBUFINFO</td>
         <td>Input structure for control call to get the buffer information.</td>
      </tr>
      <tr>
         <td>ivd_ctl_getstatus_ip_t</td>
         <td colspan="2">IVD_CMD_CTL_GETPARAMS</td>
         <td>Input structure for control call to get the parameter values of decoder.</td>
      </tr>
      <tr>
         <td>ivd_ctl_getversioninfo_ip_t</td>
         <td colspan="2">IVD_CMD_CTL_GETVERSION</td>
         <td>Input structure for control call to get the decoder version number.</td>
      </tr>
      <tr>
         <td rowspan="4">Input Structure Details</td>
         <td colspan="2">Parameter</td>
         <td colspan="2">Description</td>
      </tr>
      <tr>
         <td colspan="2">u4_size</td>
         <td colspan="2">Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td colspan="2">e_cmd</td>
         <td colspan="2">This parameter defines the function to be performed by decoder library. To call control API, the command should be IVD_CMD_VIDEO_CTL</td>
      </tr>
      <tr>
         <td colspan="2">e_sub_cmd</td>
         <td colspan="2">This is Video Control API command type and tells the functionality to be performed by the Video control API. For details referSection 3.8 - Video Control API Command Type</td>
      </tr>
      <tr>
         <td rowspan="9">Output Structure</td>
         <td colspan="4">This varies depending upon the e_sub_cmd. For details refer the individual data structures corresponding to each control API command type.</td>
      </tr>
      <tr>
         <td>StructureName</td>
         <td colspan="2">e_sub_cmd</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>ivd_ctl_flush_op_t</td>
         <td colspan="2">IVD_CMD_CTL_FLUSH</td>
         <td>Output structure for control call to flush.</td>
      </tr>
      <tr>
         <td>ivd_ctl_reset_op_t</td>
         <td colspan="2">IVD_CMD_CTL_RESET</td>
         <td>Output structure for control call to reset.</td>
      </tr>
      <tr>
         <td rowspan="2">ivd_ctl_set_config_op_t</td>
         <td colspan="2">IVD_CMD_CTL_SETPARAMS</td>
         <td>Output structure for control call to set the config parameters.</td>
      </tr>
      <tr>
         <td colspan="2">IVD_CMD_CTL_SETDEFAULT</td>
         <td>Output structure for control call to set the config parameters to default.</td>
      </tr>
      <tr>
         <td>ivd_ctl_getbufinfo_op_t</td>
         <td colspan="2">IVD_CMD_CTL_GETBUFINFO</td>
         <td>Output structure for control call to get the buffer information.</td>
      </tr>
      <tr>
         <td>ivd_ctl_getstatus_op_t</td>
         <td colspan="2">IVD_CMD_CTL_GETPARAMS</td>
         <td>Output structure for control call to get the parameter values of decoder.</td>
      </tr>
      <tr>
         <td>ivd_ctl_getversioninfo_op_t</td>
         <td colspan="2">IVD_CMD_CTL_GETVERSION</td>
         <td>Output structure for control call to get the decoder version number.</td>
      </tr>
      <tr>
         <td rowspan="4">Output Structure Details</td>
         <td colspan="2">Parameter</td>
         <td colspan="2">Description</td>
      </tr>
      <tr>
         <td colspan="2">u4_size</td>
         <td colspan="2">Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td colspan="2">u4_error_code</td>
         <td colspan="2">For the error and status codes refer Error/Status Codes.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Video Control API</p>

<H3><b>Video Decode</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Video Decode API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This API is used to decode Video content, If the bitstream given to decoder is not starting with start code, decoder will also search for start code as per the num_Bytes. In shared mode decoder will return IVD_DEC_REF_BUF_NULL error code when there are no free buffers that can be used as reference buffers. In this case application needs to wait till a new buffer is released from display.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> IVD_API_COMMAND_TYPE_T e_cmd;<br> UWORD32 u4_ts;<br> UWORD32 u4_num_Bytes;<br> void *pv_stream_buffer;<br> ivd_out_bufdesc_t s_out_buffer;<br>} ivd_video_decode_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="7">Input Structure Details</td>
         <td>API Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This parameter defines the function to be performed by decoder library. For video frame decode, this should be IVD_CMD_VIDEO_DECODE</td>
      </tr>
      <tr>
         <td>u4_ts</td>
         <td>This parameter indicates the decode time-stamp as decodedby system (through parser). This time stamp will be returned in ivd_video_decode_op_t when its corresponding output frame is given for display.</td>
      </tr>
      <tr>
         <td>u4_num_Bytes</td>
         <td>Size of input data in bytes, provided to the algorithm for decoding</td>
      </tr>
      <tr>
         <td>pv_stream_buffer</td>
         <td>This parameter points to the bit-stream</td>
      </tr>
      <tr>
         <td>s_out_buffer</td>
         <td>This is the pointer to the output YUV buffer given by the application whose size shall be at-least as requested by the codec in the IVD_CMD_CTL_GETBUFINFO call.</td>
      </tr>
      <tr>
         <td>Output Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> UWORD32 u4_error_code;<br> UWORD32 u4_num_bytes_consumed;<br> UWORD32 u4_pic_wd;<br> UWORD32 u4_pic_ht;<br> IV_PICTURE_CODING_TYPE_T e_pic_type;<br> UWORD32 u4_frame_decoded_flag;<br> UWORD32 u4_new_seq; <br> UWORD32 u4_output_present;<br> UWORD32 u4_progressive_frame_flag;<br> UWORD32 u4_is_ref_flag;<br> IV_COLOR_FORMAT_T e_output_format;<br> iv_yuv_buf_t s_disp_frm_buf;<br> ivd_sei_decode_op_t s_sei_decode_op;<br> IV_FLD_TYPE_T e4_fld_type;<br> UWORD32 u4_ts;<br> UWORD32 u4_disp_buf_id;<br>} ivd_video_decode_op_t;</td>
      </tr>
      <tr>
         <td rowspan="17">Output Structure Details</td>
         <td>API Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>u4_error_code</td>
         <td>For the error and status codes refer Error/Status Codes</td>
      </tr>
      <tr>
         <td>u4_num_bytes_consumed</td>
         <td>This gives the number of bytes the decoder consumed.</td>
      </tr>
      <tr>
         <td>u4_pic_wt</td>
         <td>Picture width (without any padding)</td>
      </tr>
      <tr>
         <td>u4_pic_ht</td>
         <td>Picture Height</td>
      </tr>
      <tr>
         <td>e_pic_type</td>
         <td>This parameter indicates the current frame/picture decoded type e.g. IDR-Frame, P-Frame, B-Frame etc. refer the enum for details.</td>
      </tr>
      <tr>
         <td>u4_frame_decoded_flag</td>
         <td>This is set to 1 if the current decode call has decoded a complete Frame/field. It is zero in case of Header decode, Flush mode or Partial picture decode.</td>
      </tr>
      <tr>
         <td>u4_new_seq</td>
         <td>New sequence detected</td>
      </tr>
      <tr>
         <td>u4_output_present</td>
         <td>This parameter is set to 1, if the current process call has returned output frame for display, else it is 0.</td>
      </tr>
      <tr>
         <td>u4_progressive_frame_flag</td>
         <td>This parameter is set to 1 if, the frame given for display is Progressive content, else it is 0. This parameter is valid only when u4_output_present is set to 1.</td>
      </tr>
      <tr>
         <td>u4_is_ref_flag</td>
         <td>This parameter is set to 1, if the frame decoded in the current decode call will used as reference, else it is 0. Invalid in flush mode.</td>
      </tr>
      <tr>
         <td>e_output_format</td>
         <td>The parameter gives the output color format given for display. This parameter is valid only when u4_output_present is set to 1.</td>
      </tr>
      <tr>
         <td>s_disp_frm_buf</td>
         <td>Contains YUV Buffer pointer and related details. This parameter is valid only when u4_output_present is set to 1.</td>
      </tr>
      <tr>
         <td>s_sei_decode_op</td>
         <td>This parameter is used to set SEI parameter values.</td>
      </tr>
      <tr>
         <td>e4_fld_type</td>
         <td>This parameter is not relevant in current configuration. The output given for display is always a complete frame.</td>
      </tr>
      <tr>
         <td>u4_ts</td>
         <td>Timestamp corresponds to the value of u4_ts given by application corresponding to its Input bitstream buffer in ivd_video_decode_ip_t. This value can be used to co-relate the Input and output buffers. In the case of Interlace pictures, this value corresponds to the time stamp of second field given by the application. This parameter is valid only when u4_output_present is set to 1.</td>
      </tr>
      <tr>
         <td>u4_disp_buf_id</td>
         <td> This element returns an ID that is associated with the buffer given out for display. This ID is used in shared display mode and has to be passed to codec during release display control call when the display buffer given out is ready for reuse in the codec. </td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Video Decode API</p>

<H3><b>Set display frame</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Set display frame API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This API should be used to give the pointers to all the display buffers to the decoder library. This command should be called before the first IVD_CMD_VIDEO_DECODEAPI command. This API command should be used only when u4_share_disp_buf in ih264d_init_ip_t is set to 1.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct<br>{<br> UWORD32 u4_size;<br> IVD_API_COMMAND_TYPE_T e_cmd;<br> UWORD32 num_disp_bufs;<br> ivd_out_bufdesc_t s_disp_buffer[IVD_VIDDEC_MAX_IO_BUFFERS]; <br>} ivd_set_display_frame_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="5">Input Structure Details</td>
         <td>API Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This parameter defines the function to be performed by decoder library. For set display frame this needs to be set to IVD_CMD_SET_DISPLAY_FRAME.</td>
      </tr>
      <tr>
         <td>num_disp_bufs</td>
         <td>This parameter indicates the number of display buffers being given to the library. This can be maximum of 32.</td>
      </tr>
      <tr>
         <td>s_disp_buffer[IVD_VIDDEC_MAX_IO_BUFFERS];</td>
         <td>This is an array of display buffer structures. Each element of this array corresponds to one display buffer. The index of the element in this array is its Buffer ID. This buffer ID will be used in the release display frame API call.</td>
      </tr>
      <tr>
         <td>Output Structure</td>
         <td colspan="2"> <br>typedef struct<br>{<br> UWORD32 u4_size;<br> UWORD32 u4_error_code;<br>} ivd_set_display_frame_op_t;</td>
      </tr>
      <tr>
         <td rowspan="3">Output Structure Details</td>
         <td>API Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>u4_error_code</td>
         <td>For the error and status codes refer Error/Status Codes</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Set display frame API</p>

<H3><b>Release display frame</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Release display frame API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This API is used to release a display frame from the application to the decoder library. When a release display frame API is called for a frame, the ownership of the buffer is transferred to the decoder library. The decoder library can now write into the buffer. This API command should be used only when u4_share_disp_buf in ih264d_init_ip_t is set to 1.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct<br>{<br> UWORD32 u4_size;<br> IVD_API_COMMAND_TYPE_T e_cmd;<br> UWORD32 u4_disp_buf_id;<br>} ivd_rel_display_frame_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="4">Input Structure Details</td>
         <td>API Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This parameter defines the function to be performed by decoder library. For Release display frame API, this should be IVD_CMD_REL_DISPLAY_FRAME</td>
      </tr>
      <tr>
         <td>u4_disp_buf_id</td>
         <td>This parameter indicates the ID of the buffer being released from display. This signals to the decoder that the buffer with this ID has been displayed and can be reused by codec. The details of the buffer must have been given to the decoder library using an IVD_CMD_SET_DISPLAY_FRAME API call earlier.</td>
      </tr>
      <tr>
         <td>Output Structure</td>
         <td colspan="2"> <br>typedef struct<br>{<br>UWORD32 u4_size;<br>UWORD32 u4_error_code;<br>} ivd_rel_display_frame_op_t;<br> </td>
      </tr>
      <tr>
         <td rowspan="3">Output Structure Details</td>
         <td>API Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>u4_error_code</td>
         <td>For the error and status codes refer Error/Status Codes</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Release display frame API</p>

<H1><b>2. Data Structures and Enumerations</b></H1>

This chapter defines some of the common data structures and enumerations used by codec APIs, to interact and exchange data with the application.

<H3><b>Memory Records</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Memory Records (iv_mem_rec_t)</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This structure is used to pass the memory requirement of decoder to application.</td>
      </tr>
      <tr>
         <td>Structure definition</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> void *pv_base;<br> UWORD32 u4_mem_size;<br> UWORD32 u4_mem_alignment;<br> IV_MEM_TYPE_T e_mem_type;<br>}  iv_mem_rec_t;</td>
      </tr>
      <tr>
         <td>Enumeration definition<br> <br> <br> <br> <br> <br> <br> <br> </td>
         <td colspan="2"> <br>typedef enum {<br> <br> IV_NA_MEM_TYPE = 0x7FFFFFFF,<br> <br> IV_INTERNAL_CACHEABLE_PERSISTENT_MEM = 0x1,<br> <br> IV_INTERNAL_CACHEABLE_SCRATCH_MEM = 0x2,<br> <br>    IV_EXTERNAL_CACHEABLE_PERSISTENT_MEM = 0x3,<br> <br> IV_EXTERNAL_CACHEABLE_SCRATCH_MEM = 0x4,<br> <br> IV_INTERNAL_NONCACHEABLE_PERSISTENT_MEM = 0x5,<br> <br>    IV_INTERNAL_NONCACHEABLE_SCRATCH_MEM = 0x6,<br> <br> IV_EXTERNAL_NONCACHEABLE_PERSISTENT_MEM = 0x7,<br> <br> IV_EXTERNAL_NONCACHEABLE_SCRATCH_MEM = 0x8<br> <br>} IV_MEM_TYPE_T; <br> <br> </td>
      </tr>
      <tr>
         <td rowspan="6">Members of structure</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Contains the size of the current memory record.</td>
      </tr>
      <tr>
         <td>pv_base</td>
         <td>Contains the base address of the current memory record.</td>
      </tr>
      <tr>
         <td>u4_mem_size</td>
         <td>Contains the size of the memory to be allocated.</td>
      </tr>
      <tr>
         <td>u4_mem_alignment</td>
         <td>Defines the alignment requirement of the base address for memory record.</td>
      </tr>
      <tr>
         <td>e_mem_type</td>
         <td>Contains the type of memory e.g. internal, scratch, persistent, etc.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: memory records (IV_MEM_REC_T)</p>

<H3><b>YUV Frame Buffer</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">YUV Frame buffer (iv_yuv_buf_t)</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This structure is used to pass the frame buffer from application to decoder and decoder uses these buffer to store decoded frame, also on get_display_frame API, decoder returns pointer to yuv_frm_buf_t</td>
      </tr>
      <tr>
         <td>Structure definition</td>
         <td colspan="2"> <br>typedef struct {<br>UWORD32          u4_size;<br>void              *pv_y_buf;<br>void              *pv_u_buf;<br>void              *pv_v_buf;<br>UWORD32           u4_y_wd; <br>UWORD32           u4_y_ht;<br>UWORD32           u4_y_strd;<br>UWORD32           u4_u_wd;<br>UWORD32           u4_u_ht;<br>UWORD32           u4_u_strd;<br>UWORD32           u4_v_wd;<br>UWORD32           u4_v_ht;<br>UWORD32           u4_v_strd;<br>} iv_yuv_buf_t;</td>
      </tr>
      <tr>
         <td rowspan="14">Members of structure</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>u4_size of the structure</td>
      </tr>
      <tr>
         <td>pv_y_buf</td>
         <td>Contains the base address of the Y component of the decoder frame.</td>
      </tr>
      <tr>
         <td>pv_u_buf</td>
         <td>Contains the base address of the U component of the decoder frame</td>
      </tr>
      <tr>
         <td>pv_v_buf</td>
         <td>Contains the base address of the V component of the decoder frame</td>
      </tr>
      <tr>
         <td>u4_y_wd</td>
         <td>Defines the width of the Y frame buffer.</td>
      </tr>
      <tr>
         <td>u4_y_ht</td>
         <td>Defines the height of the Y frame buffer.</td>
      </tr>
      <tr>
         <td>u4_y_strd</td>
         <td>Stride/Pitch of the Luma (Y) Buffer</td>
      </tr>
      <tr>
         <td>u4_u_wd</td>
         <td>Defines the width of the U component in frame buffer.</td>
      </tr>
      <tr>
         <td>u4_u_ht</td>
         <td>Defines the height of the U component in frame buffer.</td>
      </tr>
      <tr>
         <td>u4_u_strd</td>
         <td>Stride/Pitch of the U Buffer.</td>
      </tr>
      <tr>
         <td>u4_v_wd</td>
         <td>Defines the width of the V component in frame buffer.</td>
      </tr>
      <tr>
         <td>u4_v_ht</td>
         <td>Defines the height of the V component in frame buffer.</td>
      </tr>
      <tr>
         <td>u4_v_strd</td>
         <td>Stride/Pitch of the V Buffer.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: YUV frame buffer (yuv_frm_buf_t)</p>

<H3><b>Video decoder Object (Handle)</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">iv_obj_t</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This structure defines the handle for the codec instance</td>
      </tr>
      <tr>
         <td>Structure definition</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> void *pv_fxns;<br> void *pv_codec_handle;<br>} iv_obj_t;</td>
      </tr>
      <tr>
         <td rowspan="4">Members of structure</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>pv_fxns</td>
         <td>Pointer to the API function pointer table of the codec</td>
      </tr>
      <tr>
         <td>pv_codec_handle</td>
         <td>Pointer to the handle of the codec</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Video decoder Object</p>

<H3><b>VOP/Frame coding type Enumeration</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">VOP/Frame coding type </th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This Enumeration defines the frame/VOP type.</td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum {<br>    IV_NA_FRAME    = 0x7FFFFFFF,<br>    IV_I_FRAME           = 0x0,<br>    IV_P_FRAME                              = 0x1,<br>    IV_B_FRAME                              = 0x2,<br>    IV_IDR_FRAME                            = 0x3,<br>    IV_II_FRAME                             = 0x4,<br>    IV_IP_FRAME                             = 0x5,<br>    IV_IB_FRAME                             = 0x6,<br>    IV_PI_FRAME                             = 0x7,<br>    IV_PP_FRAME                             = 0x8,<br>    IV_PB_FRAME                             = 0x9,<br>    IV_BI_FRAME                             = 0xa,<br>    IV_BP_FRAME                             = 0xb,<br>    IV_BB_FRAME                             = 0xc,<br>    IV_MBAFF_I_FRAME                        = 0xd,<br>    IV_MBAFF_P_FRAME                        = 0xe,<br>    IV_MBAFF_B_FRAME                        = 0xf,<br>    IV_MBAFF_IDR_FRAME                      = 0x10,<br>    IV_NOT_CODED_FRAME                      = 0x11,<br>    IV_FRAMETYPE_DEFAULT                   = IV_I_FRAME<br>} IV_PICTURE_CODING_TYPE_T;</td>
      </tr>
      <tr>
         <td rowspan="21">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IV_NA_FRAME </td>
         <td>Frame type not available. </td>
      </tr>
      <tr>
         <td>IV_I_FRAME </td>
         <td>Intra coded frame. </td>
      </tr>
      <tr>
         <td>IV_P_FRAME </td>
         <td>Forward inter coded frame. </td>
      </tr>
      <tr>
         <td>IV_B_FRAME </td>
         <td>Bi-directional inter coded frame. </td>
      </tr>
      <tr>
         <td>IV_IDR_FRAME </td>
         <td>Intra coded frame that can be used for refreshing video content.</td>
      </tr>
      <tr>
         <td>IV_II_FRAME </td>
         <td>Interlaced Frame, both fields are I frames </td>
      </tr>
      <tr>
         <td>IV_IP_FRAME </td>
         <td>Interlaced Frame, first field is an I field picture, second field is a P field picture. </td>
      </tr>
      <tr>
         <td>IV_IB_FRAME </td>
         <td>Interlaced Frame, first field is an I field picture, second field is a B field picture. </td>
      </tr>
      <tr>
         <td>IV_PI_FRAME </td>
         <td>Interlaced Frame, first field is a P field picture, second field is an I field picture. </td>
      </tr>
      <tr>
         <td>IV_PP_FRAME </td>
         <td>Interlaced Frame, first field is a P field picture, second field is a P field picture. </td>
      </tr>
      <tr>
         <td>IV_PB_FRAME </td>
         <td>Interlaced Frame, first field is a P field picture, second field is a B field picture. </td>
      </tr>
      <tr>
         <td>IV_BI_FRAME </td>
         <td>Interlaced Frame, first field is a B field picture, second field is an I field picture. </td>
      </tr>
      <tr>
         <td>IV_BP_FRAME </td>
         <td>Interlaced Frame, first field is a B field picture, second field is a P field picture. </td>
      </tr>
      <tr>
         <td>IV_BB_FRAME </td>
         <td>Interlaced Frame, both fields are B field pictures. </td>
      </tr>
      <tr>
         <td>IV_MBAFF_I_FRAME </td>
         <td>Intra coded MBAFF frame. </td>
      </tr>
      <tr>
         <td>IV_MBAFF_P_FRAME </td>
         <td>Forward inter coded MBAFF frame. </td>
      </tr>
      <tr>
         <td>IV_MBAFF_B_FRAME </td>
         <td>Bi-directional inter coded MBAFF frame. </td>
      </tr>
      <tr>
         <td>IV_MBAFF_IDR_FRAME </td>
         <td>Intra coded MBAFF frame that can be used for refreshing video content. </td>
      </tr>
      <tr>
         <td>IV_NOT_CODED_FRAME</td>
         <td>The frame is not coded.</td>
      </tr>
      <tr>
         <td>IV_FRAMETYPE_DEFAULT </td>
         <td>Default setting.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: VOP/Frame coding type</p>

<H3><b>Skip mode Enumeration</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Skip mode Enumeration </th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This Enumeration defines the skip modes available.</td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum {<br>    IVD_SKIP_NONE = 0x7FFFFFFF,<br>    IVD_SKIP_P                    = 0x1,<br>    IVD_SKIP_B                                  = 0x2,<br>    IVD_SKIP_I                                  = 0x3,<br>    IVD_SKIP_IP                                 = 0x4,<br>    IVD_SKIP_IB                                 = 0x5,<br>    IVD_SKIP_PB                                 = 0x6,<br>    IVD_SKIP_IPB                                = 0x7,<br>    IVD_SKIP_IDR                                = 0x8,<br>    IVD_SKIP_DEFAULT                            = IVD_SKIP_NONE<br>} IVD_FRAME_SKIP_MODE_T;</td>
      </tr>
      <tr>
         <td rowspan="11">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IVD_SKIP_NONE</td>
         <td>Do not skip any frame types. </td>
      </tr>
      <tr>
         <td>IVD_SKIP_P </td>
         <td>Decode the P frame/skip frames internally, but do not copy the decoded output to the output buffers. This should be indicated by setting theout put buffers to NULL. <br>Remarks: <br>For example, if a B frame is dependent on the previously decoded P frame, the B frame shall be decoded and displayed successfully. For this, the P frame needs to be decoded, but not copied to the output buffer. </td>
      </tr>
      <tr>
         <td>IVD_SKIP_B </td>
         <td>Skip B, BI frames. For B frames, the decoder will decode the frame bit stream, and return as soon as the frame type is decisively decoded. Internally, the algorithm will modify its state, so that subsequent decoding of other frames is possible. </td>
      </tr>
      <tr>
         <td>IVD_SKIP_I </td>
         <td>Skip intra coded frame. </td>
      </tr>
      <tr>
         <td>IVD_SKIP_IP </td>
         <td>Skip I and P frame/field(s). </td>
      </tr>
      <tr>
         <td>IVD_SKIP_IB </td>
         <td>Skip I and B frame/field(s). </td>
      </tr>
      <tr>
         <td>IVD_SKIP_PB </td>
         <td>Skip P and B frame/field(s). </td>
      </tr>
      <tr>
         <td>IVD_SKIP_IPB </td>
         <td>Skip I/P/B/BI frames. </td>
      </tr>
      <tr>
         <td>IVD_SKIP_IDR </td>
         <td>Skip IDR Frame. </td>
      </tr>
      <tr>
         <td>IVD_SKIP_DEFAULT </td>
         <td>Default settings. Currently set to IVD_SKIP_NONE.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Skip mode Enumeration</p>

<H3><b>Video content type</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Video content type </th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This Enumeration defines the video content type.</td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum {<br>    IV_CONTENTTYPE_NA = 0x7FFFFFFF,<br>    IV_PROGRESSIVE    = 0x0,<br>    IV_INTERLACED                           = 0x1,<br>    IV_PROGRESSIVE_FRAME                    = 0x2,<br>    IV_INTERLACED_FRAME                     = 0x3,<br>    IV_INTERLACED_TOPFIELD                  = 0x4,<br>    IV_INTERLACED_BOTTOMFIELD               = 0x5,<br>    IV_CONTENTTYPE_DEFAULT                  = IV_PROGRESSIVE,<br>} IV_CONTENT_TYPE_T;</td>
      </tr>
      <tr>
         <td rowspan="9">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IV_CONTENTTYPE_NA </td>
         <td>Frame type is not available. </td>
      </tr>
      <tr>
         <td>IV_PROGRESSIVE </td>
         <td>Progressive frame. </td>
      </tr>
      <tr>
         <td>IV_PROGRESSIVE_FRAME </td>
         <td>Progressive Frame. </td>
      </tr>
      <tr>
         <td>IV_INTERLACED </td>
         <td>Interlaced frame. </td>
      </tr>
      <tr>
         <td>IV_INTERLACED_FRAME </td>
         <td>Interlaced frame. </td>
      </tr>
      <tr>
         <td>IV_INTERLACED_TOPFIELD </td>
         <td>Interlaced picture, top field. </td>
      </tr>
      <tr>
         <td>IV_INTERLACED_BOTTOMFIELD </td>
         <td>Interlaced picture, bottom field. </td>
      </tr>
      <tr>
         <td>IV_CONTENTTYPE_DEFAULT </td>
         <td>Default setting.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Video content type</p>

<H3><b>API command type</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">API command type</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This Enumeration defines the API command type.</td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum {<br> IV_CMD_NA = 0x7FFFFFFF,<br> IV_CMD_GET_NUM_MEM_REC = 0x0,<br> IV_CMD_FILL_NUM_MEM_REC = 0x1,<br> IV_CMD_RETRIEVE_MEMREC = 0x2,<br> IV_CMD_INIT = 0x3,<br>    IV_CMD_DUMMY_ELEMENT = 0x4,<br>} IV_API_COMMAND_TYPE_T;</td>
      </tr>
      <tr>
         <td rowspan="5">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IV_CMD_NA</td>
         <td>Unknown command. Should not be used.</td>
      </tr>
      <tr>
         <td>IV_CMD_GET_NUM_MEM_REC</td>
         <td>Get Number of Memory Records API functionality is called<br> </td>
      </tr>
      <tr>
         <td>IV_CMD_FILL_NUM_MEM_REC</td>
         <td>Fill Memory Records API functionality is called</td>
      </tr>
      <tr>
         <td>IV_CMD_INIT</td>
         <td>Initialize decoder API functionality is called<br> </td>
      </tr>
      <tr>
         <td> </td>
         <td>IV_CMD_RETRIEVE_MEMREC</td>
         <td>Retrieve memory records API functionality is called.</td>
      </tr>
      <tr>
         <td> </td>
         <td>IV_CMD_DUMMY_ELEMENT</td>
         <td>Dummy element, not used.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: API command type</p>

<H3><b>Decode API command type</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">API command type</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This Enumeration defines the API command type.</td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum {<br>      IVD_CMD_VIDEO_NA       = 0x7FFFFFFF,<br>    IVD_CMD_VIDEO_CTL        =   IV_CMD_DUMMY_ELEMENT + 1,<br>    IVD_CMD_VIDEO_DECODE,<br>    IVD_CMD_GET_DISPLAY_FRAME,<br>    IVD_CMD_REL_DISPLAY_FRAME,<br>    IVD_CMD_SET_DISPLAY_FRAME<br>} IVD_API_COMMAND_TYPE_T;</td>
      </tr>
      <tr>
         <td rowspan="5">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IV_CMD_VIDEO_NA</td>
         <td>Unknown command. Should not be used.</td>
      </tr>
      <tr>
         <td>IVD_CMD_VIDEO_CTL       </td>
         <td>This enumeration indicates control command.<br>Refer to section 2.5 for more details.</td>
      </tr>
      <tr>
         <td>IVD_CMD_VIDEO_DECODE</td>
         <td>This enumeration indicates Video decode command. Refer to section 2.6 for more details.</td>
      </tr>
      <tr>
         <td>IVD_CMD_GET_DISPLAY_FRAME</td>
         <td>The enumeration is not being used currently.</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_CMD_REL_DISPLAY_FRAME</td>
         <td>This enumeration indicates Release display frame command. Refer to section 2.8 for more details.</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_CMD_SET_DISPLAY_FRAME</td>
         <td>This Enumeration indicates Set display frame command. Refer to section 2.7 for more details.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: API command type</p>

<H3><b>Video control API command type</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Video control API command type</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This Enumeration defines the Video Control API command type.</td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum {<br>IVD_CMD_NA = 0x7FFFFFFF,<br>IVD_CMD_CTL_GETPARAMS = 0x0,<br> IVD_CMD_CTL_SETPARAMS = 0x1,<br> IVD_CMD_CTL_RESET = 0x2,<br> IVD_CMD_CTL_SETDEFAULT = 0x3,<br> IVD_CMD_CTL_FLUSH = 0x4,<br> IVD_CMD_CTL_GETBUFINFO = 0x5,<br> IVD_CMD_CTL_GETVERSION = 0x6,<br> IVD_CMD_CTL_CODEC_SUBCMD_START = 0x7<br>} IVD_CONTROL_API_COMMAND_TYPE_T;</td>
      </tr>
      <tr>
         <td rowspan="8">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IVD_CMD_NA</td>
         <td>Unknown command. Should not be used.</td>
      </tr>
      <tr>
         <td>IVD_CMD_CTL_GETPARAMS</td>
         <td>Get run-time dynamic parameters via the ivd_ctl_getstatus_ip_t and ivd_ctl_getstatus_op_t structures</td>
      </tr>
      <tr>
         <td>IVD_CMD_CTL_SETPARAMS</td>
         <td>Set run-time dynamic parameters via the ivd_ctl_set_config_ip_t and ivd_ctl_set_config_op_t structures</td>
      </tr>
      <tr>
         <td>IVD_CMD_CTL_RESET</td>
         <td>Reset the algorithm via the ivd_ctl_reset_ip_t and ivd_ctl_reset_op_t structures</td>
      </tr>
      <tr>
         <td>IVD_CMD_CTL_SETDEFAULT</td>
         <td>Set run-time dynamic parameters to default values via the ivd_set_config_ip_t and ivd_set_config_op_t structures</td>
      </tr>
      <tr>
         <td>IVD_CMD_CTL_FLUSH</td>
         <td>Handle end of stream conditions. This command forces algorithm instance to flush out allthe decoded buffers via the ivd_ctl_flush_ip_t and ivd_ctl_flush_ip_t structures</td>
      </tr>
      <tr>
         <td>IVD_CMD_CTL_GETBUFINFO</td>
         <td>Query algorithm instance regarding the properties of input and output buffers via the ivd_ctl_getbufinfo_ip_t and ivd_ctl_getbufinfo_op_t structures</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_CMD_CTL_GETVERSION</td>
         <td>Get the version information of the decoder library via the ivd_ctl_getversioninfo_ip_t and ivd_ctl_getversioninfo_op_t structures.</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_CMD_CTL_CODEC_SUBCMD_START        </td>
         <td>Codec specific control commands will start with this value.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Video control API command type</p>

<H3><b>Color Format Enumeration</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Color Format Enumeration</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This Enumeration defines the various possible color format</td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum {<br>    IV_CHROMA_NA = 0x7FFFFFFF,<br>    IV_YUV_420P           = 0x1,<br>    IV_YUV_422P = 0x2,<br>   IV_420_UV_INTL = 0x3,<br>    IV_YUV_422IBE                           = 0x4,<br>    IV_YUV_422ILE                           = 0x5,<br>    IV_YUV_444P                             = 0x6,<br>    IV_YUV_411P                             = 0x7,<br>    IV_GRAY                                 = 0x8,<br>    IV_RGB_565                              = 0x9,<br>    IV_RGB_24                               = 0xa,<br>    IV_YUV_420SP_UV                         = 0xb,<br>    IV_YUV_420SP_VU                         = 0xc,<br>
         IV_RGBA_8888                            = 0xd <br>} IV_COLOR_FORMAT_T;</td>
      </tr>
      <tr>
         <td rowspan="10">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IV_CHROMA_NA</td>
         <td>Chroma format not applicable</td>
      </tr>
      <tr>
         <td>IV_YUV_420P</td>
         <td>YUV 4:2:0 planer</td>
      </tr>
      <tr>
         <td>IV_YUV_422P</td>
         <td>YUV 4:2:2 planer</td>
      </tr>
      <tr>
         <td>IV_420_UV_INTL</td>
         <td>YUV 4:2:0 Semi-planar [Only Uand V color components are interleaved]</td>
      </tr>
      <tr>
         <td>IV_YUV_422IBE</td>
         <td>YUV 4:2:2 interleaved (bigendian).</td>
      </tr>
      <tr>
         <td>IV_YUV_422ILE</td>
         <td>YUV 4:2:2 interleaved (littleendian).</td>
      </tr>
      <tr>
         <td>IV_YUV_444P</td>
         <td>YUV 4:4:4 planar</td>
      </tr>
      <tr>
         <td>IV_YUV_411P</td>
         <td>YUV 4:1:1 planar</td>
      </tr>
      <tr>
         <td>IV_GRAY</td>
         <td>Gray format.</td>
      </tr>
      <tr>
         <td> </td>
         <td>IV_RGB_565</td>
         <td>RGB 565 color format.</td>
      </tr>
      <tr>
         <td> </td>
         <td>IV_RGB_24</td>
         <td>RGB 24 color format.</td>
      </tr>
      <tr>
         <td> </td>
         <td>IV_YUV_420SP_UV</td>
         <td>YUV 4:2:0 Semi-planar [Only Uand V color components are interleaved, with U first and V second]</td>
      </tr>
      <tr>
         <td> </td>
         <td>IV_YUV_420SP_VU</td>
         <td>YUV 4:2:0 Semi-planar [Only Uand V color components are interleaved, with V first and U second]</td>
      </tr>
      <tr>
         <td> </td>
         <td>IV_RGBA_8888</td>
         <td>RGB 8888 color format.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Color Format</p>

<H3><b>Video Decode Mode Enumeration</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Video Decode Mode Enumeration    </th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This Enumeration indicates whether the frame decode API call shall decode only header on header and frame worth of data</td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum {<br>    IVD_DECODE_MODE_NA             = 0x7FFFFFFF,<br>    IVD_DECODE_FRAME               = 0x0,<br>    IVD_DECODE_HEADER              = 0x1,<br>} IVD_VIDEO_DECODE_MODE_T;</td>
      </tr>
      <tr>
         <td rowspan="4">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IVD_DECODE_MODE_NA            </td>
         <td>Unknown command. Should not be used.</td>
      </tr>
      <tr>
         <td>IVD_DECODE_FRAME</td>
         <td>Decode both header and frame worth of data</td>
      </tr>
      <tr>
         <td>IVD_DECODE_HEADER</td>
         <td>Decode only header data</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Video Decode Mode Enumeration</p>

<H3><b>Frame Output Modes Enumeration</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Video Frame Output Mode Enumeration    </th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This Enumeration indicates whether Get Display Buffer API call shall output frames in display ordering or in decode ordering</td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum {<br> IVD_DISPLAY_ORDER_NA = 0x7FFFFFFF,<br> IVD_DISPLAY_FRAME_OUT = 0x0,<br> IVD_DECODE_FRAME_OUT = 0x1,<br>} IVD_DISPLAY_FRAME_OUT_MODE_T;</td>
      </tr>
      <tr>
         <td rowspan="4">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IVD_DISPLAY_ORDER_NA</td>
         <td>Unknown command. Should not be used.</td>
      </tr>
      <tr>
         <td>IVD_DISPLAY_FRAME_OUT</td>
         <td>To set codec to fill output buffers in display order</td>
      </tr>
      <tr>
         <td>IVD_DECODE_FRAME_OUT</td>
         <td>To set codec to fill output buffers in decode order</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Enumeration definition for IVD_DISPLAY_FRAME_OUT_MODE_T</p>

<H3><b>Frame Skip Modes Enumeration</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Skip mode Enumeration</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This Enumeration defines the skip modes available.</td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum {<br>    IVD_SKIP_NONE                                                   = 0x7FFFFFFF,<br>    IVD_SKIP_P                           = 0x1,<br>    IVD_SKIP_B                                  = 0x2,<br>    IVD_SKIP_I                                  = 0x3,<br>    IVD_SKIP_IP                                 = 0x4,<br>    IVD_SKIP_IB                                 = 0x5,<br>    IVD_SKIP_PB                                 = 0x6,<br>    IVD_SKIP_IPB                                = 0x7,<br>    IVD_SKIP_IDR                                = 0x8,<br>    IVD_SKIP_DEFAULT                            = IVD_SKIP_NONE<br>} IVD_FRAME_SKIP_MODE_T;</td>
      </tr>
      <tr>
         <td rowspan="11">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IVD_SKIP_NONE</td>
         <td>Do not skip any frame types. </td>
      </tr>
      <tr>
         <td>IVD_SKIP_P </td>
         <td>Decode the P frame/skip frames internally, but do not copy the decoded output to the output buffers. This should be indicated by setting the output buffers to NULL. <br>Remarks: <br>For example, if a B frame is dependent on the previously decoded P frame, the B frame shall be decoded and displayed successfully. For this, the P frame needs to be decoded, but not copied to the output buffer. </td>
      </tr>
      <tr>
         <td>IVD_SKIP_B </td>
         <td>Skip B, BI frames. For B frames, the decoder will decode the frame bit stream, and return as soon as the frame type is decisively decoded. Internally, the algorithm will modify its state, so that subsequent decoding of other frames is possible. </td>
      </tr>
      <tr>
         <td>IVD_SKIP_I </td>
         <td>Skip intra coded frame. </td>
      </tr>
      <tr>
         <td>IVD_SKIP_IP </td>
         <td>Skip I and P frame/field(s). </td>
      </tr>
      <tr>
         <td>IVD_SKIP_IB </td>
         <td>Skip I and B frame/field(s). </td>
      </tr>
      <tr>
         <td>IVD_SKIP_PB </td>
         <td>Skip P and B frame/field(s). </td>
      </tr>
      <tr>
         <td>IVD_SKIP_IPB </td>
         <td>Skip I/P/B/BI frames. </td>
      </tr>
      <tr>
         <td>IVD_SKIP_IDR </td>
         <td>Skip IDR Frame. </td>
      </tr>
      <tr>
         <td>IVD_SKIP_DEFAULT </td>
         <td>Default settings. Currently set to IVD_SKIP_NONE.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Enumeration definition for IVD_FRAME_SKIP_MODE_T</p>

<H1><b>3. Input/output structure details for Video Control API</b></H1>

<H3><b>Get Buffer Information</b></H3>
When e_sub_cmd in the input structure of Video Control API is IVD_CMD_CTL_GETBUFINFO, this API is used to get the Input/output Buffer size information from the decoder.

Following table details the input/output structures for the functionality

<table>
   <thead>
      <tr>
         <th colspan="3">Get Buffer Information API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This returns the details the Input/output Buffer details.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> IVD_API_COMMAND_TYPE_T e_cmd;<br> IVD_CONTROL_API_COMMAND_TYPE_T e_sub_cmd;<br>} ivd_ctl_getbufinfo_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="4">Input Structure Details</td>
         <td>API Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Stores the size of this structure.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This indicates the functionality to be performed by the decoder API. To perform this control functionality this has to be equal to IVD_CMD_VIDEO_CTL</td>
      </tr>
      <tr>
         <td>e_sub_cmd</td>
         <td>This tells the functionality to be performed by the Video control API. To get the buffer information of the decoder, this value of this parameter should be equal to IVD_CMD_ctl_GETBUFINFO</td>
      </tr>
      <tr>
         <td>Output Structure</td>
         <td colspan="2">typedef struct {<br>   UWORD32 u4_size;<br>   UWORD32 u4_error_code;<br>   UWORD32 u4_num_disp_bufs;<br>   UWORD32 u4_min_num_in_bufs;<br>   UWORD32 u4_min_num_out_bufs;<br>   UWORD32  u4_min_in_buf_size[IVD_VIDDEC_MAX_IO_BUFFERS];<br>   UWORD32 u4_min_out_buf_size[IVD_VIDDEC_MAX_IO_BUFFERS];<br>} ivd_ctl_getbufinfo_op_t;</td>
      </tr>
      <tr>
         <td rowspan="4">Output Structure Details</td>
         <td>API Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>u4_error_code</td>
         <td>The error code returned.</td>
      </tr>
      <tr>
         <td>u4_num_disp_bufs</td>
         <td>Number of display buffer sets required by codec. Application can allocate 16 more than this number at max. These 16 buffers allow handling of display depth.</td>
      </tr>
      <tr>
         <td rowspan="4"> <br><br></td>
         <td>u4_min_num_in_bufs</td>
         <td>Minimum no of Input Buffers needed bythe decoder</td>
      </tr>
      <tr>
         <td>u4_min_num_out_bufs</td>
         <td>Minimum no of Output Buffers needed by the decoder</td>
      </tr>
      <tr>
         <td>u4_min_in_buf_size[]</td>
         <td>Array containing the size (in bytes) required for each input buffer</td>
      </tr>
      <tr>
         <td>u4_min_out_buf_size []</td>
         <td>Array containing the size(in bytes) required for each output buffer</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Get Buffer Information API</p>

<H3><b>Set Params</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Set Params API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This API is used to set the run time parameters of the decoder.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct {<br>    UWORD32 u4_size;<br>  IVD_API_COMMAND_TYPE_T                      e_cmd;<br>    IVD_CONTROL_API_COMMAND_TYPE_T              e_sub_cmd;<br>    IVD_VIDEO_DECODE_MODE_T                     e_vid_dec_mode;<br>    UWORD32                                     u4_disp_wd;<br>   IVD_FRAME_SKIP_MODE_T                       e_frm_skip_mode;<br>    IVD_DISPLAY_FRAME_OUT_MODE_T                e_frm_out_mode;<br>} ivd_ctl_set_config_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="8">Input Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This parameter defines the functionality to be performed by decoder API. For control calls, it should be IVD_CMD_VIDEO_CTL</td>
      </tr>
      <tr>
         <td>e_sub_cmd</td>
         <td>This tells the functionality to be performed by the Video control API. To set the dynamic parameters of the decoder, this value of this parameter should be equal to IVD_CMD_CTL_SETPARAMS or IVD_CMD_CTL_SETDEFAULT</td>
      </tr>
      <tr>
         <td>e_vid_dec_mode</td>
         <td>This parameter is set equal to IVD_DECODE_HEADER if the application wants decoder to decode only the header in the next Video decode API call, otherwise it is set equal to IVD_DECODE_FRAME. See IVD_VIDEO_DECODE_MODE_T.</td>
      </tr>
      <tr>
         <td>u4_disp_wd</td>
         <td>This parameter is used to set the stride of the output buffer s_out_buffer, given to decoder in Video Decode API call. .</td>
      </tr>
      <tr>
         <td>e_frm_skip_mode</td>
         <td>Stores the skip mode settings. Refer IVD_FRAME_SKIP_MODE_T for the skip modes available.</td>
      </tr>
      <tr>
         <td>e_frm_out_mode</td>
         <td>Stores the display modes. Refer IVD_DISPLAY_FRAME_OUT_MODE_T for the modes available.</td>
      </tr>
      <tr>
         <td>Note</td>
         <td colspan="2">This API may be called after Initialization. If not called then the decoder initializes the parameters to their default state.</td>
      </tr>
      <tr>
         <td>Output Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> UWORD32 u4_error_code;<br>} ivd_ctl_set_config_op_t;</td>
      </tr>
      <tr>
         <td rowspan="2">Output Structure Details</td>
         <td>API Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td> </td>
         <td>u4_error_code</td>
         <td>Status of the control call</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Video Control API - Set Params</p>

<H3><b>Get Params</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Get Params API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This API is used to get the status of runtime parameters from the decoder.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> IVD_API_COMMAND_TYPE_T e_cmd;<br> IVD_CONTROL_API_COMMAND_TYPE_T e_sub_cmd;<br>} ivd_ctl_getstatus_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="4">Input Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This parameter defines the functionality to be performed by decoder API. To call this API the command should be IVD_CMD_VIDEO_CTL</td>
      </tr>
      <tr>
         <td>e_sub_cmd</td>
         <td>This tells the functionality to be performed by the Video control API. To get the status of the decoder, the value of this parameter should be equal to IVD_CMD_ctl_GETPARAMS</td>
      </tr>
      <tr>
         <td>Output Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> UWORD32          u4_error_code;<br>   UWORD32                  u4_num_disp_bufs;<br>    UWORD32                  u4_pic_ht;<br>                  UWORD32          u4_pic_wd;<br>       UWORD32                  u4_frame_rate;<br>    UWORD32                  u4_bit_rate;<br>        IV_CONTENT_TYPE_T        e_content_type;<br>  IV_COLOR_FORMAT_T        e_output_chroma_format;<br>    UWORD32                  u4_min_num_in_bufs;<br>    UWORD32                  u4_min_num_out_bufs;<br>    UWORD32 u4_min_in_buf_size[IVD_VIDDEC_MAX_IO_BUFFERS];<br>    UWORD32u4_min_out_buf_size[IVD_VIDDEC_MAX_IO_BUFFERS];<br>} ivd_ctl_getstatus_op_t;</td>
      </tr>
      <tr>
         <td rowspan="14">Output Structure Details<br>            </td>
         <td>API Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>u4_error_code</td>
         <td>Error code. Refer the enum Codec Error Code for Error bit details</td>
      </tr>
      <tr>
         <td>u4_num_disp_bufs</td>
         <td>No of display buffers needed by the decoder. Application can allocate 16 more than this if required.</td>
      </tr>
      <tr>
         <td>u4_pic_ht</td>
         <td>Height of the video content</td>
      </tr>
      <tr>
         <td>u4_pic_wd</td>
         <td>Width of the video content</td>
      </tr>
      <tr>
         <td>u4_frame_rate</td>
         <td>Frame rate the video content</td>
      </tr>
      <tr>
         <td>u4_bit_rate</td>
         <td>Bit rate of the video content</td>
      </tr>
      <tr>
         <td>e_content_type</td>
         <td>Content type. Refer enum IV_CONTENT_TYPE_T in Section 3.6</td>
      </tr>
      <tr>
         <td>e_output_chroma_format</td>
         <td>Refer enum IV_COLOR_FORMAT_T</td>
      </tr>
      <tr>
         <td>u4_min_num_in_bufs</td>
         <td>No of input buffers for storing frame</td>
      </tr>
      <tr>
         <td>u4_min_num_out_bufs</td>
         <td>No of output buffers for storing frame</td>
      </tr>
      <tr>
         <td>u4_min_in_buf_size []</td>
         <td>Array containing the size of each input buffer</td>
      </tr>
      <tr>
         <td>u4_min_out_buf_size []</td>
         <td>Array containing the size of each output buffer</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Video Control API - Get Status</p>

<H3><b>Flush</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Flush API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This API is used to flush the display buffers. In this call the decoder will prepare the decoded frames for display for the subsequent get display API calls..</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> IVD_API_COMMAND_TYPE_T e_cmd;<br> IVD_CONTROL_API_COMMAND_TYPE_T e_sub_cmd;<br>} ivd_ctl_flush_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="4">Input Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This parameter defines the functionality to be performed by decoder API. To call this API the command should be IVD_CMD_VIDEO_CTL</td>
      </tr>
      <tr>
         <td>e_sub_cmd</td>
         <td>This tells the functionality to be performed by the Video control API. To set the dynamic parameters of the decoder, the value of this parameter should be equal to IVD_CMD_CTL_FLUSH</td>
      </tr>
      <tr>
         <td>Output Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> UWORD32 u4_error_code;<br>} ivd_ctl_flush_op_t;</td>
      </tr>
      <tr>
         <td rowspan="3">Output Structure Details</td>
         <td>API Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>u4_error_code</td>
         <td>For the error and status codes refer Error/Status Codes.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Video Control API - Flush</p>

<H3><b>Reset</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Reset API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This API is used to reset the decoder. After this call is made, the decoder acquires a state similar to after initialization of the instance.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> IVD_API_COMMAND_TYPE_T e_cmd;<br> IVD_CONTROL_API_COMMAND_TYPE_T e_sub_cmd;<br>} ivd_ctl_reset_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="4">Input Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This parameter defines the functionality to be performed by decoder API. To call this API the command should be IVD_CMD_VIDEO_CTL</td>
      </tr>
      <tr>
         <td>e_sub_cmd</td>
         <td>This tells the functionality to be performed by the Video control API. To reset the decoder, the value of this parameter should be equal to IVD_CMD_CTL_RESET</td>
      </tr>
      <tr>
         <td>Output Structure</td>
         <td colspan="2">typedef struct {<br> UWORD32 u4_size;<br> UWORD32 u4_error_code;<br>} ivd_ctl_reset_op_t;</td>
      </tr>
      <tr>
         <td rowspan="3">Output Structure Details</td>
         <td>API Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>u4_error_code</td>
         <td>For the error and status codes refer Error/Status Codes.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Video Control API - Reset</p>

<H1><b>4. Error/Status Codes</b></H1>

<H3><b>API Error/Status Codes</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">API Error/status codes</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This Enumeration defines the Error/Status codes.</td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum{<br> IV_STATUS_NA = 0x7FFFFFFF,<br> IV_SUCCESS = 0x0,<br> IV_FAIL = 0x1<br>} IV_API_CALL_STATUS_T;</td>
      </tr>
      <tr>
         <td rowspan="4">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IV_STATUS_NA</td>
         <td>Unknown command. Should not be used.</td>
      </tr>
      <tr>
         <td>IV_SUCCESS</td>
         <td>The API executed successfully</td>
      </tr>
      <tr>
         <td>IV_FAIL</td>
         <td>The API could not execute successfully</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: API Error Status codes</p>

<H3><b>Codec Error Code</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Codec Error Code</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">Decoder updates e_Error_code bits as per the enumeration values corresponding to the error. Lower 8 bits of error code will be used for the below enum.</td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum {<br>    IVD_ERROR_NONE = 0x0,<br>    IVD_NUM_MEM_REC_FAILED             = 0x1,<br>    IVD_NUM_REC_NOT_SUFFICIENT                  = 0x2,<br>    IVD_FILL_MEM_REC_FAILED                     = 0x3,<br>    IVD_REQUESTED_WIDTH_NOT_SUPPPORTED          = 0x4,<br>    IVD_REQUESTED_HEIGHT_NOT_SUPPPORTED         = 0x5,<br>    IVD_INIT_DEC_FAILED                         = 0x6,<br>    IVD_INIT_DEC_NOT_SUFFICIENT                 = 0x7,<br>    IVD_INIT_DEC_WIDTH_NOT_SUPPPORTED           = 0x8,<br>    IVD_INIT_DEC_HEIGHT_NOT_SUPPPORTED          = 0x9,<br>    IVD_INIT_DEC_MEM_NOT_ALIGNED                = 0xa,<br>    IVD_INIT_DEC_COL_FMT_NOT_SUPPORTED          = 0xb,<br>    IVD_INIT_DEC_MEM_REC_NOT_SUFFICIENT         = 0xc,<br>   IVD_GET_VERSION_DATABUFFER_SZ_INSUFFICIENT  = 0xd,<br>    IVD_BUFFER_SIZE_SET_TO_ZERO                 = 0xe,<br>    IVD_UNEXPECTED_END_OF_STREAM                = 0xf,<br>    IVD_SEQUENCE_HEADER_NOT_DECODED             = 0x10,<br>    IVD_STREAM_WIDTH_HEIGHT_NOT_SUPPORTED       = 0x11,<br>    IVD_MAX_FRAME_LIMIT_REACHED                 = 0x12,<br>    IVD_IP_API_STRUCT_SIZE_INCORRECT            = 0x13,<br>    IVD_OP_API_STRUCT_SIZE_INCORRECT            = 0x14,<br>    IVD_HANDLE_NULL                             = 0x15,<br>    IVD_HANDLE_STRUCT_SIZE_INCORRECT            = 0x16,<br>    IVD_INVALID_HANDLE_NULL                     = 0x17,<br>    IVD_INVALID_API_CMD                         = 0x18,<br>    IVD_UNSUPPORTED_API_CMD                     = 0x19,<br>    IVD_MEM_REC_STRUCT_SIZE_INCORRECT           = 0x1a,<br>    IVD_DISP_FRM_ZERO_OP_BUFS                   = 0x1b,<br>    IVD_DISP_FRM_OP_BUF_NULL                    = 0x1c,<br>    IVD_DISP_FRM_ZERO_OP_BUF_SIZE               = 0x1d,<br>    IVD_DEC_FRM_BS_BUF_NULL                     = 0x1e,<br>    IVD_SET_CONFG_INVALID_DEC_MODE              = 0x1f,<br>    IVD_SET_CONFG_UNSUPPORTED_DISP_WIDTH        = 0x20,<br>    IVD_RESET_FAILED                            = 0x21,<br>    IVD_INIT_DEC_MEM_REC_OVERLAP_ERR            = 0x22,<br>    IVD_INIT_DEC_MEM_REC_BASE_NULL              = 0x23,<br>    IVD_INIT_DEC_MEM_REC_ALIGNMENT_ERR          = 0x24,<br>   IVD_INIT_DEC_MEM_REC_INSUFFICIENT_SIZE      = 0x25,<br>    IVD_INIT_DEC_MEM_REC_INCORRECT_TYPE         = 0x26,<br>    IVD_DEC_NUMBYTES_INV                        = 0x27,<br>    IVD_DEC_REF_BUF_NULL                        = 0x28,<br>    IVD_DEC_FRM_SKIPPED                         = 0x29,<br>    IVD_RES_CHANGED                             = 0x2a,<br>   IVD_DUMMY_ELEMENT_FOR_CODEC_EXTENSIONS      = 0x30,<br>} IVD_ERROR_CODES_T;</td>
      </tr>
      <tr>
         <td rowspan="34">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IVD_ERROR_NONE                           </td>
         <td>No error.</td>
      </tr>
      <tr>
         <td>IVD_NUM_MEM_REC_FAILED                   </td>
         <td>API call to get num_mem_rec failed</td>
      </tr>
      <tr>
         <td>IVD_NUM_REC_NOT_SUFFICIENT               </td>
         <td>Insufficient number of memory records</td>
      </tr>
      <tr>
         <td>IVD_FILL_MEM_REC_FAILED                  </td>
         <td>API call to get fill_mem_rec failed</td>
      </tr>
      <tr>
         <td>IVD_REQUESTED_WIDTH_NOT_SUPPPORTED       </td>
         <td>Requested Width not supported</td>
      </tr>
      <tr>
         <td>IVD_REQUESTED_HEIGHT_NOT_SUPPPORTED      </td>
         <td>Requested Height not supported</td>
      </tr>
      <tr>
         <td>IVD_INIT_DEC_FAILED                       </td>
         <td>Decoder init failed</td>
      </tr>
      <tr>
         <td>IVD_INIT_DEC_NOT_SUFFICIENT              </td>
         <td>Decoder init memory not sufficient</td>
      </tr>
      <tr>
         <td>IVD_INIT_DEC_WIDTH_NOT_SUPPPORTED        </td>
         <td>Width requested at init not supported</td>
      </tr>
      <tr>
         <td>IVD_INIT_DEC_HEIGHT_NOT_SUPPPORTED       </td>
         <td>Height requested at init not supported</td>
      </tr>
      <tr>
         <td>IVD_INIT_DEC_MEM_NOT_ALIGNED             </td>
         <td>Memory not aligned</td>
      </tr>
      <tr>
         <td>IVD_INIT_DEC_COL_FMT_NOT_SUPPORTED       </td>
         <td>Color format not supported</td>
      </tr>
      <tr>
         <td>IVD_INIT_DEC_MEM_REC_NOT_SUFFICIENT      </td>
         <td>Numberof memory record not sufficient</td>
      </tr>
      <tr>
         <td>IVD_GET_VERSION_DATABUFFER_SZ_INSUFFICIENT</td>
         <td>Numberof bytes in buffer not sufficient for version info</td>
      </tr>
      <tr>
         <td>IVD_BUFFER_SIZE_SET_TO_ZERO              </td>
         <td>Buffersize is set to 0</td>
      </tr>
      <tr>
         <td>IVD_UNEXPECTED_END_OF_STREAM             </td>
         <td>Unexpected end of stream</td>
      </tr>
      <tr>
         <td>IVD_SEQUENCE_HEADER_NOT_DECODED          </td>
         <td>Header not Decoded</td>
      </tr>
      <tr>
         <td>IVD_STREAM_WIDTH_HEIGHT_NOT_SUPPORTED    </td>
         <td>Stream Width and height not supported</td>
      </tr>
      <tr>
         <td>IVD_MAX_FRAME_LIMIT_REACHED              </td>
         <td>Maximum Frame limit reached</td>
      </tr>
      <tr>
         <td>IVD_IP_API_STRUCT_SIZE_INCORRECT         </td>
         <td>Input API structure size is incorrect</td>
      </tr>
      <tr>
         <td>IVD_OP_API_STRUCT_SIZE_INCORRECT         </td>
         <td>Output API structure size is incorrect</td>
      </tr>
      <tr>
         <td>IVD_HANDLE_NULL                          </td>
         <td>Null Codec Handle passed to codec</td>
      </tr>
      <tr>
         <td>IVD_HANDLE_STRUCT_SIZE_INCORRECT         </td>
         <td>Handle structure size is incorrect</td>
      </tr>
      <tr>
         <td>IVD_INVALID_HANDLE_NULL                  </td>
         <td>Invalid Handle</td>
      </tr>
      <tr>
         <td>IVD_INVALID_API_CMD                      </td>
         <td>Invalid API command</td>
      </tr>
      <tr>
         <td>IVD_UNSUPPORTED_API_CMD                  </td>
         <td>Unsupported API command</td>
      </tr>
      <tr>
         <td>IVD_MEM_REC_STRUCT_SIZE_INCORRECT        </td>
         <td>memory record structure size incorrect</td>
      </tr>
      <tr>
         <td>IVD_DISP_FRM_ZERO_OP_BUFS                </td>
         <td>Display frame zero output buffers</td>
      </tr>
      <tr>
         <td>IVD_DISP_FRM_OP_BUF_NULL                 </td>
         <td>Display frame output buffer is Null</td>
      </tr>
      <tr>
         <td>IVD_DISP_FRM_ZERO_OP_BUF_SIZE            </td>
         <td>Display frame output buffer size is zero</td>
      </tr>
      <tr>
         <td>IVD_DEC_FRM_BS_BUF_NULL                  </td>
         <td>Bitstream Buffer is Null</td>
      </tr>
      <tr>
         <td>IVD_SET_CONFG_INVALID_DEC_MODE           </td>
         <td>Invalid decoder mode in set config</td>
      </tr>
      <tr>
         <td>IVD_SET_CONFG_UNSUPPORTED_DISP_WIDTH     </td>
         <td>Unsupported width in set config</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_RESET_FAILED                         </td>
         <td>Reset failed</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_INIT_DEC_MEM_REC_OVERLAP_ERR         </td>
         <td>Memory records overlap</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_INIT_DEC_MEM_REC_BASE_NULL           </td>
         <td>Memory records base is Null</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_INIT_DEC_MEM_REC_ALIGNMENT_ERR       </td>
         <td>Memory records alignment error</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_INIT_DEC_MEM_REC_INSUFFICIENT_SIZE   </td>
         <td>Insufficient Memory records size</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_INIT_DEC_MEM_REC_INCORRECT_TYPE      </td>
         <td>Incorrect Memory records type</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_DEC_NUMBYTES_INV                     </td>
         <td>Invalid numbytes provided to decoder</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_DEC_REF_BUF_NULL                     </td>
         <td>Decoder reference buffer null</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_DEC_FRM_SKIPPED                      </td>
         <td>Frame skipped by decoder</td>
      </tr>
      <tr>
         <td> </td>
         <td>IVD_DUMMY_ELEMENT_FOR_CODEC_EXTENSIONS   </td>
         <td>Dummy element for codec extension</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Codec Error Code</p>

<table>
   <thead>
      <tr>
         <th colspan="3">Codec Error Code</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">Decoder updates e_Error_code bits as per the enumeration values corresponding to the error. Bits 0 to 7 from LSB side are kept free for codec specific error codes.      </td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum {<br>    IVD_APPLIEDCONCEALMENT                      = 0x8,<br>    IVD_INSUFFICIENTDATA                        = 0x9,<br>    IVD_CORRUPTEDDATA                           = 0xa,<br>    IVD_CORRUPTEDHEADER                         = 0xb,<br>    IVD_UNSUPPORTEDINPUT                        = 0xc,<br>    IVD_UNSUPPORTEDPARAM                        = 0xd,<br>    IVD_FATALERROR                              = 0xe,<br>    IVD_INVALID_BITSTREAM                       = 0xf,<br>    IVD_INCOMPLETE_BITSTREAM                    = 0x10,<br>    IVD_ERROR_BITS_T_DUMMY_ELEMENT              = 0x7FFFFFFF<br>} IVD_ERROR_BITS_T;</td>
      </tr>
      <tr>
         <td rowspan="9">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IVD_APPLIEDCONCEALMENT</td>
         <td>This bit is set if errorconcealment is applied</td>
      </tr>
      <tr>
         <td>IVD_INSUFFICIENTDATA</td>
         <td>This bit is set if decoder finds insufficient data in input buffer</td>
      </tr>
      <tr>
         <td>IVD_CORRUPTEDDATA</td>
         <td>This bit is set if decoder encounters corrupt data in bitstream</td>
      </tr>
      <tr>
         <td>IVD_CORRUPTEDHEADER</td>
         <td>This bit is set if the decoder encounters an error in the header.</td>
      </tr>
      <tr>
         <td>IVD_UNSUPPORTEDINPUT</td>
         <td>This bit is set if decoder finds any unsupported toolset in bitstream</td>
      </tr>
      <tr>
         <td>IVD_UNSUPPORTEDPARAM</td>
         <td>This bit is set if applicationtries to set any parameter and decoder does not support it.</td>
      </tr>
      <tr>
         <td>IVD_FATALERROR</td>
         <td>This bit is set if decoder encounters a fatal error.</td>
      </tr>
      <tr>
         <td>IVD_INCOMPLETE_BITSTREAM</td>
         <td>This bit is set if the bitstream given to the decoder is incomplete.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Codec error code</p>

<H1><b>Appendix A	Codec specific Notes</b></H1>
<H3><b>H264 Decoder</b></H3>
<H3><b>API Entry Point Function</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">H264 Decoder API Entry Point Function</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Name  </td>
         <td colspan="2">ih264d_api_function() </td>
      </tr>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This is an API function of the H264 decoder for the application, and is the only entry point to the h264 decoder library.</td>
      </tr>
      <tr>
         <td>Prototype</td>
         <td colspan="2">IV_API_CALL_STATUS_T ih264d_api_function(iv_obj_t *dec_hdl, void *pv_api_ip, void *pv_api_op)</td>
      </tr>
      <tr>
         <td rowspan="4">Argument details</td>
         <td>Argument</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>iv_obj_t *dec_hdl</td>
         <td>Pointer to the codec instance called as decoder handle.</td>
      </tr>
      <tr>
         <td>void *pv_api_ip</td>
         <td>Pointer to the APIs input structure type-casted as void pointer.</td>
      </tr>
      <tr>
         <td>void *pv_api_op</td>
         <td>Pointer to the APIs output structure type-casted as void pointer.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: H264 Decoder API Entry Point Function</p>

<H3><b>Extended Parameters</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">Fill Memory Records API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This extension gives the user flexibility of memory allocation if the nature of the video to be decoded is known by varying the number of reorder and reference frames.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct {<br>    iv_fill_mem_rec_ip_t            s_ivd_fill_mem_rec_ip_t;<br>    WORD32                        i4_level;<br>    UWORD32                         u4_num_reorder_frames;<br>    UWORD32                         u4_num_ref_frames;<br>    UWORD32                         u4_share_disp_buf;<br>    IV_COLOR_FORMAT_T                       e_output_format;<br>    UWORD32                             u4_num_extra_disp_buf;<br>} ih264d_fill_mem_rec_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="8">Input Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>s_ivd_fill_mem_rec_ip_t</td>
         <td>Refer iv_fill_mem_rec_ip_t</td>
      </tr>
      <tr>
         <td>i4_level</td>
         <td>This parameter defines the level of the video to be decoded.</td>
      </tr>
      <tr>
         <td>u4_num_reorder_frames</td>
         <td>This parameter should contain the maximum number of frames that are required to accomplish the reordering of the video, if any</td>
      </tr>
      <tr>
         <td>u4_num_ref_frames</td>
         <td>This parameter should contain the maximum number of frames that need to be stored in the reference frame buffers</td>
      </tr>
      <tr>
         <td>u4_share_disp_buf</td>
         <td>This should be set to 1 to enable shared display buffer mode.</td>
      </tr>
      <tr>
         <td>e_output_format</td>
         <td>The parameter gives the output color format required by the application. It is same as e_output_format in ivd_init_ip_t.</td>
      </tr>
      <tr>
         <td>u4_num_extra_disp_buf</td>
         <td>Number of extra display buffers that will be allocated to handle display pipeline depth</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Extended Fill Memory Records API</p>

<table>
   <thead>
      <tr>
         <th colspan="3">Initialize decoder API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This serves the same purpose as the extension of the Fill Memory Records extension. It has to been sured that the values level, reorder frames and reference frames values have to be the same for both Fill Memory Records and Initialize Decoder API.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2">typedef struct {<br>    ivd_init_ip_t                      s_ivd_init_ip_t;<br>    WORD32                             i4_level;<br>    UWORD32                            u4_num_reorder_frames;<br>    UWORD32                            u4_num_ref_frames;<br>    UWORD32                            u4_share_disp_buf;<br>    UWORD32                            u4_num_extra_disp_buf;<br>} ih264d_init_ip_t;</td>
      </tr>
      <tr>
         <td rowspan="6">Input Structure Details</td>
         <td>API Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>s_ivd_init_ip_t</td>
         <td>Refer ivd_init_ip_t</td>
      </tr>
      <tr>
         <td>i4_level</td>
         <td>This parameter defines the level of the video to be decoded.</td>
      </tr>
      <tr>
         <td>u4_num_reorder_frames</td>
         <td>This parameter should contain the maximum number of frames that are required to accomplish the reordering of the video, if any</td>
      </tr>
      <tr>
         <td>u4_num_ref_frames</td>
         <td>This parameter should contain the maximum number of frames that need to be stored in the reference frame buffers</td>
      </tr>
      <tr>
         <td>u4_share_disp_buf</td>
         <td>This should be set to 1 to enable shared display buffer mode. This is should be equal to u4_share_disp_buf in ih264d_fill_mem_rec_ip_t.</td>
      </tr>
      <tr>
         <td> </td>
         <td>u4_num_extra_disp_buf</td>
         <td>Number of extra display buffers that will be allocated to handle display pipeline depth</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Extended Initialize decoder API</p>

<H3><b>Extended Control call</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">IH264D_CMD_CTL_SUB_CMDS</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">Codec specific Control calls.</td>
      </tr>
      <tr>
         <td>Enumeration definition</td>
         <td colspan="2">typedef enum {<br>IH264D_CMD_CTL_SET_NUM_CORES = IVD_CMD_CTL_CODEC_SUBCMD_START,<br>IH264D_CMD_CTL_SET_PROCESSOR = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x001,<br>IH264D_CMD_CTL_GET_BUFFER_DIMENSIONS = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x100,<br>IH264D_CMD_CTL_GET_VUI_PARAMS = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x101,<br>IH264D_CMD_CTL_GPU_ENABLE_DISABLE = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x200,<br>IH264D_CMD_CTL_DEGRADE = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x300,<br>IH264D_CMD_CTL_GET_SEI_MDCV_PARAMS = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x301,<br>IH264D_CMD_CTL_GET_SEI_CLLI_PARAMS = IVD_CMD_CTL_CODEC_SUBCMD_START + 0x302}  IH264D_CMD_CTL_SUB_CMDS;<br> </td>
      </tr>
      <tr>
         <td rowspan="4">Enumeration Details</td>
         <td>Member</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>IH264D_CMD_CTL_SET_NUM_CORES<br> </td>
         <td>This sub command is used to set number of processor cores to be used by the decoder.</td>
      </tr>
      <tr>
         <td>IH264D_CMD_CTL_SET_PROCESSOR<br> </td>
         <td>This sub command is used to set the target processor architecture to be used by the decoder.</td>
      </tr>
      <tr>
         <td>IH264D_CMD_CTL_GET_BUFFER_DIMENSIONS</td>
         <td>This sub command is used to get output frame dimensions.</td>
      </tr>
      <tr>
         <td>IH264D_CMD_CTL_GET_VUI_PARAMS</td>
         <td>This sub command is used to get the VUI parameters.</td>
      </tr>
      <tr>
         <td>IH264D_CMD_CTL_GET_SEI_MDCV_PARAMS</td>
         <td>This sub command is used to get the SEI MDCV parameters.</td>
      </tr>
      <tr>
         <td>IH264D_CMD_CTL_GET_SEI_CLLI_PARAMS</td>
         <td>This sub command is used to get the SEI CLLI parameters.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: IH264D_CMD_CTL_SUB_CMDS</p>

<table>
   <thead>
      <tr>
         <th colspan="3">Set num cores API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This API is used to set the number of Processor cores that the decoder can use.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2"> <br>typedef struct {<br>    UWORD32                                     u4_size;<br>    IVD_API_COMMAND_TYPE_T                      e_cmd;<br>    IVD_CONTROL_API_COMMAND_TYPE_T              e_sub_cmd;<br>    UWORD32                                     u4_num_cores;<br>} ih264d_ctl_set_num_cores_ip_t;<br> </td>
      </tr>
      <tr>
         <td rowspan="5">Input Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This parameter defines the functionality to be performed by decoder API. For control calls, it should be IVD_CMD_VIDEO_CTL</td>
      </tr>
      <tr>
         <td>e_sub_cmd</td>
         <td>This tells the functionality to be performed by the Video control API. To set the number of processor cores that the decoder should use, this should be set to value of IH264D_CMD_CTL_SET_NUM_CORES</td>
      </tr>
      <tr>
         <td>u4_num_cores</td>
         <td>This parameter is used to inform the decoder about number of cores to be used.</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Set num cores API</p>

<table>
   <thead>
      <tr>
         <th colspan="3">Set num cores API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This API is used to set the number of Processor cores that the decoder can use.</td>
      </tr>
      <tr>
         <td>Output Structure</td>
         <td colspan="2"> <br>typedef struct {<br>    UWORD32                                     u4_size;<br>    UWORD32                                     u4_error_code;<br>} ih264d_ctl_set_num_cores_op_t;<br> </td>
      </tr>
      <tr>
         <td rowspan="3">Input Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>u4_error_code</td>
         <td>Error code returned by decoder library if any</td>
      </tr>
   </tbody>
</table>

<table>
   <thead>
      <tr>
         <th colspan="3">Get frame dimensions API</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This API is used to get output frame dimensions such as x and y offsets, display width and height, buffer width and height. This is useful when the decoder is used in shared mode where decode buffer and display dimensions are different because of padding and cropping. In non-shared mode offsets will be zero and display dimensions will be same as buffer dimensions.</td>
      </tr>
      <tr>
         <td>Input Structure</td>
         <td colspan="2"> <br>typedef struct {<br>    UWORD32                                     u4_size;<br>    IVD_API_COMMAND_TYPE_T                      e_cmd;<br>    IVD_CONTROL_API_COMMAND_TYPE_T              e_sub_cmd;<br>} ih264d_ctl_get_frame_dimensions_ip_t;<br> </td>
      </tr>
      <tr>
         <td rowspan="4">Input Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>e_cmd</td>
         <td>This parameter defines the functionality to be performed by decoder API. For control calls, it should be IVD_CMD_VIDEO_CTL</td>
      </tr>
      <tr>
         <td>e_sub_cmd</td>
         <td>This tells the functionality to be performed by the Video control API. To set the number of processor cores that the decoder should use, this should be set to value of IH264D_CMD_CTL_GET_BUFFER_DIMENSIONS</td>
      </tr>
      <tr>
         <td> <br>Output Structure</td>
         <td colspan="2"> <br>typedef struct {<br>    UWORD32                                     u4_size;<br>    UWORD32                                     u4_error_code;<br>    UWORD32                                     u4_x_offset[3];<br>    UWORD32                                     u4_y_offset[3];<br>    UWORD32                                     u4_disp_wd[3];<br>    UWORD32                                     u4_disp_ht[3];<br>    UWORD32                                     u4_buffer_wd[3];<br>    UWORD32                                     u4_buffer_ht[3];<br>} ih264d_ctl_get_frame_dimensions_op_t;</td>
      </tr>
      <tr>
         <td rowspan="9">Input Structure Details</td>
         <td>Parameter</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>u4_size</td>
         <td>Size of the structure. Useful in extending the structure with new fields.</td>
      </tr>
      <tr>
         <td>u4_error_code</td>
         <td>Error code returned by decoder library if any</td>
      </tr>
      <tr>
         <td>u4_x_offset[3]</td>
         <td>X offset for each of the components. This includes padding required by the codec and as well as frame cropping as per the standard.</td>
      </tr>
      <tr>
         <td>u4_y_offset[3]</td>
         <td>Y offset for each of the components. This includes padding required by the codec and as well as frame cropping as per the standard.</td>
      </tr>
      <tr>
         <td>u4_disp_wd[3]</td>
         <td>Display width for each of the components</td>
      </tr>
      <tr>
         <td>u4_disp_ht[3]</td>
         <td>Display height for each of the components</td>
      </tr>
      <tr>
         <td>u4_disp_wd[3]</td>
         <td>Buffer width for each of the components.</td>
      </tr>
      <tr>
         <td>u4_disp_ht[3]</td>
         <td>Buffer height for each of the components</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: Get frame dimensions API</p>

<H3><b>Codec Specific Error Codes</b></H3>

<table>
   <thead>
      <tr>
         <th colspan="3">H264 Decoder Error/status codes    </th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Purpose</td>
         <td colspan="2">This Enumeration defines the Error/Status codes specific to H264 Decoder. Bits 0 to 7 from LSB side are used here to report the codec specific error codes</td>
      </tr>
      <tr>
         <td>Error Code</td>
         <td>Error Name</td>
         <td>Description</td>
      </tr>
      <tr>
         <td>   <br>0   </td>
         <td>IH264_SUCCESS</td>
         <td>No error </td>
      </tr>
      <tr>
         <td>   <br>0x89   </td>
         <td>ERROR_ACTUAL_RESOLUTION_GREATER_THAN_INIT</td>
         <td>Resolution greater than init time resolution</td>
      </tr>
      <tr>
         <td>   <br>0x8A   </td>
         <td>ERROR_PROFILE_NOT_SUPPORTED</td>
         <td>Unsupported profile</td>
      </tr>
      <tr>
         <td>   <br>0x7FFFFFFF   </td>
         <td>IH264_FAIL</td>
         <td>Generic failure</td>
      </tr>
   </tbody>
</table>

<p align="center">Table: H264 Decoder Error/status codes</p>
