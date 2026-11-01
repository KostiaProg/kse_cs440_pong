cmake_minimum_required(VERSION 3.16)
project(SFML_Project CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML 3 package from MSYS2
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Automatically collect all .cpp files in src/
file(GLOB SOURCES "src/*.cpp")

add_executable(SFML_Project ${SOURCES})

target_link_libraries(SFML_Project PRIVATE SFML::Graphics SFML::Window SFML::System)

# Copy resources directory next to executable POST-BUILD
add_custom_command(TARGET SFML_Project POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        $<TARGET_FILE_DIR:SFML_Project>/resources
)