struct T{};
using TR = T&;

int main(){
    T t;
    TR tr = t;
    tr.~TR();
}