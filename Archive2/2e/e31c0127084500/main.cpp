#include<vector>
#include<utility>
#include<algorithm>
#include<iostream>

std::vector<std::pair<int,int> > find_pairs(std::vector<int>& arr1, std::vector<int>& arr2, int diff)
{
    std::vector<std::pair<int,int> > ret;
    
    std::sort(std::begin(arr1), std::end(arr1));
    std::sort(std::begin(arr2), std::end(arr2));

    auto it1= std::begin(arr1);
    auto it2= std::begin(arr2);

    while(it1!= std::end(arr1) && it2!= std::end(arr2))
    {
        if(std::abs(*it1-*it2) == diff)
        {
            ret.push_back(std::make_pair(*it1,*it2));
            ++it1;
            ++it2;
        }
        else if(*it1<*it2)
        {
            ++it1;
        }
        else
        {
            ++it2;
        }
    }

    return ret;
}


int main()
{

    std::vector<int> arr1 = {1,2,3,4};   
    std::vector<int> arr2 = {8,9,10,11};   
    int diff=5;
    
    auto pairs = find_pairs(arr1, arr2, diff);
    
    for(auto& i : pairs)
    {
        std::cout<<i.first<<"  "<<i.second<<std::endl;
    }
    
}