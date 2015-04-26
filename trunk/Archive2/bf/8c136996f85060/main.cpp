namespace N { namespace A {int i;} }

struct A {static int i;};

using namespace N;

int i = A::i;

int main() {}