QT += quick

CONFIG += c++11
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include
DEPENDPATH += include

SOURCES += \
        source/main.cpp \
        source/audiohandler.cpp \
        source/drumhandler.cpp \
        source/nativeobject.cpp \
        source/synthvoice.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    CuteKeys_de_DE.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/audiohandler.h \
    include/drumhandler.h \
    include/nativeobject.h \
    include/synthvoice.h \

QMAKE_LINK += -lrtaudio

DISTFILES += \
    ui/DialControl.qml \
    ui/DrumButton.qml \
    ui/DrumPage.qml \
    ui/NoteButton.qml \
    ui/Painter.qml \
    ui/SynthPage.qml \
    ui/main.qml
