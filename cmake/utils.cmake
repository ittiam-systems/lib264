include(CheckCXXCompilerFlag)
set(CMAKE_C_STANDARD 90)

# Adds compiler options for all targets
function(lib264_add_compile_options)
  if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    add_library("${projName}CompileOptions" INTERFACE)
    target_compile_options(
      "${projName}CompileOptions"
      INTERFACE /INCREMENTAL:NO
                /Oi
                /GL
                /Os
                /MP
                /W4
                /WX)
  else()
    if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch64")
      add_compile_options(-march=armv8-a)
    elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch32")
      add_compile_options(-march=armv7-a -mfpu=neon)
    else()
      add_compile_options(-msse4.2 -mno-avx)
    endif()
    add_compile_options(-Wdeclaration-after-statement)
  endif()
endfunction()

# Adds defintions for all targets
function(lib264_add_definitions)
  if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    target_compile_definitions("${projName}CompileOptions" 
      INTERFACE WINDOWS _CRT_SECURE_NO_WARNINGS)
    add_definitions(-DWIN32 -DWINDOWS -D_WINDOWS -DWINDOWS_TIMER)
  else()
    if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch64")
      add_definitions(-DARMV8 -DDEFAULT_ARCH=D_ARCH_ARMV8_GENERIC)
    elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch32")
      add_definitions(-DARMV7 -DDEFAULT_ARCH=D_ARCH_ARM_A9Q)
    else()
      add_definitions(-DX86 -DX86_LINUX=1 -DDISABLE_AVX2
                      -DDEFAULT_ARCH=D_ARCH_X86_SSE42)
    endif()
  endif()
endfunction()


# cmake-format: off
# Adds a target for an executable
#
# Arguments:
# NAME: Name of the executatble
# LIB: Library that executable depends on
# SOURCES: Source files
#
# Optional Arguments:
# INCLUDES: Include paths
# LIBS: Additional libraries
# cmake-format: on

function(lib264_add_executable NAME LIB)
  set(multi_value_args SOURCES INCLUDES LIBS)
  cmake_parse_arguments(ARG "${optional_args}" "${single_value_args}"
                        "${multi_value_args}" ${ARGN})

  add_executable(${NAME} ${ARG_SOURCES})
  target_include_directories(${NAME} PRIVATE ${ARG_INCLUDES})
  add_dependencies(${NAME} ${LIB} ${ARG_LIBS})
  target_link_libraries(${NAME} ${LIB} ${ARG_LIBS})

endfunction()
