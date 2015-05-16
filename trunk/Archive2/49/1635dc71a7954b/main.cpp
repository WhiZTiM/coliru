int main() {
    static_assert( false, 
    #ifdef __cpp_variable_templates
        "enabled!"
    #else
        "disabled!"
    #endif
    );
}