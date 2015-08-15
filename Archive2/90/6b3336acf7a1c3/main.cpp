#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

bool isPrime(int x){
    int square_root = sqrt(x);
    bool isPrime = true;
    if( x>3 ){
        for (int i=2; i<=x; i++)
        {
            if (x%i == 0) isPrime = false;
        }
    } 
    else isPrime = true;
    return isPrime;
}

vector<int>* find_primes(int a, int b){
    vector<int> *vec;
    for (int i = a; i<=b; i++){
        if(isPrime(i) == true) vec->push_back(i);
    }
    return vec;
}

int main() {
    //reading input (see task description)
    int how_many;
    cin >> how_many;
    int tab[how_many][2];
    for (int i=0; i<how_many; i++){
        cin>>tab[i][0];
        cin>>tab[i][1];
    }

    //find primes
    vector<int>*  v_tab[how_many];
    for (int i=0; i<how_many; i++){
//        v_tab[i] = find_primes(tab[i][0], tab[i][0]);
        for(int j=0; j<v_tab[i]->size(); j++){
            // ERROR IN THE LINE BELOW
            cout<<v_tab->at(i)->at(j)<<endl;    
        }   
        cout<<endl;
    }
    return 0;
}