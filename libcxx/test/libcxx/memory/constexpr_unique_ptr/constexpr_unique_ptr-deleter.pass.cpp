#include <memory>

struct Foo {
  constexpr Foo(int _x) : x{_x} {}
  int x;
};

struct D {
  constexpr void operator()(Foo* p) const { delete p; }
};

constexpr auto fun() {
  std::unique_ptr<Foo, D> p{new Foo{4}, D{}};

  return *p;
}

int main() {
  constexpr auto i = fun();

  static_assert(i.x == 4);
}
