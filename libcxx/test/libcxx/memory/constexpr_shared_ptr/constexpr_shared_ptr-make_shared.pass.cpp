#include <memory>
#include <iostream>

constexpr auto fun() {
  auto p = std::make_shared<int>(4);

  return *p;
}

auto test() {
  auto p = std::make_shared<int>(4);

  return p;
}

int main() {
  constexpr auto i = fun();

  static_assert(i == 4);

  auto s = test();

  std::cout << *s << '\n';
}
