#include <iostream>
#include <memory>
#include <vector>

using namespace std;

template<typename T>
class vecbuf : public streambuf{
private:
    shared_ptr<vector<T>> vec_;
public:
	vecbuf(shared_ptr<vector<T>>);
	streambuf* setbufdicksasdf(float a, float b, float c, float d) override;
};

int main() {
    vecbuf<char> v;
}
