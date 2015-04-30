#include <list>
#include <future>

struct listPart
{
    std::list<int> data;
    std::promise<std::list<int>> p;
};
template<typename T>
class dummy_container{
T t_;
public:
    void push_back(const T& t){
        t_ = t;       
    }
    void move_back(const T& t){
        t_ = t;    
    }
    void move_back(T&& t){
        t_ = std::move(t);    
    }
};

int main() {
    dummy_container<listPart> dc;
    listPart lp;
    //dc.push_back(std::move(lp)); // won't compile, function only handles const references
    dc.move_back(std::move(lp)); // will compile, because it moves if possible
}