#include <utility>
struct eh {
    eh() = default;
    eh(eh &&) = default;
    eh(const eh &) = delete;
};

int main() {
    eh e;
    // eh h{e}; Ill-formed - copy constructor explicitly deleted (gotten rid of)
    eh h{std::move(e)};
    throw h;
}