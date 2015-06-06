struct non_copyable {
    non_copyable() = default;
    non_copyable(non_copyable const&) = delete;
};

void foo(non_copyable) {}

int main()
{
    foo({});
}
