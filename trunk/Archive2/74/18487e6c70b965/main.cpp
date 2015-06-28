
#include <memory>
#include <cstdio>

void empty_destructor(void* /*pointer*/) {
  /* Empty. */
}

struct empty_destructor_t {
    void operator()(void* p) const {
        ::empty_destructor(p);
    }
};

typedef std::unique_ptr<void, empty_destructor_t> handle_with_destructor;
typedef std::unique_ptr<void> handle;

template<class handle_type>
class snoopy {
  handle_type handle;
};

int main()
{
  /* Find out whether the pointer to the destructor is stored. */
  std::printf("Without destructor: %li" "\n" "With destructor %li",
              sizeof(snoopy<handle>), sizeof(snoopy<handle_with_destructor>)
             );
}
