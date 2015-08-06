#include <armadillo>

using namespace arma;

int main() {  
  vec  v = cumsum(ones<vec>(16));
  mat  m = v * v.t();
  cube c(v.size(), v.size(), 3);

  c.slice(0) = m;
  c.slice(1) = 256 - abs (256 - 2*m);
  c.slice(2) = 256 - m;
  c.save ("colmap.ppm", ppm_binary);
}
