template <class T>
       auto f(T) -> decltype([]() { T::invalid; } ());
void f(...);
f(0); // error: invalid expression not part of the immediate context
     template <class T, std::size_t = sizeof([]() { T::invalid; })>
       void g(T);
void g(...);
g(0); // error: invalid expression not part of the immediate context
     template <class T>
       auto h(T) -> decltype([x = T::invalid]() { });
void h(...);
h(0); // error: invalid expression not part of the immediate context
     template <class T>
       auto i(T) -> decltype([]() -> typename T::invalid { });
void i(...);
i(0); // error: invalid expression not part of the immediate context
template <class T>
auto j(T t) -> decltype([](auto x) -> decltype(x.invalid) { } (t)); // #1

void j(...);  // #2
     j(0);    // deduction fails on #1, calls #2
