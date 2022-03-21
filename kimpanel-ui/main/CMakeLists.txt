include_directories(${CMAKE_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/plugin
    )

set(preedit_SRCS
    main.cpp
    inputPanel.cpp
    statusarea.cpp
)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/icon/res.qrc)
#qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS DBus REQUIRED)

link_directories(${CMAKE_BINARY_DIR}/plugin)


set(UDLC_UI_HEADERS
    ${PROJECT_SOURCE_DIR}/main/inputPanel.h
    ${PROJECT_SOURCE_DIR}/main/statusarea.h
    )
QT5_WRAP_CPP(UDLC_UI_HEADERS_MOC ${UDLC_UI_HEADERS})

file(GLOB ALL_HEADERS "*.h" "./main/*.h")

add_executable(kimpanelUI main.cpp inputPanel.cpp statusarea.cpp ${UDLC_UI_HEADERS_MOC} ${ALL_HEADERS} ${QRC_SOURCE_FILES})

target_link_libraries(kimpanelUI kimpanelplugin
    ${Qt5Core_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5DBus_LIBRARIES}
)
