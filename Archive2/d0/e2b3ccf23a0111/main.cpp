// Declare the prototype for the write() function, with unspecified parameters.
extern long write();

int main() {
    char const *str = "Hello";

    // Retrieve the length
    unsigned long size = 0;
    while(str[size])
        ++size;

    // Write to stdout (fd 1)
    write(1, str, size);

    return 0;
}