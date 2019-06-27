#ifndef MUSICINTERFASE_H
#define MUSICINTERFASE_H

/**
 * @author: jingbo
 * @date: 2018/05/14
 * @desc: 音乐主界面框架
 */

#include <QWidget>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QPainter>

#include "navigate.h"
#include "playcontrol.h"
#include "musiclist.h"
#include "lyriccontrol.h"
#include "musiclistplay.h"
#include "musicplay.h"


namespace Ui {
class MusicInterfase;
}

class MusicInterfase : public QWidget
{
    Q_OBJECT

public:
    explicit MusicInterfase(QWidget *parent = 0);
    ~MusicInterfase();

public slots:
    //---Nav
    void showMask();    //mask
    void hideMask();   //mask
    void miniWin();    //最小化窗口
    void closeWin();    //关闭窗口
    void customizeSkin();//自定义皮肤

private:
    Ui::MusicInterfase *ui;

    Navigate *musicNav;
    PlayControl *musicPlayControl;
    MusicList *musicList;
    LyricControl *lyricControl;

    //----------Layout
    QHBoxLayout *musicCenterLayout;
    QVBoxLayout *musicMainLayout;
    QHBoxLayout *musicNavAndWinControl;
    QHBoxLayout *windowControl;

    //----------Function
    void setControlsLayout();
    void setControlsForm();
    void connectSlot();

    //-----Nav
    QPushButton *resultPreBtn;
    QPushButton *skinBtn;
    //QPushButton *skinDiaCloseBtn;
    QPushButton *miniBtn;
    QPushButton *closeBtn;
    QPushButton *customizeSkinBtn;
    QStringList themePathList;


    QWidget *mask;
    int index=0;

    //---MusicPlay
    MusicPlay *musicPlay;


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool pressFlag;
    QPoint beginPos;
};

#endif // MUSICINTERFASE_H
