if(EXISTS "E:/github/c++/cpplearn/project/CodingInterviewChinese2/out/build/x64-Debug/my_my_main[1]_tests.cmake")
  include("E:/github/c++/cpplearn/project/CodingInterviewChinese2/out/build/x64-Debug/my_my_main[1]_tests.cmake")
else()
  add_test(my_my_main_NOT_BUILT my_my_main_NOT_BUILT)
endif()
