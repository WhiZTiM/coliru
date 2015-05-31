#include <type_traits>

struct indestructible { ~indestructible() = delete; };
static_assert(!std::is_destructible<indestructible>(), "");
static_assert(std::is_destructible<indestructible&>(), "");

struct foo { indestructible& bar; foo(); };
static_assert(std::is_destructible<foo>(), "");


void f(indestructible&) {}

void f(indestructible&&) {}
