auto foo = [](const std::string &s) {
    return [&s](const Building &b) {
        return b.code().toString() == s;
    };
};

std::find_if(begin(nodes_), end(nodes_), foo(code));