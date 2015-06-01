template <typename> struct X {
};

int main() {
    X<struct hello> a;
    X<struct world> b;  
}