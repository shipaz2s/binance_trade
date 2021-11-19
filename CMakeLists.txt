cmake_minimum_required(VERSION 3.5)

project(binance_trade_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS -fPIC)

#set(QT_INCLUDE_DIR /mnt/ssd_files/pasha/Programs/Qt/6.2.1/gcc_64/include)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools Core Network REQUIRED)

set(TS_FILES binance_trade_app_ru_RU.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

set(LIB_SOURCES
        binance_client.cpp
        binance_client.h)



add_library(binance_client STATIC
    ${LIB_SOURCES}
)

target_link_libraries(binance_client PRIVATE Qt${QT_VERSION_MAJOR}::Core
                                             Qt${QT_VERSION_MAJOR}::Network)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(binance_trade
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )


# Define target properties for Android with Qt 6 as:
#    set_property(TARGET binance_trade_app APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

    #target_include_directories(binance_client PRIVATE ${QT_INCLUDE_DIR})

else()
    if(ANDROID)
        add_library(binance_trade SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(binance_trade
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(binance_trade PRIVATE Qt${QT_VERSION_MAJOR}::Widgets binance_client)

set_target_properties(binance_trade PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(binance_trade)
endif()
