#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <boost/filesystem.hpp>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class ILoadset
{
public:
    // virtual destructor
    virtual ~ILoadset() = 0;

    // retrieves the fully qualified loadset header path
    virtual boost::filesystem::path getHeaderPath() const = 0;
};

// destructor - inline to prevent duplicate symbol definitions
inline ILoadset::~ILoadset() = default;

class Loadset : public ILoadset
{
public:
    Loadset(const boost::filesystem::path rHeaderPath)
        : ILoadset()  // is this necessary?
        , mHeaderPath(rHeaderPath)
    {}

    // prevent copy construction
    Loadset(const Loadset&) = delete;
    
    // delete the assignment operator
    Loadset& operator=(const Loadset&) = delete;
    
    // move assignment
    Loadset& operator=(Loadset&& rhs) = default;

    // destructor
    virtual ~Loadset() = 0;
    
    // retrieves the fully qualified loadset header path
    virtual boost::filesystem::path getHeaderPath() const {
        return mHeaderPath;
    };
    
protected:
    boost::filesystem::path mHeaderPath;
};

inline  Loadset::~Loadset() = default;

/** A concrete implementation of ILoadset which deals with 615A. */
class C615ALoadset : public Loadset
{
public:
    // default constructor
    explicit C615ALoadset(
        const boost::filesystem::path& rHeaderPath,
        const uint16_t rVersion)
        : Loadset(rHeaderPath)
        , mVersion(rVersion)
    {}
    
    inline uint16_t getVersion() const {
        return mVersion;
    }
private:
    // Version number that the loadset adheres to.
    uint16_t mVersion;
};

// define a move only LoadsetList
class LoadsetList : public std::vector<std::unique_ptr<ILoadset>>
{
public:
    // default constructor
    LoadsetList() = default;

    // prevent copy construction
    LoadsetList(const LoadsetList&) = delete;

    // move constructor
    LoadsetList(LoadsetList&& rhs) = default;

    // delete the assignment operator
    LoadsetList& operator=(const LoadsetList&) = delete;
    
    // move assignment
    LoadsetList& operator=(LoadsetList&& rhs) = default;

    // destructor
    virtual ~LoadsetList() = default;

    // filter entries from the LoadsetList
    size_t removeContainingPath(const boost::filesystem::path& rBasePath) {
        size_t numRemoved = 0;
        LoadsetList::erase(std::remove_if(begin(), end(),
            [&rBasePath, &numRemoved](const std::unique_ptr<ILoadset>& next)->bool {
                if (next) {
                    if (next->getHeaderPath().generic_string().find(
                        rBasePath.generic_string()) != std::string::npos) {
                        numRemoved++;
                        return true;
                    }
                    // do not remove
                    return false;
                }
                // nullptr - just remove the node
                // this should not happen
                numRemoved++;
                return true;
            }), end());
        return numRemoved;
    };
};


int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;

    auto loadset1 = std::make_unique<C615ALoadset>("/home/john/test/loadset1.luh", 0x8001);
    auto loadset2 = std::make_unique<C615ALoadset>("/home/pete/test/loadset1.luh", 0x8001);
    LoadsetList list1;
    list1.emplace_back(std::move(loadset1));
    list1.emplace_back(std::move(loadset2));
    
    std::cout << list1.size() << std::endl;
    
    LoadsetList list2 = std::move(list1);
    auto numRemoved = list2.removeContainingPath("/home/john");
    std::cout << numRemoved << std::endl;    
}
