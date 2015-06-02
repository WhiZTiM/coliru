template<typename T>
void my_function_template() {}

void my_ordinary_function() {}

int main()
{
    my_function_template<int>();
    my_ordinary_function();
}