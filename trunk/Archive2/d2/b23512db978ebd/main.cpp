#include <iostream>

template<int...>
struct sum;

template<int N, int... Args>
struct sum<N, Args...> {
    static const int value = N;
};

template<int N, int M, int... Args>
struct sum<N, M, Args...> {
    static const int value = sum<N + M, Args...>::value;
};

int main() {
    // O compilador resolve toda essa porra antes de compilar.
    // Então, todo aquele código acima, mais essa linha aqui,
    // tudo isso vira apenas o número 14. Aí sim a parada compila.
    int v = sum<2, 4, 8>::value;
    
    std::cout << "OLHA SÓ A COISINHA QUE EU FIZ: " << v << std::endl;
    return 0;
}