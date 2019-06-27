#include "musicplay.h"

MusicPlay::MusicPlay()
{

}

void MusicPlay::setPlayUrl(QString url)
{
    MusicPlay::mediaPlayer->setMedia(QUrl::fromLocalFile(url));
    int index = url.lastIndexOf("/");
    musicName = url.right(url.size() - index - 1);
    musicName = musicName.left(musicName.size() - 4);
    status = 0;

}

QString MusicPlay::countTime()
{
    QString result = "";
    if(playTime == 0)
        return QString("00:00");
    int time = playTime / 1000;
    if(playTime % 1000 != 0){
        time += 1;
    }
    int minute = time / 60;
    int second = time % 60;
    currentTime = itos(minute) + ":" + itos(second);
    result = "00:00/" + currentTime;
    return result;
}

QString MusicPlay::currentPos()
{
    QString result = "";
    qint64 pos = mediaPlayer->position();
    int time = pos / 1000 + 1;
    int minute = time / 60;
    int second = time % 60;
    result = itos(minute) + ":" + itos(second);
    return result;
}

void MusicPlay::play()
{
//    qDebug() << "执行play";
    if(status == -1)
        return;
    else if(status == 0){
//        status = 1;
        playTime = mediaPlayer->duration();
    }
    MusicPlay::mediaPlayer->play();
}

void MusicPlay::pause()
{
    MusicPlay::mediaPlayer->pause();
}

QString MusicPlay::itos(int val)
{
    int i = val;
    QString result = "";
    if(val == 0){
        result = "00";
        return result;
    }

    while(i){
        result.push_front(QString(i % 10 + '0'));
        i /= 10;
    }
    if(val / 10 == 0){
        result.push_front("0");
    }
    return result;
}

QMediaPlayer *MusicPlay::mediaPlayer = new QMediaPlayer;
int MusicPlay::status = -1;
qint64 MusicPlay::playTime = 0;
QString MusicPlay::musicName = "";
QString MusicPlay::currentTime = "";
