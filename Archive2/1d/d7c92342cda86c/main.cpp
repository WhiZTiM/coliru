#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <tuple>

enum class Action { Exit = 0, Back, ClickCell };

void onExit() { std::cout << "onExit" << std::endl; }
void onBack() { std::cout << "onBack" << std::endl; }
bool onClickCell(int index) { std::cout << "onClickCell(" << index << ")" << std::endl; return true; }

template<typename... Args>
void onAction(Action action, Args&&... args) //The result_type here is an issue, but I guess it could be solved. It does not work anyway.
{
    switch(action)
    {
        case Action::Exit:
            onExit(std::forward<Args>(args)...);
            break;
        case Action::Back:
            onBack(std::forward<Args>(args)...);
            break;
        case Action::ClickCell:
            onClickCell(std::forward<Args>(args)...);
            break;
    }
}

int main() {
    //onAction(Action::ClickCell, 3);
}
