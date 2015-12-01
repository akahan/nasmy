# Dependencies
set(REQUIRED_QT_VERSION "5.3.0")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Required Qt5 components
find_package(Qt5
    ${REQUIRED_QT_VERSION} REQUIRED
    Core
    Gui
    Widgets
    Quick
    QuickWidgets
)
find_package(OktetaGui REQUIRED)

set(NASMY_SRC
    main.cpp
    nasmy.cpp
    mainwindow.cpp
    settingswindow.cpp
    about.cpp
    project/project.cpp
    project/projectwindow.cpp
    project/projectstree.cpp
    project/projectstreeitem.cpp
    debugger/registerslist.cpp
    debugger/watchestree.cpp
    editor/asmedit.cpp
    editor/filecontroller.cpp
#     editor/syntax/highlighter.cpp
#     editor/completerpopupmodel.cpp
    qfileedit.cpp
)

add_executable(nasmy ${NASMY_SRC} nasmy.qrc)

# target_include_directories(nasmy PUBLIC $ENV{HOME}/.local/include/qt5)
target_link_libraries(nasmy
    Qt5::Core
    Qt5::Widgets
    Qt5::Quick
    Qt5::QuickWidgets
    OktetaCore
    OktetaGui
)

# add_executable(test2 test.cpp editor/asmedit.cpp resources/nasmy.qrc)
#
# target_link_libraries(test2
#     Qt5::Core
#     Qt5::Widgets
# )

include(${CMAKE_SOURCE_DIR}/cmake/add_translations_qt5.cmake)

add_translations_qt5(TS_FILES translations/nasmy_ru.ts)

## Installation
# install(FILES ${NASMY_QMS} DESTINATION "${CMAKE_SOURCE_DIR}/src/resources")
