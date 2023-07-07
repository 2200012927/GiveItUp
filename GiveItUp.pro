QT += core
QT += gui
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    banner.cpp \
    clickablelabel.cpp \
    failwidget.cpp \
    game.cpp \
    gui.cpp \
    main.cpp \
    producedby.cpp \
    settings.cpp \
    succeedwidget.cpp \
    widget.cpp

HEADERS += \
    banner.h \
    clickablelabel.h \
    failwidget.h \
    game.h \
    gui.h \
    macro.h \
    producedby.h \
    settings.h \
    succeedwidget.h \
    widget.h

FORMS += \
    banner.ui \
    failwidget.ui \
    game.ui \
    gui.ui \
    producedby.ui \
    settings.ui \
    succeedwidget.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RC_ICONS = icon.ico

RESOURCES += \
    res.qrc


