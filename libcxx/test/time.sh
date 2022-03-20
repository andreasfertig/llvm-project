#! /bin/bash

FILE=$1

echo "inheritance"
time /usr/local/bin/g++-11 -c -std=c++20 -nostdinc++ -D_LIBCPP_STD_VER=23 -isystem/usr/local/clang+llvm-14.0.0-x86_64-apple-darwin/include/c++/v1/ $FILE

echo "concepts"
time /usr/local/bin/g++-11 -c -std=c++20 -nostdinc++ -D_LIBCPP_STD_VER=23 -isystem ../../build_libcxx/build/include/c++/v1/ $FILE
