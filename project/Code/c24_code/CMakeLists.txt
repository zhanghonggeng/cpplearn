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
