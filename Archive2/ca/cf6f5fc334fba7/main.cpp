struct my_node
{
    my_node(int i = 0) :
        parent_(nullptr),
        left_  (nullptr),
        right_ (nullptr),
        int_   (i)
    { }

    my_node *parent_, *left_, *right_;
    int      color_;
    //data members
    int      int_;

    bool operator<(my_node const& other) const { return int_ < other.int_; }
};

//Define our own rbtree_node_traits
struct my_rbtree_node_traits
{
   typedef my_node                                    node;
   typedef my_node *                                  node_ptr;
   typedef const my_node *                            const_node_ptr;
   typedef int                                        color;
   static node_ptr get_parent(const_node_ptr n)       {  return n->parent_;   }
   static void set_parent(node_ptr n, node_ptr parent){  n->parent_ = parent; }
   static node_ptr get_left(const_node_ptr n)         {  return n->left_;     }
   static void set_left(node_ptr n, node_ptr left)    {  n->left_ = left;     }
   static node_ptr get_right(const_node_ptr n)        {  return n->right_;    }
   static void set_right(node_ptr n, node_ptr right)  {  n->right_ = right;   }
   static color get_color(const_node_ptr n)           {  return n->color_;    }
   static void set_color(node_ptr n, color c)         {  n->color_ = c;       }
   static color black()                               {  return color(0);     }
   static color red()                                 {  return color(1);     }
};

#include <boost/intrusive/link_mode.hpp>
namespace bi = boost::intrusive;

struct my_value_traits
{
   typedef my_rbtree_node_traits        node_traits;
   typedef node_traits::node            value_type;
   typedef node_traits::node_ptr        node_ptr;
   typedef node_traits::const_node_ptr  const_node_ptr;
   typedef value_type*                  pointer;
   typedef value_type const*            const_pointer;

   static const bi::link_mode_type link_mode = bi::link_mode_type::normal_link;

   static node_ptr       to_node_ptr    (value_type &value)       { return &value; } 
   static const_node_ptr to_node_ptr    (const value_type &value) { return &value; } 
   static pointer        to_value_ptr   (node_ptr n)              { return n;      } 
   static const_pointer  to_value_ptr   (const_node_ptr n)        { return n;      } 
};

#include <boost/intrusive/rbtree.hpp>
using mytree = bi::rbtree<my_node, bi::value_traits<my_value_traits> >;

#include <iostream>
#include <vector>

int main() {
    std::vector<my_node> storage { {1}, {3}, {4}, {2}, {3}, };
    
    mytree container;
    container.insert_equal(storage.begin(), storage.end());

    // NOW for the "have your cake and eat it too" moment:
    for (my_node& n : container) {
        std::cout << n.int_ 
            << " (parent: " << n.parent_ << ")"
            << " (left:   " << n.left_ << ")"
            << " (right:  " << n.right_ << ")"
            << "\n";
    }
}
