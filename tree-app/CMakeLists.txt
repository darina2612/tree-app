cmake_minimum_required(VERSION 3.0.2)

project(tree-app)

find_package(Qt5 5.7.1 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_definitions(-DROOT_DIR="${ROOT_DIR}")
add_definitions(-DBUILD_DIR="${BUILD_DIR}")

set(SOURCES
    main.cpp
    MainWindow.cpp
    PersonData.cpp
    Drawer.cpp
    ConversionUtils.cpp
    FamilyTree.cpp
    FamilyNode.cpp
    DataEditControl.cpp
    PictureChooser.cpp
    TextLineEditControl.cpp
    Image.cpp
    EditController.cpp)

add_executable(tree-app ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

set_property(TARGET tree-app PROPERTY CXX_STANDARD 14)
