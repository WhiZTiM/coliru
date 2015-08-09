int f()
{
  return 2;
}

int main()
{
  int x [[gnu::unused]] = f();
}
