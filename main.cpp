#include "musicinterfase.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MusicInterfase *w = new MusicInterfase;
//    w.setStyleSheet("border-image: url(../localMusic/陈一发儿/photo/cyfe1.jpg)");

    w->show();

    return a.exec();
}
