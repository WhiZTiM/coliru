struct Base {
    int var;
};

struct A : Base { };

//      Base
//      /|
//     / |
//    A  |  
//     \ |
//      \|
//       B

struct B : A, Base {
    void f() {
        Base::var = 1;  // Base is in here twice, directly and through A
                        // which one are you looking for?
    }
};

int main() {
}