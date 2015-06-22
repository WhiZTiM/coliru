#include <random>
#include <iostream>

int GPIO_Read() {
    std::random_device rd;
    std::mt19937 gen(rd());
    return std::uniform_int_distribution<int>(0, 1)(gen);
}

class Buttons {
public:
    virtual void BigRedButton() = 0;
};

class ButtonsLeft : public Buttons {
public:
    void BigRedButton() override { std::cout << "Good Bye!" << std::endl; }
};

class ButtonsRight : public Buttons {
public:
    void BigRedButton() override { std::cout << "Run for your life!" << std::endl; }
};

ButtonsLeft     btnLeft;
ButtonsRight    btnRight;

Buttons&    GetButtons() {
    static Buttons& myButtons = GPIO_Read() ? static_cast<Buttons&>(btnLeft) : static_cast<Buttons&>(btnRight);
    return myButtons;
}

int main()
{
    GetButtons().BigRedButton();
}
