class Base{
protected:
  int field;
};

class Derived : public Base{
public:
  Derived(int value) :
    Base::field(value)
  {}
};

int main(){
  Derived d(42);
}