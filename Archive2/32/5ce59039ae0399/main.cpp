#include<string>
#include<memory>
#include<vector>

    struct Base {};
    
    template<typename T>
    struct Derived : public Base {};
    
    struct Derived2 {};


    template <typename T>
    std::vector<std::unique_ptr<T> > getData()
    {
          static_assert(std::is_base_of<Base, T>::value, "T must be derived from Base");
          
          std::vector<std::unique_ptr<Base> > retData; 
          std::vector<std::unique_ptr<T> > retCastData;
    
          for (auto& item : retData)
          {
              retCastData.emplace_back(static_cast<T*>(item.release()));
          }
    
          return retCastData;
    }
    
    int main()
    {
        getData<Derived<int> >();   //ok
        //getData<Derived2>();   //error
    }

