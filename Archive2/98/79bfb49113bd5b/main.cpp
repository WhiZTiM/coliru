struct brick
{
    explicit brick(int) { };
    brick(brick const&) = delete;
    brick(brick&&) = delete;
};

brick foo() { return {42}; }

int main()
{
    brick b = {42};
}