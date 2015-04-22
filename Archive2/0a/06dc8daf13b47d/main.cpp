#include <iostream>
#include <vector>

//Parameter.h
struct Par {
    const int uniqid;
    const char *name;
    const char *description;
    constexpr Par(int uid,const char * n,const char * d)
             :uniqid(uid), name(n),description(d){}
};

class Parameters          
{
    const static Par PARAM_A;
//    ...
    const static Par PARAM_Z;
    void printParameters(std::vector<Par> parameters);
};

//Parameter.cpp
constexpr Par Parameters::PARAM_A={0,"-a","Bla a"};
//... 
constexpr Par Parameters::PARAM_Z={0,"-z","Bla z"};

void Parameters::printParameters(std::vector<Par> parameters){

    for (size_t i = 0; i < parameters.size(); i++) {
        switch (parameters[i].uniqid) {
           case PARAM_A.uniqid: 
                std::cout << "A" << std::endl;
                break;
        }
    }
}