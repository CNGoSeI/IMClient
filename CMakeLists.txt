cmake_minimum_required(VERSION 3.20)

project(IMClient LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("项目:${PROJECT_NAME} 开始配置")

if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON) #启用的GUI窗口，禁用黑框输出
endif()

if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

find_package(Qt5 COMPONENTS Widgets UiTools Core Network REQUIRED)

#Widgets
aux_source_directory(./Widgets WgtFiles)

#Common
aux_source_directory(./Common CommonFiles)

#OtherCMake
add_subdirectory(./Resource) #资源文件

if(ANDROID)
  add_library(${PROJECT_NAME} SHARED
    main.cpp
    ${WgtFiles}
    ${CommonFiles}
  )
else()
  add_executable(${PROJECT_NAME}
    main.cpp
    ${WgtFiles}
    ${CommonFiles}
)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt5::Core
    Qt5::Widgets
    Qt5::UiTools
    Qt5::Network
)

#拷贝qt的运行依赖到编译路径
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E env PATH="${QT_BIN_DIR}" 
        "${WINDEPLOYQT_EXE}"
        "$<TARGET_FILE:${PROJECT_NAME}>"
        --qmldir "${CMAKE_CURRENT_SOURCE_DIR}/qml"
        --no-translations
        --compiler-runtime
        COMMENT "Deploying Qt dependencies..."
    )
endif()

#包含所有需要拷贝的文件（相对路径）
set(RESOURCE_FILES
    "configs/config.ini"
)

# 循环遍历每个文件，为其添加拷贝命令
foreach(file ${RESOURCE_FILES})
    # 获取文件所在的目录，例如 "configs" 或 "texts"
    get_filename_component(dir ${file} DIRECTORY)
    message("拷贝文件：路径${dir} 文件${file}")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        # 先确保目标目录存在
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/${dir}"
        # 拷贝文件到对应目录下
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/${file}" "${CMAKE_BINARY_DIR}/${file}"
        COMMENT "Copying ${file} to build directory"
    )
endforeach()
