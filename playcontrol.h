#ifndef PLAYCONTROL_H
#define PLAYCONTROL_H

/**
 * @author: jingbo
 * @date: 2018/05/14
 * @desc: 播放控制/其他按钮
 */

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>


#include "customslider.h"
#include "musiclistplay.h"
#include "volumeslider.h"




class PlayControl : public QWidget
{
    Q_OBJECT
public:
    explicit PlayControl(QWidget *parent = 0);
    //static int generateRandomInteger(int min, int max);//生成随机数
    QPushButton *getLyricBtn();


signals:

public slots:
    void likeBtnSlot();
    void pauseMusicSlot(); //按下时间表
    void playTimeSlot();    //时间轴1秒
    void playStateStop();   //播放结束
    void playPreMusic();
    void playNextMusic();
    void slider_progress_clicked();
    void slider_progress_moved();
    void slider_progress_released();
    void playModeSlot(); //播放模式
    void volume_progress_clicked();
    void volume_progress_moved();
    void volume_progress_released();

    //-----------菜单-----------
//    void addMusicSlot();
//    void deleteMusicSlot();
//    void changeOrderSlot();
//    void nowPlaySlot();
//    void clearListSlot();
//    void showContextMenu(QPoint);

private:
    QPushButton *preAMusicBtn;//上一首
    QPushButton *pauseMusicBtn;//暂停
    QPushButton *nextAMusicBtn;//下一首

    QLabel *musicInfo;
    QLabel *musicTime;
    CustomSlider *musicSchedule;
    VolumeSlider *volumeSchedule;

    QPushButton *likeBtn;
    QPushButton *downloadBtn;//下载
    QPushButton *playModeBtn;//模式
    QPushButton *musicSound;//音量
    QPushButton *lyrics;//歌词
    QPushButton *soundEffect;
    QPushButton *playMusicList;//播放列表

    //------Layout

    QHBoxLayout *controlLayout; //上/暂停/下控制
    QHBoxLayout *musicInfoTimeLayout;//信息/时间
    QVBoxLayout *musicInfoScheduleLayout;//进度
    QHBoxLayout *otherActLayout;//其他
    QHBoxLayout *controlMainLayout;//汇总
    QHBoxLayout *volumeLayout;


    //----------menu event----

//    QAction *addMusic;
//    QAction *deleteMusic;
//    QAction *changeOrder;
//    QAction *nowPlay;
//    QAction *clearList;

    //--------Function
    void setControlsLayout();
    void setControlsForm();
    void setControlsStyle();
    void connectSlot();

public:
    //----
    bool isLike;    //是否喜欢
    bool isPlay;    //是否播放
    bool begin;
    bool circleflag;//是否列表循环
    bool singleflag;//是否单曲循环



    //--播放控制
    QTimer *playTime;

};

#endif // PLAYCONTROL_H
