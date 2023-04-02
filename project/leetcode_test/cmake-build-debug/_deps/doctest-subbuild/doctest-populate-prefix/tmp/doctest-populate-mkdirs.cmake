# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/github/c++/cpplearn/project/leetcode_test/cmake-build-debug/_deps/doctest-src"
  "E:/github/c++/cpplearn/project/leetcode_test/cmake-build-debug/_deps/doctest-build"
  "E:/github/c++/cpplearn/project/leetcode_test/cmake-build-debug/_deps/doctest-subbuild/doctest-populate-prefix"
  "E:/github/c++/cpplearn/project/leetcode_test/cmake-build-debug/_deps/doctest-subbuild/doctest-populate-prefix/tmp"
  "E:/github/c++/cpplearn/project/leetcode_test/cmake-build-debug/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp"
  "E:/github/c++/cpplearn/project/leetcode_test/cmake-build-debug/_deps/doctest-subbuild/doctest-populate-prefix/src"
  "E:/github/c++/cpplearn/project/leetcode_test/cmake-build-debug/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/github/c++/cpplearn/project/leetcode_test/cmake-build-debug/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/github/c++/cpplearn/project/leetcode_test/cmake-build-debug/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
