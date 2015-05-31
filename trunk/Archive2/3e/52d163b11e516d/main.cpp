#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <memory>

int main()
{
        struct ABCDEF {
            int a;
            double b;
            int* c;
            std::vector<int> e;
            std::shared_ptr<float> f;
        };

        ABCDEF x{
            0,{},nullptr,{ 1,2,3,4 },{}
        };

        ABCDEF y;
        y.a = 0;
        y.c = nullptr;
        y.e = {1,2,3,4};
        
    return 0;
}
