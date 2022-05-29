cmake_minimum_required(VERSION 3.16)

project(WheelMenu VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 6.2 COMPONENTS Quick Core REQUIRED)

qt_add_executable(appWheelMenu
    main.cpp
)

qt_add_qml_module(appWheelMenu
    URI WheelMenu
    VERSION 1.0
    QML_FILES
    main.qml
    qml/WheelMenuButton.qml
    qml/WheelMenuView.qml
    qml/GridPage.qml
    qml/OnlyItemPage.qml
    SOURCES
    src/wheelMenuModel.h
    src/wheelMenuModel.cpp
)

set_target_properties(appWheelMenu PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appWheelMenu PRIVATE src)
target_compile_definitions(appWheelMenu
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appWheelMenu
    PRIVATE Qt6::Quick Qt6::Core)
