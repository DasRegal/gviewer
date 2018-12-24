cmake_minimum_required(VERSION 3.13)

project(g_code)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_PREFIX_PATH "C:\\Qt\\5.12.0\\winrt_x86_msvc2017")

find_package(Qt5
REQUIRED
COMPONENTS
 Core Widgets OpenGL ${QT_PREFIX_HINT})

set(SOURCE_FILES
    main.cpp
    src/editor.cpp
    src/glob_state.cpp
    src/line.cpp
    src/plotter.cpp
    src/point.cpp
    src/renderarea.cpp
)

file(GLOB_RECURSE INC_FILES "inc\*.h")

add_executable(g_code ${SOURCE_FILES} ${INC_FILES})
target_link_libraries(g_code Qt5::Widgets)
