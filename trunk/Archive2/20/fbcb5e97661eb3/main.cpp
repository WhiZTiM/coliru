#include <iostream>
#include <string>
#include <functional>

struct BaseControl { virtual std::string name() const = 0; };

struct ControlA1 : public BaseControl { virtual std::string name() const { return "ControlA1"; } };
struct ControlA2 : public BaseControl { virtual std::string name() const { return "ControlA2"; } };
struct ControlB1 : public BaseControl { virtual std::string name() const { return "ControlB1"; } };
struct ControlB2 : public BaseControl { virtual std::string name() const { return "ControlB2"; } };

enum Type { A = 0, B };
enum Mode { One = 0, Two };

// 그냥 함수만 분리..
namespace case1 {

BaseControl* create_control_a(Mode m)
{
    switch (m)
    {
        case One: return new ControlA1();
        case Two: return new ControlA2();
        default : return nullptr;
    }
}

BaseControl* create_control_b(Mode m)
{
    switch (m)
    {
        case One: return new ControlB1();
        case Two: return new ControlB2();
        default : return nullptr;
    }
}
 
BaseControl* create_control(Type t, Mode m)
{
    switch (t)
    {
        case A: return create_control_a(m);
        case B: return create_control_b(m);
        default: return nullptr;
    }
}

void main()
{
    std::cout << "= case1 ==========================" << std::endl;
    std::cout << create_control(A, One)->name() << std::endl;
    std::cout << create_control(A, Two)->name() << std::endl;
    std::cout << create_control(B, One)->name() << std::endl;
    std::cout << create_control(B, Two)->name() << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << std::endl;
}

}

/// map에 type별 팩토리 함수 저장
namespace case2 {

BaseControl* create_control(Type t, Mode m)
{
    static std::function<BaseControl*()> func_tbl[3][3];
    func_tbl[A][One] = [] { return new ControlA1(); };
    func_tbl[A][Two] = [] { return new ControlA2(); };
    func_tbl[B][One] = [] { return new ControlB1(); };
    func_tbl[B][Two] = [] { return new ControlB2(); };
    
    return func_tbl[t][m]();
}
  
void main() 
{
    std::cout << "= case2 ==========================" << std::endl;
    std::cout << create_control(A, One)->name() << std::endl;
    std::cout << create_control(A, Two)->name() << std::endl;
    std::cout << create_control(B, One)->name() << std::endl;
    std::cout << create_control(B, Two)->name() << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << std::endl;
}
    
}

int main()
{
    case1::main();
    case2::main();
}
