//
// Created by Daemyung Jang on 2021/11/10
//

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

constexpr float pi = M_PI;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    glm::vec4 position(0.0f, 0.5f, 0.0f, 1.0f);
    spdlog::info("Local space: {}", glm::to_string(position));

    auto translate = glm::translate(glm::identity<glm::mat4>(), {1.0f, 0.0f, 0.0f});
    auto rotate = glm::rotate(glm::identity<glm::mat4>(), pi, {0.0f, 0.0f, 1.0f});
    auto scale = glm::scale(glm::identity<glm::mat4>(), {2.0f, 2.0f, 2.0f});
    auto model = translate * rotate * scale;
    position = model * position;
    spdlog::info("World space: {}", glm::to_string(position));

    auto view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f),
                            glm::vec3(0.0f, 0.0f, 0.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f));
    position = view * position;
    spdlog::info("View space: {}", glm::to_string(position));

    auto perspective = glm::perspective(90.0f, 1.0f, 0.001f, 100.0f);
    position = perspective * position;
    spdlog::info("Clip space: {}", glm::to_string(position));

    auto pvm = perspective * view * model;
    position = {0.0f, 0.5f, 0.0f, 1.0f};
    position = pvm * position;
    spdlog::info("Clip space: {}", glm::to_string(position));

    position /= position.w;
    spdlog::info("NDC: {}", glm::to_string(position));

    return 0;
}
