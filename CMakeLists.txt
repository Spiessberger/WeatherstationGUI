cmake_minimum_required(VERSION 3.16)

project(WeatherstationGUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(appWeatherstationGUI
    src/main.cpp
    src/application.h
    src/application.cpp
    src/panomaximageprovider.h
    src/panomaximageprovider.cpp
    src/qmldownload.h
    src/qmldownload.cpp
)

qt_add_qml_module(appWeatherstationGUI
    URI WeatherstationGUI
    VERSION 1.0
    QML_FILES
        qml/main.qml
        qml/ws2022/components/PanoramaView.qml
)

include_directories(src)

target_link_libraries(appWeatherstationGUI
    PRIVATE Qt6::Quick)

install(TARGETS appWeatherstationGUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

set(QML_IMPORT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/qml"
    CACHE STRING "Qt Creator extra qml import paths"
    FORCE
)
