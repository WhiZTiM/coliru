#include <iostream>
#include <string>
#include <vector>
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>
#include <functional>
#include <map>

typedef boost::variant<int, float, bool, std::string> TagValue;
struct Tag
{
    int id;
    TagValue value;
    int timestamp;
};

std::ostream& operator<<(std::ostream& os, const Tag& tag)
{
    os << "time: " << tag.timestamp << " id: " << tag.id << " value: " << tag.value;
    return os;
}

typedef std::vector<Tag> TagCollection;

struct Trigger
{
    virtual bool process(const Tag &tag, TagCollection &tags) = 0;
};

struct ValueChangedTrigger: Trigger
{
    bool process(const Tag &tag, TagCollection &tags) override
    {
        if (!lastTag.value.empty() && lastTag.value == tag.value)
            return false;
            
        lastTag = tag;
        tags.push_back(tag);
        return true;
    }
    Tag lastTag;
};

struct ValueBound: Trigger
{
    ValueBound(const TagValue &_lowerBound, const TagValue &_upperBound)
        : lowerBound(_lowerBound), upperBound(_upperBound)
        {
        }
    bool process(const Tag &tag, TagCollection &tags) override
    {    
        if (!lowerBound.empty() && tag.value < lowerBound)
            return false;
        
        if (!upperBound.empty() && upperBound < tag.value)
            return false;
            
        tags.push_back(tag);
        return true;
    }
    
    TagValue lowerBound;
    TagValue upperBound;
};

struct ValueDelta: Trigger
{
    bool process(const Tag &tag, TagCollection &tags) override
    {
        tags.push_back(tag);
    	auto newTag = tag;
    	newTag.value = !boost::get<bool>(tag.value);
		tags.push_back(std::move(newTag));

        return true;
    }
};

int main()
{
    TagCollection tags
    {
        {1, 1, 1},
        {1, 2, 2},
        {2, 2, 3},
        {1, 1, 4},
        {2, 4, 5},
        {2, 6, 6},
        {2, 7, 7},
        {2, 5, 8},
        {2, 3, 9},
        {3, 3.01f, 10},
        {3, 3.02f, 11},
        {3, 3.02f, 12},
        {4, true, 13},
    };
    
    std::map<int, Trigger*> processors
    {
        {1, new ValueChangedTrigger},
        {2, new ValueBound(3, 6)},
        {3, new ValueChangedTrigger},
        {4, new ValueDelta}
    };
    
    TagCollection resultTags;
    for(const auto &tag : tags)
    {
        auto it = processors.find(tag.id);
        if (it != processors.end())
        {
            if (!it->second->process(tag, resultTags))
                std::cout << tag << " filtered" << std::endl;
        }
    }
    
    for(const auto &tag : resultTags)
    {
        std::cout << tag << std::endl;
    }
}
