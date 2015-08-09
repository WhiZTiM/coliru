int f()
{
  return 2;
}

int main()
{
  int x [[unused]] = f();
}
