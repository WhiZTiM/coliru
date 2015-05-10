struct SDL_Surface { int x; };
using Image = SDL_Surface;

int something(Image* z){
  return z->x;
}

int main() {}