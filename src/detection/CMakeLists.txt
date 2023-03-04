add_library(Detection capture.cpp detect.cpp)

target_include_directories(Detection
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}    
)