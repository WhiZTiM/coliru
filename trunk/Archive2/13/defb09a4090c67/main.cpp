struct CannotCopy {
    CannotCopy(const CannotCopy&) = delete;
    CannotCopy(CannotCopy&&) = default;
    CannotCopy() = default;
};

CannotCopy foo()
{
    return {};                  // This works
}

CannotCopy bar()
{
    return CannotCopy();        // This doesn't
}

CannotCopy baz()
{
    return CannotCopy{};        // This doesn't
}