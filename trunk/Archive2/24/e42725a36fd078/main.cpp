using namespace std;

namespace testns
{

struct Foo
{
    Foo() {
         ::glovar;
    }
};

}

std::shared_ptr<testns::Foo> glovar;

int main(int argc, char* argv[])
{
    glovar = std::make_shared<testns::Foo>();

    return 0;
}