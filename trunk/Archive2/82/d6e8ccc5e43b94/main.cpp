#include <cmath>
#include <iostream>
#include <string>
#include <vector>

float k( float const& val)
     {
      const float p=1.0 / std::sqrt( 2.0 * M_PI);
      float result = 0.5 * (val*val);
      result = p * std::exp(- result);

      return result;
     };

std::vector< std::pair<float, float> > kde( float *val, int len,float h)
{
  std::vector< std::pair<float, float> > density( len );
  const float p = 1.0 / (h * len );

  for(int r=0;r<len;r++)
   {
    float sum = 0;

    for(int i=0;i<len;i++)
     sum += k( (val[r] - val[i]) / h );

    density[r] = std::make_pair( val[r], p*sum );
   }
  return density;
 }

int main()
{
  const int n=100;
  float val[n];
  
  for(int i=0;i<n;i++)
    val[i] = (float)rand() / (1.0 + RAND_MAX);
    
    
  std::vector< std::pair<float, float> > result =  kde( val,n, 0.1);
  for(auto e : result )
  {
   std::cout << e.first << " " << e.second << std::endl;   
  }
}
