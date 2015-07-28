template<typename F>
void gief_answer(F f) { f(42); }

int main()
{
    gief_answer([](int warn_me) {});
    gief_answer([](int /* don't care */) {});
}
