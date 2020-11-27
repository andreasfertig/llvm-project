#include <memory>

constexpr auto fun() {
  int* i = new int{4};
  std::unique_ptr<int> p{i};

  return *p;
}

int main() {
  constexpr auto i = fun();

  static_assert(i == 4);
}
