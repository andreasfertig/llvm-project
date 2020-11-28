#include <memory>
#include <iostream>

constexpr auto fun() {
  std::shared_ptr<int> p{new int{4}};

  return *p;
}

auto test() {
  std::shared_ptr<int> p{new int{4}};

  return p;
}

int main() {
  constexpr auto i = fun();

  static_assert(i == 4);

  auto s = test();

  std::cout << *s << '\n';
}
