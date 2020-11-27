#include <memory>

constexpr auto fun() {
  auto p = std::make_unique<int[]>(3);

  p[0] = 4;

  return p[0];
}

int main() {
  constexpr auto i = fun();

  static_assert(i == 4);
}
