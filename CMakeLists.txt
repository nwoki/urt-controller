project( urtcontroller )

find_package( KDE4 REQUIRED )                      #locates the package that you ask it for (in this case KDE4) and sets some variables describing the location of the package's headers and libraries
include( KDE4Defaults )
include_directories( ${KDE4_INCLUDES} )

set(urtcontroller_SRCS
    src/main.cpp
    src/mainwindow.cpp
)

kde4_add_executable( urtcontroller ${urtcontroller_SRCS} )
target_link_libraries( urtcontroller ${KDE4_KDEUI_LIBS} )
install( TARGETS urtcontroller ${INSTALL_TARGETS_DEFAULT_ARGS} )