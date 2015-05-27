#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <string>

struct MyVariant {
  enum { t_invalid, t_string, t_int, t_double, t_ptr, t_dictionary } type_id;
  union {
    int                             as_int;
    double                          as_double;
    std::string                     as_string;
    std::unique_ptr<int>            as_ptr;
    std::map<int, double>           as_dictionary;
  };
  
    MyVariant() : type_id{t_int}, as_int{0} {}
    ~MyVariant()
    {
      switch(type_id)
      {
          case t_int:
          case t_double:
            // trivially destructible, no need to do anything
            break;
          case t_string:
            as_string.~basic_string();
            break;
          case t_ptr:
            as_ptr.~unique_ptr<int>();
            break;
          case t_dictionary:
            as_dictionary.~map<int, double>();
            break;
          case t_invalid:
            // do nothing
            break;
          default:
            throw std::runtime_error("unknown type");
      }
    }
  
  MyVariant(const MyVariant& other)
  {
    type_id = other.type_id;
    switch (type_id) {
        case t_invalid:
            break;
        case t_string:
            new (&as_string) std::string(other.as_string);
            break;
        case t_int:
            as_int = other.as_int;
            break;
        case t_double:
            as_double = other.as_double;
            break;
        case t_ptr:
            new (&as_ptr) std::unique_ptr<int>(std::make_unique<int>(*other.as_ptr));
            break;
        case t_dictionary:
            new (&as_dictionary) std::map<int, double>(other.as_dictionary);
            break;
    }
  }
};

int main()
{
    MyVariant v;
}
