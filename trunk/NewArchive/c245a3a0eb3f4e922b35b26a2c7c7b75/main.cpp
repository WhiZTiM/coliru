foo& my_foo() {
    static foo f = ...;
    return f;
}

//Then, just include a static instance of Initializer<> at the bottom
// of your class definition, and you have a cheap and free "static constructor".