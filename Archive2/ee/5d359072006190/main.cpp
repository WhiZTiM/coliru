enum MyEnum{
A,B,C
};
struct MyClass
{
    MyEnum* my_enum;
};
int main()
{
    MyClass* m = new MyClass();
    *m->my_enum = MyEnum::A;
}