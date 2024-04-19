cmake_minimum_required(VERSION 3.20)

project("SpreadSheet")

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE HDR_FILES "src/*.h")

add_executable(app ${SRC_FILES} ${HDR_FILES})

set_target_properties(app PROPERTIES CXX_STANDARD 20)