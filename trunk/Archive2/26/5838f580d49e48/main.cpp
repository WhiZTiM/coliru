[[ noreturn ]] void f() {
throw "error";
// OK
}
[[ noreturn ]] void q(int i) {
// behavior is undefined if called with an argument <= 0
if (i > 0)
throw "positive";
}