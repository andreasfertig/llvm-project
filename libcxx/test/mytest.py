#! /usr/bin/env python3

import glob
import sys
import os

tests = glob.glob('std/utilities/optional/**/*.cpp', recursive=True)


for test in tests:
    print(test)

    if test.endswith('.fail.cpp'):
        continue

    os.system('/usr/local/bin/g++-11 -c -std=c++20 -nostdinc++ -D_LIBCPP_STD_VER=23 -isystem /Users/jim/tmp/llvm-project/build_libcxx/build/include/c++/v1/ %s -I support/' %(test))


