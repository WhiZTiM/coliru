#include <iostream>
#include <string>
#include <typeinfo>
#include <cmath>

class exponential{
    double
        base_,
        power_;
public:
    exponential(double base, double power) : base_{base}, power_{power}{}
    
    double &base(){return base_;}
    const double &base() const {return base_;}
    double &power(){return power_;}
    const double &power() const {return power_;}
    double toDouble(){return std::pow(base_, power_);}
    
    exponential operator+(const exponential &exp){
        return {std::pow(base_, power_) + std::pow(exp.base_, exp.power_), 1};
    }
    exponential operator-(const exponential &exp){
        return {std::pow(base_, power_) - std::pow(exp.base_, exp.power_), 1};
    }
    exponential operator*(const exponential &exp){
        if(base_ == exp.base_){
            return {base_, power_ + exp.power_};
        }
        else if(power_ == exp.power_){
            return {base_ * exp.base_, power_};
        }
        return {std::pow(base_, power_) * std::pow(exp.base_, exp.power_), 1};
    }
    exponential operator/(const exponential &exp){
        if(base_ == exp.base_){
            return {base_, power_ - exp.power_};
        }
        else if(power_ == exp.power_){
            return {base_ / exp.base_, power_};
        }
        return {std::pow(base_, power_) / std::pow(exp.base_, exp.power_), 1};
    }
};

int main(){
    std::cout << (exponential{0.5, 10000}/exponential{0.5, 10000}).toDouble();
}