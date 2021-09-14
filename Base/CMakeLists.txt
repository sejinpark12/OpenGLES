#
# Created by Daemyung Jang on 2021/09/01.
#

add_library(Base
    include/Base/Window.h
    include/Base/utility.h
    src/Window.cpp)

target_include_directories(Base
    PUBLIC include)

target_compile_features(Base
    PUBLIC cxx_std_17)

find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(EGL REQUIRED)
find_package(GLESv3 REQUIRED)

target_link_libraries(Base
    PUBLIC spdlog::spdlog
           glm::glm
           SDL2::SDL2
           EGL
           GLESv3)

if(${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    target_sources(Base
        PRIVATE src/cocoa/Window.mm)

    target_compile_options(Base
        PRIVATE -fobjc-arc
                -x objective-c++)
endif()
