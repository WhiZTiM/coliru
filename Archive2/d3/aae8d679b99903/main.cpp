template <typename T>
struct BitMaskTraits;

template <typename T, typename = typename BitMaskTraits<T>::enabled>
class BitMask {
  template <typename U> friend constexpr BitMask<U> operator~(U value);

  using underlying = typename BitMaskTraits<T>::type;

  T value_;

public:
  constexpr BitMask(T value) : value_(value) {}
  constexpr operator T() const { return value_; }
  constexpr operator bool() const { return static_cast<unsigned>(value_); }

  constexpr friend BitMask<T> operator&(BitMask<T> lhs, BitMask<T> rhs) {
    return T(static_cast<underlying>(static_cast<T>(lhs)) &
             static_cast<underlying>(static_cast<T>(rhs)));
  }
  constexpr friend BitMask<T> operator&(BitMask<T> lhs, T rhs) {
    return operator&(lhs, BitMask<T>(rhs));
  }
  constexpr friend BitMask<T> operator&(T lhs, BitMask<T> rhs) {
    return operator&(BitMask<T>(lhs), rhs);
  }

  constexpr friend BitMask<T> operator|(BitMask<T> lhs, BitMask<T> rhs) {
    return T(static_cast<underlying>(static_cast<T>(lhs)) |
             static_cast<underlying>(static_cast<T>(rhs)));
  }
  constexpr friend BitMask<T> operator|(BitMask<T> lhs, T rhs) {
    return operator|(lhs, BitMask<T>(rhs));
  }
  constexpr friend BitMask<T> operator|(T lhs, BitMask<T> rhs) {
    return operator|(BitMask<T>(lhs), rhs);
  }

  constexpr friend BitMask<T> operator^(BitMask<T> lhs, BitMask<T> rhs) {
    return T(static_cast<underlying>(static_cast<T>(lhs)) ^
             static_cast<underlying>(static_cast<T>(rhs)));
  }
  constexpr friend BitMask<T> operator^(BitMask<T> lhs, T rhs) {
    return operator^(lhs, BitMask<T>(rhs));
  }
  constexpr friend BitMask<T> operator^(T lhs, BitMask<T> rhs) {
    return operator^(BitMask<T>(lhs), rhs);
  }

  BitMask<T> &operator&=(T rhs) {
    value_ = T(static_cast<underlying>(value_) & static_cast<underlying>(rhs));
    return *this;
  }
  BitMask<T> &operator&=(BitMask<T> &rhs) {
    return operator&=(static_cast<T>(rhs));
  }

  BitMask<T> &operator|=(T rhs) {
    value_ = T(static_cast<underlying>(value_) | static_cast<underlying>(rhs));
    return *this;
  }
  BitMask<T> &operator|=(BitMask<T> &rhs) {
    return operator|=(static_cast<T>(rhs));
  }

  BitMask<T> &operator^=(T rhs) {
    value_ = T(static_cast<underlying>(value_) ^ static_cast<underlying>(rhs));
    return *this;
  }
  BitMask<T> &operator^=(BitMask<T> &rhs) {
    return operator^=(static_cast<T>(rhs));
  }
};

template <typename T>
constexpr BitMask<T> operator~(T value) {
  return T(~static_cast<typename BitMask<T>::underlying>(value));
}

template <typename T>
constexpr BitMask<T> operator~(BitMask<T> value) {
  return operator~(static_cast<T>(value));
}

enum class SyntaxAttr {
  None,
  GNU,
  Declspec,
  CXX,
  Pragma,
  MSAttr,
};

void test() {
  BitMask<SyntaxAttr> MSA = SyntaxAttr::CXX;
  if (MSA & ~SyntaxAttr::GNU)
    MSA |= SyntaxAttr::GNU;
  MSA ^ SyntaxAttr::GNU;

}

