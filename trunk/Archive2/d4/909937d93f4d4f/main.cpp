#include <iostream>
struct Rx
{
    bool* ptr;
    void SetPointer(bool *b) { ptr = b; }
};

int main()
{
    bool use_observations[100];
    Rx receiver_1, receiver_2, receiver_3;
    receiver_1.SetPointer(use_observations);
    receiver_2.SetPointer(use_observations);
    receiver_3.SetPointer(use_observations);
    
    std::cout << "No issues";
} // end of main()