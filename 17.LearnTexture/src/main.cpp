//
// Created by Daemyung Jang on 2021/10/19.
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
    GLuint vertex_array{0};
    GLuint vertex_buffer{0};
    GLuint index_buffer{0};
    GLuint texture{0};
    GLuint program{0};
    GLint sampler_location{0};
};

struct Vertex {
    glm::vec3 position;
    glm::vec2 st;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    App app{};
    Window window{{.title = "Texture 배우기", .size = {1280, 720}}};

    window.run([&app, &window] {
                   startup(app, window);

                   GL_TEST(glGenBuffers(1, &app.vertex_buffer));
                   GL_TEST(glBindBuffer(GL_ARRAY_BUFFER, app.vertex_buffer));
                   constexpr std::array<Vertex, 4> vertices = {
                           Vertex{{-0.5, -0.5f, 0.0f},
                                  {0.0f, 0.0f}},
                           Vertex{{0.5,  -0.5f, 0.0f},
                                  {1.0f, 0.0f}},
                           Vertex{{0.5,  0.5f, 0.0f},
                                  {1.0f, 1.0f}},
                           Vertex{{-0.5, 0.5f, 0.0f},
                                  {0.0f, 1.0f}}
                   };
                   GL_TEST(glBufferData(GL_ARRAY_BUFFER, byte_size(vertices), vertices.data(), GL_STATIC_DRAW));
                   GL_TEST(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

                   GL_TEST(glGenBuffers(1, &app.index_buffer));
                   GL_TEST(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app.index_buffer));
                   constexpr std::array<uint16_t, 6> indices = {
                           0, 1, 3, 2, 3, 1
                   };
                   GL_TEST(glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_size(indices), indices.data(), GL_STATIC_DRAW));
                   GL_TEST(glBindBuffer(GL_ARRAY_BUFFER, 0));

                   GL_TEST(glGenVertexArrays(1, &app.vertex_array));
                   GL_TEST(glBindVertexArray(app.vertex_buffer));
                   GL_TEST(glBindBuffer(GL_ARRAY_BUFFER, app.vertex_buffer));
                   GL_TEST(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app.index_buffer));
                   GL_TEST(glEnableVertexAttribArray(0));
                   GL_TEST(glEnableVertexAttribArray(1));
                   GL_TEST(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                                 GL_OFFSETOF(Vertex, position)));
                   GL_TEST(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                                 GL_OFFSETOF(Vertex, st)));
                   GL_TEST(glBindVertexArray(0));

                   GL_TEST(glGenTextures(1, &app.texture));
                   GL_TEST(glBindTexture(GL_TEXTURE_2D, app.texture));
                   constexpr std::array<GLubyte, 2 * 2 * 3> pixels = {
                           255, 0, 0,
                           0, 255, 0,
                           0, 0, 255,
                           255, 255, 255,
                   };
                   GL_TEST(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
                   GL_TEST(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data()));
                   GL_TEST(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
                   GL_TEST(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

                   app.program = create_graphics_pipeline({home() / "17.LearnTexture/res/triangle.vert",
                                                           home() / "17.LearnTexture/res/unlit.frag"});

                   app.sampler_location = glGetUniformLocation(app.program, "sampler");
               },
               [] {},
               [&app, &window] {
                   GL_TEST(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
                   GL_TEST(glClear(GL_COLOR_BUFFER_BIT));

                   GL_TEST(glViewport(0, 0, window.size().x * window.dpi(), window.size().y * window.dpi()));

                   GL_TEST(glUseProgram(app.program));
                   GL_TEST(glBindVertexArray(app.vertex_array));

                   GL_TEST(glUniform1i(app.sampler_location, 0));
                   GL_TEST(glActiveTexture(GL_TEXTURE0));
                   GL_TEST(glBindTexture(GL_TEXTURE_2D, app.texture));

                   GL_TEST(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
                   GL_TEST(glBindVertexArray(0));
                   GL_TEST(glUseProgram(0));

                   EGL_TEST(eglSwapBuffers(app.display, app.surface));
               },
               [&app] {
                   GL_TEST(glDeleteProgram(app.program));
                   app.program = 0;

                   GL_TEST(glDeleteTextures(1, &app.texture));
                   app.texture = 0;

                   GL_TEST(glDeleteVertexArrays(1, &app.vertex_array));
                   app.vertex_array = 0;

                   GL_TEST(glDeleteBuffers(1, &app.vertex_buffer));
                   app.vertex_buffer = 0;

                   GL_TEST(glDeleteBuffers(1, &app.index_buffer));
                   app.index_buffer = 0;

                   shutdown(app);
               });

    return 0;
}
