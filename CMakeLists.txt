cmake_minimum_required(VERSION 3.16)
project(tree_drawer)

set(CMAKE_CXX_STANDARD 17)

find_package (Threads)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-DVISUALIZER_TREE")
find_package(OpenGL REQUIRED)
find_package (Threads)
find_package(GLEW REQUIRED)

if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

set(SFML_LIBS sfml-graphics sfml-window sfml-system)

add_executable(tree_drawer
        imgui/imgui.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_draw.cpp
        imgui/imgui-SFML.cpp
        main.cpp
        Tree.cpp
        TreeWidget.cpp
        TreeNodeWidget.cpp
        rotationsVisualizer.cpp
        ParameterWidget.cpp
        ParametersWidget.cpp
        TreeTemplates.cpp
        )

include_directories(imgui include ${OPENGL_INCLUDE_DIRS} .)

if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

target_link_libraries(tree_drawer ${OPENGL_LIBRARY} ${SFML_LIBS} ${GLEW_LIBRARIES} Threads::Threads)