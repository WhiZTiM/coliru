#include <iostream>
#include <utility>

using namespace std;

struct Member
{
    Member () {}
	Member (Member const&) { cout << "Member: copy ctor\n"; }
	Member (Member&&) = delete;
};

struct MemberMovable
{
    MemberMovable () {}
    MemberMovable (Member const&) { cout << "MemberMovable: copy ctor\n"; }
	MemberMovable (Member&&) { cout << "MemberMovable: move ctor\n"; }
};


struct Base
{
	Base () {}
	Base (Base const&) { cout << "Base: copy ctor\n"; }
	Base (Base&&) = delete;
};

struct Class : Base
{
	Member m;
    MemberMovable mm;
};

int main ()
{
	Class a;
	cout << "move Class: a -> b\n";
	Class b { move (a) };
}