template <typename ID> class A { public: template <typename IDB> class B {}; };

template <template <typename ID> class... DependentTemplateB> class Destination {};

// Neither of these work, but they express the desired result,
// which is Destination<A<IDA>::template B, A<IDB>::template B, A<IDC>::template C>.
template <typename... IDs> using ExpandPack = Destination<A<IDs>::template B...>;
//template <typename... IDs> using ExpandPack = Destination<A<IDs>::.. template B>;

class IDA {};
class IDB {};
class IDC {};

int main()
{
    ExpandPack<IDA, IDB, IDC> destination_ida_idb_idc;
}
