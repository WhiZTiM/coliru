struct Base {
    Base (int =0, int =1) {}
};
struct Derived : Base {
    Derived(int) {}
    using Base::Base;
};
int main()
{
    Derived d(1);
}