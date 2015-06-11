#include <vector>
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstring>

using namespace std;

int countPrimes_vector(int n) {                  
    int res = 0; 
    vector<char>bitmap(n);
    memset(&bitmap[0], '1', bitmap.size() * sizeof( bitmap[0]));
    //vector<bool>bitmap(n, true); Using this one is even slower!!

    for (int i = 2; i<n; ++i){

        if(bitmap[i]=='1')++res;
        if(sqrt(n)>i)
        {
             for(int l = i*i; l < n; l += i) bitmap[l] = '0';
        }
    }

    return res;
}

int countPrimes_array(int n) {  

    int res = 0; 
    bool * bitmap = new bool[n];
    memset(bitmap, true, sizeof(bool) * n);
    for (int i = 2; i<n; ++i){

        if(bitmap[i])++res;
        if(sqrt(n)>i)
        {
             for(int j = i*i; j < n; j += i) bitmap[j] = false;
        }
    }
    delete []bitmap;
    return res;
}

int main()
{
  clock_t t;
  t = clock();
  int a;
  for(int i=0; i<10; ++i)a = countPrimes_vector(8000000); 
  t = clock() - t;
  cout<<"time for vector = "<<t<<endl;

  t = clock();
  int b;
  for(int i=0; i<10; ++i)b = countPrimes_array(8000000); 
  t = clock() - t;
  cout<<"time for array = "<<t<<endl;
}