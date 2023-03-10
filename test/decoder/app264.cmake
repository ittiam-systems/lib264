lib264_add_executable(lib264dec lib264_library SOURCES ${LIB264_ROOT}/test/decoder/main.c)
target_compile_definitions(lib264dec PRIVATE PROFILE_ENABLE MD5_DISABLE)
