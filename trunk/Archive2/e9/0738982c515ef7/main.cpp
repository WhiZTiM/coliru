#include <iostream>

class ClassA
{
    public:
    void SetSomeProperty(const int& value) { prop = value;}
    int GetSomeProperty() { return prop; }
//
//    void SetAnotherProperty(const Vec3& value) { ... }
//    Vec3 GetAnotherProperty() { ... }
private:
    int prop = 0;
};

//class ClassB
//{
//    void SetColor(const Vec4& value) { ... }
//    Vec4 GetColor() { ... }
//}

template <typename TClass, typename TType>
class PropertyAccess
{
public:
    using SetterPointer = void (TClass::*)(const TType&);
    using GetterPointer = TType(TClass::*)();

    PropertyAccess(TClass* object, SetterPointer setter, GetterPointer getter)
        : m_object(object), m_setter(setter), m_getter(getter)
    {
    }

    void Set(const TType& value) {
        (m_object->*m_setter)(value);
    }

    TType Get() {
        return (m_object->*m_getter)();
    }

private:

    TClass* m_object;
    SetterPointer m_setter;
    GetterPointer m_getter;
};


int main() {
    ClassA a;
    PropertyAccess<ClassA, int> p(&a, &ClassA::SetSomeProperty, &ClassA::GetSomeProperty);
    p.Set(10);
    std::cout << p.Get() << std::endl;
}

