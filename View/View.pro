QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Controller/s21_controller.cc \
    ../Model/s21_model.cc \
    credit_view.cc \
    deposit_view.cc \
    main.cc \
    qcustomplot.cpp \
    s21_view.cc

HEADERS += \
    ../Controller/s21_controller.h \
    ../Model/s21_model.h \
    credit_view.h \
    deposit_view.h \
    qcustomplot.h \
    s21_view.h

FORMS += \
    credit_view.ui \
    deposit_view.ui \
    s21_view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
