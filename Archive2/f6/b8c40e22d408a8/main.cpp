#include <iostream>

using namespace std;

int main()
{
    int nn;
    int numeri[nn];
    int i, numerominore=0;

    cout<<"inserisci il numero di numeri da analizzare"<<endl;
    cin>>nn;
    for(i=0;i<nn; i++){

        cout<<"inserisci il "<<i+1<< " numero"<<endl;
        cin>>numeri[i];
        cout<<numeri[i]*2<<endl;
    }

    cout << "Hello world!" << endl;
    return 0;
}
