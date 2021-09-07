//
// Created by Daemyung Jang on 2021/09/04.
//

#include "Base/Window.h"

#include <spdlog/spdlog.h>
#include <SDL_syswm.h>
#include <EGL/egl.h>
#include <AppKit/AppKit.h>

int32_t Window::native_display(const Window &window) {
    return EGL_DEFAULT_DISPLAY;
}

void *Window::native_window(const Window &window) {
    SDL_SysWMinfo sys_wm_info;
    SDL_VERSION(&sys_wm_info.version)

    if (!SDL_GetWindowWMInfo(window.window_, &sys_wm_info)) {
        spdlog::error("{}", SDL_GetError());
        throw std::runtime_error("Fail to get a native window from Window.");
    }

    NSView* view = [sys_wm_info.info.cocoa.window contentView];
    if (![view wantsLayer]) {
        [view setWantsLayer:YES];
    }

    return (__bridge void *)[view layer];
}
