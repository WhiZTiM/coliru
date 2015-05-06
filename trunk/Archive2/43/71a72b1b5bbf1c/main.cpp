int main() {
    OpenMultiMethod<int> test;
    test.add_overload([](int a) {
        std::cout << "with int\n";
        return 20;
    });
    test.add_overload([](double b) {
        std::cout << "with double\n";
        return 50;
    });
    test.add_overload([](Parent& p) {
        std::cout << "with Parent&\n";
        return 0;
    });
    test.add_overload([](ChildA& a) {
        std::cout << "with ChildA&\n";
        return 0;
    });
    test.add_overload([](ChildB& a) {
        std::cout << "with ChildB&\n";
        return 0;
    });/*
    test.add_overload([](const ChildB& uhoh) {
        std::cout << "with const ChildB&\n";
        return -1;
    });*/
    test.add_overload([](std::unique_ptr<int>&& refref) {
        return 0;
    });
    for(auto sig : qualified_signature_for<decltype(foo)>()) {
        sig.summarize();
    }
    std::cout << "============\n";
    Parent p;
    ChildA a;
    ChildB b;
    Parent& pr = p;
    Parent& ar = a;
    Parent& br = b;
    const Parent& pcr = p;
    const Parent& acr = a;
    const Parent& bcr = b;
    volatile Parent& pvr = p;
    volatile Parent& avr = a;
    volatile Parent& bvr = b;
    const volatile Parent& pcvr = p;
    const volatile Parent& bcvr = a;
    const volatile Parent& acvr = b;
    test(100);
    test(200.0);
    test(pr);
    test(ar);
    test(br);
    test(pcr);
    test(acr);
    test(bcr);/*
    test(pvr);
    test(avr);
    test(bvr);
    test(pcvr);
    test(acvr);
    test(bcvr);*/
}
/*
Outputs the following:

i
i&
const i&
volatile i&
const volatile i&
i&&
const i&&
volatile i&&
const volatile i&&
Pi
Pi
Pi
============
with int
with double
with Parent&
with ChildA&
with ChildB&
with Parent&
with ChildA&
with ChildB&
*/
