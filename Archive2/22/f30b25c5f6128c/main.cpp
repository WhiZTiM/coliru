#include <iostream>
#include <vector>

struct Base {
  using impl_ptr_t = void(*)(void*);

  void get_item () {
    get_item_ptr (this);
  }

  protected:
    Base (impl_ptr_t p)
      : get_item_ptr (p)
    { }

  private:
    impl_ptr_t get_item_ptr;
};

template<typename T>
struct B : Base {
  B ()
    : Base (&B::get_item_impl)
  { }

  static void get_item_impl (void* ptr) {
    static_cast<T*> (ptr)->get_item ();
  }
};

struct D1 : B<D1> {
  void get_item () { std::cerr << "D1::get_item\n"; }
};

struct D2 : B<D2> {
  void get_item () { std::cerr << "D2::get_item\n"; }
};

int
main (int argc, char *argv[])
{
  std::vector<Base> data {
    D1 {}, D2 {}
  };

  for (auto& obj : data) {
    obj.get_item ();
  }
}