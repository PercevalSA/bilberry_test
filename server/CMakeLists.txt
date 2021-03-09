cmake_minimum_required(VERSION 3.0)

project(server LANGUAGES CXX)

file(GLOB SRV_SRCS *.cpp)

add_executable(server ${SRV_SRCS})

find_package(Qt5 COMPONENTS Core)
find_package(Qt5 COMPONENTS Network)

target_link_libraries(server PUBLIC Qt5::Core Qt5::Network)

install(TARGETS server RUNTIME DESTINATION bin)

set_target_properties(server PROPERTIES
    WIN32_EXECUTABLE FALSE
    MACOSX_BUNDLE FALSE
)
