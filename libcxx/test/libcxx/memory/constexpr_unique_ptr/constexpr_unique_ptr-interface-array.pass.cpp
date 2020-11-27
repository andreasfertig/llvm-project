#include <memory>

constexpr auto fun() {
  int* i = new int[3]{5, 6, 7};
  std::unique_ptr<int[]> p{i};

  p = nullptr;
  p = std::make_unique<int[]>(3);

  auto* pr = p.release();

  p.reset(pr);

  auto other = std::make_unique<int[]>(3);

  other[0] = 4;

  p.swap(other);

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
