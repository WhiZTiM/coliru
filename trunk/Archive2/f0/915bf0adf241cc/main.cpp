class BaseSystem {
public:
  BaseSystem(const char* title, size_t w, size_t h, Uint32 flags) :
    window(new Window(title, w, h, flags)) {
      //Create the default renderer
      renderer = std::unique_ptr<Renderer>(new Renderer(window.get()->get()));

      //SDL_image subsystem init
      int imgFlags = IMG_INIT_PNG;
      if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "Image loading subsystem initialization error.\n";
        throw std::runtime_error(IMG_GetError());
      }

      //SDL_ttf subsystem init
      if (TTF_Init() < 0) {
        std::cerr << "TTF subsystem initialization error.\n";
        throw std::runtime_error(TTF_GetError());
      }

      //SDL_mixer subsystem init
      int mixerFlags = MIX_INIT_MP3 | MIX_INIT_OGG;
      if ((Mix_Init(mixerFlags) & mixerFlags) != mixerFlags) {
        std::cerr << "Audio mixer subsystem initialization error.\n";
        throw std::runtime_error(Mix_GetError());
      }
  }

  SDL_Window* get_window() const noexcept {
    return window.get()->get();
  }

  SDL_Renderer* get_renderer() const noexcept {
    return renderer.get()->get();
  }

private:
  std::unique_ptr<Window> window;
  std::unique_ptr<Renderer> renderer;
};
