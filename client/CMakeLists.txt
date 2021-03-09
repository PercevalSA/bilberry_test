cmake_minimum_required(VERSION 3.0)

project(client LANGUAGES CXX)

# set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB CLI_SRCS *.cpp)

add_executable(client ${CLI_SRCS})

find_package(Qt5 COMPONENTS Core)
find_package(Qt5 COMPONENTS Network)

target_link_libraries(client PUBLIC Qt5::Core Qt5::Network)

install(TARGETS client RUNTIME DESTINATION bin)

set_target_properties(client PROPERTIES
    WIN32_EXECUTABLE FALSE
    MACOSX_BUNDLE FALSE
)
