QT       += core gui printsupport multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../SmartCalc_v1.0.c \
    depcalc.cpp \
    graph.cpp \
    loancalc.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    depcalc.h \
    graph.h \
    loancalc.h \
    mainwindow.h \
    ../SmartCalc_v1.0.h \
    qcustomplot.h

FORMS += \
    depcalc.ui \
    graph.ui \
    loancalc.ui \
    mainwindow.ui

macx: ICON = ../../assets/icons/icon.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../../assets/icons/icons.qrc

DISTFILES += \
    ../../assets/icons/icon.icns


