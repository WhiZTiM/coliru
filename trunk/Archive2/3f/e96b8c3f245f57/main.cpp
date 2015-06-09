#include "/Archive2/d5/b0df05ec2106ac/main.cpp"
#include <typeinfo>
#include <cmath>

typedef unsigned int Flag_t;
template <typename T>//, typename uintt=unsigned, typename intt=int>
using Tree = DTree<T>;//, uintt, intt>;
typedef std::string string_t;

bool testPrint=0;
const bool testParce=0;

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

bool inc(string_t::const_iterator &it, const string_t &str){
        
    assert(isInside(it, str));
    ++it;
    return isInside(it, str);
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
    VARIABLE,
    UNARY,
    BINARY,
    COMMUTATIVE
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

enum COMMUTATIVEOPERATION{
    NOTCOMMUTATIVE=-1,
    ADD2,
    MULTIPLY2
};

string_t opStringC(const COMMUTATIVEOPERATION obs){
    switch (obs){
        case ADD2:
            return "+";
        case MULTIPLY2:
            return "*";
        default:
        erint "no char for NOTCOMMUTATIVE";
            return "\0";
    }
}

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
            return '\0';
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
    return isAlphabeticLower(ch) || isAlphabeticUpper(ch);
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

bool getName(string_t &name, string_t::const_iterator &it, const string_t &str, bool (*validChar)(const char)=&isAlphabetic){
    assert(isInside(it, str));
    assert(validChar(*it));
    assert(name == "");
    
    while (1){
        name += *it;
        if (!inc(it, str)){
            return false;   
        }
        if (!validChar(*it)){
            break;    
        }
    }
    return true;
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
    RIGHT,
    CHILDRENFIRST
};
static const unsigned int DIRECTIONnum = RIGHT+1;

DIRECTION toggleDIRECTION(const DIRECTION dir){
    return DIRECTION(!bool(dir));
}

template <typename T>
T toggle(const T &t){
    return T(!bool(t));
}
    
size_t highestBit(size_t siz){
    size_t bits(0);
        while (siz != size_t(0)){
            siz >>= 1;
            ++bits;
        }
        return bits;
}

template <typename Number_t = double, typename uintt=unsigned int, typename intt=int>
struct Expression{

    enum TRAVERSESTATE{
          STAYOUTVAR = 1<<1,
          STAYOUTVARNAME = 1<<2,
          TRIGHT = 1<<3,
          CHILDRENFIRST = 1<<4
    };
    static const size_t TRAVERSESTATEnum = 4; 
    /*
    template <typename True, typename FN>
    static void helpTraverse(True &tru, FN fn){
        switch(tru.expressionType()){
            case NUMBER:
                static_cast<AtomicExpression &>(tru)->traverse(fn);
                break;
            case UNARY:
            case BINARY:
                static_cast<BinaryOperator<Add> &>(tru)->traverse(fn);
                break;
            case COMMUTATIVE:
                static_cast<CommutativeOperator<Add2> &>(tru)->traverse(fn);
                break;
        }
    }*/
    
    static const uintt EXPRESSIONTYPEnum = COMMUTATIVE+1;
    
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
        
        /*template <typename Truet>
        operator OperatorBase<Truet>(){
            return *static_cast<OperatorBase<Truet> *>(this);
        }*/
        
        virtual void print(std::ostream &os) const=0;
        virtual void printExp(std::ostream &os) const=0;
        
        friend std::ostream &operator<<(std::ostream& os, const OperatorStorage &ops){
            ops.printExp(os);
            return os;
        }
        
        virtual Number_t evaluate()=0;
        
        virtual bool operator<(const OperatorStorage &ae) const=0;
        virtual bool operator>(const OperatorStorage &ae) const=0;
        virtual bool operator<=(const OperatorStorage &ae) const=0;
        virtual bool operator>=(const OperatorStorage &ae) const=0;
        virtual bool operator==(const OperatorStorage &ae) const=0;
        virtual bool operator!=(const OperatorStorage &ae) const=0;
        
        virtual OperatorStorage *derivative(const string_t &nam) const=0;
        
        virtual void destroy()=0;
        //virtual void traverse(void (*function)(OperatorStorage &), const Flag_t state=0)=0;
        void traverse(void (OperatorStorage::*function)(), const Flag_t state=0){//not optimal
                traverse(
                    [&function](OperatorStorage &ops){
                        ops->*function();
                    }, state);
        }
        template <typename FN>
            void traverse(FN fn, const Flag_t state=0) const {
            //erint "outputting number";
            if (expressionType() == NUMBER){
                //erint "hrm";
                static_cast<const AtomicExpression*>(this)->traversef(fn, state);
                //erint "hrm2";
            }
            else if (expressionType() == BINARY) {
                 static_cast<const BinaryOperator<Add>*>(this)->traversef(fn, state);
            }
            else if (expressionType() == COMMUTATIVE){
                //commutative   
                static_cast<const CommutativeOperator<Add2>*>(this)->traversef(fn, state);
            }
            else {
                assert(expressionType() == VARIABLE);
                static_cast<const Variable *>(this)->traversef(fn, state);
            }
            }
            
            template <typename FN>
            void traverse(FN fn, const Flag_t state=0) {
            //erint "outputting number";
            if (expressionType() == NUMBER){
                //erint "hrm";
                static_cast<AtomicExpression*>(this)->traversef(fn, state);
                //erint "hrm2";
            }
            else if (expressionType() == BINARY) {
                 static_cast<BinaryOperator<Add>*>(this)->traversef(fn, state);
            }
            else if (expressionType() == COMMUTATIVE){
                //commutative   
                static_cast<CommutativeOperator<Add2>*>(this)->traversef(fn, state);
            }
            else {
                assert(expressionType() == VARIABLE);
                static_cast<Variable *>(this)->traversef(fn, state);
            }
            }
            virtual OperatorStorage *makeCopy() const=0;
            OperatorStorage(){}
            OperatorStorage(const OperatorStorage &oper){}
            virtual ~OperatorStorage()=0;
            virtual OperatorStorage &operator=(const OperatorStorage &oper)=0;
    };
        struct VariableStorage{
            
            const VariableStorage *cons() const {
                return static_cast<const VariableStorage *>(this);
            }
            string_t named;
            
            const string_t &name() const{
                return named;   
            }
            string_t &setName() {
                return uncons(cons()->name());   
            }
        
            OperatorStorage *expressiond;
        
            OperatorStorage * const &expression() const{
                return expressiond;   
            }
            OperatorStorage *&setExpression(){
                return uncons(cons()->expression());   
            }
            
            bool operator<(const VariableStorage &ae) const {
                return name() < ae.name();
            }
            bool operator>(const VariableStorage &ae) const {
                return name() > ae.name();
            }
            bool operator==(const VariableStorage &ae) const {
                return name() == ae.name();
            }
            bool operator<=(const VariableStorage &ae) const {
                return !(*this > ae);
            }
            bool operator>=(const VariableStorage &ae) const {
                return !(*this < ae);
            }
            bool operator!=(const VariableStorage &ae) const {
                return !(*this == ae);
            }
            
            bool operator<(const string_t &ae) const {
                return name() < ae;
            }
            bool operator>(const string_t &ae) const {
                return name() > ae;
            }
            bool operator==(const string_t &ae) const {
                return name() == ae;
            }
            bool operator<=(const string_t &ae) const {
                return !(*this > ae);
            }
            bool operator>=(const string_t &ae) const {
                return !(*this < ae);
            }
            bool operator!=(const string_t &ae) const {
                return !(*this == ae);
            }
            
            void init(const string_t &str, OperatorStorage *ops){
                setName() = str;
                   setExpression() = ops;
                   assert(!variables().find(str));
                   setVariables().insert(*this);
            }
            
            VariableStorage(const string_t &str, OperatorStorage *ops){
                  init(str, ops);
            }
            
            void printInfo(std::ostream &os) const{
                   os << name() << ": " << *expression();
            }
            
            friend std::ostream &operator<<(std::ostream &os, const VariableStorage &vars){
                vars.printInfo(os);
                return os;
            }
        };
    //static Tree<VariableStorage> variablesd;
    
    static string_t unnamedVariabled;
    static size_t unnamedVariableNumd;
    
    static const string_t &unnamedVariable(){
        return unnamedVariabled;   
    }
    static string_t &setUnnamedVariable() {
       return unnamedVariabled;   
    }
    
    static const size_t &unnamedVariableNum(){
        return unnamedVariableNumd;   
    }
    static size_t &setUnnamedVariableNum() {
       return unnamedVariableNumd;    
    }
    
    static Tree<VariableStorage> variablesd;
    
    static const Tree<VariableStorage> &variables(){
            return variablesd;   
        }
    static Tree<VariableStorage> &setVariables(){
        return variablesd;   
    }
    
    template <typename Truet>
    struct OperatorBase: OperatorStorage{
        
        using OperatorStorage::expressionType;
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
        OperatorBase(const OperatorStorage &oper){
            init();
            assert(expressionType() == oper.expressionType());
            operator=(oper);
        }
        ~OperatorBase(){
        }
        OperatorBase &operator=(const OperatorStorage &oper){
            //setEqual(oper);
            return *this;
        }
        void init(){
            getT()->initf();
        }
        
        bool less(const OperatorStorage &ae) const {
            if (expressionType() != ae.expressionType()){
                return expressionType() < ae.expressionType();
            }
            return cons()->lessf(ae);
        }
        bool greater(const OperatorStorage &ae) const {
            if (expressionType() != ae.expressionType()){
                return expressionType() > ae.expressionType();
            }
            return cons()->greaterf(ae);
        }
        bool equal(const OperatorStorage &ae) const {
            if (expressionType() != ae.expressionType()){
                return false;
            }
            return cons()->equalf(ae);
        }
        
        bool operator<(const OperatorStorage &ae) const {
            return less(ae);
        }
        bool operator>(const OperatorStorage &ae) const {
            return greater(ae);
        }
        bool operator==(const OperatorStorage &ae) const {
            return equal(ae);
        }
        bool operator<=(const OperatorStorage &ae) const {
            return !(*this > ae);
        }
        bool operator>=(const OperatorStorage &ae) const {
            return !(*this < ae);
        }
        bool operator!=(const OperatorStorage &ae) const {
            return !(*this == ae);
        }
        
        void print(std::ostream &os) const{
            cons()->printf(os);
        }
        
        //template cannot be virtual so this is needed for calling traverse from
        //operator base
        void traverse(void (*function)(OperatorStorage &)){
            traverse(function);
        }
        void traverse(void (OperatorStorage::*function)()){
        }
        
        template <typename FN>
        void traverse(FN fn, const Flag_t state=0) const {
            cons()->traversef(fn, state);
        }
        
        template <typename FN>
        void traverse(FN fn, const Flag_t state=0) {
            getT()->traversef(fn, state);
        }
        
        void printExp(std::ostream &os) const {
            if (testPrint) erint "printExping";
            traverse([&os](const OperatorStorage &ops){
                ops.print(os);
            }, STAYOUTVAR);
        }
        void destroy(){
            traverse([](OperatorStorage &oper){
                  delete &oper;
            }, STAYOUTVAR | CHILDRENFIRST);
        }
        OperatorStorage *makeCopy() const{
            return cons()->makeCopyf();
        }
        friend std::ostream &operator<<(std::ostream &os, const OperatorBase &ae){
            //erint "helmo";
            ae.printExp(os);
            return os;
        }
        
        Number_t evaluate(){
            return getT()->evaluatef();
        }
        
        OperatorStorage *derivative(const string_t &nam) const{
            return cons()->derivativef(nam);   
        }
    };
    
    struct AtomicExpression: OperatorBase<AtomicExpression>{
        
        using OperatorBase<AtomicExpression>::cons;
        using OperatorBase<AtomicExpression>::setExpressionType;
        using OperatorBase<AtomicExpression>::expressionType;
        using OperatorBase<AtomicExpression>::init;
        using OperatorBase<AtomicExpression>::setPrecedence;
        
        //variable
        //--name
        //--
        //number
        
        Number_t valued;
        
        OperatorStorage *makeCopyf() const{
            return new AtomicExpression(value());   
        }
        
        const Number_t &value() const{
            return valued;
        }
        Number_t &setValue(){
            return uncons(cons()->value());
           // return const_cast<Number_t &>(cons()->value());
        }
        
        template <typename T>
        explicit AtomicExpression(const T &t): OperatorBase<AtomicExpression>(){
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
        void traversef(FN fn, const Flag_t state=0) const {
            fn(*this);
        }
        
        template <typename FN>
        void traversef(FN fn, const Flag_t state=0) {
            fn(*this);
        }
        
        Number_t evaluatef(){
            return value();
        }
        
        static AtomicExpression &castUp(OperatorStorage &ae){
            return static_cast<AtomicExpression &>(ae);
        }
        static const AtomicExpression &castUp(const OperatorStorage &ae){
            return static_cast<const AtomicExpression &>(ae); 
        }
        
        bool lessf(const OperatorStorage &ae) const{
            assert(expressionType() == ae.expressionType());
            return value() < castUp(ae).value();   
        }
        bool greaterf(const OperatorStorage &ae) const{
            assert(expressionType() == ae.expressionType());
            return value() > castUp(ae).value();   
        }
        bool equalf(const OperatorStorage &ae) const{
            assert(expressionType() == ae.expressionType());
            return value() == castUp(ae).value();   
        }
        
        OperatorStorage *derivativef(const string_t &nam) const{
            return new AtomicExpression(0);   
        }
    };
    
    struct Variable: OperatorBase<Variable>{
        
        using OperatorBase<Variable>::cons;
        using OperatorBase<Variable>::setExpressionType;
        using OperatorBase<Variable>::expressionType;
        using OperatorBase<Variable>::init;
        using OperatorBase<Variable>::setPrecedence;
        
        Variable(): OperatorBase<Variable>(){}
        Variable(const string_t &nam): OperatorBase<Variable>(){
            setName() = nam;
            }
        OperatorStorage *makeCopyf() const{
            return new Variable(name());   
        }
        
        string_t named;
        
        const string_t &name() const{
            return named;   
        }
        string_t &setName() {
            return uncons(cons()->name());   
        }
        
        OperatorStorage * const &expression() const{
            
            const typename Tree<VariableStorage>::Node *vars = variables().find(name()); 
            if (!vars){
                erint "shouldn't be here";
                new VariableStorage(name(), new AtomicExpression(0));
                vars = variables().find(name());
                assert(vars != NULL);
            }
            return vars->item()->expression();
        }
        //error: invalid conversion from 'const DTree<Expression<>::Variable::VariableStorage, _less<Expression<>::Variable::VariableStorage, Expression<>::Variable::VariableStorage>, int, unsigned int>::Node*' to 'DTree<Expression<>::Variable::VariableStorage, _less<Expression<>::Variable::VariableStorage, Expression<>::Variable::VariableStorage>, int, unsigned int>::Node*' [-fpermissive]
        OperatorStorage *&setExpression(){
            
            const typename Tree<VariableStorage>::Node *vars = variables().find(name()); 
            if (!vars){
                erint "shouldn't be here";
                new VariableStorage(name(), new AtomicExpression(0));
                vars = variables().find(name());
                assert(vars != NULL);
            }
            return vars->item()->setExpression();  
        }
        
        void set(){
            if (!variables().find(name())){
                new VariableStorage(name(), new AtomicExpression(0)); 
            }
        }
        
        void set(const string_t &str, OperatorStorage *ops){
            setName() = str;
            if (!variables().find(name())){
                new VariableStorage(name(), ops);   
            }
        }
        
        void initf(){
            setExpressionType() = VARIABLE;
            setPrecedence() = size_t(0);
        }
        
        Number_t evaluatef(){
            return setExpression()->evaluate();
        }
        
        template <typename FN>
        void traversef(FN fn, const Flag_t state=0) const {
            //erint "outputting number";
            if (state & CHILDRENFIRST){
                if (!(state & STAYOUTVAR)){
                expression()->traverse(fn, state);   
            }
            if (!(state & STAYOUTVARNAME)){
                fn(*this);
            }
            }
            else {
            if (!(state & STAYOUTVAR)){
                expression()->traverse(fn, state);   
            }
            if (!(state & STAYOUTVARNAME)){
                fn(*this);
            }
            }
        }
        
        template <typename FN>
        void traversef(FN fn, const Flag_t state=0) {
            if (state & CHILDRENFIRST){
                if (!(state & STAYOUTVAR)){
                expression()->traverse(fn, state);   
            }
            if (!(state & STAYOUTVARNAME)){
                fn(*this);
            }
            }
            else {
            if (!(state & STAYOUTVAR)){
                expression()->traverse(fn, state);   
            }
            if (!(state & STAYOUTVARNAME)){
                fn(*this);
            }
            }
        }
        //traverse control:
        //
        //left ot r or r to l for binary/commutative
        //into variablers or no
        //
        void printInfo(std::ostream &os=std::cout) const {
            os << name() << ": " << *expression();
        }
        
        void printf(std::ostream &os=std::cout) const {
            if (testPrint) erint "printing variable";
            os << name();
        }
        
        static bool testVariable(std::ostream &os=std::cout){
            Variable var;
            return true;    
        }
        
        static Variable &castUp(OperatorStorage &ae){
            return static_cast<Variable &>(ae);
        }
        static const Variable &castUp(const OperatorStorage &ae){
            return static_cast<const Variable &>(ae); 
        }
        
        bool lessf(const OperatorStorage &ae) const{
            assert(expressionType() == ae.expressionType());
            return name() < castUp(ae).name();   
        }
        bool greaterf(const OperatorStorage &ae) const{
            assert(expressionType() == ae.expressionType());
            return name() > castUp(ae).name();  
        }
        bool equalf(const OperatorStorage &ae) const{
            assert(expressionType() == ae.expressionType());
            return name() == castUp(ae).name(); 
        }
        
        OperatorStorage *derivativef(const string_t nam) const{
            if (name() == nam){
                return new AtomicExpression(1);   
            }
            return expression()->derivative(nam);   
        }
    };
    
    template <typename TrueT>
    struct CommutativeOperator: OperatorBase<CommutativeOperator<TrueT>>{
        //addition, multiplication
        using OperatorBase<CommutativeOperator>::cons;
        using OperatorBase<CommutativeOperator>::setExpressionType;
        using OperatorBase<CommutativeOperator>::expressionType;
        using OperatorBase<CommutativeOperator>::setPrecedence;
        using OperatorBase<CommutativeOperator>::precedence;
        
        const TrueT *getT2() const{
            return static_cast<const TrueT *>(this);   
        }
        TrueT *getT2(){
            return uncons(cons()->getT2());   
        }
        
        Tree<OperatorStorage> operandsd;
        
        const Tree<OperatorStorage> &operands() const{
            return operandsd;   
        }
        Tree<OperatorStorage> &operands(){
            return uncons(cons()->operands());   
        }
        
        COMMUTATIVEOPERATION operationd;
        
        const COMMUTATIVEOPERATION &operation() const{
            return operationd;
        }
        COMMUTATIVEOPERATION &setOperation(){
            return uncons(cons()->operation());
            // return const_cast<Number_t &>(cons()->value());
        }
        void initf(){
            setExpressionType() = COMMUTATIVE;
            getT2()->initff();
        }
        CommutativeOperator(): OperatorBase<CommutativeOperator>(){}
        
         template <typename FN>
        void traversef(FN fn, const Flag_t state=0) const {
            if (state & CHILDRENFIRST){
                operands().traverse([fn, state](const OperatorStorage &ops){
                ops.traverse(fn, state);
                });
                fn(*this);
            }
            else {
                fn(*this); 
               operands().traverse([fn, state](const OperatorStorage &ops){
                ops.traverse(fn, state);
                });
            }
        }
        template <typename FN>
        void traversef(FN fn, const Flag_t state=0) {
            if (state & CHILDRENFIRST){
                operands().traverse([fn, state](OperatorStorage &ops){
                ops.traverse(fn, state);
                });
                fn(*this);
            }
            else {
                fn(*this); 
               operands().traverse([fn, state](OperatorStorage &ops){
                ops.traverse(fn, state);
                });
            }
        }
      
        static Number_t identity(const COMMUTATIVEOPERATION bo){
            if (bo == ADD2){
               return Number_t(0);   
            }
            return Number_t(1);
        }
        Number_t identity(){
            return identity(operation());
        }
      
        Number_t evaluatef(){
            return getT2()->evaluateff();
        }
        
        string_t opString() const{
            return ::opStringC(operation());   
        }
        
        void printf(std::ostream &os) const{
            //erint "aquii";//not gonna print the in right order
            string_t opstr = opString();
            operands().traverse([&os, opstr](OperatorStorage &ops){
                os << ops << opstr;
            });
        }
        
        void insert(OperatorStorage &ops){
            operands().insert(ops);
        }
        
        static CommutativeOperator &castUp(OperatorStorage &ae){
            return static_cast<CommutativeOperator &>(ae);
        }
        static const CommutativeOperator &castUp(const OperatorStorage &ae){
            return static_cast<const CommutativeOperator &>(ae); 
        }
        
        bool lessf(const OperatorStorage &ae) const{
            assert(expressionType() == ae.expressionType());
            return false;  
        }
        bool greaterf(const OperatorStorage &ae) const{
            assert(expressionType() == ae.expressionType());
            return false;  
        }
        bool equalf(const OperatorStorage &ae) const{
            assert(expressionType() == ae.expressionType());
            return true;
        }
        
        OperatorStorage *makeCopyf() const{
            return new AtomicExpression(0);   
        }
        
        OperatorStorage *derivativef(const string_t &nam) const{
            return new AtomicExpression(0);    
        }
    };
    
    struct Add2: CommutativeOperator<Add2>{
        
        using CommutativeOperator<Add2>::setOperation;
        Number_t evaluateff(){
            return 0;
        }
        void initff(){
            setOperation() = ADD2;
        }
        void printff(std::ostream &os) const{
               
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
        using OperatorBase<BinaryOperator>::expressionType;
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
        
        OperatorStorage *makeCopyf() const{
            return new BinaryOperator(child(LEFT)->makeCopy(), child(RIGHT)->makeCopy());
        }
        
        BinaryOperator(): OperatorBase<BinaryOperator>(){}
        BinaryOperator(OperatorStorage *op1, OperatorStorage *op2): OperatorBase<BinaryOperator>(){
            setChild(LEFT) = op1;
            setChild(RIGHT) = op2;
            }
        
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
        void traversef(FN fn, const Flag_t state=0) const {
            //erint "traversing binary";
            DIRECTION dir(DIRECTION(LEFT + ((state & TRIGHT) == true)));
            if (state & CHILDRENFIRST){
                fn(*this);
                child(dir)->traverse(fn, state);
            }
            else {
                child(dir)->traverse(fn, state);
                fn(*this);
            // erint "outputting binary";
            }
            child(::toggle(dir))->traverse(fn, state);
        }
        template <typename FN>
        void traversef(FN fn, const Flag_t state=0) {
            
            DIRECTION dir(DIRECTION(LEFT + ((state & TRIGHT) == true)));
            if (state & CHILDRENFIRST){
                fn(*this);
                child(dir)->traverse(fn, state);
            }
            else {
                child(dir)->traverse(fn, state);
                fn(*this);
            // erint "outputting binary";
            }
            child(::toggle(dir))->traverse(fn, state);
        }
        
        OperatorStorage *makeCopy(){
            return new AtomicExpression(0);   
        }
        
        Number_t evaluatef(){
            return getT2()->evaluateff();
        }
        
        void printf(std::ostream &os) const{
            //erint "aquii";
            getT2()->printff(os);
        }
        
        static BinaryOperator &castUp(OperatorStorage &ae){
            return static_cast<BinaryOperator &>(ae);
        }
        static const BinaryOperator &castUp(const OperatorStorage &ae){
            return static_cast<const BinaryOperator &>(ae); 
        }
        
        bool lessf(const OperatorStorage &bo) const{
            assert(expressionType() == bo.expressionType());
            const BinaryOperator &ae = castUp(bo);
            if (operation() != ae.operation()){
                return operation() < ae.operation();
            }
            if (*child(LEFT) == *ae.child(LEFT)){
                return *child(RIGHT) < *ae.child(RIGHT);
            }
            return *child(LEFT) < *ae.child(LEFT);
        }
        bool greaterf(const OperatorStorage &bo) const{
            assert(expressionType() == bo.expressionType());
            const BinaryOperator &ae = castUp(bo);
            if (operation() != ae.operation()){
                return operation() > ae.operation();
            }
            if (*child(LEFT) == *ae.child(LEFT)){
                return *child(RIGHT) > *ae.child(RIGHT);
            }
            return *child(LEFT) > *ae.child(LEFT);  
        }
        bool equalf(const OperatorStorage &bo) const{
            assert(expressionType() == bo.expressionType());
            const BinaryOperator &ae = castUp(bo);
            if (operation() != ae.operation()){
                return false;
            }
            return (*child(LEFT) == *ae.child(LEFT) && *child(RIGHT) == *ae.child(RIGHT));
        }
        
        OperatorStorage *derivativef(const string_t &nam) const{
            return getT2()->derivativeff(nam);
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
        
        OperatorStorage *derivativeff(const string_t &nam) const{
            Add *oper = new Add;
            oper->setChild(LEFT) = child(LEFT)->derivative(nam);
            oper->setChild(RIGHT) = child(RIGHT)->derivative(nam);
            
            return oper;
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
        
        OperatorStorage *derivativeff(const string_t &nam) const{
            Subtract *oper = new Subtract;
            oper->setChild(LEFT) = child(LEFT)->derivative(nam);
            oper->setChild(RIGHT) = child(RIGHT)->derivative(nam);
            
            return oper;
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
            if (testPrint) erint "printing binary mult", child(LEFT), child(RIGHT), *child(LEFT), *child(RIGHT);
            os << ::opChar(MULTIPLY);    
        }
        
        Number_t evaluateff(){
            return (child(LEFT)->evaluate() * child(RIGHT)->evaluate());   
        }
        
        OperatorStorage *derivativeff(const string_t &nam) const{
            Add *oper = new Add;
            Multiply *mult1 = new Multiply, *mult2 = new Multiply;
            oper->setChild(LEFT) = mult1;
            oper->setChild(RIGHT) = mult2;
            
            mult1->setChild(LEFT) = child(LEFT)->derivative(nam);
            mult1->setChild(RIGHT) = child(RIGHT);
            
            mult2->setChild(LEFT) = child(LEFT);
            mult2->setChild(RIGHT) = child(RIGHT)->derivative(nam);
            return oper;
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
        
        OperatorStorage *derivativeff(const string_t &nam) const{
            Subtract *oper = new Subtract;
            Multiply *mult1 = new Multiply;
            Divide *div1 = new Divide, *div2 = new Divide;
            Power *powe = new Power;
            
            oper->setChild(LEFT) = div1;
            div1->setChild(LEFT) = child(LEFT)->derivative(nam);
            div1->setChild(RIGHT) = child(RIGHT);
            
            oper->setChild(RIGHT) = mult1;
            mult1->setChild(LEFT) = div2;
            div2->setChild(LEFT) = child(LEFT);
            div2->setChild(RIGHT) = powe;
            div2->setChild(RIGHT) = child(RIGHT);
            powe->setChild(RIGHT) = new AtomicExpression(2);
            
            mult1->setChild(RIGHT) = child(RIGHT)->derivative(nam);
            
            return oper;
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
        
        OperatorStorage *derivativeff(const string_t &nam) const{
            Multiply *oper = new Multiply;
            return oper;
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
        
        OperatorStorage *derivativeff(const string_t &nam) const{
            Subtract *oper = new Subtract;
            Multiply *mult1 = new Multiply;
            Divide *div1 = new Divide, *div2 = new Divide;
            Power *powe = new Power;
            
            oper->setChild(LEFT) = div1;
            div1->setChild(LEFT) = child(LEFT)->derivative(nam);
            div1->setChild(RIGHT) = child(RIGHT);
            
            oper->setChild(RIGHT) = mult1;
            mult1->setChild(LEFT) = div2;
            div2->setChild(LEFT) = child(LEFT);
            div2->setChild(RIGHT) = powe;
            div2->setChild(RIGHT) = child(RIGHT);
            powe->setChild(RIGHT) = new AtomicExpression(2);
            
            mult1->setChild(RIGHT) = child(RIGHT)->derivative(nam);
            
            return oper;
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
        while (1){
                if (!isInside(it, str) || !nextSymbol(it, str)){
                    AtomicExpression *ae = new AtomicExpression;
                    if (testParce) erint "exiting on end, setting ae to 0.";
                    ae->setValue() = 0;
                    setTop() = aeLast = ae;
                    return false;
                }
                if (isNumeric(*it)){
                    AtomicExpression *ae = new AtomicExpression;
                    getNumber(ae->setValue(), it, str);
                    if (testParce) erint "got", ae->value();
                    setTop() = aeLast = ae;
                    break;   
                }
                if (isAlphabetic(*it)){
                    Variable *var = new Variable;
                    getName(var->setName(), it, str, &::isAlphabetic);
                    var->set();
                     if (testParce){ erint "gotvar"; var->printInfo(cout);
                    }
                    setTop() = aeLast = var;
                    break;
                }
                if (isOpenParenthesis(*it)){
                    if (testParce) erint "exiting on",*it," not setting ae.";
                 return true;
                }
                if (isCloseParenthesis(*it)){
                    if (testParce) erint "exiting on",*it,", setting ae to 0.";
                    AtomicExpression *ae = new AtomicExpression;
                    ae->setValue() = 0;
                    setTop() = aeLast = ae;
                    return true;   
             }
                ++it;
            }
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
             if (testParce) erint "dparcef", *it, isAlphabetic(*it);
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
                    AtomicExpression *ae = new AtomicExpression;
                    getNumber(ae->setValue(), it, str);
                    if (testParce) erint "dgotnum:",ae->value();
                    aeLast=ae;
                    break;   
                }
                if (isAlphabetic(*it)){
                    Variable *var = new Variable;
                    getName(var->setName(), it, str, &::isAlphabetic);
                    var->set();
                    if (testParce){
                        erint "dgotvar", var->name(); var->printInfo(cout);
                        erint *var;
                    }
                    aeLast=var;
                    break;
                }
                if (isOpenParenthesis(*it)){ 
                    if (testParce) erint "leaving parce3 on", *it;
                    return false;
                }
                ++it;
            }
            
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
            if (testParce){ erint "choosing precedence between";
            boLast->print(cout); cout << " "; bo->print(cout);
            erint (Add::precedence(*boLast, *bo) ? "first": "second"),"one wins";
            }
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

//template <typename Number_t, typename uintt, typename intt>
//Tree<Expression<Number_t, uintt, intt>::VariableStorage> Expression<Number_t, uintt, intt>::VariableStorage::variablesd = Tree<Expression<Number_t, uintt, intt>::VariableStorage>();
    
template <typename Number_t, typename uintt, typename intt>
Expression<Number_t, uintt, intt>::OperatorStorage::~OperatorStorage(){}
//template <typename Number_t, typename uintt, typename intt>
//typename Expression<Number_t, uintt, intt>::OperatorStorage *&Expression<Number_t, uintt, intt>::OperatorStorage::setChild(const DIRECTION){}
//in order to take the address of a static member, it must be "defined" like so
template <typename Number_t, typename uintt, typename intt>
Tree<typename Expression<Number_t, uintt, intt>::VariableStorage> Expression<Number_t, uintt, intt>::variablesd;

template <typename Number_t, typename uintt, typename intt>
string_t Expression<Number_t, uintt, intt>::unnamedVariabled;

template <typename Number_t, typename uintt, typename intt>
size_t Expression<Number_t, uintt, intt>::unnamedVariableNumd;
   void test1(){
      Expression<>::Add2 com;
     exit(0);
    } 
    void testVariableStorage(){
        Expression<double, unsigned int, int>::Variable var;
    var.set("hello", new Expression<>::AtomicExpression(0));
    Expression<double, unsigned int, int>::Variable var2;
    var2.set("hellow", new Expression<>::AtomicExpression(0));
    Expression<double, unsigned int, int>::Variable var3;
    var3.set("hell", new Expression<>::AtomicExpression(0));
    Expression<double, unsigned int, int>::Variable var4;
    var4.set("a", new Expression<>::AtomicExpression(1));
    var4.setExpression() = new Expression<>::AtomicExpression(1);
    
    auto brea2 = Expression<>::variables();
    erint typeid(brea2).name();
   // brea2.insert(*new Expression<>::VariableStorage("hello", new Expression<>::AtomicExpression));
    erint brea2;
    }
    
int main(){
    
   //Expression<>::Variable::testVariable(); erint "hi"; return 0;
   //test1();
   //erint "he;llo";
    string mathstr = "3 4a";//work on right to left of ^ and double topped epressions
    Expression<> exp;
    exp.parce(mathstr);
    erint *exp.top(), "=", exp.setTop()->evaluate();
    Expression<>::OperatorStorage *der = exp.top()->derivative("a");
    Expression<>::OperatorStorage *ep2 = der->makeCopy();
    erint *der, "=", der->evaluate();
    erint *ep2, "=", ep2->evaluate();
    //erint "hello, world";
    return 0;
}
