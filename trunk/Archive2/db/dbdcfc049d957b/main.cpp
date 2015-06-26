struct S {
    static int i;
    static const int c;
};

int S::i = 5;
const int S::c = i;

int main() {}