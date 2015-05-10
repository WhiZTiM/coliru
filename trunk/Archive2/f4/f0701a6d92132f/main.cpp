namespace detail {
    struct SDL_Surface { int x; };
}

using Image = detail::SDL_Surface;

int something(Image* z){
  return z->x;
}

int main() {}