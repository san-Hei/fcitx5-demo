# Make sure it produce quwei.so instead of libquwei.so

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS DBus REQUIRED)
find_package(Fcitx5Module REQUIRED COMPONENTS Notifications DBus)
find_package(PkgConfig REQUIRED)

set(UDLC_UI_HEADERS
    ${PROJECT_SOURCE_DIR}/src/quweidbus.h
    )
QT5_WRAP_CPP(UDLC_UI_HEADERS_MOC ${UDLC_UI_HEADERS})

file(GLOB ALL_HEADERS "*.h")

add_library(quwei SHARED quwei.cpp quweidbus.cpp ${UDLC_UI_HEADERS_MOC} ${ALL_HEADERS})
target_link_libraries(quwei
    Fcitx5::Core
    ${Qt5Core_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5DBus_LIBRARIES}
    Fcitx5::Config
    Fcitx5::Module::Notifications
    Fcitx5::Module::DBus
    )
install(TARGETS quwei DESTINATION "${FCITX_INSTALL_LIBDIR}/fcitx5")



# Addon config file
# We need additional layer of conversion because we want PROJECT_VERSION in it.
configure_file(quwei-addon.conf.in.in quwei-addon.conf.in)
fcitx5_translate_desktop_file("${CMAKE_CURRENT_BINARY_DIR}/quwei-addon.conf.in" quwei-addon.conf)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/quwei-addon.conf" RENAME quwei.conf DESTINATION "${FCITX_INSTALL_PKGDATADIR}/addon")

# Input Method registration file
fcitx5_translate_desktop_file(quwei.conf.in quwei.conf)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/quwei.conf" DESTINATION "${FCITX_INSTALL_PKGDATADIR}/inputmethod")
