set(kimpanelplugin_SRCS
    kimpanel.cpp
    kimpanelagent.cpp
)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS DBus REQUIRED)
find_package(Qt5 COMPONENTS Qml REQUIRED)

QT5_ADD_DBUS_ADAPTOR(kimpanelplugin_SRCS
    org.kde.impanel.xml
    kimpanelagent.h
    PanelAgent)

include_directories(${CMAKE_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/plugin
    ${CMAKE_BINARY_DIR}/kimpanel-ui/plugin
    )
set(UDLC_UI_HEADERS
    ${PROJECT_SOURCE_DIR}/plugin/kimpanel.h
    ${PROJECT_SOURCE_DIR}/plugin/kimpanelagent.h
    )
QT5_WRAP_CPP(UDLC_UI_HEADERS_MOC ${UDLC_UI_HEADERS})

file(GLOB ALL_HEADERS "*.h" "./plugin/*.h")

add_library(kimpanelplugin SHARED ${kimpanelplugin_SRCS} ${ALL_HEADERS} ${UDLC_UI_HEADERS_MOC})
target_compile_definitions(kimpanelplugin PRIVATE -DKIMPANEL_LIBEXEC_DIR=\"${KDE_INSTALL_FULL_LIBEXECDIR}\")
target_link_libraries(kimpanelplugin
${Qt5Core_LIBRARIES}
${Qt5Widgets_LIBRARIES}
${Qt5Gui_LIBRARIES}
${Qt5DBus_LIBRARIES}
${Qt5Qml_LIBRARIES}
)
#install(TARGETS kimpanelplugin DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/private/kimpanel)
#install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/private/kimpanel)
