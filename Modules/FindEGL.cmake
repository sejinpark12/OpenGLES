#
# Created by Daemyung Jang on 2021/08/29.
#

if(TARGET EGL)
    return()
endif()

add_library(EGL SHARED IMPORTED)

find_path(EGL_INCLUDE_DIR "EGL/EGL.h"
    PATHS "${PROJECT_SOURCE_DIR}/SDK/include")

find_library(EGL_LIBRARY "EGL"
    PATHS "${PROJECT_SOURCE_DIR}/SDK/lib/${CMAKE_SYSTEM_NAME}")

set_target_properties(EGL PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${EGL_INCLUDE_DIR}"
    IMPORTED_LOCATION "${EGL_LIBRARY}")
