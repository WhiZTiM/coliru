class test {
    template<typename T>
    bool Is(int index)  {return false;}
};

template<> bool test::Is<int>   (int index) {return false;}
template<> bool test::Is<float> (int index) {return false;}
template<> bool test::Is<double>(int index) {return false;}

namespace ns_test {
    template <typename T>
    bool Is(int index) {return false;}
    
    template<> bool Is<int> (int index) {return false;}
}

namespace ns_test2 {
    
    class test{
        template<typename T>
        bool Is(int index) {return false;}
    };
    
    template<> bool test::Is<int> (int index) {return false;}    
}

namespace {
}

int main() {
    return 0;
}