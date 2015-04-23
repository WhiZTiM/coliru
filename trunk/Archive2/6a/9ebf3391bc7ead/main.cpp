template <typename T>
void fn1(T t) {
#if __GNUC__ && __GNUC__ < 4
#error "NOT SUPPORTED ON GCC < 4.0"
#endif
}

template <typename T>
void fn2(T t) {
#if __GNUC__ && __GNUC__ == 4 && __GNUC_MINOR__ >= 9
#error "NOT SUPPORTED ON GCC >= 4.9"
#endif
}

int main()
{
    fn1(1);
    fn2(2);
}