#include <cwchar>
#include <cwctype>
#include <cmath>
#include <string>
#include <sstream>
#include <cstdint>
#include <cassert>
#include <tuple>
#include <memory>

using namespace std;

inline long fn_Asc(wstring str)
{
    return (str.empty() ? -1 : (long)str[0]);
}

inline wstring fn_Hex(uint64_t v)
{
    wstring retval = L"";
    do
    {
        long digit = (int)(v % 0x10);
        v /= 0x10;
        retval = (wchar_t)(digit <= 9 ? '0' + digit : 'A' + digit - 0xA) + retval;
    }
    while(v > 0);
    return retval;
}

inline wstring fn_Oct(uint64_t v)
{
    wstring retval = L"";
    do
    {
        long digit = (int)(v % 8);
        v /= 8;
        retval = (wchar_t)('0' + digit) + retval;
    }
    while(v > 0);
    return retval;
}

inline wstring fn_Str(uint64_t v)
{
    wstring retval = L"";
    do
    {
        long digit = (int)(v % 10);
        v /= 10;
        retval = (wchar_t)('0' + digit) + retval;
    }
    while(v > 0);
    return retval;
}

inline wstring fn_Str(int64_t v)
{
    return v < 0 ? L"-" + fn_Str((uint64_t)-v) : fn_Str((uint64_t)v);
}

inline wstring fn_Str(double v)
{
    wostringstream ss;
    ss << uppercase << v;
    return ss.str();
}

inline wstring fn_LTrim(wstring str)
{
    size_t pos = str.find_first_not_of(L" ");
    if(pos == wstring::npos)
        return L"";
    return str.substr(pos);
}

inline wstring fn_RTrim(wstring str)
{
    size_t pos = str.find_last_not_of(L" ");
    if(pos == wstring::npos)
        return L"";
    return str.substr(0, pos + 1);
}

inline wstring fn_Right(wstring str, long length)
{
    if(length <= 0)
        return L"";
    if((size_t)length >= str.size())
        return str;
    return str.substr(str.size() - length);
}

inline long fn_Sgn(int64_t v)
{
    if(v < 0)
        return -1;
    if(v > 0)
        return 1;
    return 0;
}

inline long fn_Sgn(uint64_t v)
{
    if(v > 0)
        return 1;
    return 0;
}

inline long fn_Sgn(double v)
{
    if(v < 0)
        return -1;
    if(v > 0)
        return 1;
    return 0;
}

inline long fn_InStr(wstring a, wstring b, long start = 1)
{
    size_t retval = a.find(b, (size_t)(start - 1));
    if(retval == wstring::npos)
        return 0;
    return retval + 1;
}

inline wstring fn_UCase(wstring str)
{
    wstring retval;
    retval.reserve(str.size());
    for(size_t i = 0; i < str.size(); i++)
        retval += (wchar_t)std::towupper(str[i]);
    return retval;
}

inline wstring fn_LCase(wstring str)
{
    wstring retval;
    retval.reserve(str.size());
    for(size_t i = 0; i < str.size(); i++)
        retval += (wchar_t)std::towlower(str[i]);
    return retval;
}

inline bool iswodigit(wint_t ch)
{
    return (ch >= '0' && ch <= '7');
}

inline double fn_Val(wstring svalue)
{
    if(svalue.empty())
        return NAN;
    size_t stringIndex = 0;
    int peekChar = svalue[stringIndex++];
    auto getChar = [&]()->int
    {
        int retval = peekChar;
        if(stringIndex >= svalue.size())
            peekChar = EOF;
        else
            peekChar = svalue[stringIndex++];
        return retval;
    };
    double retval = 0;
    if(peekChar == '&')
    {
        getChar();
        if(peekChar == 'h' || peekChar == 'H')
        {
            getChar();
            if(!std::iswxdigit(peekChar))
                return NAN;
            while(std::iswxdigit(peekChar))
            {
                int digit;
                if(std::iswdigit(peekChar))
                    digit = peekChar - '0';
                else if(std::iswlower(peekChar))
                    digit = peekChar - 'a' + 0xA;
                else
                    digit = peekChar - 'A' + 0xA;
                retval *= 0x10;
                retval += digit;
                getChar();
            }
            if(peekChar == '_')
                return NAN;
            if(peekChar != EOF)
                return NAN;
            return retval;
        }
        else if(iswodigit(peekChar) || peekChar == 'o' || peekChar == 'O')
        {
            if(peekChar == 'o' || peekChar == 'O')
                getChar();
            if(!iswodigit(peekChar))
            {
                return NAN;
            }
            while(iswodigit(peekChar))
            {
                int digit = peekChar - '0';
                retval *= 8;
                retval += digit;
                getChar();
            }
            if(peekChar != EOF)
                return NAN;
            return retval;
        }
        return NAN;
    }
    bool gotAnyIntegerDigits = false;
    while(std::iswdigit(peekChar))
    {
        int digit = getChar() - '0';
        retval *= 10;
        retval += digit;
        gotAnyIntegerDigits = true;
    }
    if(peekChar == '.')
    {
        getChar();
        double factor = 1;
        if(!gotAnyIntegerDigits && !std::iswdigit(peekChar))
        {
            return NAN;
        }
        while(std::iswdigit(peekChar))
        {
            int digit = getChar() - '0';
            factor *= 0.1;
            retval += digit * factor;
        }
    }
    if(peekChar == 'e' || peekChar == 'E' || peekChar == 'f' || peekChar == 'F')
    {
        getChar();
        bool isExponentNegative = false;
        if(peekChar == '+' || peekChar == '-')
            isExponentNegative = (getChar() == '-');
        if(!std::iswdigit(peekChar))
            return NAN;
        int exponent = 0;
        while(std::iswdigit(peekChar))
        {
            int digit = getChar() - '0';
            if(exponent >= 10000000)
                continue;
            exponent *= 10;
            exponent += digit;
        }
        if(isExponentNegative)
            exponent = -exponent;
        retval *= std::pow(10.0L, exponent);
    }
    if(peekChar != EOF)
        return NAN;
    return retval;
}

template <typename T, size_t N = 1>
struct ArrayDescriptor final
{
    T *elements;
    long base[N];
    size_t size[N];
    template <typename ...Args>
    ArrayDescriptor(T *elements, Args... args)
        : ArrayDescriptor(args...)
    {
        static_assert(sizeof...(args) == 2 * N, "array index count doesn't match");
        this->elements = elements;
    }
    ~ArrayDescriptor()
    {
        delete []elements;
    }
    ArrayDescriptor(const ArrayDescriptor &) = delete;
    void operator =(const ArrayDescriptor &) = delete;
private:
    template <typename ...Args>
    ArrayDescriptor(long base, size_t size, Args... args)
        : ArrayDescriptor(args...)
    {
        constexpr size_t indexNumber = N - (sizeof...(args) / 2 + 1);
        this->base[indexNumber] = base;
        this->size[indexNumber] = size;
    }
    ArrayDescriptor()
    {
    }
    constexpr size_t arrayIndexSize(size_t indexNumber) const
    {
        return (indexNumber + 1 < N) ? arrayIndexSize(indexNumber + 1) * size[indexNumber] : (indexNumber < N ? size[indexNumber] : 1);
    }
    template <typename ...Args>
    inline T *atHelper(long index, Args... args) const
    {
        T *ptr = atHelper(args...);
        constexpr size_t indexNumber = N - (sizeof...(args) + 1);
        assert((size_t)(index - base[indexNumber]) < size[indexNumber]);
        return ptr + (arrayIndexSize(indexNumber + 1) * (index - base[indexNumber]));
    }
    inline T * atHelper() const
    {
        return elements;
    }
public:
    template <typename ...Args>
    inline T *at(Args... args) const
    {
        static_assert(sizeof...(args) == N, "incorrect argument count for array");
        return atHelper(args...);
    }
    inline long lbound(long index) const
    {
        assert(index >= 1 && index <= (long)N);
        return base[index - 1];
    }
    inline long ubound(long index) const
    {
        assert(index >= 1 && index <= (long)N);
        return base[index - 1] + size[index - 1] - 1;
    }
};


shared_ptr<const ArrayDescriptor<long, 2> > v_text_0;
shared_ptr<const ArrayDescriptor<float, 2> > v_picture_0;
long v_IterationCount_0;
float v_LightX_0;
float v_LightY_0;
float v_LightZ_0;
void fn_WriteByte_0(long);
void fn_WriteChar_0(long v_Ch_0);
void fn_WriteString_0(wstring v_S_0);
void fn_WriteLn_0();
void fn_WriteInteger_0(long v_v_0);
void fn_WriteDouble_0(double v_v_1);
void fn_WriteAllText_0();
float fn_getDitherValue_0(long v_x_0, long v_y_0);
void fn_DitherPicture_0();
float fn_ComputePixel_0(float v_x_1, float v_y_1);
void fn_ComputePicture_0();
int main()
{
    v_text_0 = (shared_ptr<const ArrayDescriptor<long, 2> >(new ArrayDescriptor<long, 2>(new (long[16000]), 1, 160, 1, 100)));
    v_picture_0 = (shared_ptr<const ArrayDescriptor<float, 2> >(new ArrayDescriptor<float, 2>(new (float[16000]), 1, 160, 1, 100)));
    v_IterationCount_0 = (0x100L);
    v_LightX_0 = (((float)(1L)) / (std::sqrt(3.f)));
    v_LightY_0 = (((float)(1L)) / (std::sqrt(3.f)));
    v_LightZ_0 = (((float)(1L)) / (std::sqrt(3.f)));
    (*((&fn_ComputePicture_0)))();
    (*((&fn_DitherPicture_0)))();
    (*((&fn_WriteAllText_0)))();
    return 0;
}

void fn_WriteByte_0(long v_t_0_0)
{
    putchar(v_t_0_0);
}
;

void fn_WriteChar_0(long v_Ch_0)
{
    {
        *(&v_Ch_0) = ((*(&v_Ch_0)) % (0x110000L));
        if((*(&v_Ch_0)) < (0x80L))
        {
            (*((&fn_WriteByte_0)))(*(&v_Ch_0));
        }

        else if((*(&v_Ch_0)) < (0x800L))
        {
            (*((&fn_WriteByte_0)))(((*(&v_Ch_0)) / (0x40L)) + (0xC0L));
            (*((&fn_WriteByte_0)))(((*(&v_Ch_0)) & (63L)) + (0x80L));
        }

        else if((*(&v_Ch_0)) < (0x10000L))
        {
            (*((&fn_WriteByte_0)))(((*(&v_Ch_0)) / (0x1000L)) + (0xE0L));
            (*((&fn_WriteByte_0)))((((*(&v_Ch_0)) / (0x40L)) & (63L)) + (0x80L));
            (*((&fn_WriteByte_0)))(((*(&v_Ch_0)) & (63L)) + (0x80L));
        }

        else
        {
            (*((&fn_WriteByte_0)))(((*(&v_Ch_0)) / (0x40000L)) + (0xF0L));
            (*((&fn_WriteByte_0)))((((*(&v_Ch_0)) / (0x1000L)) & (63L)) + (0x80L));
            (*((&fn_WriteByte_0)))((((*(&v_Ch_0)) / (0x40L)) & (63L)) + (0x80L));
            (*((&fn_WriteByte_0)))(((*(&v_Ch_0)) & (63L)) + (0x80L));
        }
    }
}

void fn_WriteString_0(wstring v_S_0)
{
    {
        {
            long v_i_0;
            long * t_1;
            long t_2;
            long t_3;
            bool t_4 = true;
            t_1 = (&v_i_0);
            *t_1 = (1L);
            for(;;)
            {
                t_2 = ((*(&v_S_0)).size());
                t_3 = ((long)((uint8_t)1U));
                if(t_4)
                    t_4 = false;
                else
                    *t_1 += t_3;
                if(t_3 < 0 && *t_1 < t_2)
                    break;
                if(t_3 > 0 && *t_1 > t_2)
                    break;
                {
                    (*((&fn_WriteChar_0)))(fn_Asc((&v_S_0)->substr((size_t)(*(&v_i_0)) - 1, (size_t)(1L))));
                }
            }
            l_0: ;
        }
    }
}

void fn_WriteLn_0()
{
    {
        (*((&fn_WriteChar_0)))(10L);
    }
}

void fn_WriteInteger_0(long v_v_0)
{
    {
        (*((&fn_WriteString_0)))(fn_Str((int64_t)*(&v_v_0)));
    }
}

void fn_WriteDouble_0(double v_v_1)
{
    {
        (*((&fn_WriteString_0)))(fn_Str(*(&v_v_1)));
    }
}

void fn_WriteAllText_0()
{
    {
        {
            long v_y_2;
            long * t_5;
            long t_6;
            long t_7;
            bool t_8 = true;
            t_5 = (&v_y_2);
            *t_5 = ((*(&v_text_0))->lbound(2L));
            for(;;)
            {
                t_6 = ((*(&v_text_0))->ubound(2L));
                t_7 = ((long)((uint8_t)1U));
                if(t_8)
                    t_8 = false;
                else
                    *t_5 += t_7;
                if(t_7 < 0 && *t_5 < t_6)
                    break;
                if(t_7 > 0 && *t_5 > t_6)
                    break;
                {
                    {
                        long v_x_2;
                        long * t_9;
                        long t_10;
                        long t_11;
                        bool t_12 = true;
                        t_9 = (&v_x_2);
                        *t_9 = ((*(&v_text_0))->lbound(1L));
                        for(;;)
                        {
                            t_10 = ((*(&v_text_0))->ubound(1L));
                            t_11 = ((long)((uint8_t)1U));
                            if(t_12)
                                t_12 = false;
                            else
                                *t_9 += t_11;
                            if(t_11 < 0 && *t_9 < t_10)
                                break;
                            if(t_11 > 0 && *t_9 > t_10)
                                break;
                            {
                                (*((&fn_WriteChar_0)))(*((*(&v_text_0))->at(*(&v_x_2), *(&v_y_2))));
                            }
                        }
                        l_2: ;
                    }
                    if((*(&v_y_2)) < ((*(&v_text_0))->ubound(2L)))
                    {
                        (*((&fn_WriteLn_0)))();
                    }
                }
            }
            l_1: ;
        }
    }
}

float fn_getDitherValue_0(long v_x_0, long v_y_0)
{
    float return_value;
    return_value = (0.0f);
    {
        long v_v_2;
        *(&v_x_0) = ((long)(((uint64_t)*(&v_x_0)) % ((uint64_t)16ULL)));
        *(&v_y_0) = ((long)(((uint64_t)*(&v_y_0)) % ((uint64_t)16ULL)));
        *(&v_x_0) = ((*(&v_x_0)) ^ (*(&v_y_0)));
        v_v_2 = (0L);
        if(((*(&v_x_0)) & (1L)) != (0L))
        {
            *(&v_v_2) = ((*(&v_v_2)) | (0x80L));
        }
        if(((*(&v_x_0)) & (2L)) != (0L))
        {
            *(&v_v_2) = ((*(&v_v_2)) | (32L));
        }
        if(((*(&v_x_0)) & (4L)) != (0L))
        {
            *(&v_v_2) = ((*(&v_v_2)) | (8L));
        }
        if(((*(&v_x_0)) & (8L)) != (0L))
        {
            *(&v_v_2) = ((*(&v_v_2)) | (2L));
        }
        if(((*(&v_y_0)) & (1L)) != (0L))
        {
            *(&v_v_2) = ((*(&v_v_2)) | (0x40L));
        }
        if(((*(&v_y_0)) & (2L)) != (0L))
        {
            *(&v_v_2) = ((*(&v_v_2)) | (16L));
        }
        if(((*(&v_y_0)) & (4L)) != (0L))
        {
            *(&v_v_2) = ((*(&v_v_2)) | (4L));
        }
        if(((*(&v_y_0)) & (8L)) != (0L))
        {
            *(&v_v_2) = ((*(&v_v_2)) | (1L));
        }
        *(&return_value) = (((float)((*(&v_v_2)) + (1L))) / ((float)(0x100L)));
    }
    return return_value;
}

void fn_DitherPicture_0()
{
    {
        {
            long v_y_3;
            long * t_13;
            long t_14;
            long t_15;
            bool t_16 = true;
            t_13 = (&v_y_3);
            *t_13 = ((*(&v_text_0))->lbound(2L));
            for(;;)
            {
                t_14 = ((*(&v_text_0))->ubound(2L));
                t_15 = ((long)((uint8_t)1U));
                if(t_16)
                    t_16 = false;
                else
                    *t_13 += t_15;
                if(t_15 < 0 && *t_13 < t_14)
                    break;
                if(t_15 > 0 && *t_13 > t_14)
                    break;
                {
                    {
                        long v_x_3;
                        long * t_17;
                        long t_18;
                        long t_19;
                        bool t_20 = true;
                        t_17 = (&v_x_3);
                        *t_17 = ((*(&v_text_0))->lbound(1L));
                        for(;;)
                        {
                            t_18 = ((*(&v_text_0))->ubound(1L));
                            t_19 = ((long)((uint8_t)1U));
                            if(t_20)
                                t_20 = false;
                            else
                                *t_17 += t_19;
                            if(t_19 < 0 && *t_17 < t_18)
                                break;
                            if(t_19 > 0 && *t_17 > t_18)
                                break;
                            {
                                float v_v_3;
                                float v_ditherValue_0;
                                v_v_3 = ((*((*(&v_picture_0))->at(*(&v_x_3), *(&v_y_3)))) * ((float)(3L)));
                                v_ditherValue_0 = ((*((&fn_getDitherValue_0)))(*(&v_x_3), *(&v_y_3)));
                                if((*(&v_v_3)) < (*(&v_ditherValue_0)))
                                {
                                    *((*(&v_text_0))->at(*(&v_x_3), *(&v_y_3))) = (fn_Asc(wstring(L"\u2588")));
                                }

                                else if((*(&v_v_3)) < ((*(&v_ditherValue_0)) + ((float)(1L))))
                                {
                                    *((*(&v_text_0))->at(*(&v_x_3), *(&v_y_3))) = (fn_Asc(wstring(L"\u2593")));
                                }

                                else if((*(&v_v_3)) < ((*(&v_ditherValue_0)) + ((float)(2L))))
                                {
                                    *((*(&v_text_0))->at(*(&v_x_3), *(&v_y_3))) = (fn_Asc(wstring(L"\u2592")));
                                }

                                else if((*(&v_v_3)) < ((*(&v_ditherValue_0)) + ((float)(3L))))
                                {
                                    *((*(&v_text_0))->at(*(&v_x_3), *(&v_y_3))) = (fn_Asc(wstring(L"\u2591")));
                                }

                                else
                                {
                                    *((*(&v_text_0))->at(*(&v_x_3), *(&v_y_3))) = (fn_Asc(wstring(L" ")));
                                }
                            }
                        }
                        l_4: ;
                    }
                }
            }
            l_3: ;
        }
    }
}

float fn_ComputePixel_0(float v_x_1, float v_y_1)
{
    float return_value;
    return_value = (0.0f);
    {
        float v_rSquared_0;
        float v_z_0;
        float v_dot_0;
        v_rSquared_0 = (((*(&v_x_1)) * (*(&v_x_1))) + ((*(&v_y_1)) * (*(&v_y_1))));
        if((*(&v_rSquared_0)) >= ((float)(1L)))
        {
            *(&return_value) = ((float)(0L));
            return return_value;
        }
        v_z_0 = (std::sqrt(((float)(1L)) - (*(&v_rSquared_0))));
        v_dot_0 = ((((*(&v_LightX_0)) * (*(&v_x_1))) + ((*(&v_LightY_0)) * (*(&v_y_1)))) + ((*(&v_LightZ_0)) * (*(&v_z_0))));
        if((*(&v_dot_0)) < ((float)(0L)))
        {
            *(&v_dot_0) = ((float)(0L));
        }
        *(&return_value) = ((0.349999994f) + ((0.649999976f) * (*(&v_dot_0))));
    }
    return return_value;
}

void fn_ComputePicture_0()
{
    {
        {
            long v_y_4;
            long * t_21;
            long t_22;
            long t_23;
            bool t_24 = true;
            t_21 = (&v_y_4);
            *t_21 = ((*(&v_text_0))->lbound(2L));
            for(;;)
            {
                t_22 = ((*(&v_text_0))->ubound(2L));
                t_23 = ((long)((uint8_t)1U));
                if(t_24)
                    t_24 = false;
                else
                    *t_21 += t_23;
                if(t_23 < 0 && *t_21 < t_22)
                    break;
                if(t_23 > 0 && *t_21 > t_22)
                    break;
                {
                    {
                        long v_x_4;
                        long * t_25;
                        long t_26;
                        long t_27;
                        bool t_28 = true;
                        t_25 = (&v_x_4);
                        *t_25 = ((*(&v_text_0))->lbound(1L));
                        for(;;)
                        {
                            t_26 = ((*(&v_text_0))->ubound(1L));
                            t_27 = ((long)((uint8_t)1U));
                            if(t_28)
                                t_28 = false;
                            else
                                *t_25 += t_27;
                            if(t_27 < 0 && *t_25 < t_26)
                                break;
                            if(t_27 > 0 && *t_25 > t_26)
                                break;
                            {
                                float v_xf_0;
                                float v_yf_0;
                                v_xf_0 = (((((float)((*(&v_x_4)) - ((*(&v_text_0))->lbound(1L)))) / ((float)(((*(&v_text_0))->ubound(1L)) - ((*(&v_text_0))->lbound(1L))))) * ((float)(2L))) - ((float)(1L)));
                                v_yf_0 = (((float)(1L)) - ((((float)((*(&v_y_4)) - ((*(&v_text_0))->lbound(2L)))) / ((float)(((*(&v_text_0))->ubound(2L)) - ((*(&v_text_0))->lbound(2L))))) * ((float)(2L))));
                                *((*(&v_picture_0))->at(*(&v_x_4), *(&v_y_4))) = ((*((&fn_ComputePixel_0)))(*(&v_xf_0), *(&v_yf_0)));
                            }
                        }
                        l_6: ;
                    }
                }
            }
            l_5: ;
        }
    }
}

