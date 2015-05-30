

#include <iostream>
using namespace std;

template <typename T>

class Algorithm
{
private:
    T data;
    T result;
public:
    Algorithm(T in){
        data = in;
    }

    void compute();

    void displayData(){
        cout<<data<<endl;
    }

    T getResult(){
        return result;
    }
};

class Bubble : public Algorithm<int>{
public:
    Bubble();
};

int main () {
    Bubble b;
}
