constexpr unsigned int f(unsigned n, unsigned p) 
{
    return ((n % p)*2 - 1) % p;
}

int main() {
    static_assert( f(4294967295U, 4294967291U) == 7, "" );
}