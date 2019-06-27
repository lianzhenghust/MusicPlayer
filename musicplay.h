#ifndef MUSICPLAY_H
#define MUSICPLAY_H

#include <QObject>
#include <QMediaPlayer>
#include <QUrl>


class MusicPlay
{
public:
    MusicPlay();
    static QMediaPlayer *mediaPlayer;
    static qint64 playTime;     //播放时间, 毫秒单位
    static QString currentTime;//当前歌曲总时间
    static int status;  //-1未设置播放源 0设置播放源还未开始播放 1已经播放过
    static void setPlayUrl(QString);// 设置播放源
    static QString countTime(); //毫秒统计为分钟数
    static QString currentPos();

    static void play();
    static void pause();
    static QString musicName;
    static QString itos(int);


};

#endif // MUSICPLAY_H
