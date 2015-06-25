void foo(int&) {}
void foo(int const&) = delete;

int main()
{
    int const i {};
    foo(i);
}
