#include <cstdio>
#include <iostream>

class MultAdd
{

private:
    int x;
    int y;
    virtual int add()   //virtual fuction so vtable created for Thing class
    {
            return x+y;
    }
    virtual int multiply()
    {
            return x*y;
    }
public:
    MultAdd(){
            x = 2;
            y = 10;
    }
};

////////////////////////////////////////////////////////////////////////////////////////
//// The template classes can unfortunately not be declared inside extractMultAdd ()
////////////////////////////////////////////////////////////////////////////////////////

#define ROB_PRIVATE_MEMBER_INST(CLASS, TYPE, MEMBER)    \
template<typename T>                                    \
struct CLASS##_##MEMBER##_rob_tag {                     \
  typedef T CLASS::*type;                               \
  friend type get(CLASS##_##MEMBER##_rob_tag);          \
};                                                      \
template<typename Tag, typename Tag::type M>            \
struct CLASS##_##MEMBER##_rob_private                   \
{                                                       \
	friend typename Tag::type get(Tag) { return M; }    \
};                                                      \
template struct CLASS##_##MEMBER##_rob_private<         \
CLASS##_##MEMBER##_rob_tag<TYPE> , &CLASS::MEMBER>;     \

#define ROB_PRIVATE_MEMBER_INST_FN(CLASS, TYPE, MEMBER)	\
template<typename T>                                    \
struct CLASS##_##MEMBER##_rob_tag {                     \
  typedef T type;                                       \
  friend type get(CLASS##_##MEMBER##_rob_tag);          \
};                                                      \
template<typename Tag, typename Tag::type M>            \
struct CLASS##_##MEMBER##_rob_private                   \
{                                                       \
	friend typename Tag::type get(Tag) { return M; }    \
};                                                      \
template struct CLASS##_##MEMBER##_rob_private<         \
CLASS##_##MEMBER##_rob_tag<TYPE> , &CLASS::MEMBER>;     \

#define ROB_PRIVATE_MEMBER_ACCESS(CLASS, INSTANCE, TYPE, MEMBER) \
	(INSTANCE.*get(CLASS##_##MEMBER##_rob_tag<TYPE>()))          \

////////////////////////////////////////////////////////////////////////////////////////
//// Actually use the macros
////////////////////////////////////////////////////////////////////////////////////////

ROB_PRIVATE_MEMBER_INST(MultAdd, int, x);
ROB_PRIVATE_MEMBER_INST(MultAdd, int, y);
ROB_PRIVATE_MEMBER_INST_FN(MultAdd, int(MultAdd::*)(), add);
ROB_PRIVATE_MEMBER_INST_FN(MultAdd, int(MultAdd::*)(), multiply);

////////////////////////////////////////////////////////////////////////////////////////

//ROB_PRIVATE_MEMBER_INST_FN(MultAdd, int(__thiscall *)(), add);
int extractMultAdd(void* math)
{
	// No need to pass as void*
	MultAdd *pMA(reinterpret_cast<MultAdd*>(math));

	// ROB_PRIVATE_MEMBER_INST(MultAdd, int, x); // Note that unfortunately this isn't possible

	// The 4 values, retrieved in a portable way
	int robbed_x = ROB_PRIVATE_MEMBER_ACCESS(MultAdd, *pMA, int, x);
	int robbed_y = ROB_PRIVATE_MEMBER_ACCESS(MultAdd, *pMA, int, y);
	int robbed_add = ROB_PRIVATE_MEMBER_ACCESS(MultAdd, *pMA, int(MultAdd::*)(), add)();	  // Note we're calling function with ()
	int robbed_mul = ROB_PRIVATE_MEMBER_ACCESS(MultAdd, *pMA, int(MultAdd::*)(), multiply)(); // Note we're calling function with ()

	std::cout << robbed_x << " "
			  << robbed_y << " "
			  << robbed_add << " "
			  << robbed_mul;

	return 0;
}

int main()
{
    MultAdd variable;
    printf("%d\n", extractMultAdd(&variable));
    return 0;
}