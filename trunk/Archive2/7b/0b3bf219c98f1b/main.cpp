#include <iostream>
#include <type_traits>

#define self static_cast<Self&>(*this) 

struct Struct{
    int data;
};



template<class Self = void>
struct Mix2{
    void wood(){
        std::cout <<"wood";
    }    
};

template<class Self>
struct Mix1{
    //static_assert(std::is_base_of<Mix2<Self>, Self>::value, "Mix1 requires Mix2");
    
    void check(){
        //std::cout << std::is_base_of<Mix2<Self>, Self>::value;
    }
    
    void fire(){
        std::cout <<"fire";
        self.wood();
        std::cout << self.data;
    }
};



template<int _i>
struct Resolve : h1::Mix2<Resolve<_i>>, Struct, Mix1<Resolve<_i>>
{
    int i = _i;
    void flow(){
        this->fire();
    }
};

int main(){

    Resolve<12> r;
    r.data = 100; 
    r.flow();
    
    r.check();
    
    Resolve<12> r2;
    r2.data = 455;
    r2.flow();
    
    /*Mix2<> mix;
    mix.wood();*/
  return 0;
}