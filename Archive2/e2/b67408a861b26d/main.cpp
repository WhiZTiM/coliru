#include <iostream>

template <typename TFunc>
float FloatSelect( const float in_value, TFunc&& Predicate) {
  return std::forward<TFunc>(Predicate)(in_value) ? in_value : 0.0f;
}

void DisplayFloatSelect() {
  const float value = FloatSelect(
    -1.0f,
    [] (const float v) { return value > 0.0f; }
  );

  std::cout << value << std::endl;
}

int main()
{
    return 0;
}