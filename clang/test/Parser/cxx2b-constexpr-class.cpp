// RUN: %clang_cc1 -std=c++2a %s -verify
// expected-no-diagnostics

class Test constexpr {
public:
    bool fun() const { return true; }    
    constexpr bool bun() const { return true; }
};

