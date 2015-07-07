#include <iostream>
#include <string>

struct Car {

    struct usage_calculator_t {

        const Car& considered_car ;
        usage_calculator_t( const Car& car ) : considered_car(car) {}
        void calculate_usage( int n, const double* a, double* b ) const
        { for( int i = 0 ; i < n ; ++i ) considered_car.gasoline_equation( a[i], b[i] ) ; }
    };

    const usage_calculator_t usage_calculator ;

    Car() : usage_calculator(*this) {}
    virtual ~Car() = default ;

    virtual void gasoline_equation( double a, double& b) const = 0 ;
    virtual std::string name() const = 0 ;
};

struct Audi : public Car
{
    virtual void gasoline_equation( double a, double& b) const override { b =  a * 0.2 ; }
    virtual std::string name() const override { return "Audi Spyder" ; }
};

struct Porsche : public Car
{
    virtual void gasoline_equation( double a, double& b) const override { b = a * 0.35 ; }
    virtual std::string name() const override { return "Porsche Panamera" ; }
};

int main()
{
    Audi audi ;
    Porsche porche ;

    const Car* cars[] { std::addressof(audi), std::addressof(porche) };

    const int n = 3 ;
    const double a[n] { 13.6, 44.4, 82.1 } ;
    double b[n] {} ;

    for(  const Car* car : cars )
    {
        std::cout << car->name() << ":\n" ;
        car->usage_calculator.calculate_usage( n, a, b ) ;
        for( int i = 0 ; i < n ; ++i ) std::cout << a[i] << " kms " << b[i] << " litres\n" ;
        std::cout << "----------------\n" ;
    }
}
