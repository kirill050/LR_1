# Copyright (c) 2015-2018, Ruslan Baratov
# All rights reserved.

if(DEFINED POLLY_VS_15_2017_WIN64_STORE_10_CXX17_CMAKE_)
  return()
else()
  set(POLLY_VS_15_2017_WIN64_STORE_10_CXX17_CMAKE_ 1)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/utilities/polly_init.cmake")

set(CMAKE_SYSTEM_NAME WindowsStore)
set(CMAKE_SYSTEM_VERSION 10.0)

polly_init(
    "Visual Studio 15 2017 Win64 / ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION} / C++17"
    "Visual Studio 15 2017 Win64"
)

include("${CMAKE_CURRENT_LIST_DIR}/utilities/polly_common.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/flags/vs-cxx17.cmake")
