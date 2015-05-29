struct final {
  virtual final override ();
};

struct finel final : final
{
  virtual final override () override;
  virtual final final () final;
};

int main(void) {}