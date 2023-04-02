cmake_minimum_required(VERSION 3.24)
project(leetcode_test)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
        include(FetchContent)
        FetchContent_Declare(
                doctest
                GIT_REPOSITORY https://gitee.com/acking-you/doctest.git
                GIT_TAG v2.4.9
                GIT_SHALLOW TRUE
        )
        FetchContent_MakeAvailable(doctest)

#    include(FetchContent)
#    FetchContent_Declare(
#            googletest
#            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#    )
#    # For Windows: Prevent overriding the parent project's compiler/linker settings
#    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#    FetchContent_MakeAvailable(googletest)
#    include(GoogleTest)
endif ()

#enable_testing()
add_executable(leetcode_test main.cpp)
#target_link_libraries(leetcode_test GTest::gtest_main)
target_link_libraries(leetcode_test doctest_with_main)
#gtest_discover_tests(leetcode_test)