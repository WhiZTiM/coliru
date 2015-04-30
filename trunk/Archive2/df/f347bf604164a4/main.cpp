#include <cmath>
#include <iostream>   


float Q_rsqrt( float number )
{
    long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;						// evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
    if (y<0)
        return -y;
	return y;
}
int main()
{
    for (int i = 1; i< 10000; ++i){
        double n = (rand()%10000)/10. +1;
        double x = 1./std::sqrt((double)n);
        double y = Q_rsqrt((float)(double)n);
        //std::cout << n << std::endl;   
        if (std::abs(x-y) > 1E-6){
            std::cout << x << '\t' << y << std::endl;   
            break;
        }

    }
    std::cout << "END" << std::endl; 
    
//	std::cout << 1./std::sqrt(2.) << std::endl;
  //  std::cout << Q_rsqrt((float)2.) << std::endl;
//    std::cout << 1./std::sqrt(2000.) << std::endl;
 //   std::cout << Q_rsqrt((float)2000.) << std::endl;
	return 0;
}
