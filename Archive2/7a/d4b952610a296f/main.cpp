#include <iostream>
#include <string>
#include <vector>

int counter = 0;

class Segment {

private:
    std::vector<int> ratios;
    float amplitude;
    float frequency;

public:

    bool isSpawned;
    void init() {}

    Segment(){
        init();
    };

    ~Segment(){
        //Some logging statements here for debugging.
        std::cout << "Destructor: " << counter++ << std::endl;
    }
};

int main()
{
    Segment *segment = new Segment();
    delete segment; // Malloc reports error at this line when i set breakpoint.
    
    return 0;
}