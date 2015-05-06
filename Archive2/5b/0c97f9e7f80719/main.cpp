

bool ConvertToCpp(float) { return true; }
void ConvertToCpp(int) {}

template<typename T>
auto foo() { return ConvertToCpp(T{}); }

int main()
{
    foo<int>();
    foo<float>();
    
}