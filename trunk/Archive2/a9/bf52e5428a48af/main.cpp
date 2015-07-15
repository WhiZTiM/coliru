#include <vector>  //vector
#include <memory>  //smart pointers
#include <utility> //pair
#include <string>  //string
#include <iostream>//cout

template <class T>
class Container {
public:
    inline void push(const std::string& s, const T& t) {
        objects.push_back(std::pair<std::string, std::shared_ptr<T>>(s, std::make_shared<T>(t)));   
    }

    inline T& operator [](const size_t& i)
    {
        return *(objects[i]->second);
    }
    inline T& operator [](const std::string& s)
    {
        for (auto it : objects) {
            if(s == it.first) { 
                return *(it.second);
            }
        }
    
        //welp, what do you do here if you can't find it?
    }
private:
    std::vector<std::pair<std::string, std::shared_ptr<T>>> objects;
};

int main() {
    Container<int> cont;
    std::string str {"hi"};
    int i {2};
    
    cont.push(str, i);
    
    //This is good...
    std::cout << cont["hi"] << std::endl;
    
    //But undefined behavior!
    std::cout << cont["02"] << std::endl;
    return 0;
}