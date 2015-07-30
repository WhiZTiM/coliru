

#define DEFINE_STRUCT2(Name, a, b) \
    RecursiveAttribute Pack(Name p) { \
        std::vector<RecursiveAttribute> result; \
        result.reserve(2); \
        result.push_back(Pack(p.a)); \
        result.push_back(Pack(p.b)); \
        return Pack(std::move(result); \
    } \
    void Unpack(const RecursiveAttribute& attr, Name& out) { \
        auto& vec = boost::get<const std::vector<RecursiveAttribute>&>(attr); \
        Unpack(vec.at(0), out.a); \
        Unpack(vec.at(1), out.b)); \
    }

#define DEFINE_STRUCT3(Name, a, b, c) \
    RecursiveAttribute Pack(const Name& p) { \
        std::vector<RecursiveAttribute> result; \
        result.reserve(3); \
        result.push_back(Pack(p.a)); \
        result.push_back(Pack(p.b)); \
        result.push_back(Pack(p.c)); \
        return Pack(std::move(result)); \
    } \
    RecursiveAttribute Pack(Name&& p) { \
        std::vector<RecursiveAttribute> result; \
        result.reserve(3); \
        result.push_back(Pack(std::move(p.a))); \
        result.push_back(Pack(std::move(p.b))); \
        result.push_back(Pack(std::move(p.c))); \
        return Pack(std::move(result)); \
    } \
    void Unpack(const RecursiveAttribute& attr, Name& out) { \
        auto& vec = boost::get<const std::vector<RecursiveAttribute>&>(attr); \
        Unpack(vec.at(0), out.a); \
        Unpack(vec.at(1), out.b); \
        Unpack(vec.at(2), out.c); \
    }

    
    
    
struct Point
{
    int x;
    int y;
};


DEFINE_STRUCT2(Point, x, y)



struct Stats
{
    Stats cumulative;
    Stats interval;
    Timestamp timestamp;
};


DEFINE_STRUCT3(Stats, cumulative, interval, timestamp)