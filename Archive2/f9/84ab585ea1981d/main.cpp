template<typename T> class get_false { public:
    static constexpr bool val = false; 
};

template<typename T>
class MyClass_2 {
  static_assert(get_false<T>::val, "Failure");
};

template<typename T, typename U = MyClass_2<T>>
class MyClass {};

int main() {
    MyClass<bool> obj;
}