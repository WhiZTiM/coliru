template <typename T> void foo () { }
template <> void foo<int> () { }

int main ()
{
    (void) &foo<int>;
}