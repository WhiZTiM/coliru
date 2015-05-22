#include <iostream> 
#include <memory>
#include <vector>

template<typename T>
class record{ 
public:
    record(T c_value){
        value = c_value;   
    }
  T value;
};


template<typename T>
class registry{
public:  
  registry(T c_data){
    data = std::make_shared<record<T> >(c_data);   
  }
  
  std::shared_ptr<record<T> > data;
  std::vector<std::shared_ptr<registry> > records;
};



/*template int hello(has_x);
template int hello(has_y);*/

int main()
{
   auto h1 = std::make_shared<registry<int> >(30);
   auto h2 = std::make_shared<registry<int> >(40);
   h1->records.push_back(h2);
   
   
   std::cout << h1->data->value << std::endl;
   std::cout << h1->records[0]->data->value << std::endl;
   
    
}