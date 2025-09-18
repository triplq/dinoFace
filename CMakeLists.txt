cmake_minimum_required(VERSION 3.10)

project( OpenGame )
set(CMAKE_CXX_STANDARD 17)

find_package( OpenCV REQUIRED )
find_package( onnxruntime REQUIRED )

include_directories( 
    ${OpenCV_INCLUDE_DIRS})

add_executable(OpenGame 
    main.cpp )
    
set_target_properties(OpenGame PROPERTIES
    BUILD_RPATH "/usr/local/lib"
    INSTALL_RPATH "/usr/local/lib"
)

target_link_libraries(OpenGame 
    ${OpenCV_LIBS}
    onnxruntime )