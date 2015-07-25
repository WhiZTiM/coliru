#include <iostream>
class c{
    public:
    int y;
     c(int x,int p):y(x){
    std::cout<<"has been made"<<std::endl;  
    }


};



template<int x,typename B = void>
struct checkeven{

};


template<typename B>
struct checkeven<0,B>{
    typedef B type;
};



template<int x,int y,class = typename checkeven<x%2,int>::type>
struct t{
    static const c tee;

    static const inline c& initor(){

    return tee;
    }
};


template<int x, int y>
struct t<x,y, typename checkeven<x%2,int>::type> 
{
    static const c tee;

    static const inline c& initor(){

        return tee;
    }
};

template<int x, int y>
const c t<x, y>::tee(x, y);


/*
template<int x,int y>
const c t::tee;       //how do i initialize?
*/

int main(int argc, char** argv) {

 //t<2,1>::initor();    
//t<2,2>::initor(); 

    return 0;
}