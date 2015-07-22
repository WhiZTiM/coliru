template <int X>
struct Base
{
   void foo() { }
};

template <>                    // spécialisation de Base<X>
struct Base<42>
{
   void foobar() { }
};

template <int X>
struct Derive : Base<X>
{
   void bar() { this->foo(); } // Derive<X> pourrait être spécialisé avec X=42
};                             // mais Base<42> ne contient pas de fonction foo()

int main()
{
   Derive<41> d41;
   d41.bar();                  // correct

   Derive<42> d42;
   d42.bar();                  // erreur
}
