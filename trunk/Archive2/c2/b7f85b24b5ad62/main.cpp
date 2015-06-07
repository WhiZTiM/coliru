int main()
{
    struct base { int x; };
    struct derived : base { int x; };
    
    &derived{}.base::x;
}