cmake_minimum_required(VERSION 3.20)
project(ResourceCompiler)

# 查找Qt的rcc工具（需提前设置Qt环境变量）
find_package(Qt5 COMPONENTS Core REQUIRED)
get_target_property(RCC_EXECUTABLE Qt5::rcc IMPORTED_LOCATION)


# 获取当前 CMakeLists.txt 的绝对路径
set(CURRENT_ABS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# 提取目录名称
get_filename_component(CURRENT_DIR_NAME ${CURRENT_ABS_DIR} NAME)
message(STATUS "RCC构建当前目录名: ${CURRENT_DIR_NAME}")

set(RCC_OUTPUT_ROOT "${CMAKE_CURRENT_BINARY_DIR}")

#qrc资源文件
file(GLOB QRC_FILES "./*.qrc")

# 遍历.qrc文件并生成.rcc
foreach(QRC_FILE ${QRC_FILES})
    get_filename_component(QRC_NAME ${QRC_FILE} NAME_WE)
    set(RCC_OUTPUT "${RCC_OUTPUT_ROOT}/${QRC_NAME}.rcc")
    add_custom_command(
        OUTPUT ${RCC_OUTPUT}
        COMMAND ${RCC_EXECUTABLE} --binary ${QRC_FILE} -o ${RCC_OUTPUT}
        DEPENDS ${QRC_FILE}
    )
    list(APPEND RCC_OUTPUTS ${RCC_OUTPUT})
endforeach()

# 创建资源生成目标
add_custom_target(GenerateRccResources ALL DEPENDS ${RCC_OUTPUTS})

# 删除旧的 .rcc 文件目录（在父目录中删除Resource文件夹）
add_custom_command(
    TARGET GenerateRccResources PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/${CURRENT_DIR_NAME}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/${CURRENT_DIR_NAME}"
    COMMENT "Deleting old .rcc files in Resource directory"
)

# 复制命令：从Resource目录复制到目标目录
add_custom_command(
    TARGET GenerateRccResources POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_BINARY_DIR}/${CURRENT_DIR_NAME}"
        "${CMAKE_BINARY_DIR}"
    COMMENT "Copying .rcc files to ${CMAKE_BINARY_DIR}"
)