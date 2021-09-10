//
// Created by Daemyung Jang on 2021/09/08.
//

#include <spdlog/spdlog.h>
#include <EGL/egl.h>
#include <Base/Window.h>

struct App {
    EGLDisplay display{EGL_NO_DISPLAY};
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    App app{};
    Window window{{.title = "EGL 초기화 및 종료", .size = {1280, 720}}};

    window.run([&app, &window] {
                   app.display = eglGetDisplay(Window::native_display(window));
                   if (app.display == EGL_NO_DISPLAY) {
                       spdlog::warn("윈도우로부터 EGLDisplay를 얻을 수 없습니다.");
                       app.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
                   }
                   if (app.display == EGL_NO_DISPLAY) {
                       spdlog::error("기본 디스플레이로부터 EGLDisplay를 얻을 수 없습니다.");
                       std::terminate();
                   }

                   EGLint majorVersion = 0;
                   EGLint minorVersion = 0;
                   if (!eglInitialize(app.display, &majorVersion, &minorVersion)) {
                       spdlog::error("EGL의 초기화를 실패하였습니다.");
                       std::terminate();
                   }

                   spdlog::info("현재 EGL의 버전은 {}.{} 입니다.", majorVersion, minorVersion);

                   if (!eglBindAPI(EGL_OPENGL_ES_API)) {
                       spdlog::error("OpenGL ES를 EGL의 렌더링 API로 설정할 수 없습니다.");
                       std::terminate();
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