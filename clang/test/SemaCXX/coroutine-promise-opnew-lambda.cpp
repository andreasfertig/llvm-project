#include <coroutine>

struct elements_of {
    int value;
};

class Generator {
private:
    using value = int;
    using reference = int&&;

public:
    class promise_type;

    using Handle = std::coroutine_handle<promise_type>;
    using yielded = std::conditional_t<std::is_reference_v<reference>,
                                       reference, reference&>;

    Generator(Generator&& other) noexcept;
    Generator& operator=(Generator&& other) noexcept;
    ~Generator();
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;

    explicit Generator(Handle coro) noexcept;
};

struct allocator_arg_t {};
inline allocator_arg_t allocator_arg;

class Generator::promise_type {
public:
    std::suspend_always initial_suspend() noexcept { return {}; }
    // When info is `nullptr`, equivalent to std::suspend_always
    std::suspend_always final_suspend() noexcept { return {}; }

    std::suspend_always yield_value(yielded val) noexcept;

    // clang-format off
    auto yield_value(elements_of r) noexcept {
        // clang-format on
        auto nested = [](allocator_arg_t,
                         int i)
            -> Generator {  
          co_yield 5;
        };
        nested(allocator_arg, r.value);
        return std::suspend_always{};
    }

    void return_void() noexcept {}
    void await_transform() = delete;
    void unhandled_exception();

    Generator get_return_object() noexcept;

    static void* operator new(const std::size_t size);

    // clang-format off
    template <class This, class... Args>
    static void* operator new(const std::size_t size, const This&,
                              allocator_arg_t, const Args&...);
};

void test () {
    auto f = []() -> Generator {
        co_yield elements_of{5};
    };

    auto G = f();
}

