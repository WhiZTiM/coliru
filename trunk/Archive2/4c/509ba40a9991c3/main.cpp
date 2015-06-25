struct Type {};

template <class T>
class OOPPolymorphic {
    friend T;
    void RegisterInheritence(const Type* base) {}
public:
    static const Type* GetType() {
        return nullptr;
    }
    virtual const Type* MyType() = 0;
};

class Base :public OOPPolymorphic<Base> {
public:
    virtual const Type* MyType() {
        return OOPPolymorphic<Base>::GetType();
    }
};

class Derived : public Base, public OOPPolymorphic<Derived> {
public:
    Derived() {
    OOPPolymorphic<Derived>::RegisterInheritence(Base::GetType());
    }
    virtual const Type* MyType() {
        return OOPPolymorphic<Derived>::GetType();
    }
};

int main(){
    Derived d1, d2 = d1;
}