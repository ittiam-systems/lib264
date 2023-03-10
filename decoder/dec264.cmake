# src files
list(
  APPEND
  LIB264DEC_SRCS
  "${LIB264_ROOT}/decoder/ih264d_api.c"
  "${LIB264_ROOT}/decoder/ih264d_bitstrm.c"
  "${LIB264_ROOT}/decoder/ih264d_cabac.c"
  "${LIB264_ROOT}/decoder/ih264d_cabac_init_tables.c"
  "${LIB264_ROOT}/decoder/ih264d_compute_bs.c"
  "${LIB264_ROOT}/decoder/ih264d_deblocking.c"
  "${LIB264_ROOT}/decoder/ih264d_debug.c"
  "${LIB264_ROOT}/decoder/ih264d_dpb_mgr.c"
  "${LIB264_ROOT}/decoder/ih264d_format_conv.c"
  "${LIB264_ROOT}/decoder/ih264d_function_selector_generic.c"
  "${LIB264_ROOT}/decoder/ih264d_inter_pred.c"
  "${LIB264_ROOT}/decoder/ih264d_mb_utils.c"
  "${LIB264_ROOT}/decoder/ih264d_mvpred.c"
  "${LIB264_ROOT}/decoder/ih264d_nal.c"
  "${LIB264_ROOT}/decoder/ih264d_parse_bslice.c"
  "${LIB264_ROOT}/decoder/ih264d_parse_cabac.c"
  "${LIB264_ROOT}/decoder/ih264d_parse_cavlc.c"
  "${LIB264_ROOT}/decoder/ih264d_parse_headers.c"
  "${LIB264_ROOT}/decoder/ih264d_parse_islice.c"
  "${LIB264_ROOT}/decoder/ih264d_parse_mb_header.c"
  "${LIB264_ROOT}/decoder/ih264d_parse_pslice.c"
  "${LIB264_ROOT}/decoder/ih264d_parse_slice.c"
  "${LIB264_ROOT}/decoder/ih264d_process_bslice.c"
  "${LIB264_ROOT}/decoder/ih264d_process_intra_mb.c"
  "${LIB264_ROOT}/decoder/ih264d_process_pslice.c"
  "${LIB264_ROOT}/decoder/ih264d_quant_scaling.c"
  "${LIB264_ROOT}/decoder/ih264d_sei.c"
  "${LIB264_ROOT}/decoder/ih264d_tables.c"
  "${LIB264_ROOT}/decoder/ih264d_thread_compute_bs.c"
  "${LIB264_ROOT}/decoder/ih264d_thread_parse_decode.c"
  "${LIB264_ROOT}/decoder/ih264d_utils.c"
  "${LIB264_ROOT}/decoder/ih264d_vui.c")

include_directories(${LIB264_ROOT}/decoder)
include_directories(${LIB264_ROOT}/decoder/api)

if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "aarch64" OR "${CMAKE_SYSTEM_PROCESSOR}"
                                                     STREQUAL "aarch32")
  list(
    APPEND LIB264DEC_ASMS "${LIB264_ROOT}/decoder/arm/ih264d_function_selector.c"
    "${LIB264_ROOT}/decoder/arm/ih264d_function_selector_a9q.c"
    "${LIB264_ROOT}/decoder/arm/ih264d_function_selector_av8.c")
else()
  list(
    APPEND LIB264DEC_SRCS "${LIB264_ROOT}/decoder/x86/ih264d_function_selector.c"
    "${LIB264_ROOT}/decoder/x86/ih264d_function_selector_sse42.c"
    "${LIB264_ROOT}/decoder/x86/ih264d_function_selector_ssse3.c")
endif()

add_library(lib264_library STATIC ${LIB264_COMMON_SRCS} ${LIB264_COMMON_ASMS}
                             ${LIB264DEC_SRCS} ${LIB264DEC_ASMS})
target_link_libraries(
  lib264_library
  PRIVATE ithread)