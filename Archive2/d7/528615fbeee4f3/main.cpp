int foo;

constexpr int* increment(int* p) { return p + 1; }

constexpr int* bar = increment(&foo);
constexpr int* UB = increment(bar);

constexpr int* also_UB = increment(nullptr);
