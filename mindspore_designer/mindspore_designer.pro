QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    draw_charts.cpp

HEADERS += \
    mainwindow.h \
    draw_charts.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    picture.qrc

DISTFILES += \
    mindspore_python.py \
    python_test.py

win32: LIBS += -L'C:/Program Files/Python38/libs/' -lpython38

INCLUDEPATH += 'C:/Program Files/Python38/include'
DEPENDPATH += 'C:/Program Files/Python38/include'

win32:!win32-g++: PRE_TARGETDEPS += 'C:/Program Files/Python38/libs/python38.lib'
#else:win32-g++: PRE_TARGETDEPS += 'C:/Program Files/Python38/libs/libpython38.a'
