template<typename> struct TD { };

int main()
{
   auto a = "Hello World";
   TD<decltype(a)> _;
   auto& b = "Goodbye Cruel World";
   TD<decltype(b)> _2;
}