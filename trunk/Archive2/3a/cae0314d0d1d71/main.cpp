#include <iostream>

class Object
{
  public:
  Object()
  {
    std::cout << "Default Constructor" << std::endl;
  }

  Object( const Object& other )
  {
    std::cout << "Copy Constructor" << std::endl;
  }

  Object( Object&& other )
  {
    std::cout << "Move Constructor" << std::endl;
  }

  Object& operator=( const Object& other )
  {
    std::cout << "Copy Operator" << std::endl;
    return *this;
  }

  Object& operator=( Object&& other )
  {
    std::cout << "Move Operator" << std::endl;
    return *this;
  }

  void modify()
  {
    std::cout << "Modify Object" << std::endl;
  }
};


template<class Object>
inline Object modify( Object obj )
{
  //obj.modify();
  return obj;
}


// should return new object based on original
/*Object modify( Object obj ) // cost of one copy constructor
{
  obj.modify();
  return obj;               // move constructor
}*/

/*
Object modify( const Object& obj )
{
  Object obj_new( obj ); // cost of one copy constructor
  obj_new.modify();
  return obj_new;       // cost of one move constructor
}
*/

int main()
{

  //Object obj;
  Object obj2 { modify( Object() ) }; // cost of 1 copy constructor


  //Object obj3 = modify( obj );


  return 0;
}
