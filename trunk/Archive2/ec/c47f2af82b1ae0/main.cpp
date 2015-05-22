template<typename Arg>
auto hello(Arg a) -> decltype( a.x ) { return a.x; }

template<typename Arg>
auto hello(Arg a) -> decltype( a.y ) { return a.y; }

struct has_x { int x; };
struct has_y { int y; };

template int hello(has_x);
template int hello(has_y);

int main()
{
}