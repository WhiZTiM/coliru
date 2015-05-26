#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <functional>

enum class combine_method { sum, min, max };

struct statistic_prereq
{
    combine_method method;
    
    std::uint64_t required_value;
    std::vector<std::string> statistic_names;
};

template<class PrereqType>
struct base_progress_data
{
    
    std::string name;
    std::vector<PrereqType> prereqs;
    std::vector<statistic_prereq> statistic_prereqs;
};

struct unlockable_data : base_progress_data<unsigned>
{
    unsigned index;

    std::unordered_set<unsigned> unlock_indices;
};

using statistics_map = std::map<std::string, std::uint64_t>;

struct combiner
{
    statistics_map const& statistics;
    combine_method method;
    
    std::uint64_t operator()(std::uint64_t old_value, std::string const& name)
    {
        auto it = statistics.find(name);
        if (it == statistics.end())
            return old_value;
            
        auto const value = it->second;
        switch (method)
        {
        case combine_method::sum:
            return value + old_value;
        case combine_method::min:
            return std::min(value, old_value);
        case combine_method::max:
            return std::max(value, old_value);
        }
        
        return old_value;
    }
};

#include <iostream>

int main()
{
    statistics_map statistics;
    std::vector<base_progress_data<std::string>> raw_data;
    
    // prepare input
    raw_data.push_back({ "versionBase", {}, {} });
    raw_data.push_back({ "groundTypeForest" , { "versionBase" }, {} });
    
    raw_data.push_back(
        { "groundTypeDarkForest",
            { "groundTypeForest" },
            {
                { combine_method::sum, 10,
                    {
                        "killedEnemyCharacter_wolf",
                        "killedEnemyCharacter_iceWolf"
                    }
                }
            }
        });
        
    raw_data.push_back( { "buildingTypeTradingPostB", { "versionBase" }, { { combine_method::sum, 50, { "resourceDelivered_total" } } } });
    raw_data.push_back( { "buildingTypeTradingPostC", { "buildingTypeTradingPostB" }, { { combine_method::sum, 500, { "resourceDelivered_total" } } } });
    raw_data.push_back( { "buildingTypeTradingPostD", { "buildingTypeTradingPostC" }, { { combine_method::sum, 5000, { "resourceDelivered_total" } } } });
    
    // fill real data
    std::vector<unlockable_data> unlockables(raw_data.size());
    std::unordered_set<std::string> unlocked_tags = { "versionBase", "groundTypeForest" };

    std::unordered_map<std::string, unsigned> data_indices;
    data_indices.reserve(raw_data.size());
    
    for (unsigned i = 0; i < raw_data.size(); ++i)
    {
        data_indices.emplace(raw_data[i].name, i);
    }
    
    // move and adjust raw data
    for(auto& entry : raw_data)
    {
        auto index = data_indices[entry.name];
        auto& u = unlockables[index];
        u.index = index;
        u.name = std::move(entry.name);
        
        // wire up prereq indices
        u.prereqs.reserve(entry.prereqs.size());
        for (auto const& name : entry.prereqs)
        {
            auto index_it = data_indices.find(name);
            if (index_it != data_indices.end())
                u.prereqs.push_back(data_indices[name]);
            else
                std::cout << "unknown prereq '" << name << "'\n";
        }
            
        u.statistic_prereqs = std::move(entry.statistic_prereqs);
    }
    
    // wire up unlock indices
    for (auto& u : unlockables)
    {
        for (auto const i : u.prereqs)
        {
            unlockables[i].unlock_indices.insert(u.index);
        }
    }
    
    std::cout << "\n================\n\n";
    
    // check default unlocks
    std::function<bool(unsigned)> check_unlocked = [&](unsigned i) -> bool
    {
        auto& u = unlockables[i];
        
        if (unlocked_tags.find(u.name) != unlocked_tags.end())
            return true;
        
        for (auto const i : u.prereqs)
        {
            if (!check_unlocked(i))
                return false;
        }
        
        for (auto const& sp : u.statistic_prereqs)
        {
            std::uint64_t value = std::accumulate(sp.statistic_names.begin(), sp.statistic_names.end(), std::uint64_t(0), combiner{ statistics, sp.method });
            if (value < sp.required_value)
                return false;
        }
        
        unlocked_tags.insert(u.name);
            
        return true;
    };
    
    for (auto const& u : unlockables)
    {
        check_unlocked(u.index);
    }
    
    // output
    for (auto const& u : unlockables)
    {
        std::cout << "unlockable name: " << u.name << "\n";
        std::cout << "prereqs:\n";
        for (auto const i : u.prereqs)
            std::cout << "    " << unlockables[i].name << "\n";
            
        std::cout << "statistic prereqs:\n";
        for (auto const& sp : u.statistic_prereqs)
            for (auto const& name : sp.statistic_names)
                std::cout << "    " << name << "\n";
        
        std::cout << "prereq for:\n";
        for (auto const i : u.unlock_indices)
            std::cout << "    " << unlockables[i].name << "\n";
        
        std::cout << "\n";
    }
    
    std::cout << "======== Unlocked ========\n\n";
    
    for (auto const& tag : unlocked_tags)
    {
        std::cout << unlockables[data_indices[tag]].name << "\n";
    }
    
    std::cout << "\n======== Unlockable ========\n\n";
    
    for (auto const& u : unlockables)
    {
        if (unlocked_tags.find(u.name) != unlocked_tags.end())
            continue; // already unlocked, skip
            
        bool unlockable = true;
        for (auto const i : u.prereqs)
        {
            auto const& other = unlockables[i];
            if (unlocked_tags.find(other.name) == unlocked_tags.end())
            {
                unlockable = false;
                break;
            }
        }
        
        if (unlockable)
            std::cout << u.name << "\n";
    }
}
