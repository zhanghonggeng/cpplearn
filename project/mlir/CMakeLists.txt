CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
if (POLICY CMP0068)
    cmake_policy(SET CMP0068 NEW)
    set(CMAKE_BUILD_WITH_INSTALL_NAME_DIR ON)
endif ()

if (POLICY CMP0075)
    cmake_policy(SET CMP0075 NEW)
endif ()

if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif ()

set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_STANDARD 20)
project(mlir_test)

set(LLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING 0)
link_directories(/usr/local/lib)
find_package(MLIR REQUIRED CONFIG)
message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(LLVM_RUNTIME_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/bin)
# LLVM_LIBRARY_OUTPUT_INTDIR是一个变量，用于指定LLVM库文件的输出目录
set(LLVM_LIBRARY_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/lib)
# MLIR_BINARY_DIR是一个变量，用于指定MLIR构建输出的目录
set(MLIR_BINARY_DIR ${CMAKE_BINARY_DIR})

# CMAKE_MODULE_PATH变量用于指定CMake模块的搜索路径。
# ${MLIR_CMAKE_DIR}和${LLVM_CMAKE_DIR}分别是MLIR和LLVM的CMake模块所在的路径。
list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)
include(AddMLIR)
include(HandleLLVMOptions)

# 将LLVM定义的预定义宏（如-D__STDC_CONSTANT_MACROS等）转换为CMake所需的格式，存储在LLVM_DEFINITIONS_LIST变量中。
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
# 添加LLVM定义的预定义宏到项目中。
add_definitions(${LLVM_DEFINITIONS_LIST})
# 指定链接器在搜索库文件时需要包含LLVM构建的库文件路径。
link_directories(${LLVM_BUILD_LIBRARY_DIR})
# 指定编译器在搜索头文件时需要包含MLIR的头文件路径。
include_directories(${MLIR_INCLUDE_DIRS})
# 指定编译器在搜索头文件时需要包含项目的头文件路径和生成的头文件路径。
include_directories(include/)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# 设置了需要使用的LLVM组件
set(LLVM_COMPONENTS Support)
# 设置了需要使用的LLVM组件
set(LIBS
        MLIROptLib
        MLIRExecutionEngine
        MLIRAffine
        LLVMLinker
        )
# llvm_update_compile_flags是一个CMake宏，用于更新LLVM的编译选项和标志，
# 以便与当前项目的编译选项和标志相匹配。在这里，它被用于更新名为luac的目标的编译选项和标志。
#llvm_update_compile_flags(llvmtest)
#
set(LLVM_LINK_COMPONENTS
        BitWriter
        Core
        ExecutionEngine
        MC
        MCJIT
        Support
        nativecodegen)


#add_llvm_executable(test main.cpp)
add_subdirectory(toy/Ch1)