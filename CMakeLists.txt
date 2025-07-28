cmake_minimum_required(VERSION 3.10)
project(learnOpenGL)
##################################################
# 编译选项
##################################################
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g3 -ggdb -Werror=return-type -Werror=reorder -Werror=conversion-null")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -g0 -Wall -Werror=return-type -Werror=reorder -Werror=conversion-null")

set(PROJECT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_PATH}/build)
message("CMAKE PROJECT_PATH: ${PROJECT_PATH}")
message("CMAKE OUTPUT_BIN_PATH: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

##################################################
# 三方库头文件
##################################################
set(3RD_INCLUDE_DIR_X11 ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/X11)
set(3RD_INCLUDE_DIR_EGL ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/EGL)
set(3RD_INCLUDE_DIR_GLES ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/GLES)
set(3RD_INCLUDE_DIR_GLES2 ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/GLES2)
set(3RD_INCLUDE_DIR_GLES3 ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/GLES3)
set(3RD_INCLUDE_DIR_GLM ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/glm)
set(3RD_INCLUDE_DIR_YAML_CPP ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/yaml-cpp)
set(3RD_INCLUDE_DIR_SPDLOG ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/spdlog/include)
set(3RD_INCLUDE_DIR_ASSIMP ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/assimp/include/assimp)
set(3RD_INCLUDE_DIR_STB ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/stb)

##################################################
# 三方库SO
##################################################
set(LIB_THREAD pthread)
set(LIB_SO_PATH_X11 ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/X11/lib/libX11.so)
set(LIB_SO_PATH_EGL ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/EGL/lib/libEGL.so)
set(LIB_SO_PATH_GLES2 ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/GLES2/lib/libGLESv2.so)
set(LIB_SO_PATH_YAML_CPP ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/yaml-cpp/lib/libyaml-cpp.so)
set(LIB_SO_PATH_ASSIMP ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/assimp/lib/libassimp.so)

set(ALL_3RD_LIBS
    ${LIB_THREAD}
    ${LIB_SO_PATH_X11}
    ${LIB_SO_PATH_EGL}
    ${LIB_SO_PATH_GLES2}
    ${LIB_SO_PATH_YAML_CPP}
    ${LIB_SO_PATH_ASSIMP}
)

##################################################
# 代码源文件
##################################################
file(GLOB SOURCE
    ${PROJECT_SOURCE_DIR}/learnOpenGL/3rdlib/stb/*.cpp
    ${PROJECT_SOURCE_DIR}/learnOpenGL/*.cpp
    ${PROJECT_SOURCE_DIR}/learnOpenGL/module/egl/lib/*.cpp
    ${PROJECT_SOURCE_DIR}/learnOpenGL/module/opengl/lib/*.cpp
    ${PROJECT_SOURCE_DIR}/learnOpenGL/module/render/*.cpp
    ${PROJECT_SOURCE_DIR}/learnOpenGL/module/render/rctx_config/*.cpp
    ${PROJECT_SOURCE_DIR}/learnOpenGL/module/render/rmgr_func/lib/*.cpp
)

# 递归添加源文件
# file(GLOB_RECURSE
    # ${PROJECT_SOURCE_DIR}/learnOpenGL/*.cpp
# )

##################################################
# 指定资源路径
##################################################
# add_definitions(-DRESOURCE_PATH="${PROJECT_SOURCE_DIR}/learnOpenGL/resource/")

##################################################
# 生成可执行目标
##################################################
add_executable(${PROJECT_NAME} ${SOURCE})

##################################################
# 为目标添加源代码头文件
##################################################
target_include_directories(${PROJECT_NAME} PRIVATE
    ${3RD_INCLUDE_DIR_X11}
    ${3RD_INCLUDE_DIR_EGL}
    ${3RD_INCLUDE_DIR_GLES}
    ${3RD_INCLUDE_DIR_GLES2}
    ${3RD_INCLUDE_DIR_GLES3}
    ${3RD_INCLUDE_DIR_GLM}
    ${3RD_INCLUDE_DIR_YAML_CPP}
    ${3RD_INCLUDE_DIR_SPDLOG}
    ${3RD_INCLUDE_DIR_ASSIMP}
    ${3RD_INCLUDE_DIR_STB}
    ${PROJECT_SOURCE_DIR}/learnOpenGL/module/egl/include
    ${PROJECT_SOURCE_DIR}/learnOpenGL/module/opengl/include
    ${PROJECT_SOURCE_DIR}/learnOpenGL/module/render
    ${PROJECT_SOURCE_DIR}/learnOpenGL/module/render/rctx_update
    ${PROJECT_SOURCE_DIR}/learnOpenGL/module/render/rctx_config
    ${PROJECT_SOURCE_DIR}/learnOpenGL/module/render/rctx_config/rconfig
    ${PROJECT_SOURCE_DIR}/learnOpenGL/module/render/rmgr_func/include
)
##################################################
# 为目标链接三方库头文件
##################################################
target_link_libraries(${PROJECT_NAME} ${ALL_3RD_LIBS})

##################################################
# 为目标指定资源路径
##################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_PATH="${PROJECT_SOURCE_DIR}/learnOpenGL/resource/")
message("RESOURCE_PATH: ${PROJECT_SOURCE_DIR}/learnOpenGL/resource/")
