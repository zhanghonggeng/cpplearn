cmake_minimum_required(VERSION 3.24)
project(CodingInterviewChinese2 LANGUAGES C CXX)

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
#    include(FetchContent)
#    FetchContent_Declare(
#            doctest
#            GIT_REPOSITORY https://gitee.com/acking-you/doctest.git
#            GIT_TAG v2.4.9
#            GIT_SHALLOW TRUE
#    )
#    FetchContent_MakeAvailable(doctest)

    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)
endif ()

## 获取当前目录下所有子目录的列表
#file(GLOB SUBDIRS CONFIGURE_DEPENDS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
## 遍历子目录列表
#foreach(subdir ${SUBDIRS})
#    # 如果是目录并且包含CMakeLists.txt文件，则添加到项目中
#    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${subdir} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/CMakeLists.txt)
##        message("add_subdirectory "${subdir})
#        add_subdirectory(${subdir})
#    endif()
#endforeach()


# 遍历当前目录下的所有 .cpp 文件，并将它们添加到一个列表中
file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS *.cpp)

# 遍历列表中的每个源文件，将其添加到可执行文件中
foreach (src ${CPP_FILES})
    # 从源文件的完整路径中提取文件名（不带扩展名）
    get_filename_component(src_name ${src} NAME_WE)
    # 检查 src_name 是否以 my_ 开头
    string(FIND ${src_name} "my_" my_prefix_index)
    if (my_prefix_index EQUAL 0)
        enable_testing()
        # 将源文件添加到可执行文件中，使用源文件名作为可执行文件名
        add_executable(my_${src_name} ${src})
#        target_link_libraries(my_${src_name} doctest_with_main)
        target_link_libraries(my_${src_name} GTest::gtest_main)
        gtest_discover_tests(my_${src_name})
    endif ()
    #    message(STATUS my_${src_name})
endforeach ()