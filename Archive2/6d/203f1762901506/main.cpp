struct X{};
struct Y{};
struct Z{};

void foo(X data){}
void foo(Y data){}
// void foo(Z data){}

template<typename T>
void bar(T data){
    foo(data);
}

int main(){
    foo(X{});
    foo(Y{});
    foo(Z{});
}
