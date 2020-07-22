###############################################################################
#                                                                             #
# ExifTool Project                                                           #
#                                                                             #
###############################################################################

###############################################################################
# define path
unix:{
    include(partform_unix.pri)
}


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# COMPONENTS
QT       += core gui
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# CONFIG
TARGET = ExifTool
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += APP_VERSION="\\\"V$${EXIFTOOL_VERSION}\\\""
CONFIG += c++11

# SRC CONFIG
SOURCES += \
    src/exifdecode.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/exifdecode.h \
    src/mainwindow.h

FORMS += \
    src/view.ui

#RESOURCES += \
#    src/img.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# OUT
build_type =
CONFIG(debug, debug|release) {
    build_type = build_debug
} else {
    build_type = build_release
}

DESTDIR     = $$build_type/out
OBJECTS_DIR = $$build_type/obj
MOC_DIR     = $$build_type/moc
RCC_DIR     = $$build_type/rcc
UI_DIR      = $$build_type/ui

# PLATFORM
unix:{
    QMAKE_RPATHDIR=$ORIGIN
    QMAKE_LFLAGS += -no-pie

    INCLUDEPATH += -I $${EXIV2_DIR}/include
    DEPENDPATH +=$${EXIV2_DIR}/include

    LIBS += -L $${EXIV2_DIR}/lib/ -lexiv2
}
