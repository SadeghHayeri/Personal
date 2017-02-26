#-------------------------------------------------
#
# Project created by QtCreator 2016-05-26T00:02:09
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A7-3-new
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../net/client/client.cpp \
    ../net/client/client_socket.cpp \
    ../net/client/interface.cpp \
    ../net/client/local_book.cpp \
    ../net/client/local_chapter.cpp \
    ../net/client/local_version.cpp \
    ../net/client/repository.cpp \
    ../net/client/tools.cpp \
    ../net/client/utility.cpp \
    serveraddress.cpp \
    firstfrom.cpp \
    qtools.cpp \
    codeeditor.cpp \
    loadingpage.cpp \
    error.cpp \
    downgradeform.cpp \
    editline.cpp \
    newbookform.cpp \
    newchapterform.cpp \
    downloadform.cpp \
    editbookForm.cpp \
    requestlistform.cpp \
    changeroleform.cpp

HEADERS  += mainwindow.h \
    ../net/client/add_line.h \
    ../net/client/book.h \
    ../net/client/book_maker.h \
    ../net/client/change_line.h \
    ../net/client/client.h \
    ../net/client/client_socket.h \
    ../net/client/colormod.h \
    ../net/client/delete_line.h \
    ../net/client/edit_line.h \
    ../net/client/exception.h \
    ../net/client/interface.h \
    ../net/client/local_book.h \
    ../net/client/local_chapter.h \
    ../net/client/local_version.h \
    ../net/client/network_exception.h \
    ../net/client/repository.h \
    ../net/client/tools.h \
    ../net/client/utility.h \
    serveraddress.h \
    firstfrom.h \
    qtools.h \
    codeeditor.h \
    mytree.h \
    loadingpage.h \
    error.h \
    downgradeform.h \
    editline.h \
    newbookform.h \
    newchapterform.h \
    downloadform.h \
    editbookForm.h \
    requestlistform.h \
    changeroleform.h

FORMS    += mainwindow.ui \
    serveraddress.ui \
    firstfrom.ui \
    loadingpage.ui \
    error.ui \
    downgradeform.ui \
    editline.ui \
    newbookform.ui \
    newchapterform.ui \
    downloadform.ui \
    editbookForm.ui \
    requestlistform.ui \
    changeroleform.ui
