project( urtcontroller )

find_package( KDE4 REQUIRED )
include( KDE4Defaults )
include_directories( ${KDE4_INCLUDES} )

add_subdirectory( icons )

set(urtcontroller_SRCS
    src/main.cpp
    src/mainwindow.cpp
    src/server.cpp
    src/servermanager.cpp
)

kde4_add_executable( urtcontroller ${urtcontroller_SRCS} )

target_link_libraries( urtcontroller ${KDE4_KDEUI_LIBS} )
install( TARGETS urtcontroller DESTINATION ${BIN_INSTALL_DIR} )