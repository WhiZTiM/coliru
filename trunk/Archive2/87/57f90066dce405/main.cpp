#include <exception>
#include <iostream>
#include <type_traits>
#include <utility>

namespace refp {
  struct value_wrapper_base {
    value_wrapper_base (void const * ptr, bool d) : ptr (ptr), d (d) { }
    void const * ptr; bool d;
  };

  template<typename T>
  struct shared_ptr {
    struct value_wrapper : value_wrapper_base {
       value_wrapper (T const * ptr)
         : value_wrapper_base (static_cast<void const*> (ptr), false)
       { }

      ~value_wrapper () {
        if (value_wrapper_base::d)
          delete static_cast<T const*> (value_wrapper_base::ptr);
      }
    };

    shared_ptr ()                  = default;
    shared_ptr (shared_ptr&&)      = default;
    shared_ptr (shared_ptr const&) = default;

    template<typename U>
    shared_ptr (U const* ptr)
      : e (std::make_exception_ptr<value_wrapper> (value_wrapper (ptr)))
    {
      static_assert (std::is_convertible<U*, T*>::value,
        "U is not compatible with shared_ptr<T>"
      );

      w    = & get_wrapper ();
      w->d = true;
    }

    template<typename U>
    shared_ptr (shared_ptr<U> const& src)
      : e (src.e), w (src.w)
    {
      static_assert (std::is_convertible<U*, T*>::value,
        "shared_ptr<U> is not compatible with shared_ptr<T>"
      );
    }

    shared_ptr<T>& operator= (shared_ptr const& src) {
      return this->operator=<T> (src);
    }

    template<typename U> 
    shared_ptr<T>& operator= (shared_ptr<U> const& src)
    {
      static_assert (std::is_convertible<U*, T*>::value,
        "shared_ptr<U> is not compatible with shared_ptr<T>"
      );

      e = src.e;
      w = src.w;

      return *this;
    }

    value_wrapper& get_wrapper () const {
      try   { std::rethrow_exception (e); }
      catch (value_wrapper_base& ref) { return static_cast<value_wrapper&> (ref); }
    }

    T*         get () const { return const_cast<T*> (static_cast<T const*> (w->ptr)); }
    T* operator->  () const { return get (); }

    std::exception_ptr   e;
    value_wrapper_base * w;
  };

  template<typename T, typename... Args>
  shared_ptr<T>
  make_shared (Args&&... args)
  {
    return shared_ptr<T> (new T (std::forward<Args> (args) ... ));
  }
}

struct Obj {
  Obj (            ) : id (counter++), value (0) { std::cerr << "+Obj_" << id << " = " << value << "\n"; }
  Obj (int        i) : id (counter++), value (i) { std::cerr << "+Obj_" << id << " = " << value << "\n"; }
  Obj (Obj const& s) : id (counter++), value (s.value) { std::cerr << "=Obj_" << id << " = " << value << "\n"; }
  Obj (Obj&&      s) : id (counter++), value (s.value) { std::cerr << ">Obj_" << s.id << " = " << value << "\n"; }
  virtual ~Obj (   ) { std::cerr << "-Obj_" << id << " = " << value << "\n"; };

  virtual void func () { std::cerr << "inside Obj!\n"; }

  int const  id;
  int value = 0;
  static int counter;
};

int Obj::counter = 0;

struct Obj2 : Obj {
  using Obj::Obj;

  virtual void func () { std::cerr << "inside Obj2!\n"; }
};

int
main (int argc, char *argv[])
{
  refp::shared_ptr<Obj> p1;

  {
    auto p2 = refp::make_shared<Obj2> (123);
    p1 = p2;
  }

  p1->func ();
}