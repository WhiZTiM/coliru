#include <boost/iterator/iterator_facade.hpp>
#include <iostream>

struct node_base
{
    node_base* next() 
    {
        std::cout << "next()" << std::endl;
        return this;
    }
};

template <class Value>
class node_iter
  : public boost::iterator_facade<
        node_iter<Value>
      , Value
      , boost::random_access_traversal_tag
    >
{
 public:
    node_iter()
      : m_node(0) {}

    explicit node_iter(Value* p)
      : m_node(p) {}

 private:
    friend class boost::iterator_core_access;

    bool equal(node_iter<Value> const& other) const
    {
        return this->m_node == other.m_node;
    }

    void increment()
    { m_node = m_node->next(); }

    void advance(size_t n_)
    {
      for (size_t i = 0; i < n_; ++i) increment();
    }
    
    Value& dereference() const
    { return *m_node; }

    Value* m_node;
};
typedef node_iter<node_base> node_iterator;
typedef node_iter<node_base const> node_const_iterator;

int main()
{
    node_base node;
    node_iterator it(&node);
    it += 12;
    return 0;
}