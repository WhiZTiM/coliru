#include <cstddef>

namespace detail {
    namespace with_std {
        using namespace std;
        using max_align_t_workaround = max_align_t;
    }
    
    using max_align_t = with_std::max_align_t_workaround;
}

int main(int argc, char** argv) {
    detail::max_align_t t;
    return 0;
}