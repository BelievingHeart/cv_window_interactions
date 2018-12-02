cmake_minimum_required(VERSION 3.12)
project(cv_window_interactions)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_LINK_WHAT_YOU_USE TRUE)
set(CMAKE_CXX_COMPILE_FEATURES  -Wall -Wextra -Wpedantic -Weffc++)

find_program(TIDY "clang-tidy")
set(CMAKE_CXX_CLANG_TIDY ${TIDY} "-checks=*")
find_program(CPPCHECK cppcheck "--std=c++14")
set(CMAKE_CXX_CPPCHECK ${CPPCHECK})
find_program(IWYU include-what-you-use)
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE  ${IWYU})

find_package(OpenCV REQUIRED)
add_executable(main main.cpp)
target_include_directories(main PRIVATE ${OpenCV_INCLUDE_DIRS})
#target_link_libraries(hello PRIVATE ${OpenCV_LIBS})
target_link_libraries(main PRIVATE opencv_highgui opencv_core opencv_imgcodecs)