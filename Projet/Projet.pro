QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = MonExecutable
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    associationinteractiontodo.cpp \
    contact.cpp \
    databaseinsert.cpp \
    databsedelete.cpp \
    gestioncontact.cpp \
    gestioninteraction.cpp \
    gestiontodo.cpp \
    historiquedialogue.cpp \
    interaction.cpp \
    interactiondialogue.cpp \
    main.cpp \
    mainwindow.cpp \
    personne.cpp \
    table.cpp \
    todo.cpp \
    tododialogue.cpp

HEADERS += \
    associationinteractiontodo.h \
    contact.h \
    databaseinsert.h \
    databsedelete.h \
    date.h \
    gestioncontact.h \
    gestioninteraction.h \
    gestiontodo.h \
    historiquedialogue.h \
    interaction.h \
    interactiondialogue.h \
    mainwindow.h \
    personne.h \
    table.h \
    todo.h \
    tododialogue.h

FORMS += \
    historiquedialogue.ui \
    interactiondialogue.ui \
    mainwindow.ui \
    tododialogue.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
# Add a Valgrind target
valgrind.target = valgrind
valgrind.commands = valgrind --leak-check=full ./$${TARGET}
valgrind.depends = all

# Add the new target to the default targets
QMAKE_EXTRA_TARGETS += valgrind
