#include <memory> 
#include <iostream> 
#include <unordered_map>
using namespace std;
 
void fun(std::shared_ptr<int>& sp)
{   
    shared_ptr<int> sp3 = sp;
    std::cout << "fun: sp.use_count() == " << sp.use_count() << '\n'; 
    unordered_map<int, shared_ptr<int>> mymap; 
    auto temp = make_pair(*sp,sp);
    std::cout << "fun: sp.use_count() == " << sp.use_count() << '\n'; 
    mymap.insert(temp);
    std::cout << "fun: sp.use_count() == " << sp.use_count() << '\n'; 
}
 
int main() 
{ 
        
    auto sp1 = std::make_shared<int>(5);
    std::cout << "sp1.use_count() == " << sp1.use_count() << '\n'; 
 
    fun(sp1);
    std::cout << "sp1.use_count() == " << sp1.use_count() << '\n'; 
}