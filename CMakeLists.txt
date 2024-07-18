cmake_minimum_required(VERSION 3.22)
project(acwing)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE DIR_BASIC ./algorithm_basic/*.cpp)
file(GLOB_RECURSE DIR_PRACTICE ./practice/*.cpp)
file(GLOB_RECURSE DIR_IMPROVE ./algorithm_improve/*.cpp)

include_directories(.)
include_directories(algorithm_basic)
include_directories(algorithm_improve)
include_directories(practice)

set(SOURCE_FILES ${DIR_BASIC} ${DIR_PRACTICE} ${DIR_IMPROVE})

# 遍历每个源代码文件并添加为可执行文件
foreach(SOURCE_FILE ${SOURCE_FILES})
    # 获取源代码文件的文件名（不包含路径和扩展名）
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    # 添加可执行文件
    add_executable(${FILE_NAME} ${SOURCE_FILE})
endforeach()