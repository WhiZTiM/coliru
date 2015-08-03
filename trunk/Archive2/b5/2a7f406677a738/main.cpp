#include <iostream>
using namespace std;

struct SM {
    int val;

    SM(int a) : val(a) {
        cout << "Constructor val=" << a << endl;
    }
    ~SM() {
        cout << "Destructor val=" << val << endl;
    }
private:
    SM& operator=(const SM&) = delete;
    SM& operator=(SM&&) = delete;
    SM(const SM&) = delete;
    SM(SM&&) = delete;
};

int main() {
    SM sc[8] = { { 0 }, { 1 }, { 2 }, { 3 }, { 4 }, { 5 }, { 6 }, { 7 } };
}
