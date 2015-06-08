class Foo{
public:
  static void f1();
private:
  static int* list;
};

int* Foo::list = new int[10];

int main() {}
