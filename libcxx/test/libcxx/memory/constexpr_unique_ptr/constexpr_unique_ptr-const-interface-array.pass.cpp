#include <memory>

constexpr auto fun() {
  const int* i = new int[3]{4, 6, 7};
  std::unique_ptr<const int[]> p{i};

  auto other = std::unique_ptr<const int[]>{new int[3]{8, 5, 6}};

  [[maybe_unused]] auto* ig = p.get();

  [[maybe_unused]] auto& del = p.get_deleter();

  if (p) {
  }

  if (p == other) {
  }

  if (p != other) {
  }

  // issue: note: comparison has unspecified value
  //if(p < other) {}

  // issue: note: comparison has unspecified value
  //  if(p <= other) {}

  // issue: note: comparison has unspecified value
  //  if(p > other) {}

  // issue: note: comparison has unspecified value
  //  if(p >= other) {}

  return p[0];
}

int main() {
  constexpr auto i = fun();

  static_assert(i == 4);
}
