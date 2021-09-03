//
// Created by Daemyung Jang on 2021/09/02.
//

#include <array>
#include <catch2/catch.hpp>
#include <Base/Window.h>

TEST_CASE("윈도우 생성 및 변경 테스트", "[Window]") {
    Window window{{.title = "hello", .size = {1280, 720}}};

    REQUIRE(window.title() == "hello");
    REQUIRE(window.size() == glm::ivec2{1280, 720});
    REQUIRE(window.native() != nullptr);

    SECTION("제목 변경") {
        window.title("world");

        REQUIRE(window.title() == "world");
    }

    SECTION("크게 변경") {
        window.size({720, 1280});

        REQUIRE(window.size() == glm::ivec2{720, 1280});
    }
}

TEST_CASE("윈도우 이벤트 루프 테스트", "[Window]") {
    std::array<bool, 4> is_function_called{false, false, false, false};
    Window window{{.size = {1280, 720}}};

    window.run([&is_function_called, &window] {
                   is_function_called[0] = true;
               },
               [&is_function_called, &window] {
                   is_function_called[1] = true;
                   window.stop();
               },
               [&is_function_called, &window] {
                   is_function_called[2] = true;
               },
               [&is_function_called, &window] {
                   is_function_called[3] = true;
               });

    REQUIRE(std::all_of(std::begin(is_function_called), std::end(is_function_called),
                        [](bool element) { return element; }));
}
