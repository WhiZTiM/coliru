struct A {
    int propose();
};

struct A1 : A {
    int propose(int);
    using A::propose;
};

struct B1 : A1 {
protected:
    using A1::propose;
public:
    using A::propose;
};

int main() {
    B1().propose();
}