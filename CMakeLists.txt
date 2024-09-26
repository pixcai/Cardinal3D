cmake_minimum_required(VERSION 3.22)

project(Cardinal3D
    VERSION 1.0
    DESCRIPTION "Stanford CS248 - Interactive Computer Graphics"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES_CARDINAL3D_GUI
    "src/gui/ui_main_menu_bar.cpp"
    "src/gui/manager.cpp"
)

set(SOURCES_CARDINAL3D_RENDERING
    "src/rendering/camera.cpp"
    "src/rendering/framebuffer.cpp"
    "src/rendering/mesh.cpp"
    "src/rendering/renderer.cpp"
    "src/rendering/scene_object.cpp"
    "src/rendering/scene.cpp"
    "src/rendering/shader.cpp"
)

set(SOURCES_CARDINAL3D
    ${SOURCES_CARDINAL3D_GUI}
    ${SOURCES_CARDINAL3D_RENDERING}
    "src/application.cpp"
    "src/platform.cpp"
    "src/main.cpp"
)

add_executable(Cardinal3D ${SOURCES_CARDINAL3D})

if(MSVC)
    target_compile_options(Cardinal3D PRIVATE /W4 /WX /wd4201 /wd4840 /wd4100 /fp:fast)
else()
    target_compile_options(Cardinal3D PRIVATE -Wall -Wextra -Werror -Wno-reorder -Wconversion)
endif()

include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(Stb REQUIRED)
target_include_directories(Cardinal3D PRIVATE ${Stb_INCLUDE_DIR})

find_package(assimp CONFIG REQUIRED)
target_link_libraries(Cardinal3D PRIVATE assimp::assimp)

find_package(glm CONFIG REQUIRED)
target_link_libraries(Cardinal3D PRIVATE glm::glm)

find_package(glad CONFIG REQUIRED)
target_link_libraries(Cardinal3D PRIVATE glad::glad)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(Cardinal3D PRIVATE imgui::imgui)

find_package(tinyfiledialogs CONFIG REQUIRED)
target_link_libraries(Cardinal3D PRIVATE tinyfiledialogs::tinyfiledialogs)