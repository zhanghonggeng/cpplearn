# For a better template to copy, see examples/standalone
set(LLVM_LINK_COMPONENTS Support)
#include_directories(include/)

add_llvm_executable(toyc-ch1 toyc.cpp parser/AST.cpp)
target_link_libraries(toyc-ch1 PRIVATE MLIRSupport)

file(GLOB_RECURSE srcs CONFIGURE_DEPENDS parser/*.cpp include/*.h)
add_library(myLib STATIC ${srcs})
target_include_directories(myLib PUBLIC include)

target_link_libraries(toyc-ch1 PUBLIC myLib)