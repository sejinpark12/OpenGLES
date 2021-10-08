//
// Created by Daemyung Jang on 2021/10/05.
//

#include <vector>
#include <spdlog/spdlog.h>
#include <glm/gtx/string_cast.hpp>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <Base/Window.h>
#include <Base/utility.h>

struct App {
    EGLDisplay display{EGL_NO_DISPLAY};
    EGLConfig config{nullptr};
    EGLContext context{EGL_NO_CONTEXT};
    EGLSurface surface{EGL_NO_SURFACE};
    GLuint buffer_size{0};
    GLuint buffer{0};
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

inline std::string to_string(const Vertex &vertex) {
    return fmt::format("position: {:.1f}, {:.1f}, {:.1f} | color: {:.1f}, {:.1f}, {:.1f}",
                       vertex.position.x, vertex.position.y, vertex.position.z,
                       vertex.color.x, vertex.color.y, vertex.color.z);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    App app{};
    Window window{{.title = "Buffer 배우기", .size = {1280, 720}}};

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
                   app.buffer_size = byte_size(vertices);
                   GL_TEST(glBufferData(GL_ARRAY_BUFFER, app.buffer_size, vertices.data(), GL_DYNAMIC_DRAW));

                   GL_TEST(glBindBuffer(GL_ARRAY_BUFFER, 0));
               },
               [] {},
               [&app] {
                   GL_TEST(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
                   GL_TEST(glClear(GL_COLOR_BUFFER_BIT));

                   GL_TEST(glBindBuffer(GL_ARRAY_BUFFER, app.buffer));
                   void *contents = glMapBufferRange(GL_ARRAY_BUFFER, 0, app.buffer_size, GL_MAP_READ_BIT);
                   if (contents) {
                       auto *vertex = static_cast<Vertex *>(contents);
                       const uint32_t vertex_count = app.buffer_size / sizeof(Vertex);
                       for (auto i = 0; i != vertex_count; ++i, vertex += 1) {
                           spdlog::info("Vertex[{}]: {}", i, to_string(*vertex));
                           vertex->position += 0.1f;
                           vertex->color -= 0.1f;
                       }
                   }

                   GL_TEST(glUnmapBuffer(GL_ARRAY_BUFFER));
                   GL_TEST(glBindBuffer(GL_ARRAY_BUFFER, 0));

                   EGL_TEST(eglSwapBuffers(app.display, app.surface));
               },
               [&app] {
                   GL_TEST(glDeleteBuffers(1, &app.buffer));
                   app.buffer = 0;

                   shutdown(app);
               });

    return 0;
}

