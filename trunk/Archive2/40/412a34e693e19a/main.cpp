#include <iostream>
#include <string>

using namespace std;

void findMax()
{
    int arr[5] = {1, 7, -1, 5, 3};
    
    int maxValue = arr[0]; // start with first element
    // loop from 2nd element (i.e. index 1)
    for (int index = 1; index < 5; ++index)
    {
        // is the value in array at this index greater than saved value
        if (arr[index] > maxValue) 
        {
            // yes, we got a new max
            maxValue = arr[index]; // overwrite existing max
        }
        else
        {
            // nothing to do here, as our maxValue remains same
        }
        
    }
    cout << "The Max value in the array is " << maxValue << endl;
}


void findSecondMax()
{
    int arr[7] = {11, 7, -1, 5, 3, 10, -2};
    
    int firstMax = 0;
    int secondMax = 0;
    
    if (arr[0] > arr[1])
    {
        firstMax = arr[0];
        secondMax = arr[1];
    }
    else
    {
        firstMax = arr[1];
        secondMax = arr[0];        
    }
    
    // loop from 3rd element (i.e. index 1)
    for (int index = 2; index < 7; ++index)
    {
        // is the value in array at this index greater than first Max Value
        if (arr[index] > firstMax) 
        {
            
            // yes, we got a new max
            // lets transfer the existing firstMax to second Max
            secondMax = firstMax;
            // Now overwrite firstMax with this new array value
            firstMax = arr[index]; 
            
        }
        else
        {
            // we reach here is the current array index value is less than firstMax
            // but is it less than second Max too ? we need to check that
            if (arr[index] > secondMax)
            {
                // so, current array value is less than firstMax, but greater than secondMax,
                // this means we go a new secondMax, lets overwrite secondMax
                secondMax = arr[index];
            }
            else
            {
                // current array value is also less than second max, so we dont have to 
                // do anything here, just skip
            }
        }
        
    }
    cout << "The firstMax  value in the array is = " << firstMax << endl;
    cout << "The secondMax value in the array is = " << secondMax << endl;        
    
}


int main ()
{
    
   cout << "\n--- Finding Max --- " << endl;
    
   findMax();  
  
   cout << "\n\n--- Finding First Max And Second Max--- " << endl;  
   findSecondMax();

  return 0;
}
