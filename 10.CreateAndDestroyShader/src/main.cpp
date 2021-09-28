//
// Created by Daemyung Jang on 2021/09/23.
//

#include <vector>
#include <spdlog/spdlog.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <Base/utility.h>

struct App {
    EGLDisplay display{EGL_NO_DISPLAY};
    EGLConfig config{nullptr};
    EGLContext context{EGL_NO_CONTEXT};
    EGLSurface surface{EGL_NO_SURFACE};
    std::array<GLuint, 2> shaders{0, 0};
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    App app{};
    Window window{{.title = "Shader 생성 및 파괴", .size = {1280, 720}}};

    window.run([&app, &window] {
                   startup(app, window);

                   app.shaders[0] = create_shader(home() / "10.CreateAndDestroyShader/res/triangle.vert");
                   app.shaders[1] = create_shader(home() / "10.CreateAndDestroyShader/res/unlit.frag");
               },
               [] {},
               [&app, &window] {
                   GL_TEST(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
                   GL_TEST(glClear(GL_COLOR_BUFFER_BIT));

                   EGL_TEST(eglSwapBuffers(app.display, app.surface));
               },
               [&app] {
                   GL_TEST(glDeleteShader(app.shaders[0]));
                   app.shaders[0] = 0;
                   GL_TEST(glDeleteShader(app.shaders[1]));
                   app.shaders[1] = 0;

                   shutdown(app);
               });

    return 0;
}
