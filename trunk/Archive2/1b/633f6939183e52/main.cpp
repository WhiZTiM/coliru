struct A {static int const i = 3;};
int const A::i;
int main() {&A::i;}