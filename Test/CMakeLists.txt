#
# Created by Daemyung Jang on 2021/09/01.
#

add_executable(Test
    src/utility_test.cpp
    src/window_test.cpp)

target_include_directories(Test
    PRIVATE src)

find_package(Catch2 CONFIG REQUIRED)

target_link_libraries(Test
    PRIVATE Base
            Catch2::Catch2WithMain)
