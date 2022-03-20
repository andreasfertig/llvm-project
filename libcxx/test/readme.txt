cd llvm-project
mkdir build_libcxx
cd build_libcxx

export CXX=/usr/local/clang+llvm-13.0.0-x86_64-apple-darwin/bin/clang++
export CC=/usr/local/clang+llvm-13.0.0-x86_64-apple-darwin/bin/clang

cmake -G Ninja -S runtimes -B build -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" -DLIBCXX_ENABLE_EXPERIMENTAL_LIBRARY=Yes -DLIBCXX_INSTALL_EXPERIMENTAL_LIBRARY=Yes ../runtimes/


$ ninja -C build cxx cxxabi unwind cxx_experimental                                                       # Build


export CXX=/usr/local/clang+llvm-13.0.0-x86_64-apple-darwin/bin/clang++
export CC=/usr/local/clang+llvm-13.0.0-x86_64-apple-darwin/bin/clang
../../build_lbcxx/build/bin/llvm-lit std/utilities/optional/




$ ninja -C build check-cxx check-cxxabi check-unwind                                      # Test


docker run -v ~/tmp/llvm-project:/workspace/cppinsights --rm -it --security-opt seccomp=unconfined andreasfertig/cppinsights-builder-gitpod /bin/bash
