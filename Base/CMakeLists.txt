#
# Created by Daemyung Jang on 2021/09/01.
#

add_library(Base
    include/Base/Window.h
    src/Window.cpp)

target_include_directories(Base
    PUBLIC include)

target_compile_features(Base
    PUBLIC cxx_std_17)

target_compile_options(Base
    PUBLIC $<$<PLATFORM_ID:Darwin>:-x objective-c++>
           $<$<PLATFORM_ID:Darwin>:-fobjc-arc>)

find_package(glm CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(EGL REQUIRED)
find_package(GLESv3 REQUIRED)

target_link_libraries(Base
    PUBLIC glm::glm
           SDL2::SDL2
           EGL
           GLESv3)
