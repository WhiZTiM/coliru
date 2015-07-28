#include <iostream>
#include <random>
int main()
{
  const int minimum = 0;
  const int maximum = 1;
  std::uniform_int_distribution<int> distribution(minimum, maximum);
  // entiers répartis au hasard de manière uniforme
  std::default_random_engine generateur;
  const auto tirages = 10; // nb de tirages
  for (auto i = 0; i < tirages; ++i) {
    int nombre = distribution(generateur);
    std::cout << nombre << std::endl;
  }
  return 0;
}