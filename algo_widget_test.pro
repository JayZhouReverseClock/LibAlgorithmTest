QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG+= console
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QComTools.cpp \
    ReadSeismFile.cpp \
    main.cpp \
    mainwindow.cpp \
    test.cpp

HEADERS += \
    QComTools.h \
    ReadSeismFile.h \
    mainwindow.h \
    test.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../6_30algorithm_debug/build-dx_qc_data_analysis-Desktop_Qt_5_15_0_MinGW_64_bit-Debug/release/ -ldx_qc_data_analysis
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../6_30algorithm_debug/build-dx_qc_data_analysis-Desktop_Qt_5_15_0_MinGW_64_bit-Debug/debug/ -ldx_qc_data_analysis
else:unix: LIBS += -L$$PWD/../../6_30algorithm_debug/build-dx_qc_data_analysis-Desktop_Qt_5_15_0_MinGW_64_bit-Debug/ -ldx_qc_data_analysis

INCLUDEPATH += $$PWD/../../6_30algorithm_debug/build-dx_qc_data_analysis-Desktop_Qt_5_15_0_MinGW_64_bit-Debug/debug
DEPENDPATH += $$PWD/../../6_30algorithm_debug/build-dx_qc_data_analysis-Desktop_Qt_5_15_0_MinGW_64_bit-Debug/debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../data_process/build-dx_qc_data_analysis-Desktop_Qt_5_15_0_MinGW_64_bit-Debug/release/ -ldx_qc_data_analysis
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../data_process/build-dx_qc_data_analysis-Desktop_Qt_5_15_0_MinGW_64_bit-Debug/debug/ -ldx_qc_data_analysis
else:unix: LIBS += -L$$PWD/../data_process/build-dx_qc_data_analysis-Desktop_Qt_5_15_0_MinGW_64_bit-Debug/ -ldx_qc_data_analysis

INCLUDEPATH += $$PWD/../data_process/dx_qc_data_analysis
DEPENDPATH += $$PWD/../data_process/dx_qc_data_analysis
