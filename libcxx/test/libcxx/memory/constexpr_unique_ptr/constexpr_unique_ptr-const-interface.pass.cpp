#include <memory>

constexpr auto fun() {
  const int* i = new int{4};
  const std::unique_ptr<const int> p{i};

  auto other = std::make_unique<const int>(6);

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

  return *p;
}

int main() {
  constexpr auto i = fun();

  static_assert(i == 4);
}
