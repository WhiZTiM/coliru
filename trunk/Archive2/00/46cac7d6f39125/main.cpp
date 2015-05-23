template<int L, typename T>
class Vector {

  template<int L2, typename T2> friend
  Vector<L2, T2> operator+(const Vector<L2, T2>&, const Vector<L2, T2>&) {
    return Vector<L2, T2>();
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