#include <type_traits>

struct move_only
{
    move_only() = default;
    move_only(move_only const&) = delete;
    move_only(move_only&&) = default;
    
    move_only& operator=(move_only) { return *this; }
};

static_assert(!std::is_copy_assignable<move_only>(), "aww :(");

int main(){}