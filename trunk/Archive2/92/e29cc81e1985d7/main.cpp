#include <iostream>
#include <string>
#include <vector>

template<typename T>
class DrawStage
{
public:
    struct Setup { int x; };

    virtual void Render(Setup& setup) = 0;
};

template<typename T>
class DrawStageThing : public DrawStage<T>
{
public:
    void Render(Setup& setup) {
        std::cout << setup.x << std::endl;
    }
};

int main()
{
    DrawStageThing<int>::Setup setup;
    
    DrawStageThing<int> thing;
    thing.Render(setup);
    return 0;
}
