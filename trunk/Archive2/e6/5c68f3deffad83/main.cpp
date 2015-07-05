using G = auto (*)(int)->int;

void f(G) {}
int g(int) { return 42; }

int main() { f(g); }