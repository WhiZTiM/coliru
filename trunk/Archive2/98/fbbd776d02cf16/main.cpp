template<class T> 
int p(T) { return 0; }

template <typename T>
void start(T t) {
    [a = p(t)] () {
        [a] () {};
    };
}

int main()
{
    start(0);
}