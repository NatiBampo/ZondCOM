QT       += core gui
QT += serialport
QT += sql
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    LoggingCategories.cpp \
    keithley.cpp \
    main.cpp \
    mainwindow.cpp \
    stats.cpp \
    tabcanvas.cpp \
    worker.cpp

HEADERS += \
    LoggingCategories.h \
    keithley.h \
    mainwindow.h \
    stats.h \
    tabcanvas.h \
    worker.h

FORMS += \
    keithley.ui \
    mainwindow.ui \
    stats.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    images.qrc
