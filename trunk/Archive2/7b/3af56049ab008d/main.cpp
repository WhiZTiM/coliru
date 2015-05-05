#include <cfloat>
#include <cstdio>
#include <cstdlib>
#include <cmath>

float rcp(float f)
{
  return 1.f / f;
}

int main()
{
    float roughness = 0.f;
  	while (roughness <= 1.f)
    {
        float rrcp = rcp(roughness * roughness);
        float shininess = (2.f * rrcp - 2.f);
        if (shininess < 0.f)
            printf("fault at %.18f -> %.18f (rcp=%.18f)\n", roughness, shininess, rrcp), abort();

        roughness = nextafterf(roughness, 1.f);
    }
}