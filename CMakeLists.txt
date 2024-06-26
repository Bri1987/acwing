cmake_minimum_required(VERSION 3.22)
project(acwing)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE DIR_BASIC ./basic/*.cpp)
file(GLOB_RECURSE DIR_STRUCTURE ./structure/*.cpp)
file(GLOB_RECURSE DIR_SEARCH_GRAPH ./search_graph/*.cpp)
file(GLOB_RECURSE DIR_MATH_KNOWLEDGE ./math_knowledge/*.cpp)
file(GLOB_RECURSE DIR_DP ./dp/*.cpp)
file(GLOB_RECURSE DIR_GREEDY ./greedy/*.cpp)
file(GLOB_RECURSE DIR_PRACTICE ./practice/*.cpp)

include_directories(.)
include_directories(basic)
include_directories(structure)
include_directories(search_graph)
include_directories(math_knowledge)
include_directories(dp)
include_directories(greedy)
include_directories(practice)

set(SOURCE_FILES ${DIR_BASIC} ${DIR_STRUCTURE} ${DIR_SEARCH_GRAPH} ${DIR_MATH_KNOWLEDGE} ${DIR_DP} ${DIR_GREEDY} ${DIR_PRACTICE})

# 遍历每个源代码文件并添加为可执行文件
foreach(SOURCE_FILE ${SOURCE_FILES})
    # 获取源代码文件的文件名（不包含路径和扩展名）
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    # 添加可执行文件
    add_executable(${FILE_NAME} ${SOURCE_FILE})
endforeach()