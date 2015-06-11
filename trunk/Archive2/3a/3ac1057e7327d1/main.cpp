#include <vector>

template<int iCount, int... neurons>
class network {
private:
public:
    network() {
        addLayer<iCount, neurons...>();
    }
    template<int prev, int nc, int... further>
    void addLayer() {
        addLayer<nc, further...>();
    }
};

int main()
{
    network<1, 3, 5, 7> n;
}
