namespace J {
    namespace tag {
        struct ExampleClass : public java::lang::Object {
            static constexpr const char* signature = "LExampleClass";

            Method<void()> speak;
            Method<Int()> bar;
            Method<java::lang::String()> qux;
            Method<ExampleClass()> get_self;

            ExampleClass(JNIEnv* env, jobject obj) :
                Object(env, obj),
                speak(m<void>("speak", "()V")),
                bar(m<Int>("bar", "()I")),
                qux(m<java::lang::String>("qux", "()Ljava/lang/String;")),
                get_self(m<ExampleClass>("get_self", "()LExampleClass;"))
                {
            }
        };
    }
}

JNIEXPORT void JNICALL Java_ExampleClass_foo(JNIEnv* env, jobject obj) {
    auto example = J::tag::ExampleClass(env, obj);
    std::cout << static_cast<std::string>(example.qux()) << "\n";
}