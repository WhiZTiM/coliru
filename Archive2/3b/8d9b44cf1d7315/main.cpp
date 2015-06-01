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


    enum DIRECTION{
        LEFT,
        RIGHT
    };
    static const unsigned int DIRECTIONnum = RIGHT+1;
template <typename Number_t = double, typename uintt=unsigned int, typename intt=int>
struct Expression{
    
    
    
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
            //erint "helmo";
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
        
        AtomicExpression(Number_t num): OperatorBase<AtomicExpression>(){
            //erint "AEing";
            setValue() = num;
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
            //erint "setting shild";
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
            setPrecedence() = size_t((bino-ADD)/2);
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
        using BinaryOperator<Add>::setOperation;
        
        void initff(){
            setAssociativeDirection() = LEFT; 
            setOperation(ADD);
        }
        
        void printff(std::ostream &os) const{
            //os << child(LEFT) << endl;
            //os << child(RIGHT) << endl;
            os << ::opChar(ADD);    
        }
        
        Number_t evaluateff(){
            return (child(LEFT)->evaluate() + child(RIGHT)->evaluate());   
        }
    };
    
    struct Subtract: BinaryOperator<Subtract>{
        using BinaryOperator<Subtract>::child;
        using BinaryOperator<Subtract>::setAssociativeDirection;
        using BinaryOperator<Subtract>::setOperation;
        
        void initff(){
            setAssociativeDirection() = LEFT;
            setOperation(SUBTRACT);
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
        using BinaryOperator<Multiply>::setOperation;
        
        void initff(){
            setAssociativeDirection() = LEFT; 
            setOperation(MULTIPLY);
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
        using BinaryOperator<Divide>::setOperation;
        
        void initff(){
            setAssociativeDirection() = LEFT;   
            setOperation(DIVIDE);
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
        using BinaryOperator<Power>::setOperation;
        
        void initff(){
            setAssociativeDirection() = RIGHT;  
            setOperation(POWER);
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
        using BinaryOperator<Logarithm>::setOperation;
        
        void initff(){
            setAssociativeDirection() = RIGHT; 
            setOperation(LOGARITHM);
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
    
    constexpr static const bool testParce=1;
    OperatorStorage *topd;
    
    OperatorStorage * const &top() const{
        return topd;   
    }
    
    OperatorStorage *&setTop(){
        return topd;   
    }
    void parce(const string_t &str){
        //empty string
        string_t::const_iterator it = str.begin();
        Exar<Parenthesis> parens;
        ++parens = Parenthesis();
        while ((parens.top().*(parens.top().parceFunction()))(it, str, parens)){
            if (isOpenParenthesis(*it)){
                if (testParce) erint "opening parenthesis";
                ++parens = Parenthesis();
                if (!inc(it, str) || !nextSymbol(it, str)){
                    parens.top().setTop() = new AtomicExpression(Number_t(0));
                    if (testParce) erint"going here";
                    break;
                }
                //erint "not here";
                
            }
            else if (isCloseParenthesis(*it)){
                  if (testParce)erint " parenthesis";
                if (parens.size() != 1){
                    if (testParce) erint "inhither";
                    (&parens.top()-1)->aeLast = parens.top().top();
                     --parens;
                    //assert(
                    assert(parens.top().parceFunction() != &Parenthesis::parce);
                    if (parens.top().parceFunction() == &Parenthesis::secondaryParce){
                        if (testParce)erint "aquiiit";
                            parens.top().setTop() = parens.top().aeLast;
                    }
                    else {
                         if (testParce)erint "aquiiit2";
                        assert(parens.top().parceFunction() == &Parenthesis::secondaryDeepParce ||
                        parens.top().parceFunction() == &Parenthesis::deepParce);
                        
                        parens.top().boLast->setChild(RIGHT) = parens.top().aeLast;
                    }
                }
                else {
                    parens.top().aeLast = parens.top().top();
                    parens.top().setParceFunction() = &Parenthesis::secondaryParce;
                }
                if (!inc(it, str)){
                        break;      
                    }
            }
        }
        //if (testParce) erint parens.size();
        for (Parenthesis *pit=&parens.top()-1; pit!=&parens[-1]; --pit){
            erint "looping7:",pit-&parens[0], pit->top()->print(cout), pit->aeLast->print(cout);
            //pit->boLast->printf(cout);
                pit->aeLast = (pit+1)->setTop();
                erint *pit->aeLast;
                if (testParce) erint "results:", pit->parceFunction() == &Parenthesis::secondaryDeepParce, pit->parceFunction() == &Parenthesis::secondaryParce, 
                pit->parceFunction() == &Parenthesis::parce, pit->parceFunction() == &Parenthesis::deepParce;
                if (pit->parceFunction() == &Parenthesis::secondaryDeepParce || pit->parceFunction() == &Parenthesis::deepParce){
                    if (testParce){ erint "symbol"; pit->boLast->print(cout); cout << endl;
                    }
                    pit->boLast->setChild(RIGHT) = pit->aeLast;
                    erint *pit->boLast;
                    pit->top();
                    
                }
                else if (pit->parceFunction() == &Parenthesis::secondaryParce) {
                    pit->setTop() = pit->aeLast;
                    //erint "p1";
                   
                    /*
                    pit->aeLast->print(cout);
                    pit->boLast->print(cout);
                    assert(pit->boLast->child(RIGHT) == pit->aeLast);
                    static_cast<BinaryOperator<Power>*>(pit->boLast->child(RIGHT))->child(RIGHT)->print(cout);
                    assert(pit->boLast == pit->top());
                    assert(pit->top() == pit->boLast);
                    assert(parens[0].top() == pit->boLast);*/
                }
        }
       // erint "aqui2";
        setTop() = parens[0].top();
        //if (testParce) erint "aqui3";
        //top()->print(cout); cout << endl;
        //erint *top();
    }
    //base epression just a number
    //expressions are epressions intermittent with operators
    
    struct Parenthesis{
      OperatorStorage *topd,*aeLast;
        BinaryOperator<Add> *boLast;
    
    OperatorStorage * const &top() const{
        return topd;   
    }
    
    OperatorStorage *&setTop(){
        return topd;   
    }
        
        void init(){
            setParceFunction() = &Parenthesis::parce;   
            assert(parceFunction() == &Parenthesis::parce);
            setIsCloseFunction() = &isCloseParenthesis;
            boLast = NULL;
            aeLast = NULL;
        }
        
        Parenthesis(){
         init();   
         
        }
        bool (Parenthesis::*parceFunctiond)(string_t::const_iterator &, const string_t &, Exar<Parenthesis> &parens);
        bool (*isCloseFunctiond)(const char &);
        
        bool ( Parenthesis:: *const  &parceFunction() const)(string_t::const_iterator &, const string_t &, Exar<Parenthesis> &parens) {
            return parceFunctiond;
        }
        bool (Parenthesis::*&setParceFunction())(string_t::const_iterator &, const string_t &, Exar<Parenthesis> &parens){
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
         bool parce(string_t::const_iterator &it, const string_t &str, Exar<Parenthesis> &parens){
             //repeatedly skip until numeric input or parenthesis
        //assumes no positions filled
        if (testParce) erint "parce";
        setParceFunction() = &Parenthesis::secondaryParce;
        AtomicExpression *ae = new AtomicExpression;
        setTop() = ae;
        while (1){
                if (!isInside(it, str) || !nextSymbol(it, str)){
                    if (testParce) erint "exiting on end, setting ae to 0.";
                    ae->setValue() = 0;
                    return false;
                }
                if (isNumeric(*it)){
                    break;   
                }
                if (isOpenParenthesis(*it)){
                    if (testParce) erint "exiting on",*it," not setting ae.";
                 return true;
             }
             if (isCloseParenthesis(*it)){
                 if (testParce) erint "exiting on",*it,", setting ae to 0.";
                 ae->setValue() = 0;
                return true;   
             }
                ++it;
            }
        assert(isNumeric(*it));
        assert(isInside(it, str));
        getNumber(ae->setValue(), it, str);
        if (testParce) erint "got", ae->value();
        aeLast = ae;
        return secondaryParce(it, str, parens);
    }
    
         
         bool secondaryParce(string_t::const_iterator &it, const string_t &str, Exar<Parenthesis> &parens){
             //one go at an operator
             if (testParce) erint "parce2";
        //aelast is filled
        //no boLast or ae or bo
        if (!isInside(it, str) || !nextSymbol(it, str)){
             if (testParce) erint "leaving parce2 on end";
            return false;
        }
        if (setIsCloseFunction()(*it)){
            if (testParce) erint "leaving parce2 on", *it;
            return true;   
         }
        setParceFunction() = &Parenthesis::deepParce;
         BINARYOPERATION bop = isBinary(*it);
         if (bop == NOTBINARY){
             if (testParce) erint "implied mult";
             bop = MULTIPLY;//setting implied function
         }
         else {
            ++it;   
         }
         if (testParce) erint "got", ::opChar(bop);
         boLast = newBinary(bop);
        boLast->setOperation(bop);
        boLast->setChild(LEFT) = aeLast;
        setTop() = boLast;
        if (!isInside(it, str) || !nextSymbol(it, str)){
                return false;
            }
            if (isOpenParenthesis(*it)){
                return true;   
            }
        return deepParce(it, str, parens);
         }
         
         bool deepParcef(string_t::const_iterator &it, const string_t &str, Exar<Parenthesis> &parens){
             if (testParce) erint "parcef", *it;
              assert(parceFunction() == &Parenthesis::secondaryDeepParce);
              assert(isInside(it, str));
            while (1){
               // erint "hi";
                if (!isInside(it, str) || !nextSymbol(it, str)){
                    if (testParce) erint "leaving parce3 on end, setting boLast->R to:", boLast->identity();
                    aeLast = new AtomicExpression(boLast->identity());
                    return false;
                }
                if (isCloseParenthesis(*it)){
                    if (testParce) erint "leaving parce3 on", *it, ", setting boLast->R to:", boLast->identity();
                    aeLast = new AtomicExpression(boLast->identity());
                    return false;
                }
                if (isNumeric(*it)){
                    break;   
                }
                if (isOpenParenthesis(*it)){ 
                    if (testParce) erint "leaving parce3 on", *it;
                    return false;
                }
                ++it;
            }
            assert(isNumeric(*it));
            assert(isInside(it, str));
            AtomicExpression *ae = new AtomicExpression;
            getNumber(ae->setValue(), it, str);
            if (testParce) erint "dgot:",ae->value();
            aeLast=ae;
            //if (testParce) erint it - str.begin(), str.length(), *it;
            return isInside(it, str);
         }
         
        bool deepParce(string_t::const_iterator &it, const string_t &str, Exar<Parenthesis> &parens){
            if (testParce) erint "parce3";
            //no ae, bo 
            //has aeLast, boLast
            setParceFunction() = &Parenthesis::secondaryDeepParce;
           deepParcef(it, str, parens);
            return secondaryDeepParce(it, str, parens);
        //return setTop();
    }
     bool secondaryDeepParce(string_t::const_iterator &it, const string_t &str, Exar<Parenthesis> &parens){
         if (testParce) erint "parce4";
         //no bo
         //has aeLast, boLast, ae
         while (1){
             //erint "loop2";
         if (!isInside(it, str) || !nextSymbol(it, str)){
             if (testParce) erint "leaving parce4 on end";
                boLast->setChild(RIGHT) = aeLast;
                return false;
            }
            if (setIsCloseFunction()(*it)){
                if (testParce) erint "leaving parce4 on", *it;
                boLast->setChild(RIGHT) = aeLast;
            return true;   
         }
            BINARYOPERATION bop = isBinary(*it);
             if (bop == NOTBINARY){
                   if (testParce) erint "implied mult deep";
                bop = MULTIPLY;   
             }
             else {
                ++it;   
             }
             if (testParce) erint "dgot:", ::opChar(bop);
             //BinaryOperator<Add> *
             BinaryOperator<Add> *bo = newBinary(bop);
             bo->setOperation() = bop;
            if (Add::precedence(*boLast, *bo)){//true if boLast is Higher
            if (testParce) erint "choosing precedence between";
            boLast->print(cout); cout << " "; bo->print(cout);
            erint (Add::precedence(*boLast, *bo) ? "first": "second"),"one wins";
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
            if (!isInside(it, str) || !nextSymbol(it, str)){
                return false;
            }
            if (isOpenParenthesis(*it)){
                return true;   
            }
            deepParcef(it, str, parens);
         }
     }
};
};

int main(){
    string mathstr = "3+4*2";//work on right to left of ^ and double topped epressions
    Expression<> exp;
    exp.parce(mathstr);
    //erint "moving on";
    //exp.top()->print(cout); cout << endl;
    
    //erint *static_cast<Expression<>::BinaryOperator<Expression<>::Add> *>(exp.top())->child(LEFT);
    //static_cast<Expression<>::BinaryOperator<Expression<>::Add> *>(exp.top())->child(RIGHT)->print(cout); cout << endl;
    erint *exp.top();
    erint exp.setTop()->evaluate();
    //erint "hello, world";
    return 0;
}