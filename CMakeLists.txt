cmake_minimum_required(VERSION 3.10)

project(launchpad-init)

add_subdirectory(libs/libremidi)

include_directories(
    libs/libremidi/include
)

add_executable(${PROJECT_NAME}
    src/main.cpp
)
target_link_libraries(${PROJECT_NAME} libremidi)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
)
