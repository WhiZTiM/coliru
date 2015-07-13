template <typename T>
class one  { T x;};

template <typename T>
class two:public T {};

template <typename T>
class three : public one<T> {};


int main(){}