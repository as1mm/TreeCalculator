QT       += core gui
QT += core gui widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SpeciesDatabase.cpp \
    TreeVolumeCalculator.cpp \
    customersdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    orderdetaildialog.cpp \
    ordersdialog.cpp \
    speciesdialog.cpp \
    stockdialog.cpp

HEADERS += \
    SpeciesDatabase.h \
    TreeVolumeCalculator.h \
    customersdialog.h \
    mainwindow.h \
    orderdetaildialog.h \
    ordersdialog.h \
    speciesdialog.h \
    stockdialog.h

FORMS += \
    customersdialog.ui \
    mainwindow.ui \
    orderdetaildialog.ui \
    ordersdialog.ui \
    speciesdialog.ui \
    stockdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    style.qrc \

