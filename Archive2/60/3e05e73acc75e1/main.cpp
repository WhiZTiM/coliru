#include <iostream>

class Goomba
{
  bool alive;
public:
  static int liveGoombas;

  Goomba()
    : alive(true)
  { liveGoombas++; }

  Goomba(const Goomba& rhs)
    : alive(rhs.alive)
  {
    if (alive)
      liveGoombas++;
  }

  // Move constructor
  Goomba(Goomba&& rhs)
    : alive(std::move(rhs.alive))
  {
    if (alive)
      liveGoombas++;
    rhs.kill(); // modifies moved from object!
  }

  Goomba& operator =(const Goomba& rhs)
  {
    alive = rhs.alive;
    if (alive)
      liveGoombas++;
    return *this;
  }

  // Move assignment
  Goomba& operator =(Goomba&& rhs)
  {
    alive = std::move(rhs.alive);
    if (alive)
      liveGoombas++;
    rhs.kill(); // modifies moved from object!
    return *this;
  }

  ~Goomba() {
    kill();
  }

private:
  void kill() {
    if (alive) {
      liveGoombas--;
      alive = false;

      // insert other death/dying code here
    }
  }
};

int Goomba::liveGoombas = 0;

int main() {
    Goomba g;
    std::cout << Goomba::liveGoombas << std::endl;
    Goomba f(std::move(g)); // g dies
    std::cout << Goomba::liveGoombas << std::endl;
    Goomba copy_of_f(f);
    std::cout << Goomba::liveGoombas << std::endl;
    Goomba dead_goomba(g); // copy of a dead goomba
    std::cout << Goomba::liveGoombas << std::endl;
    return 0;
}