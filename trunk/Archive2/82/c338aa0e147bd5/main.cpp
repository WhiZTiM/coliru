#include <type_traits>

#define LLVM_CONSTEXPR constexpr

template <typename T,
          typename = typename std::enable_if<std::is_integral<T>::value ||
                                             std::is_enum<T>::value>::type>
class BitMask {
  using underlying = typename std::conditional<
      std::is_enum<T>::value, typename std::underlying_type<T>::type, T>::type;

  T value_;

public:
  LLVM_CONSTEXPR BitMask(T value) : value_(value) {}
  LLVM_CONSTEXPR operator T() const { return value_; }

  LLVM_CONSTEXPR friend BitMask<T> operator &(BitMask<T> lhs, BitMask<T> rhs) {
    return T(static_cast<underlying>(static_cast<T>(lhs)) &
             static_cast<underlying>(static_cast<T>(rhs)));
  }
  LLVM_CONSTEXPR friend BitMask<T> operator &(BitMask<T> lhs, T rhs) {
    return operator &(lhs, BitMask<T>(rhs));
  }
  LLVM_CONSTEXPR friend BitMask<T> operator &(T lhs, BitMask<T> rhs) {
    return operator &(BitMask<T>(lhs), rhs);
  }

  LLVM_CONSTEXPR friend BitMask<T> operator |(BitMask<T> lhs, BitMask<T> rhs) {
    return T(static_cast<underlying>(static_cast<T>(lhs)) |
             static_cast<underlying>(static_cast<T>(rhs)));
  }
  LLVM_CONSTEXPR friend BitMask<T> operator |(BitMask<T> lhs, T rhs) {
    return operator |(lhs, BitMask<T>(rhs));
  }
  LLVM_CONSTEXPR friend BitMask<T> operator |(T lhs, BitMask<T> rhs) {
    return operator |(BitMask<T>(lhs), rhs);
  }

  LLVM_CONSTEXPR friend BitMask<T> operator ^(BitMask<T> lhs, BitMask<T> rhs) {
    return T(static_cast<underlying>(static_cast<T>(lhs)) ^
             static_cast<underlying>(static_cast<T>(rhs)));
  }
  LLVM_CONSTEXPR friend BitMask<T> operator ^(BitMask<T> lhs, T rhs) {
    return operator ^(lhs, BitMask<T>(rhs));
  }
  LLVM_CONSTEXPR friend BitMask<T> operator ^(T lhs, BitMask<T> rhs) {
    return operator ^(BitMask<T>(lhs), rhs);
  }

  LLVM_CONSTEXPR friend BitMask<T> operator ~(BitMask<T> value) {
    return operator~(static_cast<T>(value));
  }
  LLVM_CONSTEXPR friend BitMask<T> operator ~(T value) {
    return T(~static_cast<underlying>(value));
  }

  BitMask<T> & operator&=(T rhs) {
    value_ = T(static_cast<underlying>(value_) & static_cast<underlying>(rhs));
    return *this;
  }
  BitMask<T> & operator&=(BitMask<T> &rhs) {
    return operator&=(static_cast<T>(rhs));
  }

  BitMask<T> & operator|=(T rhs) {
    value_ = T(static_cast<underlying>(value_) | static_cast<underlying>(rhs));
    return *this;
  }
  BitMask<T> & operator|=(BitMask<T> &rhs) {
    return operator|=(static_cast<T>(rhs));
  }

  BitMask<T> & operator^=(T rhs) {
    value_ = T(static_cast<underlying>(value_) ^ static_cast<underlying>(rhs));
    return *this;
  }
  BitMask<T> & operator^=(BitMask<T> &rhs) {
    return operator^=(static_cast<T>(rhs));
  }
};



enum class SyntaxAttr {
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
    MSA &= ~SyntaxAttr::GNU;
}

