void f(struct X*) { }  // ok
// void g(Y*) { }  // error

int main()
{
    f(0);
}
