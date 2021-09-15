//
// Created by Daemyung Jang on 2021/09/08.
//

#include <vector>
#include <spdlog/spdlog.h>
#include <EGL/egl.h>
#include <Base/Window.h>
#include <Base/utility.h>

const std::vector<std::pair<EGLenum, std::string>> config_attribute_and_names = {
        {EGL_RED_SIZE,           "RED_SIZE"},
        {EGL_GREEN_SIZE,         "GREEN_SIZE"},
        {EGL_BLUE_SIZE,          "BLUE_SIZE"},
        {EGL_ALPHA_SIZE,         "ALPHA_SIZE"},
        {EGL_BUFFER_SIZE,        "BUFFER_SIZE"},
        {EGL_DEPTH_SIZE,         "DEPTH_SIZE"},
        {EGL_STENCIL_SIZE,       "STENCIL_SIZE"},
        {EGL_MAX_PBUFFER_WIDTH,  "MAX_PBUFFER_WIDTH"},
        {EGL_MAX_PBUFFER_HEIGHT, "MAX_PBUFFER_HEIGHT"},
        {EGL_MAX_PBUFFER_PIXELS, "MAX_PBUFFER_PIXELS"},
        {EGL_MAX_SWAP_INTERVAL,  "MAX_SWAP_INTERVAL"},
        {EGL_MIN_SWAP_INTERVAL,  "MIN_SWAP_INTERVAL"},
};

void print(EGLDisplay display, EGLConfig config) {
    spdlog::info("(EGLConfig){} 속성 출력 시작", config);
    for (auto[attribute, name]: config_attribute_and_names) {
        EGLint value;
        EGL_TEST(eglGetConfigAttrib(display, config, attribute, &value));
        spdlog::info("    {}는 {}입니다.", name, value);
    }
    spdlog::info("(EGLConfig){} 속성 출력 종료", config);
}

struct App {
    EGLDisplay display{EGL_NO_DISPLAY};
    EGLConfig config{nullptr};
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    App app{};
    Window window{{.title = "EGLConfig 선택", .size = {1280, 720}}};

    window.run([&app, &window] {
                   app.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
                   if (app.display == EGL_NO_DISPLAY) {
                       spdlog::error("기본 디스플레이로부터 EGLDisplay를 얻을 수 없습니다.");
                       std::terminate();
                   }

                   EGL_TEST(eglInitialize(app.display, nullptr, nullptr));
                   EGL_TEST(eglBindAPI(EGL_OPENGL_ES_API));

                   {
                       EGLint num_config;
                       EGL_TEST(eglGetConfigs(app.display, nullptr, 0, &num_config));

                       std::vector<EGLConfig> configs(num_config);
                       EGL_TEST(eglGetConfigs(app.display, configs.data(), configs.size(), &num_config));

                       for (EGLConfig config: configs) {
                           print(app.display, config);
                       }
                   }

                   {
                       EGLint config_attributes[] = {
                               EGL_RED_SIZE, 8,
                               EGL_GREEN_SIZE, 8,
                               EGL_BLUE_SIZE, 8,
                               EGL_ALPHA_SIZE, 8,
                               EGL_DEPTH_SIZE, 16,
                               EGL_STENCIL_SIZE, 8,
                               EGL_NONE
                       };
                       EGLint num_config;
                       EGL_TEST(eglChooseConfig(app.display, config_attributes, &app.config, 1, &num_config));

                       print(app.display, app.config);
                   }

                   window.stop();
               },
               [] {},
               [] {},
               [&app] {
                   if (!eglTerminate(app.display)) {
                       spdlog::error("EGL을 종료를 실패하였습니다.");
                       std::terminate();
                   }

                   app.display = EGL_NO_DISPLAY;
               });

    return 0;
}