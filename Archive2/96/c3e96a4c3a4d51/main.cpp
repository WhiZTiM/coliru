enum struct foo { f };
enum struct bar { g };

int main()
{
    switch(foo::f) {
    case bar::g:;
    }
}