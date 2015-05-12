//
//  Exar.cpp
//  the simplifier
//
//  Created by Elliot MacNeille on 2/21/15.
//  Copyright (c) 2015 Elliot MacNeille. All rights reserved.
//
//#include <assert.h>
#include "/Archive2/9e/24bc4490b5e137/main.cpp"
#include <limits.h>
//using namespace __hidden__;

bool testcopyt=0;

template <typename T, typename F>
static void copy2(T *t1, const F *t2, const F * const t2end){
    assert(t2 <= t2end);
    if (testcopyt){
        erint "copying";
    }
    if (t2 != t2end) while (1){
        *t1 = *t2;
        ++t2;
        if (t2 == t2end) break;
        ++t1;
    }
    if (testcopyt){
        erint "done copying";
    }
}

template <typename T>
int isinside(T const t, T const tend, T const tin){
    if (tin < t) return -1;
    if (tin >= tend) return 1;
    return 0;
}

void printspacez(unsigned num, std::ostream &os=cout){
    while (num != 0){
        os << " ";
        --num;
    }
}

template <typename T, typename uintt=unsigned, typename intt=int>
struct Exar {
    
    T *data;
    uintt siz;
    uintt capa;
    
    enum FUNCS{
        EXPAND=0,
        TESTEXPAND
    };
    
    static const unsigned numfuns = TESTEXPAND+1;
    bool test[numfuns];
    
    void settest(){
        for (unsigned i = 0; i != numfuns; ++i){
            test[i] = false;
        }
        test[EXPAND] = 0;
        test[TESTEXPAND] = 0;
    }
    template <typename F>
    void settest(const Exar<F> &ex){
        for (unsigned i = 0; i != numfuns; ++i){
            test[i] = ex.test[i];
        }
    }
    
    T *&t(){
        return data;
    }
    const T *t() const{
        return data;
    }
    
    T *&begin(){
        return data;
    }
    const T *begin() const{
        return data;
    }
    
    uintt &size(){
        return siz;
    }
    const uintt &size() const{
        return siz;
    }
    
    uintt &s(){
        return siz;
    }
    const uintt &s() const{
        return siz;
    }
    uintt &c(){
        return capa;
    }
    const uintt &c() const{
        return capa;
    }
    
    uintt &cap(){
        return capa;
    }
    const uintt &cap() const{
        return capa;
    }
    
    T &operator[](intt a){
        return *(t()+a);
    }
    const T &operator[](intt a) const{
        return *(t()+a);
    }
    
    T &at(uintt a){
        if (a >= c()){
            expand(a+1);
            s() = a+1;
        }
        else {
            s() = max(s(), a+1);
        }
        return *((&t())+a);
    }
    
    void expand(uintt a=0){
        
        if (test[EXPAND]){
            erint "expanding";
        }
        if (a==0){
            assert(s() == c());
            assert(c() < s() * 2 || (c() == s() && c() == uintt(0)));
            if (test[EXPAND]){
               cout << "c() set from " << c();
            }
            c() = (s() == uintt(0) ? 1 : s()*2);
            if (test[EXPAND]){
                erint " to", c();
            }
        }
        else {
            assert(a > s());
            assert(a > c());
            if (test[EXPAND]){
                cout << "c() set from " << c();
            }
            c() = a;
            if (test[EXPAND]){
                erint " to value of a,", c();
            }
            //s() = max(s()*s(), a);
        }
        T *bar = new T[c()];
        copy2(bar, t(), t()+s());
        delete [] t();
        t() = bar;
        if (test[EXPAND]){
            erint "done expanding";
        }
    }
    
    T &ins(const uintt &pos=0){//needs work
        if (pos >= s()){
            expand(pos);
        }
        return new T();
    }
    
    
    
    bool full(){
        return size() == cap();
    }
    
    T &operator++(){
        if (full()){
            expand();
        }
        ++size();
        return top();
    }
    
    T &operator--(){
        assert(s() != uintt(0));
        //if (s() == uintt(0)){
           // erint "cannot decrement";
           // return T();
      //  }
        --size();
        return *end();
    }
    
    void clear(uintt siz=uintt(8)){
        if (cap() > siz){
            cap() = siz;
            delete [] begin();
            begin() = new T[siz];
        }
        s()=uintt(0);
        //m=t();
    }
    
    void init(uintt a=uintt(0)){
        assert((uintt(0)-1) > uintt(0) || a >= 0);
        c() = a;
        t() = new T[a];
    }
    
    Exar(uintt a=uintt(0)){
        
        settest();
        init(a);
        s() = uintt(0);
    }
    
    template <typename F>
    Exar(const Exar<F> &ex){
        
        settest(ex);
        s() = ex.s();
        c() = ex.c();
        t() = new T[ex.c()];
        copy(t(), ex.t(), ex.end());
    }
    ~Exar(){
        delete [] t();
    }
    
    T *end(){
        return const_cast<T *>(cons().end());
        //return t()+s();
    }
    const T *end() const{
        return begin()+size();
    }
    
    const T &top() const {
        assert(size() > 0);
        return *(end()-1);
    }
    
    const Exar & cons() const {
        return static_cast<const Exar &>(*this);
    }
    
    T &top(){
        return const_cast<T &>(cons().top());
        //return const_cast<T &>(static_cast<const Exar &>(*this).top());
    }
    
    bool empty() const {
        return size() == uintt(0);
    }
    
    //test functions
    
    static bool tester(std::ostream &os=cout){
        return testexpand(os);
    }
    
    static bool testexpand(std::ostream &os=cout){
        Exar<int> ex;
        for (int i = 0; i != 10; ++i){
            ++ex = i;
            if (ex.test[Exar<int>::TESTEXPAND])cout << ex.top() << " ";
            assert(ex.top() == i);
        }
        if (ex.test[Exar<int>::TESTEXPAND])cout << endl;
        for (int i = 0; i != 10; ++i){
            if (ex.test[Exar<int>::TESTEXPAND])cout << ex[i] << " ";
            assert(ex[i] == i);
        }
       if (ex.test[Exar<int>::TESTEXPAND]) cout << endl;
        for (int i = 9; i != -1; --i){
            assert(--ex == i);
            if (ex.test[Exar<int>::TESTEXPAND]) cout << *ex.end() << " ";
        }
        if (ex.test[Exar<int>::TESTEXPAND])cout << endl;
        return true;
    }
    
    std::ostream &print(std::ostream &os=cout) const {
        const T *it = begin();
        if (size() != uintt(0)) while (1){
            os << *it;
            ++it;
            if (it == end()){
                break;
            }
            os << ' ';
            assert(isinside(begin(), begin()+size(), it) == 0);
        }
        return os;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const Exar<T> &ex){
        return ex.print(os);
    }
};
/*
template <typename T, typename uintt=unsigned, typename intt=int>
struct Queue {
    
    Exar<T, uintt, intt> exar;
    
    Exar<T> &ex(){
        return exar;
    }
    
    const Exar<T> &ex() const {
        return exar;
    }
    
    Queue(uintt a=0){}
    uintt starty;
    
    enum FUNCS{
        EXPAND=0,
        TESTEXPAND
    };
    
    static const unsigned numfuns = TESTEXPAND+1;
    bool test[numfuns];
    
    void settest(){
        for (unsigned i = 0; i != numfuns; ++i){
            test[i] = false;
        }
        test[EXPAND] = 0;
        test[TESTEXPAND] = 0;
    }
    template <typename F>
    void settest(const Exar<F> &ex){
        for (unsigned i = 0; i != numfuns; ++i){
            test[i] = ex.test[i];
        }
    }
    
    T *&t(){
        return ex().t();
    }
    const T *t() const{
        return ex().t();
    }
    
    uintt &start(){
        return starty;
    }
    const uintt start() const{
        return starty;
    }
    
    T *&begin(){
        return t() + start();
    }
    const T *begin() const{
        return t() + start();
    }
    
    uintt &size(){
        return ex().size();
    }
    const uintt &size() const{
        return ex().size();
    }
    
    uintt &cap(){
        return ex().cap();
    }
    const uintt &cap() const{
        return ex().cap();
    }
    
    bool full(){
        return size() == cap();
    }
    
    T &operator++(){
        if (full()){
            expand();
        }
        ++s();
        return top();
    }
    
    T &operator--(){
        assert(s() != uintt(0));
        //if (s() == uintt(0)){\
        erint "cannot decrement";\
        return T();\
        }
        --s();
        return *end();
    }
    
    void clear(){
        size()=uintt(0);
        //m=t();
    }
    
    void init(uintt a=uintt(0)){
        assert((uintt(0)-1) > uintt(0) || a >= 0);
        c() = a;
        t() = new T[a];
    }
    
    T *end(){
        return const_cast<T *>(cons().end());
        //return t()+s();
    }
    const T *end() const{
        return begin()+size();
    }
    
    const T &top() const {
        assert(size() > 0);
        return *(end()-1);
    }
    
    const Exar & cons() const {
        return static_cast<const Exar &>(*this);
    }
    
    T &top(){
        return const_cast<T &>(cons().top());
        //return const_cast<T &>(static_cast<const Exar &>(*this).top());
    }
    
    bool empty() const {
        return size() == uintt(0);
    }
    
    //test functions
    
    static bool tester(std::ostream &os=cout){
        return testexpand(os);
    }
    
    static bool testexpand(std::ostream &os=cout){
        Exar<int> ex;
        for (int i = 0; i != 10; ++i){
            ++ex = i;
            if (ex.test[Exar<int>::TESTEXPAND])cout << ex.top() << " ";
            assert(ex.top() == i);
        }
        if (ex.test[Exar<int>::TESTEXPAND])cout << endl;
        for (int i = 0; i != 10; ++i){
            if (ex.test[Exar<int>::TESTEXPAND])cout << ex[i] << " ";
            assert(ex[i] == i);
        }
        if (ex.test[Exar<int>::TESTEXPAND]) cout << endl;
        for (int i = 9; i != -1; --i){
            assert(--ex == i);
            if (ex.test[Exar<int>::TESTEXPAND]) cout << *ex.end() << " ";
        }
        if (ex.test[Exar<int>::TESTEXPAND])cout << endl;
        return true;
    }
    
    std::ostream &print(std::ostream &os=cout) const {
        const T *it = begin();
        if (size() != uintt(0)) while (1){
            os << *it;
            ++it;
            if (it == end()){
                break;
            }
            os << ' ';
            assert(isinside(begin(), begin()+size(), it) == 0);
        }
        return os;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const Exar<T> &ex){
        return ex.print(os);
    }
};
*/
enum COMP{
    LESS=0,
    GREATER
};
static const unsigned numcomps = GREATER+1;

template <typename T, typename F>
bool _less(const T &t, const F &f){
    return t < f;
}

template <typename T, typename F>
bool _greater(const T &t, const F &f){
    return t > f;
}

template <typename T, typename F>
bool _equal(const T &t, const F &f){
    return t == f;
}

template <typename T, typename F>
bool _equalmem(const T &t, const F &f){
    if (&t == &f){
        assert(equal(t, f));
    }
    return &t == &f;
}
/*
template <typename T, bool (*comp)(const T&, const T&)=_less, typename intt=int, typename uintt=unsigned>
struct Tree{
    
};*/

template <typename T, typename NODE, typename intt=int, typename uintt=unsigned int>
struct Tree22{
    
    NODE *find(const NODE &te) const {
        return static_cast<const T *>(this)->find_();
    }
    
    NODE *&findr(const NODE &te) const {
        return static_cast<const T *>(this)->findr_();
    }
};

template <typename T, bool (*comp)(const T&, const T&)=_less, typename intt=int, typename uintt=unsigned>
struct Treeog{
    
    enum DIR{
        LEFT,
        RIGHT
    };
    
    struct Node{
        
        enum NODEFUNC{
            TREEPRINT,
            TOTALDEPTH,
            BUILDIDEAL,
            TRAVERSE
        };
        static const unsigned nodefuns = TRAVERSE+1;
        bool test[nodefuns];
        
        void settest(){
            for (int i = 0; i != nodefuns; ++i){
                test[i] = 0;
            }
            test[TREEPRINT] = 0;
            test[TOTALDEPTH] = 0;
            test[TRAVERSE] = 0;
            test[BUILDIDEAL] = 1;
        }
        
        intt child[RIGHT+1];
        T *data;
        
        Node(){
            settest();
        }
        
        T *&t(){
            return data;
        }
        const T *t() const{
            return data;
        }
        
        intt &l(){
            return child[LEFT];
        }
        const intt &l() const{
            return child[LEFT];
        }
        
        intt &r(){
            return child[RIGHT];
        }
        const intt &r() const{
            return child[RIGHT];
        }
        intt &dist(const DIR d){
            return child[d];
        }
        
        const intt &dist(const DIR d) const{
            return child[d];
        }
        Node *nav(const DIR d){
            return this + dist(d);
        }
        
        const Node *nav(const DIR d) const{
            return this + dist(d);
        }
        Node *nav2(const DIR d){
            if (terminal(d)){
                return nullptr;
            }
            assert(dist(d) != uintt(0));
            return nav(d);
        }
        
        const Node *nav2(const DIR d) const{
            if (terminal(d)){
                return nullptr;
            }
            assert(dist(d) != uintt(0));
            return nav(d);
        }
        
        bool terminal(DIR d) const{
            return dist(d) == uintt(0);
        }
        
        Node *operator[](const DIR d){
            return nav(d);
        }
        
        const Node *operator[](const DIR d) const{
            return nav(d);
        }
        
        void init(T &item){
            //pointto(RIGHT, this);
            //pointto(LEFT, this);
            r() = l() = intt(0);
            t() = &item;
        }
        
        void init(Node &no){
            pointto(RIGHT, no->nav(RIGHT));
            pointto(LEFT, no->nav(LEFT));
            t() = no.t();
        }
        
        void pointto(DIR d, Node *no){
            dist(d) = no - this;
        }
        
        template <typename FN>
        void iteratenode(FN fn){
            if (!this) return;
            fn(nav2(LEFT));
            fn(this);
            fn(nav2(RIGHT));
        }
        
        template <typename FN>
        void traverse(FN fn){
            if (test[TRAVERSE]){
                erint "traversing";
            }
            if (!terminal(LEFT)){
                nav(LEFT)->traverse(fn);
            }
            fn(*t());
            if (!terminal(RIGHT)){
                nav(RIGHT)->traverse(fn);
            }
            if (test[TRAVERSE]){
                erint "done traversing";
            }
        }
        
        template <typename FN>
        void traverse(FN fn) const{
            if (test[TRAVERSE]){
                erint "traversing const";
            }
            if (!terminal(LEFT)){
                nav(LEFT)->traverse(fn);
            }
            fn(*t());
            if (!terminal(RIGHT)){
                nav(RIGHT)->traverse(fn);
            }
            if (test[TRAVERSE]){
                erint "done traversing const";
            }
        }
        
        void Treeprint(std::ostream &os=cout, uintt level=uintt(0)){
            
            if (test[TRAVERSE]){
                erint "traversing const";
            }
            printspacez(level, os);
            erint *t();
            if (!terminal(LEFT)){
                (*this)[LEFT]->Treeprint(os, level+1);
            }
            if (!terminal(RIGHT)){
                (*this)[RIGHT]->Treeprint(os, level+1);
            }
            if (test[TRAVERSE]){
                erint "done traversing const";
            }
        }
        
        void Treeprintbetter(std::ostream &os=cout, uintt level=uintt(0), uintt mdepth=uintt(0)){
            
            if (test[TREEPRINT]){
                erint "TREEprint", mdepth;
            }
            assert(level <= mdepth);
            
            if (!terminal(LEFT)){
                (*this)[LEFT]->Treeprintbetter(os, level+1, mdepth);
            }
            printspacez(2*(mdepth - level), os);
            os << *t() << endl;
            if (!terminal(RIGHT)){
                (*this)[RIGHT]->Treeprintbetter(os, level+1, mdepth);
            }
            if (test[TREEPRINT]){
                erint "treeprint";
            }
        }
        
        void totaldepthbetter(uintt &sumt, uintt level=uintt(1)) const{
            
            if (test[TOTALDEPTH]){
                erint "totaldepth, adding", level, "to", sumt;
            }
            
            sumt+=level;
            if (!terminal(LEFT)){
                (*this)[LEFT]->totaldepthbetter(sumt, level+1);
            }
            if (!terminal(RIGHT)){
                (*this)[RIGHT]->totaldepthbetter(sumt, level+1);
            }
        }
        
        uintt maxdepth(){
            if (nav(LEFT) == this){
                if (nav(RIGHT) == this){
                    return uintt(1);
                }
                return nav(RIGHT)->maxdepth() + 1;
            }
            if (nav(RIGHT) == this){
                return nav(LEFT)->maxdepth() + 1;
            }
            return max((*this)[RIGHT]->maxdepth(), (*this)[LEFT]->maxdepth()) + 1;
        }
        
        void printlevel(std::ostream &os=cout, uintt level=1, uintt spacing=0){
            assert(level != uintt(0));
            --level;
            if (level == uintt(0)){
                for (int i = 0; i != spacing; ++i){
                    os << ' ';
                }
                os << *t();
                return;
            }
            if (nav(LEFT) != this){
                nav(LEFT)->printlevel(os, level, spacing);
            }
            else {
                for (int i = 0; i != spacing+3; ++i){
                    os << ' ';
                }
            }
            if (nav(RIGHT) != this){
                nav(RIGHT)->printlevel(os, level, spacing);
            }
            else {
                for (int i = 0; i != spacing+3; ++i){
                    os << ' ';
                }
            }
        }
        
        void maketerminal(DIR dir){
            dist(dir) = intt(0);
        }
        
        static constexpr const bool testbuildideal=0;
        
        static void buildideall(Node *lb, Node *rb){
            if (testbuildideal){
                erint "buildideall", rb-lb, *rb->t();
            }
            if (lb == rb){
                if (testbuildideal){
                    erint "setting", *rb->t(),"LEFT to terminal";
                }
                rb->maketerminal(LEFT);
                return;
            }
            
            Node *it = lb + (rb - lb)/2;
            if (testbuildideal){
                erint "setting value:",  *it->t();
            }
            
            rb->pointto(LEFT, it);
            
            buildideall(lb, it);
            buildidealr(it, rb);
        }
        
        static void buildidealr(Node *lb, Node *rb){
            if (testbuildideal){
                erint "buildideallr", rb-lb, *lb->t();
            }
            assert(rb > lb);
            if (lb == rb-1){
                if (testbuildideal){
                    erint "setting", *lb->t(),"RIGHT to terminal";
                }
                lb->maketerminal(RIGHT);
                return;
            }
            Node *it = lb + (rb - lb)/2;
            
            if (testbuildideal){
                erint "setting value:",  *it->t();
            }
            
            lb->pointto(RIGHT, it);
            
            buildideall(lb+1, it);
            buildidealr(it, rb);
        }
    };
    
    uintt totaldepth(){
        if (empty()) return uintt(0);
        uintt mmm(0);
        r()->totaldepthbetter(mmm);
        return mmm;
    }
    
    uintt depth(Node *no){
        if (empty()){
            return uintt(0);
        }
        uintt dep = 1;
        const T *item = no->t();
        Node *it = r();
        while (item != it->t()){
            assert(it != it->nav(DIR(comp(*it->t(), *item))));
            it = it->nav(DIR(comp(*it->t(), *item)));
            ++dep;
        }
        return dep;
    }
    
    void Treeprintbetter(std::ostream &os=cout){
        if (empty()) return;
        assert(r() != nullptr);//nor would it
        r()->Treeprintbetter(os, 1, maxdepth());
    }
    
    uintt maxdepth(){
        return empty() ? 0 : r()->maxdepth();
    }
    
    enum TreeFUNC{
        MAKEIDEAL,
        REMEQ,
        REPLACE,
        REM
    };
    static const unsigned treefuns = REM+1;
    bool test[treefuns];
    
    void settest(){
        for (int i = 0; i != treefuns; ++i){
            test[i] = 0;
        }
        test[REM] = 0;
        test[REMEQ] = 0;
        test[REPLACE] = 0;
        test[MAKEIDEAL] = 0;
    }
    
    uintt root;
    Exar<Node> exar;
    COMP compare;
    Exar<Node*> memstore;
    
    uintt &ro(){
        return root;
    }
    const uintt &ro() const{
        return root;
    }
    
    Node *r() {
        return begin() + ro();
    }
    
    const Node *r() const{
        return begin() + ro();
    }
    
    Exar<Node> &t(){
        return exar;
    }
    const Exar<Node> &t() const{
        return exar;
    }
    
    Exar<Node*> &ms(){
        return memstore;
    }
    
    const Exar<Node*> &ms() const{
        return memstore;
    }

    Node *begin(){
        return t().t();
    }
    
    const Node *begin() const{
        return t().t();
    }
    
    Node *endmem(){
        return begin()+c();
    }
    
    const Node *endmem() const{
        return begin()+c();
    }
    
    uintt &s(){
        return t().s();
    }
    const uintt &s() const{
        return t().s();
    }
    
    uintt &c(){
        return t().c();
    }
    const uintt &c() const{
        return t().c();
    }
    
    bool empty() const{
        return t().empty();
    }
    
    Treeog(uintt a=uintt(0)){
        settest();
        t().init(a);
        //leaving r() unitialized
    }
    
    virtual Node *alloc(){
        if (ms().empty()){
            return &++t();
        }
        return --ms();
    }
    
    void dealloc(Node *no){
        ++ms() = no;
    }
    
    void setnodes(){
        
    }
    
    void newideal(){//needs work
        
        if (empty()){
            return;
        }
        Node *tee = new Node[size()], *tee2(tee), *teeend(tee+size()), *it(tee);
        r()->traverse([&tee2](const T &t){++tee2->t() = t;});
        ms().clear();
        delete [] t().t();
        t().t() = tee;
        assert(size() == t().size());
        makeideal();
    }
    
    void makeideal(){
        if (test[MAKEIDEAL]){
            erint "makeideal, size of:", size();
        }
        if (empty()) return;
        
        ro() = t().size()/2;
        if (test[MAKEIDEAL]){
            erint "root set to position", ro(), "with value of", *r()->t();
        }
        r()->buildideall(t().t(), r());
        r()->buildidealr(r(), t().t() + t().size());
    }
    
    void loadtree(Treeog<T> &tr){
        
        tr.clear();
        if (!empty()){
            r()->traverse([&tr](const T &t){++tr.t() = t;});
        }
        Node *it = tr.begin();
    }
    
    void loadexar(Exar<T> &ex){
        
        ex.clear();
        if (!empty()){
            r()->traverse([&ex](const T &t){++ex = t;});
        }
    }
    
    void ins(T &item){
        
        assert( s()== 0 || isinside(begin(), endmem(), r()) == 0);
        Node *spot = alloc();
        assert( s()< 2 || isinside(begin(), endmem(), r()) == 0);

        spot->init(item);

        place(spot);
        assert(isinside(begin(), endmem(), r()) == 0);
    }
    
    Node *find(const T &item, bool (*eqcomp)(const T &, const T &)){//find item or nullptr
        //for searching
        if (empty()){
            return nullptr;
        }
        Node *it = r();
        assert(it != nullptr);
        DIR dir;
        while (!eqcomp(*it->t(), item)){
            dir = DIR(comp(*it->t(), item));
            if (it->terminal(dir)){
                return nullptr;
            }
            it = it->nav(dir);//comvention
        }
        return it;
    }
    //for removing
    Node *findr(const T &item, bool (*eqcomp)(const T &, const T &)){//find item or nullptr and remove parent's link
        
        if (empty()){
            return nullptr;
        }
        if (eqcomp(*r()->t(), item)){
            return r();
        }
        Node *it = r(), *par;
        assert(it != nullptr);
        DIR dir;
        while (1){
            dir = DIR(comp(*it->t(), item));
            if (it->terminal(dir)){
                return nullptr;
            }
            par = it;
            it = it->nav(dir);//comvention
            if (eqcomp(*it->t(), item)){
                break;
            }
        }
        assert(par != nullptr);
        return it;
    }
    //for finding a spot to insert
    void findi(Node const * const newnode){//find point at which to add item
        
        if (empty()){
            r() = newnode;
            return;
        }
        Node *it = r();

    }
    
    Node *replace(Node *no){
        if (test[REPLACE]){
            erint "replacing";
        }
        if (no->dist(LEFT) != 0){
            if (no->dist(RIGHT) != 0){
                //both dirrections
                if (test[REPLACE]){
                    erint "children left and right";
                }
                Node *it = no->nav(LEFT), *itlast = nullptr;
                
                while (it->dist(RIGHT) != uintt(0)){//unsymetrical
                        itlast = it;
                        it = it->nav(RIGHT);
                }
                if (itlast != nullptr){
                    itlast->pointto(RIGHT, it->nav(LEFT));
                    it->pointto(LEFT, no->nav(LEFT));
                }
                it->pointto(RIGHT, no->nav(RIGHT));
                return it;
            }
            else {
                if (test[REPLACE]){
                    erint "done replacing, left child";
                }
                return no->nav(LEFT);
            }
        }
        else if (no->dist(RIGHT) != uintt(0)){
            if (test[REPLACE]){
                erint "done replacing, right child";
            }
            return no->nav(RIGHT);
        }
        if (test[REPLACE]){
            erint "done replacing, no children";
        }
        return nullptr;
    }
    
    void clear(){
        s() = uintt(0);
        ms().s() = uintt(0);
    }
    
    bool remeq(const T &item, bool (*eqcomp)(const T &, const T &) = _equal){
        if (test[REMEQ]){
            erint "remeqing", item;
        }
        if (empty()){
            if (test[REMEQ]){
                erint "done remeqing, didnt find it, empty";
            }
            return false;
        }
        if (eqcomp(*r()->t(), item)){
            
            Node *nod = replace(r());
            ++ms() = r();
            if (nod == nullptr){
                if (test[REMEQ]){
                    erint "Tree now empty";
                }
                clear();
                assert(empty());
            }
            else {
                if (test[REMEQ]){
                    cout << "changing root from position " << ro();
                }
                ro() = nod - begin();
                if (test[REMEQ]){
                    erint " to", ro(), "which is", *r()->t();
                }
            }
            if (test[REMEQ]){
                erint "done remeqing, found it";
            }
            return true;
        }
        Node *it = r(), *itlast;
        intt *trav;
        while (!eqcomp(*it->t(), item)){
            if (test[REMEQ]){
                erint "traveling", (comp(*it->t(), item) ? "left" : "right");
            }
            trav = &it->dist(DIR(comp(*it->t(), item)));
            if (*trav == 0){
                if (test[REMEQ]){
                    erint "done remeqing, didnt find it";
                }
                return false;
            }
            itlast = it;
            it += *trav;
        }
        Node *nod = replace(it);
        if (nod == nullptr){
            itlast->dist(DIR(comp(*itlast->t(), item))) = intt(0);
            
        }
        else {
            itlast->pointto(DIR(comp(*itlast->t(), item)), nod);
            assert(itlast->dist(DIR(comp(*itlast->t(), item))) != intt(0));
        }
        ++ms() = it;
        if (test[REMEQ]){
            erint "done remeqing, found it";
        }
        return true;
    }
    
    bool remex(const T &item){//could try derefing items with fnptr
        return remeq(item, _equalmem);
    }
    
    friend std::ostream &operator<<(std::ostream &os, const Treeog &tree){
        if (!tree.empty()){
            tree.r()->traverse([&os](const T& item){
                os << item << " ";
            });
        }
        return os;
    }
    
    const uintt size() const{
        return t().s() - ms().s();
    }
    
    //testfunctions
    struct Testobj{
        Exar<T> keep, eint;
        Treeog<T> tree;
        
        Testobj(){}
    };
    
    template <typename F>
    bool operator==(const Exar<F> &exarf) const{
        if (empty()) return exarf.empty();
        bool br = true;
        const F *fit = exarf.begin();
        r()->traverse([&br, &fit, &exarf](const T &t){
            erint *fit, t, fit - exarf.begin();
            if (*fit != t){
                br = false;
            }
            ++fit;
        });
        return br;
    }
    
    static uintt idealtotaldepth(uintt num) {
        uintt i(1), j(0), dep(1), tdep(0);
        bool breakbool = false;
        while (1){
            if (i > num - j){
                i = num - j;
                breakbool=true;
            }
            j += i;
            //cout << "tdep from:"<<  tdep;
            tdep += dep*i;
            
             //cout << " to " << tdep << endl;
            //erint dep, i;
            if (breakbool == true){
                break;
            }
            ++dep;
            i <<= 1;
        }
        return tdep;
    }
    
    uintt idealtotaldepth() const{
        return idealtotaldepth(size());
    }
    
    static uintt idealmaxdepth(uintt num){
        uintt bits(0);
        while (num != 0){
            num >>= 1;
            ++bits;
        }
        return bits;
    }
    
    uintt idealmaxdepth(){
        return idealmaxdepth(size());
    }
    
    static bool testins(std::ostream &os=cout){
        Exar<int> keep, eint;
        const uintt numtrees=50;
        Treeog<int> tree[numtrees];
        
        uintt tsize=1000;
        for (int j = 0; j != numtrees; ++j){
            for (int i = 0; i != tsize; ++i){
                int &nint = *new int(rand()%1000);
                ++keep = nint;
                tree[j].ins(nint);
            }
            tsize += 1000;
            uintt td(0);
            tree[j].r()->totaldepthbetter(td);
            erint tsize, td, tree[j].idealtotaldepth(), double(td)/tree[j].size(), double(tree[j].idealtotaldepth())/tree[j].size(), double(td)/tree[j].size()-double(tree[j].idealtotaldepth())/tree[j].size();
        
        }
        return true;
    }
    
    void printstats(std::ostream &os=cout){
        os << totaldepth() << " " << idealtotaldepth() << " " << double(totaldepth())/size() << " " << double(idealtotaldepth())/size() << " " << double(totaldepth())/size()-double(idealtotaldepth())/size();
    }
    
private:
    
    void place(Node *spot){
        if (s() == uintt(1)){
            ro() = spot-begin();
            assert(spot-begin() == 0);
            assert(isinside(begin(), endmem(), r()) == 0);
            assert(isinside(begin(), endmem(), spot) == 0);
            return;
        }
        assert(isinside(begin(), endmem(), r()) == 0);
        Node *it = r();
        assert(isinside(begin(), endmem(), it) == 0);
        DIR dir;
        while (1){
            //it
            //Node::DIR d = Node::LEFT;
            assert(isinside(begin(), endmem(), it) == 0);
            dir = DIR(comp(*it->t(), *spot->t()));
            if (it->terminal(dir)){
                break;
            }
            it = it->nav(dir);
        }
        it->pointto(dir, spot);
        assert(it->nav(dir) == spot);
    }


};

template <typename T, bool (*comp)(const T&, const T&)=_less, typename intt=int, typename uintt=unsigned>
struct Tree2 : Treeog<T, comp, intt>{//with passive reorginization upon exar expands
    
    using Treeog<T, comp, intt>::t;
    using Treeog<T, comp, intt>::ms;
    using Treeog<T, comp, intt>::makeideal;
    using Treeog<T, comp, intt>::empty;
    using typename Treeog<T, comp, intt>::Node;
    
    enum TREE2FUNC{
        ALLOC,
        EXPAND
    };
    static const unsigned tree2funs = EXPAND+1;
    bool test[tree2funs];
    
    void settest(){
        for (int i = 0; i != tree2funs; ++i){
            test[i] = 0;
        }
        test[EXPAND] = 0;
        test[ALLOC] = 0;
    }
    
    void expand(uintt a=0){
        if (test[EXPAND]){
            erint "treeexpanding";
        }
        
        if (a==0){
            assert(t().full());
            assert(t().c() < t().s() * 2 || (t().c() == t().s() && t().c() == uintt(0)));
            if (test[EXPAND]){
                cout << "c() set from " << t().c();
            }
            t().c() = (t().s() == uintt(0) ? 1 : t().s()*2);
        }
        if (test[EXPAND]){
            erint " to", t().c();
        }
        Node *newnode = new Node[t().c()];
        uintt keep(0);
        if (!empty()) this->r()->traverse([&newnode, &keep](T &te){
            (newnode+keep)->t() = &te;
            ++keep;
        });
        delete [] t().t();
        t().t() = newnode;
        makeideal();
    }
    
    Tree2(uintt a=uintt(0)):Treeog<T, comp, intt, uintt>(a){
        settest();
    }
    
    typename Treeog<T, comp, intt>::Node *alloc(){
        if (test[ALLOC]){
            erint "Tree2 alloc";
        }
        if (ms().empty()){
            if (t().full()){
                expand();
            }
            return &++t();
        }
        return --ms();
    }
    
    static bool tester(std::ostream &os=cout){
        
        
        /*for (int i = 0; i != 15; ++i){
            erint Tree<int>::idealmaxdepth(i);
        }
        for (int i = 0; i != 15; ++i){
            erint Tree<int>::idealtotaldepth(i);
        }*/

        Tree2<int> tree;
        for (int i = 0; i != 32; ++i){
            //erint "ins ", i;
            tree.ins(*new int(rand()%100));
            //erint "tree is not empty", tree.empty(), tree.size(), "just added", i ;
        }
        
        tree.Treeprintbetter();
        tree.printstats();
        
        tree.makeideal();
        
        tree.Treeprintbetter();
        tree.printstats();
        return true;
    }
    
    static bool testins2(std::ostream &os=cout){
        Exar<int> keep, eint;
        const uintt numtrees=50;
        Tree2<int> tree[numtrees];
        
        
        uintt tsize=1000;
        for (int j = 0; j != numtrees; ++j){
            for (int i = 0; i != tsize; ++i){
                int &nint = *new int(rand()%1000);
                ++keep = nint;
                tree[j].ins(nint);
            }
            tsize += 1000;
            uintt td(0);
            tree[j].r()->totaldepthbetter(td);
            erint tsize, td, tree[j].idealtotaldepth(), double(td)/tree[j].size(), double(tree[j].idealtotaldepth())/tree[j].size(), double(td)/tree[j].size()-double(tree[j].idealtotaldepth())/tree[j].size();
            
        }
        return true;
    }
};

template <typename intt=int, typename uintt=unsigned, uintt uinttmax = UINT_MAX, typename buintt=unsigned long, buintt buinttmax=ULONG_MAX>
struct Exn{
    
    Exar<uintt> num;
    
    Exar<uintt> &n(){
        return num;
    }
    
    const Exar<uintt> &n() const{
        return num;
    }
    
    void zero(){
        n().clear();
    }
    
    uintt &d(){
        return n().s();
    }
    const uintt &d() const{
        return n().s();
    }
    uintt &c(){
        return n().c();
    }
    const uintt &c() const{
        return n().c();
    }
    uintt &t(){
        return n().t();
    }
    const uintt &t() const{
        return n().t();
    }
    
    Exn(uintt val = uintt(0), uintt digits = uintt(0), uintt cap = uintt(0)){
        assert(digits >= cap);
        assert(val <= digits);
        n().init(cap);
        d() = digits;
        if (digits != uintt(0)){
            *(n().t()+digits) += val;
            //n()[digits] += val;
        }
    }
    Exn(const Exn &ex){
        n().init(ex.c());
        d() = ex.s();
        copy(t(), ex.t(), ex.t()+ex.s());
    }
    
    void addto(const Exn &ex){
        uintt *it = t(), *it2 = ex.t(), *it2end = ex.end();
        while (it2 != it2end){
            
        }
    }
    
    void add(const Exn &ex){
        if (c() < ex.c()){
            n().expand(ex.c()+1);
        }
        else if (d() == c()){
            n().expand(c()+1);
        }
        else {
            assert(d() < c());
        }
    }
};

template <typename T, bool (*comp)(const T&, const T&)=_less, typename intt=int, typename uintt=unsigned>
struct DTree{
    
    enum DTREEFUNC{
        TREEPRINT,
        TOTALDEPTH,
        BUILDIDEAL,
        TRAVERSE
    };
    static const unsigned nodefuns = TRAVERSE+1;
    bool test[nodefuns];
    
    void settest(){
        for (int i = 0; i != nodefuns; ++i){
            test[i] = 0;
        }
        test[TREEPRINT] = 0;
        test[TOTALDEPTH] = 0;
        test[TRAVERSE] = 0;
        test[BUILDIDEAL] = 1;
    }

    enum DIR{
        LEFT=0,
        RIGHT
    };
    
    static DIR anti(DIR d){
        return DIR(!bool(d));
    }
    
    static constexpr const uintt DIRnum = RIGHT+1;
    struct Node{
        
        enum NODEFUNC{
            TREEPRINT,
            TOTALDEPTH,
            BUILDIDEAL,
            TRAVERSE
        };
        static const unsigned nodefuns = TRAVERSE+1;
        bool test[nodefuns];
        
        void settest(){
            for (int i = 0; i != nodefuns; ++i){
                test[i] = 0;
            }
            test[TREEPRINT] = 0;
            test[TOTALDEPTH] = 0;
            test[TRAVERSE] = 0;
            test[BUILDIDEAL] = 1;
        }
        
        void pointto(DIR dir, Node *it){
            kid(dir) = it;
        }

        Node *child[DIRnum];
        T *theitem;
        
        Node *&kid(DIR d){
            return child[d];
        }
        Node * const &kid(DIR d) const{
            return child[d];
        }
        
        T *&item(){
            return theitem;
        }
        T * const &item() const{
            return theitem;
        }
        
        void init(){
            kid(LEFT) = kid(RIGHT) = nullptr;
        }
        
        void init(T &ite){
            item() = &ite;
            init();
        }
        
        void maketerminal(DIR dir){
            kid(dir) = nullptr;
        }
        
        bool terminal(DIR dir) const {
            return kid(dir) == nullptr;
        }
        
        Node(){
            init();
        }
        
        Node(T &item){
            init(item);
        }
        
        void totaldepth(uintt &sum, uintt level=1){
            
            assert(this != nullptr);
            sum += level;
            if (!terminal(LEFT)){
                kid(LEFT)->totaldepth(sum, level + 1);
            }
            if (!terminal(RIGHT)){
                kid(RIGHT)->totaldepth(sum, level + 1);
            }
        }
        
        uintt totaldepthbetter() const {
            if (this == nullptr){
                return 0;
            }
            return 3 + totaldepthbetter(kid(LEFT)) + totaldepthbetter(kid(RIGHT));
        }
        
        uintt depthbetter() const {
            if (this == nullptr){
                return 0;
            }
            return 1 + max(kid(LEFT)->depthbetter(), kid(RIGHT)->depthbetter());
        }
        
        uintt depth() const {
            assert(this != nullptr);
            if (terminal(LEFT)){
                if (terminal(RIGHT)){
                    return 1;
                }
                return 1 + kid(RIGHT)->depth();
            }
            if (terminal(RIGHT)){
                return 1 + kid(LEFT)->depth();
            }
            return 1 + max(kid(LEFT)->depth(), kid(RIGHT)->depth());
        }
        
        template <typename FN>
        void traverse(FN fn) {
            if (!terminal(LEFT)){
                kid(LEFT)->traverse(fn);
            }
            fn(*item());
            if (!terminal(RIGHT)){
                kid(RIGHT)->traverse(fn);
            }
        }
        
        template <typename FN>
        void traverse(FN fn) const {
            if (!terminal(LEFT)){
                kid(LEFT)->traverse(fn);
            }
            fn(*item());
            if (!terminal(RIGHT)){
                kid(RIGHT)->traverse(fn);
            }
        }
        
        template <typename FN>
        void traversen(FN fn) {
            if (!terminal(LEFT)){
                kid(LEFT)->traversen(fn);
            }
            fn(*this);
            if (!terminal(RIGHT)){
                kid(RIGHT)->traversen(fn);
            }
        }
        
        template <typename FN>
        void traversen(FN fn) const {
            if (!terminal(LEFT)){
                kid(LEFT)->traversen(fn);
            }
            fn(*this);
            if (!terminal(RIGHT)){
                kid(RIGHT)->traversen(fn);
            }
        }
        
        template <typename FN>
        void traversebetter(FN fn){
            if (this == nullptr){
                return;
            }
            kid(LEFT)->traverse(fn);
            fn(item());
            kid(RIGHT)->traverse(fn);
        }
        
        void treeprint(uintt mdepth=uintt(1), uintt level=uintt(1), std::ostream &os=cout){
            if (test[TREEPRINT]){
                erint "TREEprint", mdepth;
            }
            assert(level <= mdepth);
            
            if (!terminal(LEFT)){
                kid(LEFT)->treeprint(mdepth, level+1, os);
            }
            printspacez(2*(mdepth - level), os);
            os << *item() << endl;
            if (!terminal(RIGHT)){
                kid(RIGHT)->treeprint(mdepth, level+1, os);
            }
            if (test[TREEPRINT]){
                erint "treeprint";
            }

        }
        
        static constexpr const bool testbuildideal=0;
        
        static void buildideall(Node **lb, Node **rb){
            if (testbuildideal){
                erint "buildideall", (*rb)-(*lb), *(*rb)->item();
            }
            if (lb == rb){
                if (testbuildideal){
                    erint "setting", *(*rb)->item(),"LEFT to terminal";
                }
                (*rb)->maketerminal(LEFT);
                return;
            }
            
            Node **it = lb + (rb - lb)/2;
            if (testbuildideal){
                erint "setting value:",  *(*it)->item();
            }
            
            (*rb)->pointto(LEFT, *it);
            
            buildideall(lb, it);
            buildidealr(it, rb);
        }
        
        static void buildidealr(Node **lb, Node **rb){
            if (testbuildideal){
                erint "buildideallr", (*rb)-(*lb), *(*lb)->item();
            }
            assert(rb > lb);
            if (lb == rb-1){
                if (testbuildideal){
                    erint "setting", *(*lb)->item(),"RIGHT to terminal";
                }
                (*lb)->maketerminal(RIGHT);
                return;
            }
            Node **it = lb + (rb - lb)/2;
            
            if (testbuildideal){
                erint "setting value:",  *(*it)->item();
            }
            
            (*lb)->pointto(RIGHT, *it);
            
            buildideall(lb+1, it);
            buildidealr(it, rb);
        }
        
    };//possible upgrade item[5]
    
    const DTree &cons() const {
        return static_cast<const DTree &>(*this);
    }
    
    void makeideal(){
        
        if (empty()){
            return;
        }
        Exar<Node *> stor;
        traversen([&stor](Node &no){
            ++stor = &no;
        });
        assert(stor.size() == size());
        Node **mid = stor.begin() + stor.size()/2;
        root() = *mid;
        
        Node::buildideall(stor.begin(), mid);
        Node::buildidealr(mid, stor.end());
    }
    
    Node *roo;
    
    Node *&root(){
        return const_cast<Node *&>(cons().root());
    }
    Node * const &root() const{
        return roo;
    }
    
    void init(){
        //erint "init";
        root() = nullptr;
    }
    
    DTree(){
        init();
    }
    
    enum TreeFncs{
        FIND,
        INS,
        REM
    };
    
    uintt depth() const {
        return empty() ? uintt(0) : root()->depth();
    }
    
    uintt totaldepth() const {
        if (empty()){
            return uintt(0);
        }
        uintt sum(0);
        root()->totaldepth(sum);
        return sum;
    }
    
    uintt size() const {
        if (empty()){
            return uintt(0);
        }
        uintt cou(0);
        root()->traverse([&cou](const T &ite){
            ++cou;
        });
        return cou;
    }
    
    double depthave() const {
        return double(totaldepth())/size();
    }
    
    void stats(std::ostream &os){
        os << "size: " << size() << " depth: " << depth() << " ideal depth: " << Treeog<int>::idealmaxdepth(size()) << " depth ave: " << depthave() << " ideal depth ave: " << double(Treeog<int>::idealtotaldepth(size()))/size() << " total depth: " << totaldepth() << "\n";
    }

    bool empty() const {
        return root() == nullptr;
    }
    
    const Node *searchfi(const T &that, bool (*equalcomp)(const T &, const T &) = &_equal) const{
        //can be empty
        const Node *it = root();
        DIR dir;
        while (1){
            if (!it) break;
            if (equalcomp(*it->item(), that)){
                break;
            }
            dir = DIR(comp(*it->item(), that));
            it = it->kid(dir);
        }
        return it;
    }
    
    Node *searchfi(const T &that, bool (*equalcomp)(const T &, const T &) = &_equal) {
        
        return const_cast<Node *>(static_cast<const DTree &>(*this).searchfi(that, equalcomp));
    }
    
    Node *&searchin(T & that){
        
        if (empty()){
            return root();
        }
        Node *it = root();
        DIR dir;
        while (1){
            dir = DIR(comp(*it->item(), that));
            if (it->terminal(dir)){
                break;
            }
            it = it->kid(dir);
        }
        return it->kid(dir);
    }
    
    Node *&searchin(T & that, uintt &dep){

        assert(dep == 0);
        if (empty()){
            return root();
        }
        Node *it = root();
        DIR dir;
        while (1){
            ++dep;
            dir = DIR(comp(*it->item(), that));
            if (it->terminal(dir)){
                break;
            }
            it = it->kid(dir);
        }
        return it->kid(dir);
    }
    
    Node *&searchre2(const T &that, bool (*equalcomp)(const T &, const T &) = &_equal){
        Node **it, **oldit;
        *it = root();
        assert(!empty());
        DIR dir;
        while (1){
            
            if (equalcomp(it->item(), that)){
                return *it;
            }
            dir = comp(*&it->item(), that);
            assert(!(*it)->terminal(dir));
            oldit = it;
            it = (*it)->kid(dir);
            assert(*it == (*oldit)->kid(dir));
        }
        return it;
    }
    
    Node **searchre(const T &that, bool (*equalcomp)(const T &, const T &) = &_equal){
        Node **it, **oldit;
        *it = root();
        DIR dir;
        while (1){
            if (it == nullptr){
                break;
            }
            if (equalcomp((*it)->item(), that)){
                break;
            }
            dir = comp(*&it->item(), that);
            if ((*it)->terminal(dir)){
                return nullptr;
            }
            oldit = it;
            it = (*it)->kid(dir);
            assert(*it == (*oldit)->kid(dir));
        }
        return it;
    }

    void ins(T &item){
        
        searchin(item) = new Node(item);
    }
    
    template <typename FN>
    void traverse(FN fn) const {
        if (!empty()){
            root()->traverse(fn);
        }
    }
    
    template <typename FN>
    void traverse(FN fn) {
        
        //cons().traverse(fn);//dont think you want this if fn will change item()
        //return;
        if (!empty()){
            root()->traverse(fn);
        }
    }
    
    template <typename FN>
    void traversen(FN fn) const {
        if (!empty()){
            root()->traversen(fn);
        }
    }
    
    template <typename FN>
    void traversen(FN fn) {
        
        //cons().traverse(fn);//dont think you want this if fn will change item()
        //return;
        if (!empty()){
            root()->traversen(fn);
        }
        //if ideal, musto only go through array1
    }
    
    const Node *find(const T &ite) const{
        return searchfi(ite);
    }
    
    Node *find(const T &ite) {
        return const_cast<Node *>(cons().find(ite));
    }
    
    void treeprint(std::ostream &os=cout){
        
        if (empty()){
            return;
        }
        root()->treeprint(depth(), 1, os);
    }
    
    static bool tester(std::ostream &os=cout){
        
        
        for (int j = 100; j != 10000; j+= 100){
            DTree<int> tree;
            //erint "hello";
            //erint tree.empty();
            //erint "yowser";
            for (int i = 0; i != j; ++i){
                tree.ins(*new int(rand()%10000));
                
                
            }
            //tree.treeprint();
            tree.stats(os);
            //os << tree << '\n';
            
            tree.makeideal();
            
            //tree.treeprint();
            tree.stats(os);
            os << endl;
            //os << tree << '\n';
        }
            
        for (int i = 0; i != 10; ++i){
            //assert(tree.find(i));
        }
        return true;
    }
    
    std::ostream &print(std::ostream &os) const {
        
        traverse([&os](const T &ite){
            os << ite << ' ';
        });
        return os;
    }
    
    friend ostream &operator<<(std::ostream &os, const DTree &dt){
        return dt.print(os);
    }
    
    //return address of adjactent decendant
    Node *getnext(DIR dir){
        Node *it = kid(dir);
        DIR adir = anti(dir);
        if (it) while (1){
            if (it->terminal(adir)){
                break;
            }
            it = it->kid(adir);
        }
        return it;
    }
    
    Node *rem(const T &item){
        
    }
    
};

struct Treema{
    
    struct Node{
        
    };
    
};

