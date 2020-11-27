#include <memory>

struct Foo {
  constexpr Foo(int _x) : x{_x} {}
  int x;
};

constexpr auto fun() {
  int* i = new int{5};
  std::unique_ptr<int> p{i};

  p = nullptr;
  p = std::make_unique<int>(6);

  auto* pr = p.release();

  p.reset(pr);

  auto other = std::make_unique<int>(2);

  p.swap(other);

  [[maybe_unused]] auto* ig = p.get();

  [[maybe_unused]] auto& del = p.get_deleter();

  if (p) {
  }

  if (p == other) {
  }

  if (p == nullptr) {
  }

  if (p != other) {
  }

  if (p != nullptr) {
  }

  // issue: note: comparison has unspecified value
  //  if(p < other) {}

  //  if(p < nullptr) {}

  // issue: note: comparison has unspecified value
  //  if(p <= other) {}
  //  if(p <= nullptr) {}

  // issue: note: comparison has unspecified value
  //  if(p > other) {}
  //    if(p > nullptr) {}

  // issue: note: comparison has unspecified value
  //  if(p >= other) {}
  //    if(p >= nullptr) {}

  std::unique_ptr<int> pm{std::move(p)};

  p = std::move(pm);

  auto f = std::make_unique<Foo>(2);

  return *p + f->x;
}

int main() {
  constexpr auto i = fun();

  static_assert(i == 4);
}
