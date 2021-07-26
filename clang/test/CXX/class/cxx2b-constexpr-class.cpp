// RUN: %clang_cc1 -std=c++2a %s -verify

class Test constexpr {
public:
    bool fun() const { return true; }    
    constexpr bool bun() const { return true; }
};

constexpr Test t{};

static_assert(Test{}.fun());


class Final final {
};

Final f{};

//class FinalFwd final; //expected-error {{variable has incomplete type}} \
                        expected-note {{forward declaration of 'FinalFwd'}} \
                        expected-note {{previous definition is here}}


struct ConstexprAndFinal constexpr final {
    bool fun() const { return true; }
};

ConstexprAndFinal ceaf{};

#if 0
struct FinalAndConstexpr final constexpr { // expected-error {{redefinition of 'final'}} \
                                              expected-error {{expected ';' after top level declarator}} \
                                              expected-error {{expected unqualified-id}} \
                                              expected-note {{forward declaration of 'FinalAndConstexpr'}}
    bool fun() const { return true; }
};

FinalAndConstexpr face{}; // expected-error {{variable has incomplete type 'FinalAndConstexpr'}}
#endif

//struct Forward constexpr; // expected-error {{expected forward decl}}

struct Forward constexpr {
    bool fun() const { return true; }
};


struct ForwardFirstWO;

struct ForwardFirstWO constexpr {
    bool fun() const { return true; }
};


//struct ForwardSecondWO constexpr; // expected-error {{expected forward decl}}

struct ForwardSecondWO {
    bool fun() const { return true; }
};


//template<typename T>
//struct TForward constexpr; // expected-error {{expected forward decl}}

template<typename T>
struct TForward constexpr {
    bool fun() const { return true; }
};



template<typename T>
struct PrimaryTmpl {
    bool fun() const { return false; }
};

template<>
struct PrimaryTmpl<int> constexpr {
    bool fun() const { return true; }
};

//static_assert(PrimaryTmpl<char>{}.fun());
static_assert(PrimaryTmpl<int>{}.fun());


struct foo { int this_is_not_constexpr() { return 1;} }; // expected-note {{declared here}}


struct bar constexpr : foo { int this_is_constexpr() { return 1; }
};

//static_assert(bar{}.this_is_not_constexpr()); // expected-error {{static_assert expression is not an integral constant expression}} \
                                                 expected-note {{non-constexpr function 'this_is_not_constexpr' cannot be used in a constant expression}}


struct foo2 constexpr { int this_is_constexpr() { return 1;} };

struct bar2 : foo2 { int this_is_not_constexpr() { return 1; } // expected-note {{declared here}}
};


//static_assert(bar2{}.this_is_not_constexpr()); // expected-error {{static_assert expression is not an integral constant expression}} \
                                                 expected-note {{non-constexpr function 'this_is_not_constexpr' cannot be used in a constant expression}}


class ClassWithFriend constexpr {
private:
  int mValue;

public:
  ClassWithFriend(int value)
  : mValue{value}
  {}

  // add Cents + Cents using a friend function
  friend ClassWithFriend operator+(const ClassWithFriend& lhs, const ClassWithFriend& rhs) {
    return {lhs.mValue + rhs.mValue};
  }

  int get() const { return mValue; }
};

struct ClassWithStaticMember constexpr {
  static bool test() { return true; }
};

static_assert(ClassWithStaticMember::test());


struct ClassWithSpecialMembers constexpr {
  ClassWithSpecialMembers() {}
  ClassWithSpecialMembers(const ClassWithSpecialMembers& rhs) // user provided copy-ctor, check that it gets marked constexpr as well
  {}

  ~ClassWithSpecialMembers() {} // user provided destructor. Check that it gets marked constexpr as well
};

#if 0
struct NotConstexpr {
    NotConstexpr() {}
};

struct FromNotConstexpr constexpr : NotConstexpr {
};

constexpr FromNotConstexpr fromNotConstexpr{};
#endif



namespace tests {
    struct BaseA constexpr {
        bool fun() { return true; }
    };

    struct DerivedA : BaseA {
        bool run() { return true; }
    };


    static_assert(DerivedA{}.fun());
    //static_assert(DerivedA{}.run());  // not constexpr

    struct BaseB {
        bool fun() { return true; }
    };
    

    struct DerivedB constexpr : BaseB {
       bool run() { return true; }
    };

    // static_assert(DerivedB{}.fun()); // not constexpr
    static_assert(DerivedB{}.run());
    

    struct BaseC {
        BaseC() = default;
        BaseC(int) {}
    };
    

    struct DerivedC constexpr : BaseC {        
       DerivedC(double) : BaseC{} {}

       using BaseC::BaseC;
    };

    //constexpr DerivedC c1{3}; // BaseC isn't constexpr
    //constexpr DerivedC c2{3.4}; // DerivedC isn't constexpr
    

    struct BaseD constexpr {
        BaseD(int) {}
    };
    

    struct DerivedD : BaseD {
       DerivedD(double) : BaseD{2} {} // not valid would never produce a constant expression because BaseC ctor isn't constexpr

       using BaseD::BaseD;
    };
    
    constexpr DerivedD d1{3}; // BaseD is constexpr
    //constexpr DerivedD d2{3.4}; // DerivedD isn't constexpr

    
    struct A {
        void fun() {}
    };

    struct B constexpr : A {
        bool run() { return true; }
    };

    // If we would require that B constexpr makes A constexpr what would we do with C?
    // For constexpr it could be somewhat silent, but not for constevl
    struct C : A {
        bool run() { return true; }
    };
}

namespace NNN {
template <class T> struct Wrap constexpr
{
    T t;
};
struct NonLiteral
{
    NonLiteral();
    ~NonLiteral();
    constexpr int some_bits_are_constexpr() { return 2; }
};

consteval auto Fun()
{
    Wrap<NonLiteral> w;
    w.t.some_bits_are_constexpr();

    return true; 
}
    
}




int main() {
  if constexpr(Test{}.fun() && Test{}.bun() && ConstexprAndFinal{}.fun() && Forward{}.fun() && ForwardFirstWO{}.fun() && TForward<int>{}.fun() && bar{}.this_is_constexpr() && bar2{}.this_is_constexpr()) {
    return 1;
  }

  constexpr ClassWithFriend cf1{6};
  constexpr ClassWithFriend cf2{8};
  constexpr ClassWithFriend cfSum{cf1 + cf2};

  static_assert(cfSum.get() == 14);

  constexpr ClassWithSpecialMembers cwsp1{};
  constexpr ClassWithSpecialMembers cwsp2{cwsp1};

  auto x = NNN::Fun();

  return 3;
}


