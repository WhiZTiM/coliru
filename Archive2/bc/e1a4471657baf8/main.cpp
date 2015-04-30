#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

struct Callbacks
{
    std::function<void()> exitCallback;
    std::function<void()> backCallback;
    std::function<bool(int)> clickCellCallback;
};

void onExit() { std::cout << "onExit" << std::endl; }
void onBack() { std::cout << "onBack" << std::endl; }
bool onClickCell(int index) { std::cout << "onClickCell(" << index << ")" << std::endl; return true; }

int main()
{
    Callbacks cbs = {&onExit, &onBack, &onClickCell};
    cbs.clickCellCallback(3);
}
