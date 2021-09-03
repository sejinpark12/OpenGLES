//
// Created by Daemyung Jang on 2021/09/01.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <glm/glm.hpp>
#include <SDL.h>

/// 윈도우 클래스.
class Window {
public:
    /// 서술자 구조체.
    struct Descriptor {
        std::string title;
        glm::ivec2 size;
    };

public:
    /// 생성자.
    /// \param descriptor 생성할 윈도우를 서술한 객체입니다.
    explicit Window(const Descriptor &descriptor);

    /// 소멸자.
    ~Window();

    /// 이벤트 루프를 실행합니다.
    /// \param startup 시작 이벤트때 호출되는 함수입니다.
    /// \param update 업데이트 이벤트때 호출되는 함수입니다.
    /// \param render 렌더 이벤트때 호출되는 함수입니다.
    /// \param shutdown 종료 이벤트때 호출되는 함수입니다.
    void run(const std::function<void()> &startup, const std::function<void()> &update,
             const std::function<void()> &render, const std::function<void()> &shutdown);

    /// 이벤트 루프를 종료합니다.
    void stop();

    /// 윈도우의 제목을 반환합니다.
    /// \return 현재 윈도우의 제목입니다.
    [[nodiscard]] std::string title() const;

    /// 윈도우 제목을 변경합니다.
    /// \param title 변경할 윈도우 제목입니다.
    void title(const std::string &title);

    /// 윈도우 크기를 반환합니다.
    /// \return 현재 윈도우의 크기입니다.
    [[nodiscard]] glm::ivec2 size() const;

    /// 윈도우 크기를 변경합니다.
    /// \param size 변경할 윈도우 크기입니다.
    void size(const glm::ivec2 &size);

    /// 네이티브 윈도우를 반환합니다.
    /// \return 네이티브 윈도우입니다.
    [[nodiscard]] void *native() const;

private:
    /// 이벤트를 처리합니다.
    /// \return 이벤트 루프를 유지하는 경우는 참, 종료하는 경우는 거짓을 반환합니다.
    [[nodiscard]] bool process_event() const;

private:
    SDL_Window *window_{nullptr};
};

#endif //WINDOW_H
