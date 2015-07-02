struct S {
  int data[4];
  operator decltype((data)) () { return data; }
};


int main() {
}
