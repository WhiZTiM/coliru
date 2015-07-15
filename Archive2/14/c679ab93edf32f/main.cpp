#include <map>
#include <unordered_map>
#include <cassert>

template<class Key>
class mutable_key
{
public:
    mutable_key(Key const& value) : value{value} {}
    operator Key const& () const { return value; }
    template<class Container>
    void mutate(Container const& container, Key const& new_value) const {
        auto&& comp = container.key_comp();
        assert(!comp(value, new_value) && !comp(new_value, value));
        value = new_value;
    }
private:
    Key mutable value;
};

template<class Key>
class mutable_unordered_key
{
public:
    mutable_unordered_key(Key const& value) : value{value} {}
    operator Key const& () const { return value; }
    template<class Container>
    void mutate(Container const& container, Key const& new_value) const {
        auto&& hash = container.hash_function();
        auto&& eq = container.key_eq();
        assert(hash(new_value) == hash(value));
        assert(eq(new_value, value));
        value = new_value;
    }
private:
    Key mutable value;
};

int main() {
    auto comp = [](int lhs, int rhs) { return (lhs % 10) < (rhs % 10); };
    std::map<mutable_key<int>, int, decltype(comp)> m{{{1, 1}, {2, 2}}, comp};
    m.find(1)->first.mutate(m, 11);
    assert(m.begin()->first == 11);

    auto hash = [](int value) { return std::hash<int>()(value % 10); };
    auto eq = [](int lhs, int rhs) { return (lhs % 10) == (rhs % 10); };
    std::unordered_map<mutable_unordered_key<int>, int, decltype(hash), decltype(eq)> um{{{1, 1}, {2, 2}}, 0, hash, eq};
    um.find(1)->first.mutate(um, 11);
    assert(um.find(1)->first == 11);
}