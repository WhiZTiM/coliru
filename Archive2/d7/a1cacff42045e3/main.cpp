#include <iostream>
#include <type_traits>
#include <vector>

// **** MISCELLANEOUS STUFF ****

template <class container_type>
struct container_traits {
  typedef const typename container_type::value_type* const_pointer;

  static const_pointer get_const_array_pointer(const container_type& c) {
      return &c[0];
  }
}; // etc.

template <class container_type>
typename container_traits<container_type>::const_pointer
get_const_array_pointer(const container_type& c) {
  return container_traits<container_type>::get_const_array_pointer(c);
}

// **** OPTIONS IMPLEMENTATION ****

namespace options {

template <class Ignored, class... Bases>
struct Options : public Bases... {
    Options(Bases... b) : Bases(b)... {}
};

//template <class Ignored>
//struct Options {
//};

template <class... Bases>
Options<void, Bases...> make_options(Bases... bases) {
    return Options<void, Bases...>(bases...);
}

} // namespace options

// **** DEVIATES NORMAL VECTOR IMPLEMENTATION HELPERS ****
namespace deviates_normal_vector_options {

namespace impl {

struct mean_vector_tag {};
struct stddev_vector_tag {};

template <class mean_vector_type_>
struct MeanVector : public mean_vector_tag {
  typedef mean_vector_type_ mean_vector_type;

  MeanVector() : mu(NULL) {}
  MeanVector(const mean_vector_type* mean_vector) : mu(mean_vector) {}

  const mean_vector_type* mu;
};

template <class stddev_vector_type_>
struct StddevVector : public stddev_vector_tag {
  typedef stddev_vector_type_ stddev_vector_type;

  StddevVector() : sigma(NULL) {}
  StddevVector(const stddev_vector_type* stddev_vector) : sigma(stddev_vector) {}

  const stddev_vector_type* sigma;
};

template <class pointer_type, class OptionType, class Enable = void>
struct mean_getter {
    static pointer_type get_mean(OptionType) {
        return NULL;
    }
};

template <class pointer_type, class OptionType>
struct mean_getter<pointer_type, OptionType,
    typename std::enable_if<std::is_base_of<mean_vector_tag, OptionType>::value>::type> {
  static pointer_type get_mean(OptionType& opt) {
    return get_const_array_pointer(*opt.mu);
  }
};

template <class pointer_type, class OptionType>
pointer_type get_mean(OptionType opt) {
  return mean_getter<pointer_type, OptionType>::get_mean(opt);
}

template <class pointer_type, class OptionType, class Enable = void>
struct stddev_getter {
    static pointer_type get_stddev(OptionType) {
        return NULL;
    }
};

template <class pointer_type, class OptionType>
struct stddev_getter<pointer_type, OptionType,
    typename std::enable_if<std::is_base_of<stddev_vector_tag, OptionType>::value>::type> {
  static pointer_type get_stddev(OptionType& opt) {
    return get_const_array_pointer(*opt.sigma);
  }
};

template <class pointer_type, class OptionType>
pointer_type get_stddev(OptionType opt) {
  return stddev_getter<pointer_type, OptionType>::get_stddev(opt);
}

} // namespace impl

template <class mean_vector_type>
impl::MeanVector<mean_vector_type> mean(const mean_vector_type& mu) {
  return impl::MeanVector<mean_vector_type>(&mu);
}

template <class stddev_vector_type>
impl::StddevVector<stddev_vector_type> stddev(const stddev_vector_type& stddev) {
  return impl::StddevVector<stddev_vector_type>(&stddev);
}

} // namespace deviates_normal_vector_options

// **** DEVIATES NORMAL VECTOR ****
enum class error_code {
  fail = -1,
  success = 0,
};

template <class p_vector_type, class x_vector_type, class... Optionals>
error_code deviates_normal_vector(const p_vector_type& p, x_vector_type& x,
                                  Optionals... optionals) {
  std::cout << "In deviates_normal_vector\n";
  namespace impl = deviates_normal_vector_options::impl;
  auto options = options::make_options(optionals...); 
  const double* mu = impl::get_mean<const double*>(options);
  const double* sigma = impl::get_stddev<const double*>(options);
  
  if (mu) { std::cout << mu[0] << "\n"; }
  else { std::cout << "NULL\n"; }

  if (sigma) { std::cout << sigma[0] << "\n"; }
  else { std::cout << "NULL\n"; }
  
  return error_code::success;
}

// **** TESTS ****
void required_parmeters_passed_in_order() {
  std::vector<double> x(10);
  std::vector<double> p(10);
  deviates_normal_vector(p, x);
}

void optional_parameters_in_any_order() {
  std::vector<double> x(10);
  std::vector<double> p(10);
  std::vector<double> mu(10);
  mu[0] = 42;
  std::vector<double> sigma(10);
  sigma[0] = 1337;
  namespace dnvo = deviates_normal_vector_options;
  deviates_normal_vector(p, x, dnvo::mean(mu));
  deviates_normal_vector(p, x, dnvo::stddev(sigma));
  deviates_normal_vector(p, x, dnvo::mean(mu), dnvo::stddev(sigma));
  deviates_normal_vector(p, x, dnvo::stddev(sigma), dnvo::mean(mu));
}

// **** MAIN ****
int main() {
  required_parmeters_passed_in_order();
  optional_parameters_in_any_order();
  return 0;
}
