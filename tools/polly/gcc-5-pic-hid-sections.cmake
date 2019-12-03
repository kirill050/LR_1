# Copyright (c) 2016-2018, Ruslan Baratov
# Copyright (c) 2018, David Hirvonen
# All rights reserved.

if(DEFINED POLLY_GCC_5_PIC_HID_SECTIONS_CMAKE_)
  return()
else()
  set(POLLY_GCC_5_PIC_HID_SECTIONS_CMAKE_ 1)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/utilities/polly_init.cmake")

polly_init(
    "gcc 5 / PIC / c++11 support / hidden / function-sections / data-sections"
    "Unix Makefiles"
)

include("${CMAKE_CURRENT_LIST_DIR}/utilities/polly_common.cmake")

include("${CMAKE_CURRENT_LIST_DIR}/compiler/gcc-5.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/flags/cxx11.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/flags/fpic.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/flags/function-sections.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/flags/data-sections.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/flags/hidden.cmake")
