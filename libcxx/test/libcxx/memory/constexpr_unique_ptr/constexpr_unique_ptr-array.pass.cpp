#include <memory>

constexpr auto fun() {
  int* i = new int[3]{4};
  std::unique_ptr<int[]> p{i};

  return p[0];
}

int main() {
  constexpr auto i = fun();

  static_assert(i == 4);
}
