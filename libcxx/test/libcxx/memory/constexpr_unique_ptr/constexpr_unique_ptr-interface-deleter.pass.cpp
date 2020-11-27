#include <memory>

struct D {
  constexpr void operator()(int* p) const { delete p; }
};

constexpr auto fun() {
  std::unique_ptr<int, D> p{new int{5}, D{}};

  p = nullptr;
  p = std::unique_ptr<int, D>{new int{2}, D{}};

  auto* pr = p.release();

  p.reset(pr);

  auto other = std::unique_ptr<int, D>{new int{4}, D{}};

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

  std::unique_ptr<int, D> pm{std::move(p)};

  p = std::move(pm);

  return *p;
}

int main() {
  constexpr auto i = fun();

  static_assert(i == 4);
}
