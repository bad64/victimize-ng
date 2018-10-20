QT += widgets
CONFIG -= debug_and_release
CONFIG += release

SOURCES += \
    src/main.cpp

HEADERS += \
    src/includes.h

TRANSLATIONS += src/translations/victimize_en.ts src/translations/victimize_fr.ts
RESOURCES = src/resources.qrc

win32 {
    TARGET = bin/victimize-ng
    translations.path = bin/translations
    QMAKE_POST_LINK = windeployqt --no-translations --release bin/victimize-ng.exe
    bin.path =
    bin.files =
    INSTALLS += translations
}

unix {
    TARGET = victimize
    translations.path = /usr/local/share/victimize-ng
    QMAKE_POST_LINK =
    bin.path = /usr/local/bin/
    bin.files = victimize
    INSTALLS += bin translations
}

QMAKE_CLEAN += Makefile .qmake.stash

RESOURCES += \
    src/resources.qrc
