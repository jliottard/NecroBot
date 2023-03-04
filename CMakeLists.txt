cmake_minimum_required(VERSION 3.15)
project(NecroBot)

set(CMAKE_BUILD_TYPE Debug)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# X11
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})


add_subdirectory(src)
list(APPEND EXTRA_LIBS Detection)

add_executable(NecroBot src/necrobot.cpp)
target_link_libraries(NecroBot
    ${EXTRA_LIBS}
    ${OpenCV_LIBS}
    ${X11_LIBRARIES}
)

target_include_directories(NecroBot PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )