namespace J {
    namespace tag {
        struct ExampleClass : public java::lang::Object {
            static constexpr const char* signature = "LExampleClass";

            Method<void()> speak = m<void>("speak", "()V");
            Method<Int()> bar = m<Int>("bar", "()I");
            Method<java::lang::String()> qux = m<java::lang::String>("qux", "()Ljava/lang/String;");
            Method<ExampleClass()> get_self = m<ExampleClass>("get_self", "()LExampleClass;");

            ExampleClass(JNIEnv* env, jobject obj) : Object(env, obj) {
            }
        };
    }
}

JNIEXPORT void JNICALL Java_ExampleClass_foo(JNIEnv* env, jobject obj) {
    auto example = J::tag::ExampleClass(env, obj);
    std::cout << static_cast<std::string>(example.qux()) << "\n";
}
