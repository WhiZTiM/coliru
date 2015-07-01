template<typename> void type_is();

template<typename T>
void func(T&& univ) {
    // ??
    type_is<T>();
    type_is<decltype((univ))>();
}

int sum(int a, int b) {
 return a+b;   
}

int main() {

    func(sum);

}