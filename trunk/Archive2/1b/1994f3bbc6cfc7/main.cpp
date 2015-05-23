template<int L, typename T>
class Vector {

  friend
  Vector operator+(const Vector&, const Vector&) {
    return Vector();
  }

private:
  T data[L];
};

int main() {
  Vector<42, double> v42d;
  Vector<24, int> v24i;
  (void) v42d;
  (void) v24i;
}