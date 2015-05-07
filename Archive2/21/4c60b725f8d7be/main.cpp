void foo() {}
void bar() { return foo(); }

int main()
{
    bar();
}