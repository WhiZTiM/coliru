template<class T> class foo {};
template<class T> class foo1 { static int i; };
class bar { class baz {}; public: using public_baz = baz; };

template<>
class foo<bar::baz> {};

int main()
{
    foo<bar::public_baz> f;
    (void)f;
}
