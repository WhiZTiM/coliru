#include <iostream>
#include <vector>
#include <array>
#include <cmath>

template <typename T, std::size_t M, std::size_t N> class matref;

template <typename T, std::size_t M, std::size_t N>
class densebase
{
public:
  using Col = matref<T,M,1>;

  virtual T& coeff(std::size_t row, std::size_t col) = 0;
  virtual T& coeff(std::size_t index) = 0;

  virtual const T& coeff(std::size_t row, std::size_t col) const = 0;
  virtual const T& coeff(std::size_t index) const = 0;

  Col col(std::size_t index) { return Col(*this, 0, index); }
  const Col col(std::size_t index)const { return Col(*this, 0, index); }

  T& operator()(std::size_t row, std::size_t col) { return coeff(row, col); }
  T& operator[](std::size_t index) { return coeff(index); }

  const T& operator()(std::size_t row, std::size_t col) const { return coeff(row, col); }
  const T& operator[](std::size_t index) const { return coeff(index); }
};

template <typename T, std::size_t M, std::size_t N>
class mat : public densebase<T,M,N>
{
public:
  mat(): data_(M*N) {}
  mat(std::initializer_list<T> vals) : data_{vals} {}

  T& coeff(std::size_t row, std::size_t col) { return data_[row*N + col]; }
  T& coeff(std::size_t index) { return data_[index]; }

  const T& coeff(std::size_t row, std::size_t col) const { return data_[row*N + col]; }
  const T& coeff(std::size_t index) const { return data_[index]; }

private:
  std::vector<T> data_;
};

template <typename T, std::size_t M, std::size_t N>
class matref : public densebase<T,M,N>
{
public:
  template <std::size_t M2, std::size_t N2> matref(densebase<T,M2,N2>& m, std::size_t iM = 0, std::size_t iN = 0)
  {
    for (std::size_t i = 0; i < M; ++i)
      for (std::size_t j = 0; j < N; ++j)
        data_[i*N + j] = &m.coeff(iM+i, iN+j);
  }

  T& coeff(std::size_t row, std::size_t col) { return *data_[row*N + col]; }
  T& coeff(std::size_t index) { return *data_[index]; }

  const T& coeff(std::size_t row, std::size_t col) const { return *data_[row*N + col]; }
  const T& coeff(std::size_t index) const { return *data_[index]; }

private:
  std::array<T*, M*N> data_;
};

template <typename T, std::size_t N>
T getnorm(const densebase<T,N,1>& vec)
{
  T n = 0;
  for (std::size_t i = 0; i < N; ++i)
    n += vec[i]*vec[i];

  return std::sqrt(n);
}

template <typename T, std::size_t N>
densebase<T,N,1>& normalizes(densebase<T,N,1>& vec)
{
  T n = getnorm(vec);
  for (std::size_t i = 0; i < N; ++i)
    vec[i] /= n;

  return vec;
}

/*template <typename T, std::size_t N>
densebase<T,N,1>& normalizes(densebase<T,N,1>&& vec)
{
  T n = getnorm(vec);
  for (std::size_t i = 0; i < N; ++i)
    vec[i] /= n;

  return vec;
}*/

int main(int argc, char* argv[])
{
  mat<float, 5, 1> matte;
  normalizes(matte);

  mat<float, 2, 2> yo { 4, 2, 6, 1 };
  // normalizes(yo.col(1)); PROBLEM BITCH
  auto tt = yo.col(0);
  normalizes(tt);
  for (std::size_t i = 0; i < 4; ++i)
    std::cout << yo[i] << std::endl;
}
