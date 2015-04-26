#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;
void outputSort(int integers[],int numElements);
void quickSort(int arr[], int left, int right,string type)
{

      int i = left, j = right;

      int tmp;
      int pivot;
      if (type == "firstPivot")
      {
          pivot = arr[left];
      }
      else if (type == "randomPivot")
      {
    	  pivot = arr[right-1];
      }
      else //middle
      {
    	  pivot = arr[(left + right) / 2];
      }
      /* partition */

      while (i <= j) {

            while (arr[i] < pivot)

                  i++;

            while (arr[j] > pivot)

                  j--;

            if (i <= j) {

                  tmp = arr[i];

                  arr[i] = arr[j];

                  arr[j] = tmp;

                  i++;

                  j--;

            }

      };



      /* recursion */

      if (left < j)

            quickSort(arr, left, j,type);

      if (i < right)

            quickSort(arr, i, right,type);

}

int main()
{
    int N = 50000;
    int integers5[N];
	int index = 0;
	while(index < N)
	{
		integers5[index] = rand()%10000000000+1;
		index++;
	}

	quickSort(integers5,0,N-1,"firstPivot");
    int start = clock();
    start = clock();
	quickSort(integers5,0,N-1,"firstPivot");
	int end = clock();
	double timeFP = (double) (end-start) / CLOCKS_PER_SEC ;
		cout << timeFP;
}
