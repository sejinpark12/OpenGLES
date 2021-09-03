//
// Created by Daemyung Jang on 2021/09/01.
//

#include "Base/Window.h"

#include <stdexcept>
#include <SDL_syswm.h>

#if SDL_VIDEO_DRIVER_COCOA
#include <AppKit/AppKit.h>
#endif

Window::Window(const Descriptor &descriptor) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("Error: Fail to initialize SDL.");
    }

    window_ = SDL_CreateWindow(descriptor.title.c_str(),
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               descriptor.size.x,
                               descriptor.size.y,
                               0);

    if (!window_) {
        throw std::runtime_error("Error: Fail to create SDL window.");
    }
}

Window::~Window() {
    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }

    SDL_Quit();
}

void Window::run(const std::function<void()> &startup, const std::function<void()> &update,
                 const std::function<void()> &render, const std::function<void()> &shutdown) {
    startup();
    SDL_ShowWindow(window_);

    while (process_event()) {
        update();
        render();
    }

    SDL_HideWindow(window_);
    shutdown();
}

void Window::stop() {
    SDL_Event event{.window{.windowID = SDL_GetWindowID(window_), .event=SDL_WINDOWEVENT_CLOSE}};
    SDL_PushEvent(&event);
}

std::string Window::title() const {
    return SDL_GetWindowTitle(window_);
}

void Window::title(const std::string &title) {
    SDL_SetWindowTitle(window_, title.c_str());
}

glm::ivec2 Window::size() const {
    glm::ivec2 size;
    SDL_GetWindowSize(window_, &size.x, &size.y);
    return size;
}

void Window::size(const glm::ivec2 &size) {
    SDL_SetWindowSize(window_, size.x, size.y);
}

void *Window::native() const {
    SDL_SysWMinfo sys_wm_info;

    SDL_VERSION(&sys_wm_info.version)
    if (!SDL_GetWindowWMInfo(window_, &sys_wm_info)) {
        return nullptr;
    }

#if SDL_VIDEO_DRIVER_COCOA
    NSView* view = [sys_wm_info.info.cocoa.window contentView];
    if (![view wantsLayer]) {
        [view setWantsLayer:YES];
    }
    return (__bridge void *)[view layer];
#else
    return nullptr;
#endif
}

bool Window::process_event() const {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.window.windowID == SDL_GetWindowID(window_) && event.window.event == SDL_WINDOWEVENT_CLOSE) {
            return false;
        }
    }

    return true;
}