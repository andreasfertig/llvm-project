// RUN: %clang_cc1 -std=c++2a %s -verify

struct Test consteval {
     bool fun() const { return true; }    
    constexpr bool bun() const { return true; }
};


struct Derived : Test {
};


#if 0
struct ClassWithSpecialMembers constexpr {
  ClassWithSpecialMembers() {}
  ClassWithSpecialMembers(const ClassWithSpecialMembers& rhs) // user provided copy-ctor, check that it gets marked constexpr as well
  {}

  ~ClassWithSpecialMembers() {} // user provided destructor. Check that it gets marked constexpr as well
};
#endif

static_assert(Test{}.fun());

consteval auto X()
{
    Test t{};

    Test t2 = t;

    return true;
}

static_assert(X());


#if 0
consteval auto D()
{
    Derived t{};

    Derived t2 = t;  // Derived copy ctor must be consteval!

    return false;
}

//static_assert(D());
#endif

namespace working {
struct Derived : Test {
    Derived() = default;
    consteval Derived(const Derived&) {}
    
    bool win() const { return true; }
};

consteval auto D()
{
    Derived t{};

    Derived t2 = t;

    return true;
}

static_assert(D());

}


struct A {
    consteval A() {}
    consteval ~A() {}

    bool RunTime() { return true; }
};

struct B consteval : A {

    bool RunTimeToo() { return true; }
};


int main() {


    B b;
    b.RunTimeToo();
    
    b.RunTime();


#if 0
Derived d{};
auto x = d.fun();

Derived* pd = new Derived{};
auto y = pd->fun();
#endif

  return 3;
}



