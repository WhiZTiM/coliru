#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<string>
#include<random>


    int main()
    {
        std::vector<std::tuple<std::string,int> > prizeBox;
        prizeBox.push_back(std::make_tuple("toy car",100));
        prizeBox.push_back(std::make_tuple("football",50));
        prizeBox.push_back(std::make_tuple("book",50));
        prizeBox.push_back(std::make_tuple("cash 1000",10));
    
        std::vector<int> chance;
        std::transform(std::begin(prizeBox), std::end(prizeBox), std::back_inserter(chance), [](auto p){return std::get<1>(p);});
        
        std::mt19937_64 rng;
        auto dist = std::discrete_distribution<int>(std::begin(chance), std::end(chance));
        
        //draws ten times from the prize box
        for(int i=0;i<10;++i)
        {
            
            std::cout<<std::get<0>(prizeBox[dist(rng)])<<std::endl;
        }
    }

