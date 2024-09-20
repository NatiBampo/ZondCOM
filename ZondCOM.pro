QT += core gui
QT += serialport
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    LoggingCategories.cpp \
    connector.cpp \
    keithley.cpp \
    keysight.cpp \
    light.cpp \
    main.cpp \
    mainwindow.cpp \
    meter.cpp \
    planar.cpp \
    stats.cpp \
    tabcanvas.cpp \
    worker.cpp

HEADERS += \
    LoggingCategories.h \
    connector.h \
    keysight.h \
    light.h \
    meter.h \
    keithley.h \
    mainwindow.h \
    planar.h \
    serials.h \
    stats.h \
    tabcanvas.h \
    visa/visa.h \
    worker.h

FORMS += \
    mainwindow.ui \
    stats.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/visa/ -lvisa64

INCLUDEPATH += $$PWD/visa
DEPENDPATH += $$PWD/visa

RESOURCES += \
    images.qrc
