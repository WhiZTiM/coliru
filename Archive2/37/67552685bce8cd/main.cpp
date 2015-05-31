#include "/Archive2/87/2a2aee8929ae60/main.cpp"
#include <typeinfo>
#include <cmath>


template <typename T>//, typename uintt=unsigned, typename intt=int>
using Tree = DTree<T>;//, uintt, intt>;
typedef std::string string_t;


template <typename useT>
useT *&uncons2(const useT *const &ut){
    return const_cast<useT *&>(ut);
}

template <typename useT>
useT &uncons(const useT &ut){
    return const_cast<useT &>(ut);
}

template <typename useT>
useT *uncons(const useT *ut){
    return const_cast<useT *>(ut);
}

enum PARENTHESIS{
  CURVED,
  SQUARE,
  CURLY
};
static const unsigned PARENTHESISnum=CURLY+1;

enum PARENTHESISTYPE{
    OPENCURVED=0,
    CLOSECURVED,
    OPENSQUARE,
    CLOSESQUARE,
    OPENCURLY,
    CLOSECURLY
};
static const unsigned PARENTHESISTYPEnum=CLOSECURLY+1;
//

//assert(PARENTHESISTYPEnum == PARENTHESISnum*2);

bool isOpenCurved(const char ch){
    return ch == '(';   
}
bool isCloseCurved(const char ch){
    return ch == ')';   
}
bool isOpenSquare(const char ch){
    return ch == '[';   
}
bool isCloseSquare(const char ch){
    return ch == ']';   
}
bool isOpenCurly(const char ch){
    return ch == '{';   
}
bool isCloseCurly(const char ch){
    return ch == '}';   
}

bool isOpenParenthesis(const char ch){
    return isOpenCurved(ch) || isOpenSquare(ch) || isOpenCurly(ch);   
}

bool isCloseParenthesis(const char &ch){
    return isCloseCurved(ch) || isCloseSquare(ch) || isCloseCurly(ch);   
}
bool isCurved(const char ch){
    return isOpenCurved(ch) || isCloseCurved(ch);
}
bool isSquare(const char ch){
    return isOpenSquare(ch) || isCloseSquare(ch);
}
bool isCurly(const char ch){
    return isOpenCurly(ch) || isCloseCurly(ch);
}
bool isParenthesis(const char ch){
    return isCurved(ch) || isSquare(ch) || isCurly(ch);
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

enum EXPRESSIONTYPE{
    NUMBER=0,
    UNARY,
    BINARY
};

enum BINARYOPERATION{
    NOTBINARY=-1,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    POWER,
    LOGARITHM
};

char opChar(const BINARYOPERATION obs){
        switch (obs){
        case ADD:
            return '+';
        case SUBTRACT:
            return '-';
        case MULTIPLY:
            return '*';
        case DIVIDE:
            return '/';
        case POWER:
            return '^';
        case LOGARITHM:
            return '&';
        default:
        erint "no char for NOTBINARY";
            return NOTBINARY;
    }
        
}

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
    
    static const uintt EXPRESSIONTYPEnum = BINARY+1;
    
    template <typename Truet>
    struct OperatorBase;
    
    struct AtomicExpression;
    template <typename TrueT>
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
        
        size_t precedenced;
        
        const size_t &precedence() const{
            return precedenced;
        }
        size_t &setPrecedence(){
            return uncons(static_cast<const OperatorStorage *>(this)->precedence());
            // return const_cast<Number_t &>(cons()->value());
        }
        
        template <typename Truet>
        operator OperatorBase<Truet>(){
            return *static_cast<OperatorBase<Truet> *>(this);
        }
        
        virtual void print(std::ostream &os) const=0;
        virtual void printExp(std::ostream &os) const=0;
        
        friend std::ostream &operator<<(std::ostream& os, const OperatorStorage &ops){
            ops.printExp(os);
            return os;
        }
        
        virtual Number_t evaluate()=0;
    };
    
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
        
        template <typename FN>
        void traverse(FN fn) const {
            cons()->traversef(fn);
        }
        
        template <typename FN>
        void traverse(FN fn) {
            getT()->traversef(fn);
        }
        
        void printExp(std::ostream &os) const {
            //erint "printExping";
            traverse([&os](const OperatorStorage &ops){
                ops.print(os); os << " ";
            });
        }
        
        friend std::ostream &operator<<(std::ostream &os, const OperatorBase &ae){
            erint "helmo";
            ae.printExp(os);
            return os;
        }
        
        Number_t evaluate(){
            return getT()->evaluatef();
        }
    };
    
    struct AtomicExpression : OperatorBase<AtomicExpression>{
        
        using OperatorBase<AtomicExpression>::cons;
        using OperatorBase<AtomicExpression>::setExpressionType;
        using OperatorBase<AtomicExpression>::init;
        using OperatorBase<AtomicExpression>::setPrecedence;
        
        //variable
        //--name
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
        
        template <typename T>
        AtomicExpression(const T &t): OperatorBase<AtomicExpression>(){
            setValue() = t;    
        }
        
        AtomicExpression(): OperatorBase<AtomicExpression>(){
            //erint "AEing";
            setValue() = Number_t(0);
        }
        
        void initf(){
            //erint "initfing";
            setExpressionType() = NUMBER;
            setPrecedence() = size_t(0);
            //erint value(), Number_t(0);
        }
        
        enum STUFFS{
            PRINTF
        };
        constexpr static const bool test[2] = {0};
        void printf(std::ostream &os) const{
            
            if (test[PRINTF]) erint "aqui";
            os << value();
        }
        
        template <typename FN>
        void traversef(FN fn) const {
            //erint "outputting number";
            fn(*this);
        }
        
        template <typename FN>
        void traversef(FN fn) {
            fn(*this);
        }
        
        Number_t evaluatef(){
            return value();
        }
    };
    
    template <typename TrueT>
    struct BinaryOperator: OperatorBase<BinaryOperator<TrueT>> {
        
        const TrueT *getT2() const{
            return static_cast<const TrueT *>(this);   
        }
        TrueT *getT2(){
            return uncons(cons()->getT2());   
        }
        
        
        using OperatorBase<BinaryOperator>::cons;
        using OperatorBase<BinaryOperator>::setExpressionType;
        using OperatorBase<BinaryOperator>::setPrecedence;
        using OperatorBase<BinaryOperator>::precedence;
        
        static const uintt BINARYOPERATIONnum = LOGARITHM+1;

        static Number_t identity(const BINARYOPERATION bo){
            if (bo <= SUBTRACT){
               return Number_t(0);   
            }
            return Number_t(1);
        }
        Number_t identity(){
            return identity(operation());
        }
    
        OperatorStorage *childd[DIRECTIONnum];
        
        OperatorStorage * const &child(const DIRECTION dir) const{
            return childd[dir];
        }
        OperatorStorage *&setChild(const DIRECTION dir){
            return childd[dir];
            //return uncons2(cons()->child(dir));
        }
        
        BinaryOperator(): OperatorBase<BinaryOperator>(){}
        
        void initf(){
            setExpressionType() = BINARY;
            getT2()->initff();
        }
        
        BINARYOPERATION operationd;
        
        const BINARYOPERATION &operation() const{
            return operationd;
        }
        BINARYOPERATION &setOperation(){
            return uncons(cons()->operation());
            // return const_cast<Number_t &>(cons()->value());
        }
        
        DIRECTION associativeDirectiond;
        
        const DIRECTION &associativeDirection() const{
            return associativeDirectiond;
        }
        DIRECTION &setAssociativeDirection(){
            return uncons(cons()->associativeDirection());
            // return const_cast<Number_t &>(cons()->value());
        }
        
        void setOperation(const BINARYOPERATION bino){
            setPrecedence() = size_t(bino) + 1;
            setOperation() = bino;
            // return const_cast<Number_t &>(cons()->value());
        }
        
        static bool precedence(const BinaryOperator &boLast, const BinaryOperator &bo){
            assert(boLast.expressionType() == BINARY);
            assert(bo.expressionType() == BINARY);
            if (boLast.precedence() == bo.precedence()){
                return boLast.associativeDirection() == LEFT;
            }
            return boLast.precedence() > bo.precedence();//leftassociative
        }
        
        char opChar() const{
            return ::opChar(operation());   
        }
        
        template <typename FN>
        void traversef(FN fn) const {
            //erint "traversing binary";
            if (child(LEFT)->expressionType() == NUMBER){
                //erint "hrm";
                static_cast<AtomicExpression*>(child(LEFT))->traversef(fn);
                //erint "hrm2";
            }
            else {
                 static_cast<BinaryOperator*>(child(LEFT))->traversef(fn);
            }
            // erint "outputting binary";
            fn(*this);
            if (child(RIGHT)->expressionType() == NUMBER){
                static_cast<AtomicExpression*>(child(RIGHT))->traversef(fn);
            }
            else {
                 static_cast<BinaryOperator*>(child(RIGHT))->traversef(fn);
            }
        }
        template <typename FN>
        void traversef(FN fn) {
            if (child(LEFT)->expressionType() == NUMBER){
                //erint "hrm";
                static_cast<AtomicExpression*>(child(LEFT))->traversef(fn);
                //erint "hrm2";
            }
            else {
                 static_cast<BinaryOperator*>(child(LEFT))->traversef(fn);
            }
            // erint "outputting binary";
            fn(*this);
            if (child(RIGHT)->expressionType() == NUMBER){
                static_cast<AtomicExpression*>(child(RIGHT))->traversef(fn);
            }
            else {
                 static_cast<BinaryOperator*>(child(RIGHT))->traversef(fn);
            } 
        }
        
        Number_t evaluatef(){
            return getT2()->evaluateff();
        }
        
        void printf(std::ostream &os) const{
            //erint "aquii";
            getT2()->printff(os);
        }
    };
    
    struct Add: BinaryOperator<Add>{
        using BinaryOperator<Add>::child;
        using BinaryOperator<Add>::setAssociativeDirection;
        
        void initff(){
            setAssociativeDirection() = LEFT;   
        }
        
        void printff(std::ostream &os) const{
            os << ::opChar(ADD);    
        }
        
        Number_t evaluateff(){
            return (child(LEFT)->evaluate() + child(RIGHT)->evaluate());   
        }
    };
    
    struct Subtract: BinaryOperator<Subtract>{
        using BinaryOperator<Subtract>::child;
        using BinaryOperator<Subtract>::setAssociativeDirection;
        
        void initff(){
            setAssociativeDirection() = LEFT;   
        }
        void printff(std::ostream &os) const{
            os << ::opChar(SUBTRACT);    
        }
        
        Number_t evaluateff(){
            return (child(LEFT)->evaluate() - child(RIGHT)->evaluate());   
        }
    };
    
    struct Multiply: BinaryOperator<Multiply>{
        using BinaryOperator<Multiply>::child;
        using BinaryOperator<Multiply>::setAssociativeDirection;
        
        void initff(){
            setAssociativeDirection() = LEFT;   
        }
        void printff(std::ostream &os) const{
            os << ::opChar(MULTIPLY);    
        }
        
        Number_t evaluateff(){
            return (child(LEFT)->evaluate() * child(RIGHT)->evaluate());   
        }
    };
    
    struct Divide: BinaryOperator<Divide>{
        using BinaryOperator<Divide>::child;
        using BinaryOperator<Divide>::setAssociativeDirection;
        
        void initff(){
            setAssociativeDirection() = LEFT;   
        }
        void printff(std::ostream &os) const{
            os << ::opChar(DIVIDE);    
        }
        
        Number_t evaluateff(){
            return (child(LEFT)->evaluate() / child(RIGHT)->evaluate());   
        }
    };
    
    struct Power: BinaryOperator<Power>{
        using BinaryOperator<Power>::child;
        using BinaryOperator<Power>::setAssociativeDirection;
        
        void initff(){
            setAssociativeDirection() = RIGHT;   
        }
        void printff(std::ostream &os) const{
            os << ::opChar(POWER);    
        }
        
        Number_t evaluateff(){
            return pow(child(LEFT)->evaluate(), child(RIGHT)->evaluate());   
        }
    };
    
    struct Logarithm: BinaryOperator<Logarithm>{
        using BinaryOperator<Logarithm>::child;
        using BinaryOperator<Logarithm>::setAssociativeDirection;
        
        void initff(){
            setAssociativeDirection() = RIGHT;   
        }
        void printff(std::ostream &os) const{
            os << ::opChar(LOGARITHM);    
        }
        
        Number_t evaluateff(){
            return log2(child(RIGHT)->evaluate()) / log2(child(LEFT)->evaluate());   
        }
    };
    
    /*
    enum BINARYOPERATION{
    NOTBINARY=-1,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    POWER,
    LOGARITHM
};*/
    
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
    
    static bool inc(string_t::const_iterator &it, const string_t &str){
        assert(isInside(it, str));
        ++it;
        return isInside(it, str);
    }
    
    static BinaryOperator<Add> *newBinary(const BINARYOPERATION bop){
        OperatorStorage *nop;
        switch(bop){
            case ADD:
                nop = new Add;
                break;
            case SUBTRACT:
                nop = new Subtract;
                break;
            case MULTIPLY:
                nop = new Multiply;
                break;
            case DIVIDE:
                nop = new Divide;
                break;
            case POWER:
                nop = new Power;
                break;
            case LOGARITHM:
                nop = new Logarithm;
                break;
            default:
            erint "shouldn't be here";
                assert(false);
                
        }
        return static_cast<BinaryOperator<Add> *>(nop);
    }
    
    constexpr static const bool testParce=0;
    OperatorStorage *topd;
    
    OperatorStorage * const &top() const{
        return topd;   
    }
    
    OperatorStorage *&setTop(){
        return topd;   
    }
    void parce(const string_t &str){
        string_t::const_iterator it = str.begin();
        Exar<Parenthesis> parens;
        ++parens = Parenthesis();
        while ((parens.top().*(parens.top().parceFunction()))(it, str)){
            if (isOpenParenthesis(*it)){
                ++parens = Parenthesis();
            }
            else if (isCloseParenthesis(*it)){
                if (parens.size() != 1){
                    (&parens.top()-1)->aeLast = static_cast<AtomicExpression*>(parens.top().top());
                    --parens;
                }
            }
            
        }
        setTop() = parens[0].top();
    }
    
    struct Parenthesis{
      OperatorStorage *topd;
    
    OperatorStorage * const &top() const{
        return topd;   
    }
    
    OperatorStorage *&setTop(){
        return topd;   
    }
    //OperatorStorage *ae, *aeLast;
      AtomicExpression *ae, *aeLast;
        BinaryOperator<Add> *bo, *boLast;
        BINARYOPERATION bop;
        
        void init(){
            setParceFunction() = &Parenthesis::parce;   
            assert(parceFunction() == &Parenthesis::parce);
            setIsCloseFunction() = &isCloseParenthesis;
        }
        
        Parenthesis(){
         init();   
         
        }
        bool (Parenthesis::*parceFunctiond)(string_t::const_iterator &, const string_t &);
        bool (*isCloseFunctiond)(const char &);
        
        bool ( Parenthesis:: *const  &parceFunction() const)(string_t::const_iterator &, const string_t &) {
            return parceFunctiond;
        }
        bool (Parenthesis::*&setParceFunction())(string_t::const_iterator &, const string_t &){
            return parceFunctiond;
            //return uncons(cons()->parceFunction());
        }
        bool (*const &isCloseFunction() const)(const char &) {
            return isCloseFunctiond;
        }
        bool (*&setIsCloseFunction())(const char &){
            return isCloseFunctiond;
            //return uncons(cons()->parceFunction());
        }
         bool parce(string_t::const_iterator &it, const string_t &str){
        //assumes no positions filled
        setParceFunction() = &Parenthesis::secondaryParce;
       aeLast = new AtomicExpression;
        setTop() = aeLast;
        while (1){
                if (!nextSymbol(it, str)){
                    aeLast->setValue() = 0;
                    return false;
                }
                if (isNumeric(*it)){
                    break;   
                }
                if (isOpenParenthesis(*it)){
                 return true;
             }
             if (isCloseParenthesis(*it)){
                 aeLast->setValue() = 0;
                return true;   
             }
                if (!inc(it, str)){
                    return false;   
                }
            }
        assert(isNumeric(*it));
        assert(isInside(it, str));
        if (!getNumber(aeLast->setValue(), it, str)){
            return false;
        }
        return secondaryParce(it, str);
    }
    
         
         bool secondaryParce(string_t::const_iterator &it, const string_t &str){
        //assumes aelast is filled, no boLast or ae or bo
        if (!nextSymbol(it, str)){
            return false;
        }
        if (setIsCloseFunction()(*it)){
            return true;   
         }
        setParceFunction() = &Parenthesis::deepParce;
         bop = isBinary(*it);
         if (bop == NOTBINARY){
             bop = MULTIPLY;
         }
          
         boLast = newBinary(bop);
        boLast->setOperation(bop);
        boLast->setChild(LEFT) = aeLast;
        setTop() = boLast;
        if (isOpenParenthesis(*it)){
                 return true;
             }
       if (!inc(it, str)){
            ae = new AtomicExpression;
            ae->setValue() = boLast->identity();
            boLast->setChild(RIGHT) = ae;
            return false;
          }

        return deepParce(it, str);
         }
         
         bool deepParcef(string_t::const_iterator &it, const string_t &str){
              assert(parceFunction() == &Parenthesis::secondaryDeepParce);
              assert(isInside(it, str));
           if (testParce) erint "looping", *it;
            while (1){
                if (!nextSymbol(it, str)){
                    ae->setValue() = boLast->identity();
                    boLast->setChild(RIGHT) = ae;
                    return false;
                }
                if (isCloseParenthesis(*it)){
                      ae->setValue() = boLast->identity();
                    boLast->setChild(RIGHT) = ae;
                    return false;
                }
                if (isNumeric(*it)){
                    break;   
                }
                if (isOpenParenthesis(*it)){ 
                    return false;
                }
                if (!inc(it, str)){
                    return false;   
                }
            }
            assert(isNumeric(*it));
            assert(isInside(it, str));
            ae = new AtomicExpression;
            if (!getNumber(ae->setValue(), it, str)){
                if (testParce) erint "here";
                boLast->setChild(RIGHT) = ae;
                return false;
            }
            if (testParce) erint "here2";
            aeLast=ae;
            if (testParce) erint it - str.begin(), str.length(), *it;
            return true;
         }
         
        bool deepParce(string_t::const_iterator &it, const string_t &str){
            //assumes no ae or bo
            setParceFunction() = &Parenthesis::secondaryDeepParce;
           if (!deepParcef(it, str)){
               return isInside(it, str);
           }
            return secondaryDeepParce(it, str);
        //return setTop();
    }
     bool secondaryDeepParce(string_t::const_iterator &it, const string_t &str){
         
         while (1){
         if (!nextSymbol(it, str)){
                boLast->setChild(RIGHT) = aeLast;
                return false;
            }
             bop = isBinary(*it);
             //erint ::opChar(bop);
             bo = newBinary(bop);
            if (bop == NOTBINARY){
                bo->setOperation(MULTIPLY);            
            }
            else {
                bo->setOperation(bop);
            }
            if (Add::precedence(*boLast, *bo)){//true if boLast is Higher
                boLast->setChild(RIGHT) = aeLast;
                bo->setChild(LEFT) = boLast;
                if (Add::precedence(*static_cast<Add*>(setTop()), *bo)){
                    setTop() = bo;
                }
            }
            else {
                boLast->setChild(RIGHT) = bo;
                bo->setChild(LEFT) = aeLast;
            }
            boLast = bo;
            if (!inc(it, str)){
                ae = new AtomicExpression;
                ae->setValue() = boLast->identity();
                boLast->setChild(RIGHT) = ae;
                return false;
            }
            if (!deepParcef(it, str)){
                return isInside(it, str);    
            }
         }
     }
};
};

int main(){
    string mathstr = "3+4^5^";//work on right to left of ^ and double topped epressions
    Expression<> exp;
    exp.parce(mathstr);
   // erint "moving on";
    erint *exp.top();
    erint exp.setTop()->evaluate();
    //erint "hello, world";
    return 0;
}