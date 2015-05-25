std::map<std::string, json::value> _limits;

// Works as expected.
auto get_limit_by_name(std::string name) const -> json::value const& {
    auto const& it = _limits.find(name);
    
    if (it != _limits.end()) {
        return it->second;
    }

    return nullptr;
}

// Doesn't.
auto get_limit_by_name(std::string name) const -> json::value const& {
    auto const& it = _limits.find(name);
    return (it != _limits.end()) ? it->second : nullptr;
}