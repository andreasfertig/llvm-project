#include <memory>

struct D {
  constexpr void operator()(int* p) const { delete[] p; }
};

constexpr auto fun() {
  int* i = new int[3]{5, 6, 7};
  std::unique_ptr<int[], D> p{i, D{}};

  p = nullptr;
  p = std::unique_ptr<int[], D>{new int[3]{6, 7, 8}, D{}};

  auto* pr = p.release();

  p.reset(pr);

  auto other = std::unique_ptr<int[], D>{new int[3]{4, 5, 6}, D{}};

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
