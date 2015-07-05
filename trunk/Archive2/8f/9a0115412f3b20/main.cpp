void f(auto (*X)(int) -> int) {}
int g(int) { return 42; }

int main() { f(g); }