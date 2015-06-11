#include <memory>

int main()
{
    std::shared_ptr<double> array (new double [256], [](double * d){
        delete [] d;
    });
    
    array.get()[2] = 5;
}
