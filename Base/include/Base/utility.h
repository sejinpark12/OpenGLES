//
// Created by Daemyung Jang on 2021/09/12.
//

#ifndef UTILITY_H
#define UTILITY_H

#include <spdlog/spdlog.h>
#include <EGL/egl.h>

#define STRING(x) #x

#ifndef NDEBUG
#define EGL_TEST(function) do { \
    if (!function) { \
        EGLint error = eglGetError(); \
        if (error != EGL_SUCCESS) { \
            spdlog::error("{} with 0x{:x}.", STRING(function), error); \
            throw std::runtime_error("Err to call EGL function."); \
        } \
    } \
} while(false)
#else
#define EGL_TEST(function) \
    function
#endif

#endif //UTILITY_H
