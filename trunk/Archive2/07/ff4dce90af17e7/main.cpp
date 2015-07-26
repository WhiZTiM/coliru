// spec: does not modify either argument
extern void* fopen(char* file, char* mode); // legacy / bad API

// own wrapper for bad API
inline void* fopen(char const* file, char const* mode)
{
    return fopen(const_cast<char*>(file), const_cast<char*>(mode));
}