int subtractFive(int num) {
    return num -5;
}

int foo(int i) {
    return subtractFive(i) * 5;
}

int main(int argc, char *argv[]) {
  return foo(6);
}
