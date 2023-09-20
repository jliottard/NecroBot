add_library(Capture screenshot.cpp)

target_include_directories(Capture
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}    
)
