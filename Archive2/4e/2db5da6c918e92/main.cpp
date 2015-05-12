#include <iostream>
#include <type_traits>

template<int I> typename std::enable_if<I % 2 == 0, void>::type
/* void */ div() {
    // this overload is selected when I is even
    std::cout << "even" << std::endl;
}
template<int I> typename std::enable_if<I % 2 == 1, void>::type
/* void */ div() {
    // this overload is selected  when I is odd
    std::cout << "odd" << std::endl;
}

int main()
{
    div<1>(); // compilador ignora a versão do I%2==0 pq não deu pra instancia-la, então chama a do I%2==1
    div<2>(); // compilador ignora a versão do I%2==1 pq não deu pra instancia-la, então chama a do I%2==0
}