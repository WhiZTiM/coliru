struct S {
    double operator()(char, int&);
};
 
int main()
{
    std::result_of<S(char, int&)>::type f = 3.14; // f has type double
}