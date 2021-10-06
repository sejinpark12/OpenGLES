//
// Created by Daemyung Jang on 2021/09/29.
//

#include <vector>
#include <spdlog/spdlog.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <Base/Window.h>
#include <Base/utility.h>

struct App {
    EGLDisplay display{EGL_NO_DISPLAY};
    EGLConfig config{nullptr};
    EGLContext context{EGL_NO_CONTEXT};
    EGLSurface surface{EGL_NO_SURFACE};
    GLuint program{0};
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    App app{};
    Window window{{.title = "Program 생성 및 파괴", .size = {1280, 720}}};

    window.run([&app, &window] {
                   startup(app, window);

                   app.program = create_graphics_pipeline({home() / "11.CreateAndDestroyProgram/res/triangle.vert",
                                                           home() / "11.CreateAndDestroyProgram/res/unlit.frag"});
               },
               [] {},
               [&app, &window] {
                   GL_TEST(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
                   GL_TEST(glClear(GL_COLOR_BUFFER_BIT));

                   GL_TEST(glViewport(0, 0, window.size().x * window.dpi(), window.size().y * window.dpi()));

                   GL_TEST(glUseProgram(app.program));
                   GL_TEST(glDrawArrays(GL_TRIANGLES, 0, 3));

                   EGL_TEST(eglSwapBuffers(app.display, app.surface));
               },
               [&app] {
                   GL_TEST(glDeleteProgram(app.program));
                   app.program = 0;

                   shutdown(app);
               });

    return 0;
}
