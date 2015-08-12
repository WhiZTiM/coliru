namespace N{

void foo()
{
    void bar();
    bar();
}

}

int main()
{
    N::foo();
}


namespace N{
void bar()
{
}
}