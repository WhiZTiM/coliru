struct brick
{
    explicit brick() = default;
    brick(brick const&) = delete;
    brick(brick&&) = delete;
};

brick foo() { return {}; }

int main()
{
    brick b = {};
}