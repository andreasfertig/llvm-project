
template <class T>
using A = decltype([] { }); // A<int> and A<char> refer to different closure types

A<int> ai{};
A<char> ac{};

//static_assert(
