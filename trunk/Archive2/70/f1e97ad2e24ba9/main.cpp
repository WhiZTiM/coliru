template<class T>
void f1(T=0) {};

int main() {
    auto f2 = [] (auto x=0) {};
    //f1();
    //f2();
    //[](auto x=0){}();
}