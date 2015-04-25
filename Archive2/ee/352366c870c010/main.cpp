template <int* p>
void name_of_the_function_template() { *p = 42; }

extern int name_of_the_external_variable;

template void name_of_the_function_template<&name_of_the_external_variable>();