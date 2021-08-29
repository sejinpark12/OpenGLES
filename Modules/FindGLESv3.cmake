#
# Created by Daemyung Jang on 2021/08/29.
#

if(TARGET GLESv3)
    return()
endif()

add_library(GLESv3 SHARED IMPORTED)

find_path(GL3_INCLUDE_DIR "GLES3/gl3.h"
    PATHS "${PROJECT_SOURCE_DIR}/SDK/include")

find_library(GLESv2_LIBRARY "GLESv2"
    PATHS "${PROJECT_SOURCE_DIR}/SDK/lib/${CMAKE_SYSTEM_NAME}")

set_target_properties(GLESv3 PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GL3_INCLUDE_DIR}"
    IMPORTED_LOCATION "${GLESv2_LIBRARY}")
