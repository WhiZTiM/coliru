#include <string>
#include <set>
#include <unordered_map>
#include <iostream>
#include <cstring>

struct CldrValidRange
{
    std::string Lowest;
    std::string Highest;
};

struct CldrValidRangeSort
{
    typedef void is_transparent;
    
    // We don't want to do lexographic string compares either, sice the value "BTA" is NOT
    // in the range BA-BZ. So we'll we'll change the underlying string comparison to order
    // by length first, then compare each character. This gives us the ordering of
    //
    // A-Z 0-9 AA-AZ A0-A9 BA-BZ ... ZA-ZZ AAA-AAZ ...
    //
    // Which fits in to how we want to compare the ranges given to us by the CLDR data
    //
    // We're also assuming each input range only has strings of the same length
    
    bool operator()(const CldrValidRange& left, const CldrValidRange& right)
    {
        // We're assuming that there is are no colliding ranges
        if (left.Lowest.size() == right.Lowest.size())
        {
            return left.Lowest < right.Lowest;
        }
        else
        {
            return left.Lowest.size() < right.Lowest.size();
        }
    }
    
    bool operator()(const char* left, const CldrValidRange& right)
    {
        size_t left_len = std::strlen(left);
        
        if (left_len == right.Lowest.size())
        {
            return left < right.Lowest;
        }
        else
        {
            return left_len < right.Lowest.size();
        }
    }

    bool operator()(const CldrValidRange& left, const char* right)
    {
        size_t right_len = std::strlen(right);
        
        if (left.Highest.size() == right_len)
        {
            return left.Highest < right;
        }
        else
        {
            return left.Highest.size() < right_len;
        }
    }
};

struct CldrData
{
    std::set<CldrValidRange, CldrValidRangeSort> AllowedValues;

    bool Contains(const char* value)
    {
        auto it = AllowedValues.find(value);
        return (it != AllowedValues.end());
    }
};


int main()
{
    CldrData data
    {{
        CldrValidRange{"AB", "AD"},
        CldrValidRange{"AF", "AZ"},
        CldrValidRange{"CA", "CZ"},
        CldrValidRange{"D1", "D2"},
        CldrValidRange{"D4", "D5"},
    }};
    
    auto check = [&data](const char* val)
    {
        std::cout << std::boolalpha << val << ": " << data.Contains(val) << std::endl;
    };
    
    check("A");
    check("AA");
    check("AB");
    check("AB0");
    check("ABZ");
    check("AC");
    check("AD");
    check("AE");
    check("AF");
    
    check("BA");
    check("BZ");
    
    check("CA");
    check("CZ");
    
    return 0;    
}


/*
enum class ValidityStatus
{
    Regular,
    Special,
    Deprecated,
    PrivateUse,
    MacroRegion
};

struct DataKey
{
    std::string Type;
    ValidityStatus Status;
};

class CldrValidityData
{
    // each data set represented by a 'type' and 'idStatus' value
    std::unordered_map<DataKey, CldrData> Sections;
};*/
