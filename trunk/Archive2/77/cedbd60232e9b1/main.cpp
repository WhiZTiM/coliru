template<typename>
int i {};

template<typename... Xs>
void bar()
{
    // error: expansion pattern 'i<Xs>' contains no argument packs
    int is[] = { i<Xs>... };
}

int main()
{
    bar<void, void, void>();
}
