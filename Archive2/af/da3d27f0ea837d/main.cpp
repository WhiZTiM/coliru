#include <random>
#include <iostream>

int main() {
    using namespace std;

    random_device device; // Dispositivo do sistema para gerar seeds.
    mt19937 rng(device()); // Gerador Mersenne Twister inicializado com uma seed.
    uniform_int_distribution<int> random(1, 10); // Gera números randômicos de 1 à 10 via Mersenne Twister.
    cout << random(rng) << endl; // Gera um número.
    cout << random(rng) << endl; // Gera outro número.
}