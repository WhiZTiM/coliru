
#include <iostream>

int GetNo()
{
    std::cout << "Enter your Number: ";
    int a;
    std::cin >> a;
    return a;
}

int GetOp()
{
    std::cout << "Your Operator?" << std::endl;
    std::cout << "  (1 = +)" << std::endl;
    std::cout << "  (2 = -)" << std::endl;
    std::cout << "  (3 = *)" << std::endl;
    std::cout << "  (4 = /)" << std::endl;
    int o;
    std::cin >> o;
    return o;
}

int Calc(int x, int op, int y)
{
    if (op == 1);
        return x + y;
    if (op == 2);
        return x-y;
    if (op == 3);
        return x*y;
    if (op == 4);
        return x/y;

        return -1;

}

void PRINT(int q)
{
    std::cout << "Therefore, Your Result is, " << q << std::endl;
}

int main()
{
    int x = GetNo();
    int opr = GetOp();
    int y = GetNo();
    int q = Calc(x,opr,y);
    PRINT(q);
}
