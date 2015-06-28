#include <list>
#include <iostream>
#include <unordered_map>

int sign(int a){return ((a > 0) - (a < 0));}
int absolute(int a){return a * sign(a);}

struct SignRecord{
    SignRecord() : value_{NEITHER}{}
    enum SignGrouping{
        NEITHER, NEGATIVE, POSITIVE, BOTH
    } value_;

    SignGrouping& modify(int modifier){
        auto intToGrouping = [](int a) -> SignGrouping {return a < 0 ? NEGATIVE : POSITIVE;};
        if(value_ == NEITHER){value_ = intToGrouping(modifier);}
        else if(value_ == BOTH){return value_;}
        else if(value_ == intToGrouping(modifier)){return value_;}
        else{
            return value_ = BOTH;
        }
        return value_;
    }
};

std::ostream& operator<< (std::ostream &out, const SignRecord &printValue){
    switch( printValue.value_ ){
    case SignRecord::SignGrouping::NEITHER:
        out << "Neither";
        break;
    case SignRecord::SignGrouping::NEGATIVE:
       out << "Negative";
        break;
    case SignRecord::SignGrouping::POSITIVE:
        out << "Positive";
        break;
    default:
        out << "Both";
        break;
    }
    return out;
}

int main(){
    
    std::list<std::list<int>>
        myInts{
            {1,3},{1,-3},{2,5},{-2,-5},
            {-3,4},{-5,4},{3,5,-4},{6,-8},
            {-7,-8},{-6,-7,8},{-7,9},{-7,-9},
            {3,8,-10},{-3,-8,-10},{-3,8,10},
            {3,-8,10},{4,9,-11},{-4,-9,-11},
            {-4,9,11},{4,-9,11},{10,11},
            {1,6},{1,-6},{-2,-7},{2,-7}
        };
        
    std::unordered_map<int, SignRecord>
        intOrganizer;
        
    for(auto &&subList : myInts){
        for(auto &&entry : subList){
            intOrganizer[absolute(entry)].modify(entry);
        }
    }
    
    for(auto &&entry : intOrganizer){
        std::cout << entry.first << ": " << entry.second << '\n';
    }
}