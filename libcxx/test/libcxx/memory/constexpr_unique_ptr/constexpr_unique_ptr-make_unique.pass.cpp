#include <memory>

constexpr auto fun() {
  auto p = std::make_unique<int>(4);

  return *p;
}

int main() {
  constexpr auto i = fun();

  static_assert(i == 4);
}
