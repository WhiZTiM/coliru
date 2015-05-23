#include <iostream>

using namespace std;

int main()
    {
    int valorConta;
    int N;
    cin >> N;
    if (N<=10) {
        valorConta=7;
        } else if (N<31 && N>10) {
            valorConta=7+(N-10);
            } else if (N>30 && N<101) {
                valorConta=7+20+((N-30)*2);
                } else if (N>=101) {
                    valorConta=7+20+140+((N-100)*5);
                    }
    cout << valorConta;

    return 0;
    }