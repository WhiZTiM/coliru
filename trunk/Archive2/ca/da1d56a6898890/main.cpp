#include <iostream>
#include <unordered_set>

enum {
    One,
    Two
};

class Complex {
public:
    void func(std::unordered_multiset<int>);
};

static int alpha() { static int idx(std::ios_base::xalloc()); return idx; }

struct alpha_num_facet : std::num_put<char> {
    alpha_num_facet(std::ostream& os) : os_(os) {}
    iter_type do_put(iter_type out, std::ios_base& str, char c, long v) const {
        if (str.iword(alpha())) {    
            static const char* buf[2] = {"One", "Two", /*...*/};
            os_ << buf[v];
        } else {
            out = std::num_put<char>::do_put(out, str, c, v);
        }
        return out;
    }
private:
    std::ostream& os_;
};

std::ostream& print_alpha_num(std::ostream& os) {
    os.iword(alpha()) = true;
    if (!std::has_facet<alpha_num_facet>(os.getloc())) {
        os.imbue(std::locale(os.getloc(), new alpha_num_facet(os)));
    }
    return os;
}

std::ostream& no_print_alpha_num(std::ostream& os) {
    os.iword(alpha()) = false;
    return os;
}

void Complex::func(std::unordered_multiset<int> v) {
    v.insert(One);
    v.insert(Two);
    for (std::unordered_multiset<int>::const_iterator i(v.begin()), end(v.end()); i != end; ++i){
        std::cout  << print_alpha_num << "Num: " << *i << std::endl;
    }
}

int main(){
    Complex c;
    std::unordered_multiset<int> ms;
    c.func(ms);
}