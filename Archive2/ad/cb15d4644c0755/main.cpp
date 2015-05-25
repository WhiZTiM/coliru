long const& f(long const& arg) { return true ? arg : 0; }

int main()
{
    long l = 0;
    long const& r = f(0);
}
