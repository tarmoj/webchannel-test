#-------------------------------------------------
#
# Project created by QtCreator 2015-09-10T12:59:27
#
#-------------------------------------------------

QT       += core gui
QT       += network webenginewidgets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jsDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    htmlpage.cpp \
    csoundobject.cpp

HEADERS  += mainwindow.h \
    htmlpage.h \
    csoundobject.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES +=

linux: INCLUDEPATH += /usr/local/include/csound

win32:contains(QT_ARCH, i386) {
	INCLUDEPATH += "$$(PROGRAMFILES)\\Csound6\\include\\csound"
	LIBS += -L "$$(PROGRAMFILES)\\Csound6\\bin"
	message("32-bit")
}
win32:contains(QT_ARCH, x86_64){
	INCLUDEPATH += "$$(PROGRAMFILES)\\Csound6_x64\\include\\csound"
	LIBS += -L "$$(PROGRAMFILES)\\Csound6_x64\\bin"
	message("64-bit")
}


linux|win32: LIBS += -lcsound64

mac: {
LIBS += -F/Library/Frameworks/ -framework CsoundLib64
INCLUDEPATH += /Library/Frameworks/CsoundLib64.framework/Versions/6.0/Headers
}
