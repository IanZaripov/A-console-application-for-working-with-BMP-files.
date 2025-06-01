cmake_minimum_required(VERSION 3.10)
project(BMP_Processor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bmp_processor
    BMP.cpp
    BMP_READER.cpp
    BMP.h
)

if(WIN32)
    target_link_libraries(bmp_processor gdi32)
endif()

set_target_properties(bmp_processor PROPERTIES OUTPUT_NAME "bmp_processor")

if(MSVC)
    target_compile_options(bmp_processor PRIVATE /W4 /WX-) 
endif()