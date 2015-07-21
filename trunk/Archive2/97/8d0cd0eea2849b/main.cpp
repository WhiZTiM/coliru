namespace apple{
    void myfunction(){}
}

namespace orange{
    void myfunction(){}
}

int main()
{
    using namespace apple; 
    using namespace orange;
    
    apple::myfunction(); // call the version into the apple namespace
    orange::myfunction(); // call the orange one
    myfunction(); // error: there is no using declaration / directive
}