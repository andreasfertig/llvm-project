template<class T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant; // using injected-class-name
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; } // since c++14
};


using true_type =	integral_constant<bool, true>;
using false_type =	integral_constant<bool, false>;


template<class T, class U>
struct is_same : false_type {};
 
template<class T>
struct is_same<T, T> : true_type {};


class Test constexpr {
public:
    static inline int i{3};
};

static_assert(is_same<const int, decltype(Test::i)>::value);


class West  {
public:
    static inline int i{3};
};

static_assert(not is_same<const int, decltype(West::i)>::value);

