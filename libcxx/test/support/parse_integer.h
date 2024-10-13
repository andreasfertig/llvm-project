//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LIBCPP_TEST_SUPPORT_PARSE_INTEGER_H
#define LIBCPP_TEST_SUPPORT_PARSE_INTEGER_H

#include <string>
#include <charconv>
#include <iterator>
#include <algorithm>

namespace detail {
template <class T>
struct parse_integer_impl;

template <>
struct parse_integer_impl<int> {
    template <class CharT>
    int operator()(std::basic_string<CharT> const& str) const {
        return std::stoi(str);
    }
};

template <>
struct parse_integer_impl<long> {
    template <class CharT>
    long operator()(std::basic_string<CharT> const& str) const {
        return std::stol(str);
    }
};

template <>
struct parse_integer_impl<long long> {
    template <class CharT>
    long long operator()(std::basic_string<CharT> const& str) const {
        return std::stoll(str);
    }
};

template <>
struct parse_integer_impl<unsigned int> {
    template <class CharT>
    unsigned int operator()(std::basic_string<CharT> const& str) const {
        return std::stoul(str);
    }
};

template <>
struct parse_integer_impl<unsigned long> {
    template <class CharT>
    unsigned long operator()(std::basic_string<CharT> const& str) const {
        return std::stoul(str);
    }
};

template <>
struct parse_integer_impl<unsigned long long> {
    template <class CharT>
    unsigned long long operator()(std::basic_string<CharT> const& str) const {
        return std::stoull(str);
    }
};

template <class T, class CharT>
constexpr T convert(std::basic_string<CharT> const& str) {
  T result{};
  std::from_chars(str.data(), str.data() + str.size(), result);

  return result;
}

template <class T>
constexpr T convert(std::basic_string<wchar_t> const& str) {
  std::string s{};
  std::transform(str.begin(), str.end(), std::back_inserter(s), [](wchar_t c) { return static_cast<char>(c); });

  return convert<T>(s);
}

} // end namespace detail

template <class T, class CharT>
constexpr T parse_integer(std::basic_string<CharT> const& str) {
    return detail::convert<T>(str);
}

#endif // LIBCPP_TEST_SUPPORT_PARSE_INTEGER_H
