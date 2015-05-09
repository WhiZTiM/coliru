template <typename T>
void start(T t) {
    [a = t] { [a]{}; };
}

int main()
{
    start(0);
}