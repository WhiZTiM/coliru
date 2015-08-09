#include <iostream>

int main()
{
    int number = 3875 ; // for example (non-negative)

    std::cout << "the number " << number << " contains the digits " ;

    while( number != 0 ) // repeat till we have nothing left
    {
        const int last_digit = number % 10 ; // 3875 %10 yields 5
        std::cout << last_digit << ' ' ; // print out the digit

        number /= 10 ; // dividing by 10 throws away the last digit
                       // 3875/10 == 387; last digit of 387 is 387%10 == 7
                       // 387/10 == 38; last digit of 38 is 38%10 == 8 etc.
    }

    std::cout << " (in reverse order)\n" ;
}
