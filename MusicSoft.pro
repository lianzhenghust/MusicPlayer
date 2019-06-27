#-------------------------------------------------
#
# Project created by QtCreator 2018-05-11T18:18:05
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicSoft
TEMPLATE = app



SOURCES += main.cpp\
        musicinterfase.cpp \
    navigate.cpp \
    playcontrol.cpp \
    musiclist.cpp \
    musiclistplay.cpp \
    musicplay.cpp \
    customslider.cpp \
    volumeslider.cpp \
    lyriccontrol.cpp

HEADERS  += musicinterfase.h \
    navigate.h \
    playcontrol.h \
    musiclist.h \
    musiclistplay.h \
    musicplay.h \
    customslider.h \
    volumeslider.h \
    lyriccontrol.h

FORMS    += musicinterfase.ui

DISTFILES += \
    qss/musicMain.qss \
    qss/navigate.qss \
    qss/playcontrol.qss \
    img/close.png \
    img/mini.png \
    img/icon.png \
    img/result.png \
    img/search1.png \
    img/skin.png \
    img/next.png \
    img/pre.png \
    img/stop.png \
    img/like1.png \
    img/sound.png \
    img/theme1.jpg \
    img/theme2.jpg \
    img/theme3.jpg \
    img/theme4.jpg \
    qss/musicList.qss \
    img/search2.png \
    img/update.png \
    img/cloud3.png \
    img/jack.png \
    img/wifi.png \
    qss/musicListCloud.qss \
    qss/musicListPhone.qss \
    img/Ruler.png \
    img/ruler1.png \
    img/maxSearch.png \
    img/MusicBox.png \
    qss/musicListSearch.qss \
    img/like2.png \
    img/item00.png \
    img/item02.png \
    img/item03.png \
    img/item04.png \
    img/item10.png \
    img/item12.png \
    img/item13.png \
    img/item14.png \
    img/download.png \
    img/continue.png \
    img/item01.png \
    img/item11.png \
    qss/musicListPlay.qss \
    img/showList.png \
    img/hideList.png \
    qss/musicSet.qss \
    qss/skinDialog.qss \
    img/item20.png \
    img/item21.png \
    img/item22.png \
    img/item23.png \
    img/item24.png \
    exeicon.rc \
    icon.ico \
    exeicon.rc \
    icon.ico \
    img/playcircle.png \
    img/playrandom.png \
    img/playsingle.png \
    img/defaulttheme.png \
    img/Eason.jpg

RC_FILE = exeicon.rc

RESOURCES += \
    res.qrc


