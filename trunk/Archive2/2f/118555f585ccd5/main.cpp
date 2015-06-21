#include <iostream>
#include <vector>

using namespace std;

void bubbleSort(vector<int>& a);

void printVector(vector<int> a);

int main(int argc, char const *argv[])
{
 vector<int> a {3,2,6,1};

 printVector(a);

 bubbleSort(a);

 printVector(a);



}

void bubbleSort(vector<int>& a)
{
      bool swapp = true;
      while(swapp){
        swapp = false;
        for (size_t i = 0; i < a.size()-1; i++) {
            if (a[i]>a[i+1] ){
                a[i] += a[i+1];
                a[i+1] = a[i] - a[i+1];
                a[i] -=a[i+1];
                swapp = true;
            }
        }
    }
}

void printVector(vector<int> a){
    for (size_t i=0;  i <a.size();  i++) {
        cout<<a[i]<<" ";

    }
  cout<<endl;
}