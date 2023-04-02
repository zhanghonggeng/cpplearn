add_test([=[HelloTest.BasicAssertions]=]  [==[E:/github/c++/cpplearn/project/CodingInterviewChinese2/out/build/x64-Debug/my_my_main.exe]==] [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY [==[E:/github/c++/cpplearn/project/CodingInterviewChinese2/out/build/x64-Debug]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  my_my_main_TESTS HelloTest.BasicAssertions)
