//
// Created by Daemyung Jang on 2021/10/11.
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
    GLuint buffer{0};
    GLuint program{0};
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    App app{};
    Window window{{.title = "Attribute 설정", .size = {1280, 720}}};

    window.run([&app, &window] {
                   startup(app, window);

                   GL_TEST(glGenBuffers(1, &app.buffer));
                   GL_TEST(glBindBuffer(GL_ARRAY_BUFFER, app.buffer));

                   constexpr std::array<Vertex, 3> vertices = {
                           Vertex{{-0.5, -0.5f, 0.0f},
                                  {1.0f, 0.0f,  0.0f}},
                           Vertex{{0.5,  -0.5f, 0.0f},
                                  {0.0f, 1.0f,  0.0f}},
                           Vertex{{0.0,  0.5f, 0.0f},
                                  {0.0f, 0.0f, 1.0f}}
                   };
                   GL_TEST(glBufferData(GL_ARRAY_BUFFER, byte_size(vertices), vertices.data(), GL_STATIC_DRAW));

                   GL_TEST(glBindBuffer(GL_ARRAY_BUFFER, 0));

                   app.program = create_graphics_pipeline({home() / "14.SetAttribute/res/triangle.vert",
                                                           home() / "14.SetAttribute/res/unlit.frag"});
               },
               [] {},
               [&app, &window] {
                   GL_TEST(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
                   GL_TEST(glClear(GL_COLOR_BUFFER_BIT));

                   GL_TEST(glViewport(0, 0, window.size().x * window.dpi(), window.size().y * window.dpi()));

                   GL_TEST(glUseProgram(app.program));
                   GL_TEST(glBindBuffer(GL_ARRAY_BUFFER, app.buffer));

                   GL_TEST(glEnableVertexAttribArray(0));
                   GL_TEST(glEnableVertexAttribArray(1));
                   GL_TEST(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                                 GL_OFFSETOF(Vertex, position)));
                   GL_TEST(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                                 GL_OFFSETOF(Vertex, color)));
                   GL_TEST(glDrawArrays(GL_TRIANGLES, 0, 3));
                   GL_TEST(glDisableVertexAttribArray(1));
                   GL_TEST(glDisableVertexAttribArray(0));

                   GL_TEST(glUseProgram(0));
                   GL_TEST(glBindBuffer(GL_ARRAY_BUFFER, 0));

                   EGL_TEST(eglSwapBuffers(app.display, app.surface));
               },
               [&app] {
                   GL_TEST(glDeleteProgram(app.program));
                   app.program = 0;

                   GL_TEST(glDeleteBuffers(1, &app.buffer));
                   app.buffer = 0;

                   shutdown(app);
               });

    return 0;
}
