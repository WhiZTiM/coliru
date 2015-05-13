#include "/Archive2/61/8a7158c571e83b/main.cpp"
#include <typeinfo>


template <typename T>//, typename uintt=unsigned, typename intt=int>
using Tree = DTree<T>;//, uintt, intt>;
typedef std::string string_t;

template <typename useT>
useT &uncons(const useT &ut){
    return const_cast<useT &>(ut);
}

template <typename useT>
useT *uncons(const useT *ut){
    return const_cast<useT *>(ut);
}

bool isInside(const string_t::const_iterator &it, const string_t &str){
    return it < str.end() && it >= str.begin();
}

bool isPlus(const char ch){
    return ch == '+';
}

bool isStar(const char ch){
    return ch == '*';
}

bool isDash(const char ch){
    return ch == '-';
}

bool isSlash(const char ch){
    return ch == '/';
}

bool isCarrot(const char ch){
    return ch == '^';
}

bool isAnd(const char ch){
    return ch == '&';
}

enum BINARYOPERATION{
    NOTBINARY=-1,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    POWER,
    LOGARITHM
};

BINARYOPERATION isBinary(const char ch){
    switch (ch){
        case '+':
            return ADD;
        case '-':
            return SUBTRACT;
        case '*':
            return MULTIPLY;
        case '/':
            return DIVIDE;
        case '^':
            return POWER;
        case '&':
            return LOGARITHM;
        default:
            return NOTBINARY;
    }
    
    //return isPlus(ch) || isDash(ch) || isStar(ch) || isSlash(ch) || isCarrot(ch) || isAnd(ch);
}

bool isNumeric(const char ch){
    return ch >= '0' && ch <= '9';
}

bool isAlphabeticLower(const char ch){
    return ch >= 'a' && ch <= 'z';
}

bool isAlphabeticUpper(const char ch){
    return ch >= 'A' && ch <= 'Z';
}

bool isAlphabetic(const char ch){
    return isAlphabeticLower(ch) && isAlphabeticUpper(ch);
}

bool isPeriod(const char ch){
    return ch == '.';
}

template <typename uintt=unsigned int>
uintt charToUintt(const char ch){
    return ch - '0';
}

bool whiteSpace(const char ch){
    return ch <= ' ';
}

template <typename uintt=unsigned int, typename intt=int>
bool addDecimal(double &number, string_t::const_iterator &it, const string_t &str, uintt base=uintt(10)){
    assert(isInside(it, str));
    assert(isNumeric(*it));
    
    double deckeep = double(1)/base;
    while (1){
        number += charToUintt(*it)*deckeep;
        ++it;
        if (!isInside(it, str)){
            return false;
        }
        if (!isNumeric(*it)){
            break;
        }
        deckeep /= base;
    }
    return true;
}

template <typename uintt=unsigned int, typename intt=int>
bool getNumber(double &number, string_t::const_iterator &it, const string_t &str, uintt base=uintt(10)){
    assert(isInside(it, str));
    assert(isNumeric(*it));
    assert(number == double(0));
    while (1) {
        number += charToUintt(*it);
        ++it;
        if (!isInside(it, str)){
            return false;
        }
        if (!isNumeric(*it)){
            if (isPeriod(*it)){
                ++it;
                if (!isInside(it, str)){
                    return false;
                }
                if (isNumeric(*it)){
                    return addDecimal(number, it, str, base);
                }
            }
            break;
        }
        number *= base;
    }
    return true;
}

template <typename Number_t = double, typename uintt=unsigned int, typename intt=int>
struct Expression{
    
    enum DIRECTION{
        LEFT,
        RIGHT
    };
    static const uintt DIRECTIONnum = RIGHT+1;
    
    enum EXPRESSIONTYPE{
        NUMBER,
        UNARY,
        BINARY,
    };
    
    static const uintt EXPRESSIONTYPEnum = BINARY+1;
    
    template <typename Truet>
    struct OperatorBase;
    
    struct AtomicExpression;
    struct BinaryOperator;
    
   // BinaryOperator *(*bofn)();
    //void *mypointer;
    
    struct OperatorStorage{
        
        EXPRESSIONTYPE expressionTyped;
        
        const EXPRESSIONTYPE &expressionType() const{
            return expressionTyped;
        }
        EXPRESSIONTYPE &setExpressionType(){
            return uncons(static_cast<const OperatorStorage *>(this)->expressionType());
            // return const_cast<Number_t &>(cons()->value());
        }
        
        template <typename Truet>
        operator OperatorBase<Truet>(){
            return *static_cast<OperatorBase<Truet> *>(this);
        }
        
        //virtual const OperatorStorage *getit() const=0;
        template <typename Truet>
        const OperatorBase<Truet> *getit() const{
            return static_cast<const OperatorBase<Truet> *>(this);
        }
        template <typename Truet>
        OperatorBase<Truet> *getit(){
            return static_cast<OperatorBase<Truet> *>(this);
        }
        
        virtual OperatorStorage *getit2()=0;
        
        template<typename Truet>
        const OperatorBase<Truet> *herey() const{
            switch (expressionType()){
                case NUMBER:
                    return static_cast<const OperatorBase<AtomicExpression>*>(this);
                case BINARY:
                    return static_cast<const OperatorBase<BinaryOperator>*>(this);
            }
        }
    };
    
    template <typename Truet>
    static Truet *gotchya(OperatorStorage *ops){
        return static_cast<Truet *>(ops);
    }
    template <typename Truet>
    static const Truet *gotchya(const OperatorStorage *ops){
        return static_cast<const Truet *>(ops);
    }
    
    template <typename Truet>
    struct OperatorBase : OperatorStorage{
        
        OperatorBase<Truet> *getit2(){
           // erint "ello", typeid(this).name();
            //reinterpret_cast<OperatorBase<Truet> *>(mypointer) = this;
            return this;
        }
        /*const OperatorBase *getit() const{
            erint"hello";
            return static_cast<const OperatorBase *>(this);
        }
        OperatorBase *getit(){
            erint"hello";
            return static_cast<OperatorBase *>(this);
        }*/
       // typedef Truet hellor;
        const Truet *cons() const {
            return static_cast<const Truet *>(this);
        }
        Truet *getT(){
            return uncons(cons());
        }
    
        OperatorBase(){
            //erint "OBing";
            init();
        }
        void init(){
            getT()->initf();
        }
    
        bool operator<(const OperatorBase &ae) const {
            return true;
        }
        bool operator>(const OperatorBase &ae) const {
            return false;
        }
        bool operator<=(const OperatorBase &ae) const {
            return !(*this > ae);
        }
        bool operator>=(const OperatorBase &ae) const {
            return !(*this < ae);
        }
        bool operator==(const OperatorBase &ae) const {
            return true;
        }
        bool operator!=(const OperatorBase &ae) const {
            return !(*this == ae);
        }
        
        void print(std::ostream &os) const{
            cons()->printf(os);
        }
        
        friend std::ostream &operator<<(std::ostream &os, const OperatorBase &ae){
            ae.print(os);
            return os;
        }
    };
    
    struct AtomicExpression : OperatorBase<AtomicExpression>{
        
        using OperatorBase<AtomicExpression>::cons;
        using OperatorBase<AtomicExpression>::setExpressionType;
        using OperatorBase<AtomicExpression>::init;
        
        //variable\
        //--name\
        //--
        //number
        
        Number_t valued;
        
        const Number_t &value() const{
            return valued;
        }
        Number_t &setValue(){
            return uncons(cons()->value());
           // return const_cast<Number_t &>(cons()->value());
        }
        
        AtomicExpression(): OperatorBase<AtomicExpression>(){
            //erint "AEing";
        }
        
        void initf(){
            //erint "initfing";
            setExpressionType() = NUMBER;
            setValue() = Number_t(0);
            assert(value() == Number_t(0));
            //erint value(), Number_t(0);
        }
        
        enum STUFFS{
            PRINTF
        };
        constexpr static const bool test[2] = {};
        void printf(std::ostream &os) const{
            if (test[PRINTF]) erint "aqui";
            os << value();
        }
    };
    
    static const uintt BINARYOPERATIONnum = LOGARITHM+1;
    
    struct BinaryOperator : OperatorBase<BinaryOperator> {
        
        using OperatorBase<BinaryOperator>::cons;
        using OperatorBase<BinaryOperator>::setExpressionType;
        
        AtomicExpression *childd[DIRECTIONnum];
        
        const AtomicExpression *&child(DIRECTION dir) const{
            return childd[dir];
        }
        AtomicExpression *&child(DIRECTION dir){
            return uncons(cons()->child(dir));
        }
        
        BinaryOperator(): OperatorBase<BinaryOperator>(){}
        
        
        void initf(){
            setExpressionType() = BINARY;
        }
        
        BINARYOPERATION operationd;
        
        const BINARYOPERATION &operation() const{
            return operationd;
        }
        BINARYOPERATION &setOperation(){
            return uncons(cons()->operation());
            // return const_cast<Number_t &>(cons()->value());
        }
        
        
    };
    
    const Expression<> *cons() const {
        return static_cast<const Expression<> *>(this);
    }
    
    Tree<AtomicExpression> expressiond;
    
    const Tree<AtomicExpression> &expression() const{
        return expressiond;
    }
    
    Tree<AtomicExpression> &expression(){
        return const_cast<Tree<AtomicExpression> &>(cons()->expression());
    }
    
    static bool skipWhiteSpace(string_t::const_iterator &it, const string_t &str){
        assert(isInside(it, str));
        while (whiteSpace(*it)){
            ++it;
            if (!isInside(it, str)){
                return false;
            }
        }
        return true;
    }
    
    static bool nextSymbol(string_t::const_iterator &it, const string_t &str){
        return skipWhiteSpace(it, str);
    }

    static void printit(OperatorStorage &ops){
        //erint "it is", ops.expressionType();
        //erint *ops->herey();
        //erint *gotchya<OperatorBase<AtomicExpression>>(ops);
        //erint *(ops->getit());
        //erint *(ops->getit<OperatorBase<AtomicExpression>());
        //erint static_cast<const OperatorBase<AtomicExpression> &>(*(ops->getit()));
        //nrint "heya", typeid(ops).name(), typeid(ops.getit2()).name(), typeid(OperatorStorage *).name(), typeid(OperatorStorage).name(), typeid(OperatorBase<AtomicExpression>).name(), typeid(AtomicExpression).name();
        
        
        erint static_cast<const OperatorBase<AtomicExpression> &>(ops);
    }
    
    static void parce(const string_t &str){
        
        Exar<OperatorStorage *> getit;
        AtomicExpression *ae;
        BinaryOperator *bo;
        string_t::const_iterator it = str.begin();
        while (it != str.end()){
            
            if (!nextSymbol(it, str)){
                break;
            }
            
            if (isNumeric(*it)){
                ae = new AtomicExpression;
                ++getit = ae;
                if (!getNumber(ae->setValue(), it, str)){
                    printit(*getit.top());
                    break;
                }
                printit(*getit.top());
            }
            assert(!isNumeric(*it));
            assert(isInside(it, str));
            
            if (!nextSymbol(it, str)){
                break;
            }
            
            BINARYOPERATION bop = isBinary(*it);
            if (bop != NOTBINARY){
                bo = new BinaryOperator;
                ++getit = bo;
                bo->setOperation() = bop;
            }
            
            
        }
    }
    
};

int main(){
    erint "hello world";
    return 0;   
}