cmake_minimum_required(VERSION 3.24)
project(Code LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

if (clang)
    # 使用libc++
    SET(CMAKE_CXX_FLAGS "-std=c++20 -stdlib=libc++ -fexperimental-library")
    SET(CMAKE_EXE_LINKER_FLAGS "-lc++ -lc++abi ")
endif ()

if (NOT MSVC)
    find_program(CCACHE_PROGRAM ccache)
    if (CCACHE_PROGRAM)
        message(STATUS "Found CCache: ${CCACHE_PROGRAM}")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
    endif ()
endif ()

# 查看WSL和Windows进程之间共享环境变量是否生效
#message("PATH: $ENV{PATH}")
message("LD_LIBRARY_PATH: $ENV{LD_LIBRARY_PATH}")
message("TVM_HOME: $ENV{TVM_HOME}")
message("PYTHONPATH: $ENV{PYTHONPATH}")
message("CCACHE_EXEC: $ENV{CCACHE_EXEC}")

# 使用doctest
if (MSVC)
    include(FetchContent)
    FetchContent_Declare(
            doctest
            GIT_REPOSITORY https://gitee.com/acking-you/doctest.git
            GIT_TAG v2.4.9
            GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(doctest)
endif ()

# 获取当前目录下所有子目录的列表
file(GLOB SUBDIRS CONFIGURE_DEPENDS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
# 遍历子目录列表
foreach(subdir ${SUBDIRS})
    # 如果是目录并且包含CMakeLists.txt文件，则添加到项目中
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${subdir} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/CMakeLists.txt)
#        message("add_subdirectory:" ${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()















