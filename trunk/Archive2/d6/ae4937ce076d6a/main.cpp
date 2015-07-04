bool Init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
    success = false;
  } else {
    gWindow = SDL_CreateWindow("HI",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               800,
                               600,
                               SDL_WINDOW_OPENGL);
    if (gWindow == nullptr) {
      std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
      success = false;
    } else {
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
      if (gRenderer == nullptr) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
      } else {
        //Init PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          std::cout << "SDL_Image could not be initalized! SDL_image Error: " << IMG_GetError() << std::endl;
          success = false;
        }
      }
    }
  }

  return success;
}
