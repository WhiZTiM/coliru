#include <iostream>

template <typename T>
struct Field {
  typename T::value_type storage;

  typename T::value_type &operator[](const T &c) {
    return storage;
  }
};

    template<class...Ts>
    struct operator_index_inherit {};
    template<class T0, class T1, class...Ts>
    struct operator_index_inherit<T0, T1, Ts...>:
      T0, operator_index_inherit<T1, Ts...>
    {
      using T0::operator[];
      using operator_index_inherit<T1, Ts...>::operator[];
    };
    template<class T0>
    struct operator_index_inherit<T0>:
      T0
    {
      using T0::operator[];
    };

    template<class... Fields>
    struct ctmap : operator_index_inherit<Field<Fields>...> {
      using base = operator_index_inherit<Field<Fields>...>;
      using base::operator[];
    };
int main() {
    struct age { typedef int value_type; };
    struct last_name { typedef std::string value_type; };

    ctmap<last_name, age> person;

    person[last_name()] = "Smith";
    person[age()] = 104;
    std::cout << "Hello World!" << std::endl;
    return 0;
}