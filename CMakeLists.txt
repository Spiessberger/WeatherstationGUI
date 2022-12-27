cmake_minimum_required(VERSION 3.16)

project(WeatherstationGUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Mqtt REQUIRED)

qt_add_executable(appWeatherstationGUI
    src/main.cpp
    src/application.h
    src/application.cpp
    src/panomaximageprovider.h
    src/panomaximageprovider.cpp
    src/downloadproxy.h
    src/downloadproxy.cpp
    src/system.h
    src/system.cpp
    src/data/weatherdataprovider.h
    src/data/weatherdataprovider.cpp
    src/data/mockweatherdataprovider.h
    src/data/mockweatherdataprovider.cpp
    src/data/i2cweatherdataprovider.h
    src/data/i2cweatherdataprovider.cpp
    src/data/mqttweatherdataprovider.h
    src/data/mqttweatherdataprovider.cpp
    src/data/qmlweatherdata.h
    src/data/qmlweatherdata.cpp
    src/data/weatherdatamanager.h
    src/data/weatherdatamanager.cpp

    qml/qml.qrc
    resources/resources.qrc
)

include_directories(src)

target_link_libraries(appWeatherstationGUI
    PRIVATE
        Qt6::Quick
        Qt6::Mqtt
    )

install(TARGETS appWeatherstationGUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

set(QML_IMPORT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/qml"
    CACHE STRING "Qt Creator extra qml import paths"
    FORCE
)
