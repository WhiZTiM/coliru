class Outer {
    class Inner {
        static int StaticMember;
    };
};

int Outer::Inner::StaticMember = 5;

int main() {}