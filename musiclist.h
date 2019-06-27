#ifndef MUSICLIST_H
#define MUSICLIST_H

/**
 * @author: jingbo
 * @date: 2018/05/14
 * @desc: 音乐列表
 */

#include <QWidget>
#include <QPushButton>
#include <QStackedLayout>
#include <QFile>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <vector>
#include <QString>


#include "musiclistplay.h"

enum SelectMusicItem{PLAYLIST, CLOUD, PHONE, DOWNLOAD, SEARCH};
class MusicList : public QWidget
{
    Q_OBJECT
public:
    explicit MusicList(QWidget *parent = 0);

signals:

public slots:
    void musicListItemSwitch();

private:
    QPushButton *playListBtn;
    QPushButton *cloudBtn;
    QPushButton *downloadBtn;
    QPushButton *phoneBtn;
    QPushButton *searchBtn;
    std::vector<QPushButton*> vbtnPtr;
    //----------Layout
    QHBoxLayout *operNavLayout;
    QStackedLayout *operObjLayout;
    QVBoxLayout *musicListMainLayout;

    //--------Fcuntion
    void setControlsLayout();
    void setControlsForm();
    void setControlsStyle();
    void connectSlot();

    MusicListPlay *playPage;
};

#endif // MUSICLIST_H
