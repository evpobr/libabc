cmake_minimum_required(VERSION 3.8)

project(ABC VERSION 4)

include(GNUInstallDirs)
include(CheckSymbolExists)
include(CheckFunctionExists)

check_symbol_exists(__GNU_LIBRARY__ "features.h" _GNU_SOURCE)

check_function_exists(secure_getenv HAVE_SECURE_GETENV)
check_function_exists(__secure_getenv HAVE___SECURE_GETENV)
if(NOT (HAVE_SECURE_GETENV OR HAVE___SECURE_GETENV))
    message(FATAL_ERROR "Neither secure_getenv nor __secure_getenv is available!")
endif()

add_library(ABC
    src/abc/libabc.h
    src/libabc-private.h
    src/libabc.c
)
target_compile_features(ABC PRIVATE c_std_11)
target_include_directories(ABC
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_definitions(ABC
    PRIVATE
        $<$<BOOL:${HAVE_SECURE_GETENV}>:HAVE_SECURE_GETENV>
        $<$<BOOL:${HAVE_SECURE___GETENV}>:HAVE_SECURE___GETENV>
        $<$<BOOL:${_GNU_SOURCE}>:_GNU_SOURCE>
)
