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

#保存一下就执行，因此每次执行之后都要构建这个任务
file(REMOVE_RECURSE "${CMAKE_CURRENT_BINARY_DIR}")

#qrc资源文件
file(GLOB QRC_FILES "./*.qrc")

# 遍历.qrc文件并生成.rcc
foreach(QRC_FILE ${QRC_FILES})
    get_filename_component(QRC_NAME ${QRC_FILE} NAME_WE)
    set(RCC_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${QRC_NAME}.rcc")
    message(STATUS "拷贝文件: ${RCC_OUTPUT}")
    add_custom_command(
        OUTPUT ${RCC_OUTPUT}
        COMMAND ${RCC_EXECUTABLE} --binary ${QRC_FILE} -o ${RCC_OUTPUT}
        DEPENDS ${QRC_FILE}
    )
    list(APPEND RCC_OUTPUTS ${RCC_OUTPUT})
endforeach()

# 创建资源生成目标
add_custom_target(GenerateRccResources ALL DEPENDS ${RCC_OUTPUTS})