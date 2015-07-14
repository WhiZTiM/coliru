#define SET_COPY(T, A) T(T const&) = A; T& operator=(T const&) = A
#define SET_MOVE(T, A) T(T&&) = A; T& operator=(T&&) = A
#define SET_COPY_MOVE(T, A, B) SET_COPY(T, A); SET_MOVE(T, B)

struct A
{
    int n;

    SET_COPY_MOVE(A, delete, default);
};

struct B
{
    int n;

    B()
    {
    }

    B(A const& a)
    : n(a.n)
    {
    }

    SET_COPY_MOVE(B, delete, default);
};

struct C : A, B
{
    C()
    : B(static_cast<A const&>(*this)) // [1]
    {
        static_cast<B&>(*this) = B(); // [2]
    }
};