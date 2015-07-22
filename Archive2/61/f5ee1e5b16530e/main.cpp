#include <iostream>
#include <cstdlib>

int main()
{
    srand(time(NULL));
    for (int i = 0; i < 20; ++i) {
        float jitter_dx = -0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5f - (-0.5f))));
        float jitter_dy = -0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5f - (-0.5f))));
        std::cout << jitter_dx << " " << jitter_dy << "\n";
    }
}