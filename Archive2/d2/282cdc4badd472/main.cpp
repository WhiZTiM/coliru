namespace CORBA {
    class Any {};
}
class AnyTest {};

namespace PortableGroup {                    
    class Holder {};
}
class HolderTest {};

void operator<<= (CORBA::Any&, PortableGroup::Holder*);

template<typename Any, typename Ptr>
class TEST { 
public:   
    TEST () {
           Any any;
           any <<= this->x_;
    }
private:
    Ptr x_;
};                                                                                                 

void operator<<= (CORBA::Any&, HolderTest*);
void operator<<= (AnyTest&, PortableGroup::Holder*);

void test (PortableGroup::Holder * excep_holder) {
    TEST<AnyTest, PortableGroup::Holder*>  test1; 
    TEST<CORBA::Any, HolderTest*>  test2;
    TEST<CORBA::Any, PortableGroup::Holder*>  test3;  
}