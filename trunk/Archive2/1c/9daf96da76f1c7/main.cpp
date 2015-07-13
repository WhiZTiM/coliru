#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>

class field {
public:
    explicit field(std::size_t offset) : offset(offset) { }

    void* read(void* object) const {
        void* result;
        std::memcpy(&result, (char*)object + offset, sizeof(void*));
        return result;
    }

    void write(void* object, void* value) const {
        std::memcpy((char*)object + offset, &value, sizeof(void*));
    }

private:
    std::size_t offset;
};

class type {
public:
    explicit type(std::vector<std::string> field_names) {
        size = 8;
        for (std::size_t i = 0; i < field_names.size(); ++i) {
            fields.emplace(field_names[i], field(size));
            size += 8;
        }
    }

private:
    std::size_t size;
    std::unordered_map<std::string, field> fields;
};