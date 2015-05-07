namespace ns1 {
    using Name = int;  
}

namespace ns1 {
namespace ns2 {

    class Foo {
    public:
      Foo() = default;
      ~Foo() = default;

    private:
      ns1::Name name;   // ns1::Name comes from Third-party library
    };
} // ns2
} // ns1

int main() {
    ns1::ns2::Foo f;   
}