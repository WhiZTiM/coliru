#include <iostream>
#include <string>
#include <vector>

namespace sdl {
    using window = std::unique_ptr<SDL_Window, SDL_DestroyWindow>;
    using renderer = std::unique_ptr<SDL_Renderer, SDL_DestroyRenderer>;
    
    window make_window(std::string title, int w, int h) {
        auto ptr = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINODW_OPENGL);
        if (!ptr) {
            throw std::runtime_error(SDL_GetError());
        }
        return window(ptr);
    }
    
    renderer make_renderer(const window& wnd) {
        auto ptr = SDL_CreateRenderer(*wnd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
        if (!ptr) {
            throw std::runtime_error(SDL_GetError());
        }
        return renderer(ptr);
    }
    
    void init() {
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            throw std::runtime_error(IMG_GetError());
        }

        if (TTF_Init() < 0) {
            throw std::runtime_error(TTF_GetError());
        }

        int mixerFlags = MIX_INIT_MP3 | MIX_INIT_OGG;
        if ((Mix_Init(mixerFlags) & mixerFlags) != mixerFlags) {
            throw std::runtime_error(Mix_GetError());
        }
    }
}

int main() {
    sdl::init();
    auto window = sdl::make_window("whatever", 1280, 720);
    auto renderer = sdl::make_renderer(window);
}