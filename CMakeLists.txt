cmake_minimum_required(VERSION 3.8)

project(ABC VERSION 4)

include(GNUInstallDirs)
include(CheckFunctionExists)

check_function_exists(secure_getenv HAVE_SECURE_GETENV)
check_function_exists(__secure_getenv HAVE___SECURE_GETENV)
if(NOT (HAVE_SECURE_GETENV OR HAVE___SECURE_GETENV))
    message(FATAL_ERROR "Neither secure_getenv nor __secure_getenv is available!")
endif()

configure_file(config.h.cmake config.h)

add_library(ABC
    src/abc/libabc.h
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
    src/libabc-private.h
    src/libabc.c
)
target_compile_features(ABC PRIVATE c_std_11)
target_include_directories(ABC
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_definitions(ABC
    PRIVATE
        HAVE_CONFIG_H
)
