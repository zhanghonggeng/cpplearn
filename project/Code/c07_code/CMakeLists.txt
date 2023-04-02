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

# 遍历当前目录下的所有 .cpp 文件，并将它们添加到一个列表中
file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS *.cpp)

# 遍历列表中的每个源文件，将其添加到可执行文件中
foreach(src ${CPP_FILES})
    # 从源文件的完整路径中提取文件名（不带扩展名）
    get_filename_component(src_name ${src} NAME_WE)
    # 将源文件添加到可执行文件中，使用源文件名作为可执行文件名
    if(NOT ${src_name} STREQUAL "Leaky MS VC++")
        add_executable(my_${src_name} ${src})
        target_link_libraries(my_${src_name}  doctest_with_main)
    endif()
        #message(STATUS my_${src_name})
endforeach()