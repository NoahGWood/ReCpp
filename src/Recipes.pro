QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ingredients.cpp \
    main.cpp \
    mainwindow.cpp \
    recipecard.cpp \
    recipeimage.cpp \
    recipeitem.cpp \
    recipesearch.cpp \
    recipesteps.cpp \
    themeeditor.cpp \
    themetools.cpp

HEADERS += \
    ingredients.h \
    mainwindow.h \
    recipecard.h \
    recipeimage.h \
    recipeitem.h \
    recipesearch.h \
    recipesteps.h \
    themeeditor.h \
    themetools.h

FORMS += \
    ingredients.ui \
    mainwindow.ui \
    recipecard.ui \
    recipeimage.ui \
    recipesearch.ui \
    recipesteps.ui \
    themeeditor.ui \
    themetools.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    dark.css \
    light.css

RESOURCES += \
    theme.qrc
