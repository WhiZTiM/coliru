class Base {
public:
    virtual void sayHi() const {}
    virtual void sayHello() {}
    virtual ~Base(){}
};

class Derived : public Base {
public:
    void sayHi()          override {}
    void sayHello() const override {}
};

int main(){}