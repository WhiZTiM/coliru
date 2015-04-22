#include <iostream>
#include <type_traits>
#include <vector>

// **** MISCELLANEOUS STUFF ****

template <class container_type>
struct container_traits {
  typedef typename container_type::value_type * pointer;
  typedef const typename container_type::value_type * const_pointer;

  static const_pointer get_const_array_pointer(const container_type& c) {
      return &c[0];
  }

  static pointer get_array_pointer(container_type& c) {
    return &c[0];
  }
}; // etc.

template <class container_type>
typename container_traits<container_type>::pointer
get_array_pointer(container_type& c) {
  return container_traits<container_type>::get_array_pointer(c);
}

template <class container_type>
typename container_traits<container_type>::const_pointer
get_const_array_pointer(const container_type& c) {
  return container_traits<container_type>::get_const_array_pointer(c);
}

//// **** OPTIONS IMPLEMENTATION ****

namespace options {

template <class base_type, class wrapped_type>
struct option_wrapper : public base_type {
  typedef wrapped_type type;
  typedef wrapped_type * pointer;

  option_wrapper() : data(nullptr) {}
  option_wrapper(pointer ptr) : data(ptr) {}

  pointer data;
};

template <class base_type, class wrapped_type>
struct const_option_wrapper : public base_type {
  typedef wrapped_type type;
  typedef const wrapped_type * const_pointer;

  const_option_wrapper() : data(nullptr) {}
  const_option_wrapper(const_pointer ptr) : data(ptr) {}

  const_pointer data;
};

template <class tag_type>
typename tag_type::pointer get() {
  return nullptr;
}

template <class tag_type, class Head>
typename std::enable_if<!std::is_base_of<tag_type, Head>::value,
                        typename tag_type::pointer>::type
get(Head h) {
  return nullptr;
}

template <class tag_type, class Head>
typename std::enable_if<std::is_base_of<tag_type, Head>::value,
                        typename tag_type::pointer>::type
get(Head h) {
  return get_array_pointer(*h.data);
}

template <class tag_type, class Head, class... Tail>
typename std::enable_if<!std::is_base_of<tag_type, Head>::value,
                        typename tag_type::pointer>::type
get(Head h, Tail... t) {
  return get<tag_type>(t...);
}

template <class tag_type, class Head, class... Tail>
typename std::enable_if<std::is_base_of<tag_type, Head>::value,
                        typename tag_type::pointer>::type
get(Head h, Tail... t) {
  return get_array_pointer(*h.data);
}

template <class tag_type>
typename tag_type::const_pointer get() {
  return nullptr;
}

template <class tag_type, class Head>
typename std::enable_if<!std::is_base_of<tag_type, Head>::value,
                        typename tag_type::const_pointer>::type
get(Head h) {
  return nullptr;
}

template <class tag_type, class Head>
typename std::enable_if<std::is_base_of<tag_type, Head>::value,
                        typename tag_type::const_pointer>::type
get(Head h) {
  return get_const_array_pointer(*h.data);
}

template <class tag_type, class Head, class... Tail>
typename std::enable_if<!std::is_base_of<tag_type, Head>::value,
                        typename tag_type::const_pointer>::type
get(Head h, Tail... t) {
  return get<tag_type>(t...);
}

template <class tag_type, class Head, class... Tail>
typename std::enable_if<std::is_base_of<tag_type, Head>::value,
                        typename tag_type::const_pointer>::type
get(Head h, Tail... t) {
  return get_const_array_pointer(*h.data);
}

struct double_pointer_tag {
  typedef double * pointer;
};

struct const_double_pointer_tag {
  typedef const double * const_pointer;
};

} // namespace options

// **** DEVIATES_NORMAL_VECTOR IMPLEMENTATION DETAILS ****
namespace deviates_normal_vector_options {

namespace impl {

struct mean_tag : options::double_pointer_tag {};

struct stddev_tag : options::const_double_pointer_tag {};

} // namespace impl

template <class mean_vector_type>
options::option_wrapper<impl::mean_tag, mean_vector_type>
mean(mean_vector_type& mu) {
  return options::option_wrapper<impl::mean_tag, mean_vector_type>(&mu);
}

template <class stddev_vector_type>
options::const_option_wrapper<impl::stddev_tag, stddev_vector_type>
stddev(const stddev_vector_type& sigma) {
  return options::const_option_wrapper<impl::stddev_tag, stddev_vector_type>(&sigma);
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
  std::cout << "In deviates_normal_vector:\n";
  namespace impl = deviates_normal_vector_options::impl;
  const double* mu =
    options::get<impl::mean_tag>(optionals...);
  const double* sigma =
    options::get<impl::stddev_tag>(optionals...);
  
  std::cout << " mean: ";
  if (mu) { std::cout << mu[0] << "\n"; }
  else { std::cout << "not provided\n"; }

  std::cout << " stddev: ";
  if (sigma) { std::cout << sigma[0] << "\n"; }
  else { std::cout << "not provided\n"; }

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

