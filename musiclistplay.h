#ifndef MUSICLISTPLAY_H
#define MUSICLISTPLAY_H

/**
 * @author: jingbo
 * @date: 2018/05/16
 * @desc: 音乐列表-播放列表
 */

#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QListView>
#include <QTreeView>
#include <QHeaderView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QFileDialog>

#include "musicplay.h"




class PlayControl;


class MusicListPlay : public QWidget
{
    Q_OBJECT
public:
    explicit MusicListPlay(QWidget *parent = 0);
    static QStringList *playUrlList;
    static int playingIndex;//记录正在播放的歌的索引
    static QStandardItemModel *model;
    static bool autoPlay; //决定播放状态的改变究竟是由播放结束还是点击下/上一首以及打断播放所引起
    static bool playAnother;
    QListView *defaultPlayList;
    QStandardItem *item;
signals:

public slots:
    void isShowList();
    void showContextMenu(QPoint);
    void addMusicSlot();
    void deleteMusicSlot();
    void changeOrderSlot();
    void nowPlaySlot();
    void clearListSlot();

private:

    QPushButton *defaultListBtn;//310宽度
    QAction *addMusic;
    QAction *deleteMusic;
    QAction *changeOrder;
    QAction *nowPlay;
    QAction *clearList;




    QVBoxLayout *musicListPlayMainLayout;
    //---Funciton
    void setControlsLayout();
    void setControlsForm();
    void setControlsStyle();
    void connectSlot();



    //---Other
    bool isShowDefault;
    bool isShowRecent;

};

#endif // MUSICLISTPLAY_H
