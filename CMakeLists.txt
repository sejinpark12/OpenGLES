#
# Created by Daemyung Jang on 2021/08/29.
#

cmake_minimum_required(VERSION 3.18)
project(OpenGLES LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/Modules)

add_subdirectory(Base)
add_subdirectory(Test)
add_subdirectory(04.InitializeAndTerminateEGL)
add_subdirectory(05.ChooseEGLConfig)
add_subdirectory(06.CreateAndDestroyEGLContext)
add_subdirectory(07.CreateAndDestroyEGLSurface)
add_subdirectory(08.MakeCurrentEGL)
add_subdirectory(10.CreateAndDestroyShader)
