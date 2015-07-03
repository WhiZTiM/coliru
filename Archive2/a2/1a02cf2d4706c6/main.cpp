struct ValidTag
{
    void foo(){}
};

using WrongTag = int;

int main()
{
    auto lambda = [](auto x){ return x.foo(); };
    
    decltype(&decltype(lambda)::operator()<ValidTag>) x; // OK
    decltype(&decltype(lambda)::operator()<WrongTag>) x; // Error
}
