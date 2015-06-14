#include<iostream>
#include<vector>
   
int main()
{ 
    int arr[] = {1, 2, 4, 7, 10};
    std::vector<int> vect;
    vect.assign(arr, arr + 5);
    for(std::vector<int>::iterator it = vect.begin(); it != vect.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    
    std::cout << "-------------------------------------" << std::endl;
    
    for(std::vector<int>::iterator it = vect.begin(); it != vect.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}