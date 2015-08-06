#include <vector>
#include <iostream>

template <typename C>
void output(const C& c_)
{
    for ( auto& i : c_ )
    {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}

void swap(int *i, int *j)
{
    int temp = *j;
    *j = *i;
    *i = temp;
}

void myAlgo(std::vector<int>& a)
{
    int size = a.size();
    
    if ( size < 2 )
    {
        return;     // No need to process.   
    }
    
    int left = 0;
    int right = size - 1;
    
    // Mark the first 0 they meet
    int leftMarker = -1;
    int rightMarker = -1;
    
    while( left < right )
    {
        while (( a[left] <= 0 ) && (left < size - 1))
        {
            if( ( a[left] == 0 ) && ( leftMarker == -1 ) )    
                leftMarker = left;
                
            if( ( a[left] != 0 ) && ( leftMarker != -1 ) )
            {
                swap( &a[left], &a[leftMarker]);
                left = leftMarker;
                leftMarker = -1;
            }
            ++left;
        }
        
        while (( a[right] >= 0 ) && (right > 0))
        {
            if( ( a[right] == 0 ) && ( rightMarker == -1 ) )    
                rightMarker = right;
                
            if( ( a[right] != 0 ) && ( rightMarker != -1 ) )
            {
                swap( &a[right], &a[rightMarker]);
                right = rightMarker;
                rightMarker = -1;
            }
            right--;
        }
        
        if(left == right)
        {
            if( (a[left] < 0) && (leftMarker != 1) )
                swap( &a[left], &a[leftMarker]);
            if( (a[left] > 0) && (rightMarker != 1) )
                swap( &a[left], &a[rightMarker]);
        }
        else if(left < right)
        {
            swap( &a[left], &a[right]);
        }
    }
    
    
}

int main(int argc, char* argv[])
{
    std::vector<int> vec { 1, 0, -1, 1, -1, 0, 0 };
    std::cout << "Input: " << std::endl;
    output(vec);
    myAlgo(vec);
    std::cout << "Output: " << std::endl;
    output(vec);  
    return 0;
}

