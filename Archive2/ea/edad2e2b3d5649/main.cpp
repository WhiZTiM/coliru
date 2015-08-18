#include <iostream>

using namespace std;

template <size_t N>
typename enable_if<(N > 1), void>::type f(){
    cout << N - 1 << ' ';
    f<N - 1>();
}
template <size_t N>
typename enable_if<N == 1, void> ::type f() {
    cout << 1;
}
int main() {
    f<4>();
}