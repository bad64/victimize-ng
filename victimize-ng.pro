QT += widgets
CONFIG -= debug_and_release
CONFIG += release


SOURCES += \
    src/main.cpp

HEADERS += \
    src/includes.h

win32 {
    TARGET = bin/victimize-ng
    QMAKE_POST_LINK = windeployqt --no-translations --release bin/victimize-ng.exe
    bin.path =
    bin.files =
    INSTALLS =
}

unix {
    TARGET = victimize
    QMAKE_POST_LINK =
    bin.path = /usr/local/bin/
    bin.files = victimize
    INSTALLS += bin
}

QMAKE_CLEAN += Makefile .qmake.stash
