#define UNUSED __attribute__((__unused__))

int main()
{
           int i    UNUSED;
    UNUSED int j;
           int k(1) UNUSED;
           int l    UNUSED (1);
    UNUSED int m(1);
}