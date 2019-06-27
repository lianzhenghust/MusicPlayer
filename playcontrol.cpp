#include "playcontrol.h"

/**
 * @author: jingbo
 * @date: 2018/05/14
 * @desc: 播放控制/其他按钮
 */

PlayControl::PlayControl(QWidget *parent) : QWidget(parent)
{
    preAMusicBtn = new QPushButton;
    pauseMusicBtn = new QPushButton;
    nextAMusicBtn = new QPushButton;

    musicInfo = new QLabel;
    musicTime = new QLabel;
    musicSchedule = new CustomSlider();
    musicSchedule->setOrientation(Qt::Horizontal);
    volumeSchedule = new VolumeSlider();
    volumeSchedule->setOrientation(Qt::Horizontal);
    musicSchedule->setEnabled(false);
    //volumeSchedule->setEnabled(false);


    likeBtn = new QPushButton;
    downloadBtn = new QPushButton;
    playModeBtn = new QPushButton;
    musicSound = new QPushButton;
    soundEffect = new QPushButton;
    lyrics = new QPushButton;
    playMusicList = new QPushButton;

    controlLayout = new QHBoxLayout;
    musicInfoTimeLayout = new QHBoxLayout;
    musicInfoScheduleLayout = new QVBoxLayout;
    otherActLayout = new QHBoxLayout;
    controlMainLayout = new QHBoxLayout;
    volumeLayout = new QHBoxLayout;

    playTime = new QTimer;
    setLayout(controlMainLayout);//添加布局
    setFixedHeight(68);//设置高度
    setControlsLayout();
    setControlsForm();
    setControlsStyle();
    connectSlot();

    begin = true;
    circleflag = false;
    singleflag = false;

}

QPushButton *PlayControl::getLyricBtn()
{
    return lyrics;
}
void PlayControl::likeBtnSlot()
{
    if(isLike){
        likeBtn->setIcon(QIcon(":/img/like1.png"));
        isLike = false;
    }
    else{
        likeBtn->setIcon(QIcon(":/img/like2.png"));
        isLike = true;
    }
}

void PlayControl::pauseMusicSlot()
{
    qDebug() << "运行pauseMusicSlot";
    if(MusicListPlay::playUrlList->empty())
        return;
    if(begin)
    {
        qDebug() << "执行begin";
        musicSchedule->setEnabled(true);
        begin = false;
        //if(MusicListPlay::playAnother == false)
            MusicPlay::setPlayUrl(MusicListPlay::playUrlList->at(MusicListPlay::playingIndex));
    }
    if(isPlay){
        qDebug() << "执行isplay为真";
        musicSchedule->setEnabled(true);
        pauseMusicBtn->setIcon(QIcon(":/img/stop.png"));
        isPlay = false;
        MusicPlay::pause();
        playTime->stop();
    }
    else if(MusicListPlay::playAnother == true)
    {
        MusicListPlay::playAnother = false;
        qDebug() << "执行isplay为假";
        MusicPlay::setPlayUrl(MusicListPlay::playUrlList->at(MusicListPlay::playingIndex));
        musicSchedule->setEnabled(true);
        pauseMusicBtn->setIcon(QIcon(":/img/continue.png"));
        isPlay = true;
        MusicPlay::play();
        qDebug() << "-------------";
        if(MusicPlay::status == 0){
            musicInfo->setText(MusicPlay::musicName);
            musicTime->setText(MusicPlay::countTime());
            //musicSchedule->setRange(0, (int)MusicPlay::playTime);
            MusicPlay::status = 1;
        }
        playTime->start();

    }
    else
    {
        qDebug() << "执行palyanother为假";
        //MusicPlay::setPlayUrl(MusicListPlay::playUrlList->at(MusicListPlay::playingIndex));
        musicSchedule->setEnabled(true);
        pauseMusicBtn->setIcon(QIcon(":/img/continue.png"));
        isPlay = true;
        MusicPlay::play();
        qDebug() << "-------------";
        if(MusicPlay::status == 0){
            musicInfo->setText(MusicPlay::musicName);
            musicTime->setText(MusicPlay::countTime());
            //musicSchedule->setRange(0, (int)MusicPlay::playTime);
            MusicPlay::status = 1;
        }
        playTime->start();
    }
}

void PlayControl::playTimeSlot()
{
    QString curr = MusicPlay::countTime();
    musicTime->setText(MusicPlay::currentPos() + "/" + MusicPlay::currentTime);
    qint64 pos = MusicPlay::mediaPlayer->position();
    musicSchedule->setValue((int)pos);
}

void PlayControl::playStateStop()//涉及播放顺序的问题
{

    if(MusicPlay::mediaPlayer->state() != QMediaPlayer::StoppedState || MusicListPlay::autoPlay == false)
    {
        MusicListPlay::autoPlay = true;
        return ;
    }

    else if(MusicListPlay::playAnother == true)//如果是选定某一首播放则执行
    {
        qDebug() << "播放选定歌曲";
        //MusicListPlay::playAnother = false;
        isPlay = false;
        begin = false;
        MusicPlay::status = 0;

        pauseMusicSlot();
    }
    else //自己播放完毕自动跳向下一首
    {
        MusicListPlay::autoPlay = true;
        qDebug() << "运行playStateStop";
        musicSchedule->setValue(0);
        QString text = "00:00/" + MusicPlay::currentTime;
        musicTime->setText(text);
        pauseMusicBtn->setIcon(QIcon(":/img/stop.png"));
        playNextMusic();
    }

}





void PlayControl::playPreMusic()
{
    qDebug() << "运行playPreMusic";
    MusicListPlay::autoPlay = false;
//    pauseMusicBtn->setIcon(QIcon(":/img/continue.png"));
    if(circleflag == true)
    {
        if(MusicListPlay::playingIndex>0 && MusicListPlay::playingIndex<=(MusicListPlay::playUrlList->count()-1))
        {
            isPlay = false;
            begin = true;
            MusicPlay::status = -1;
            MusicListPlay::playingIndex--;
            pauseMusicSlot();
        }
        else
        {
            MusicListPlay::playingIndex = MusicListPlay::playUrlList->count()-1;
            MusicPlay::status = -1;
            isPlay = false;
            begin = true;
            pauseMusicSlot();
        }
    }
    else if(singleflag == true)
    {
        MusicPlay::status = -1;
        isPlay = false;
        begin = true;
        pauseMusicSlot();
    }
    else
    {
        int nRandom=0;
        if(MusicListPlay::playUrlList->count() == 1)
        {
            MusicPlay::status = -1;
            isPlay = false;
            begin = true;
            pauseMusicSlot();
        }
        else
        {
            while(nRandom == MusicListPlay::playingIndex)
            {
                Q_ASSERT(0 < MusicListPlay::playUrlList->count());
                // 加入随机种子。种子是当前时间距离0点0分0秒的秒数。
                // 每次启动程序，只添加一次种子，以做到数字真正随机。
                static bool seedStatus;
                if (!seedStatus)
                {
                    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
                    seedStatus = true;
                }
                nRandom = qrand() % (MusicListPlay::playUrlList->count());
            }
            MusicListPlay::playingIndex = nRandom;
            MusicPlay::status = -1;
            isPlay = false;
            begin = true;
            pauseMusicSlot();
        }

    }
}






void PlayControl::playNextMusic()
{
    qDebug() << "运行playNextMusic";
    MusicListPlay::autoPlay = false;
    //pauseMusicBtn->setIcon(QIcon(":/img/continue.png"));
    if(circleflag == true)
    {
        if(MusicListPlay::playingIndex>=0 && MusicListPlay::playingIndex<(MusicListPlay::playUrlList->count()-1))
        {
            MusicListPlay::playingIndex++;
            MusicPlay::status = -1;
            isPlay = false;
            begin = true;
            pauseMusicSlot();
        }
        else
        {
            MusicListPlay::playingIndex = 0;
            MusicPlay::status = -1;
            isPlay = false;
            begin = true;
            pauseMusicSlot();
        }
    }
    else if(singleflag == true)
    {
        MusicPlay::status = -1;
        isPlay = false;
        begin = true;
        pauseMusicSlot();
    }
    else
    {
        int nRandom=0;
        if(MusicListPlay::playUrlList->count() == 1)
        {
            MusicPlay::status = -1;
            isPlay = false;
            begin = true;
            pauseMusicSlot();
        }
        else
        {
            while(nRandom == MusicListPlay::playingIndex)
            {
                Q_ASSERT(0 < MusicListPlay::playUrlList->count());
                // 加入随机种子。种子是当前时间距离0点0分0秒的秒数。
                // 每次启动程序，只添加一次种子，以做到数字真正随机。
                static bool seedStatus;
                if (!seedStatus)
                {
                    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
                    seedStatus = true;
                }
                nRandom = qrand() % (MusicListPlay::playUrlList->count());
            }
            MusicListPlay::playingIndex = nRandom;
            MusicPlay::status = -1;
            isPlay = false;
            begin = true;
            pauseMusicSlot();
        }

    }

}

void PlayControl::playModeSlot()
{
    qDebug() << "运行playModeSlot";
    if(singleflag == false && circleflag == false)
    {
        circleflag = true;
        playModeBtn->setIcon(QIcon(":/img/playcircle.png"));
    }
    else if(singleflag == true && circleflag == false)
    {
        singleflag = false;
        playModeBtn->setIcon(QIcon(":/img/playrandom.png"));

    }
    else if(singleflag == false && circleflag == true)
    {
        circleflag = false;
        singleflag = true;
        playModeBtn->setIcon(QIcon(":/img/playsingle.png"));
    }

}

void PlayControl::slider_progress_clicked()
{
    MusicPlay::mediaPlayer->setPosition(musicSchedule->value());
}

void PlayControl::slider_progress_moved()
{
    //暂时停止计时器，在用户拖动过程中不修改slider的值
    playTime->stop();
    MusicPlay::mediaPlayer->setPosition(musicSchedule->value());
    musicTime->setText(MusicPlay::currentPos() + "/" + MusicPlay::currentTime);
}

void PlayControl::slider_progress_released()
{
    //用户释放滑块后，重启定时器
    playTime->start();
}


void PlayControl::volume_progress_clicked()
{
    MusicPlay::mediaPlayer->setVolume(volumeSchedule->value());
}

void PlayControl::volume_progress_moved()
{
    MusicPlay::mediaPlayer->setVolume(volumeSchedule->value());
}

void PlayControl::volume_progress_released()
{

}

void PlayControl::setControlsLayout()
{
    controlLayout->setMargin(10);
    controlLayout->setSpacing(20);//待调整数值
    controlLayout->addSpacing(10);
    controlLayout->addWidget(preAMusicBtn);
    controlLayout->addWidget(pauseMusicBtn);
    controlLayout->addWidget(nextAMusicBtn);

    musicInfoTimeLayout->setMargin(0);
    musicInfoTimeLayout->setSpacing(0);
    musicInfoTimeLayout->addWidget(musicInfo);
    musicInfoTimeLayout->addStretch();
    musicInfoTimeLayout->addWidget(musicTime);

    musicInfoScheduleLayout->setMargin(0);
    musicInfoScheduleLayout->setSpacing(5);//调整数值
    musicInfoScheduleLayout->addStretch();
    musicInfoScheduleLayout->addLayout(musicInfoTimeLayout);
    musicInfoScheduleLayout->addWidget(musicSchedule);
    musicInfoScheduleLayout->addStretch();

    volumeLayout->setMargin(0);
    volumeLayout->setSpacing(0);
    volumeLayout->addWidget(musicSound);
    volumeLayout->addWidget(volumeSchedule);

    otherActLayout->setMargin(10);
    otherActLayout->setSpacing(30);//调整数值
//    otherActLayout->addWidget(likeBtn);
    //otherActLayout->addWidget(downloadBtn);
    otherActLayout->addStretch();
    otherActLayout->addWidget(playModeBtn);
    otherActLayout->addLayout(volumeLayout);

//    otherActLayout->addWidget(soundEffect);
//    otherActLayout->addWidget(lyrics);
//    otherActLayout->addWidget(playMusicList);

    controlMainLayout->setMargin(0);
    controlMainLayout->setSpacing(20);//调整数值
    controlMainLayout->addLayout(controlLayout);
    controlMainLayout->addLayout(musicInfoScheduleLayout);
    controlMainLayout->addStretch(1);
    controlMainLayout->addLayout(otherActLayout);
    controlMainLayout->addStretch(2);
}

void PlayControl::setControlsForm()
{
    preAMusicBtn->setFixedSize(35,35);
    preAMusicBtn->setIconSize(QSize(15,15));
    preAMusicBtn->setIcon(QIcon(":/img/pre.png"));
    preAMusicBtn->setStyleSheet("border: 2px solid white;");
    preAMusicBtn->setCursor(QCursor(Qt::PointingHandCursor));

    pauseMusicBtn->setFixedSize(45,45);
    pauseMusicBtn->setIconSize(QSize(40,40));
    pauseMusicBtn->setIcon(QIcon(":/img/stop.png"));
    pauseMusicBtn->setStyleSheet("border-radius: 22px;border: 2px solid white;");
    pauseMusicBtn->setCursor(QCursor(Qt::PointingHandCursor));
    isPlay = false;

    nextAMusicBtn->setFixedSize(35,35);
    nextAMusicBtn->setIconSize(QSize(15,15));
    nextAMusicBtn->setIcon(QIcon(":/img/next.png"));
    nextAMusicBtn->setStyleSheet("border: 2px solid white;");
    nextAMusicBtn->setCursor(QCursor(Qt::PointingHandCursor));

    musicInfo->setText(tr("音乐播放器"));
    musicTime->setText(tr("00:00/00:00"));
    musicSchedule->setFixedWidth(365);
    musicSchedule->setCursor(QCursor(Qt::PointingHandCursor));

    likeBtn->setFixedSize(20,20);
    likeBtn->setIconSize(QSize(20,20));
    likeBtn->setIcon(QIcon(":/img/like1.png"));
    likeBtn->setCursor(QCursor(Qt::PointingHandCursor));
    isLike = false;

    downloadBtn->setFixedSize(20,20);
    downloadBtn->setIconSize(QSize(20,20));
    downloadBtn->setIcon(QIcon(":/img/download.png"));
    downloadBtn->setCursor(QCursor(Qt::PointingHandCursor));

    playModeBtn->setFixedSize(20,20);
    playModeBtn->setIconSize(QSize(20,20));
    playModeBtn->setIcon(QIcon(":/img/playrandom.png"));
    playModeBtn->setCursor(QCursor(Qt::PointingHandCursor));

    musicSound->setFixedSize(20,20);
    musicSound->setIconSize(QSize(20,20));
    musicSound->setIcon(QIcon(":/img/sound.png"));
    musicSound->setCursor(QCursor(Qt::PointingHandCursor));
    volumeSchedule->setFixedWidth(80);
    volumeSchedule->setRange(0, 120);
    volumeSchedule->setValue(40);
    MusicPlay::mediaPlayer->setVolume(40);
    volumeSchedule->setCursor(QCursor(Qt::PointingHandCursor));

    soundEffect->setFixedSize(50,20);
    soundEffect->setStyleSheet("border: 1px solid white; border-radius: 10px; color: white;");
    soundEffect->setText(tr("音 效"));
    soundEffect->setCursor(QCursor(Qt::PointingHandCursor));

    lyrics->setFixedSize(20, 20);
    lyrics->setText(tr("词"));
    lyrics->setStyleSheet("font: 16px; font-weight: bold; color: white; font-family: 黑体;");
    lyrics->setCursor(QCursor(Qt::PointingHandCursor));

    playMusicList->setFixedSize(20,20);
    playMusicList->setIconSize(QSize(20,20));
    playMusicList->setIcon(QIcon(":/img/cloud1.png"));
    playMusicList->setCursor(QCursor(Qt::PointingHandCursor));



    this->setWindowFlags(Qt::FramelessWindowHint);
}

void PlayControl::setControlsStyle()
{
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255,255,255,40));
    this->setPalette(palette);

    QFile file(QString(":/qss/playcontrol.qss"));
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
}

void PlayControl::connectSlot()
{
    connect(MusicPlay::mediaPlayer, &QMediaPlayer::durationChanged, this , [&](qint64 dur) {
        MusicPlay::playTime = dur;
        musicSchedule->setRange(0, (int)MusicPlay::playTime);
    });
    connect(likeBtn, &QPushButton::clicked, this, &PlayControl::likeBtnSlot);
    connect(pauseMusicBtn, &QPushButton::clicked, this, &PlayControl::pauseMusicSlot);
    connect(playTime, SIGNAL(timeout()), this, SLOT(playTimeSlot()));
    connect(MusicPlay::mediaPlayer, &QMediaPlayer::stateChanged, this, &PlayControl::playStateStop);

    connect(preAMusicBtn, &QPushButton::clicked, this, &PlayControl::playPreMusic);
    connect(nextAMusicBtn, &QPushButton::clicked, this, &PlayControl::playNextMusic);
    connect(playModeBtn, &QPushButton::clicked, this, &PlayControl::playModeSlot);

    connect(musicSchedule,&CustomSlider::costomSliderClicked,this,&PlayControl::slider_progress_clicked);
    connect(musicSchedule,&CustomSlider::sliderMoved,this,&PlayControl::slider_progress_moved);
    connect(musicSchedule,&CustomSlider::sliderReleased,this,&PlayControl::slider_progress_released);

    connect(volumeSchedule, &VolumeSlider::volumeSliderClicked, this, &PlayControl::volume_progress_clicked);
    connect(volumeSchedule, &VolumeSlider::sliderMoved, this, &PlayControl::volume_progress_moved);
    connect(volumeSchedule, &VolumeSlider::sliderReleased, this, &PlayControl::volume_progress_released);
    //connect(playModeBtn, &QPushButton::clicked, this, &PlayControl::playModeChange);
}
