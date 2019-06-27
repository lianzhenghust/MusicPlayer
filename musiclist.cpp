#include "musiclist.h"

/**
 * @author: jingbo
 * @date: 2018/05/14
 * @desc: 音乐列表
 */

MusicList::MusicList(QWidget *parent) : QWidget(parent)
{
    playListBtn = new QPushButton;
    cloudBtn = new QPushButton;
    downloadBtn = new QPushButton;
    phoneBtn = new QPushButton;
    searchBtn = new QPushButton;
    vbtnPtr.push_back(cloudBtn);
    vbtnPtr.push_back(phoneBtn);
    vbtnPtr.push_back(searchBtn);
    vbtnPtr.push_back(playListBtn);
    vbtnPtr.push_back(downloadBtn);

    operNavLayout = new QHBoxLayout;
    operObjLayout = new QStackedLayout;
    musicListMainLayout = new QVBoxLayout;

    playPage = new MusicListPlay;

    this->setFixedSize(310,527);
    this->setLayout(musicListMainLayout);

    setControlsLayout();
    setControlsForm();
    setControlsStyle();
    connectSlot();
}

//---------------slot
void MusicList::musicListItemSwitch()
{
    QPushButton *senderBtn = qobject_cast<QPushButton *>(sender());
    for(int i = 0; i < 4; ++i){
        if(senderBtn == vbtnPtr[i]){
            operObjLayout->setCurrentIndex(i);
            QString url = ":/img/item1";
            url +=  (i + '0');
            url += ".png";
            senderBtn->setIcon(QIcon(url));
        }
        else{
            QString url = ":/img/item0";
            url +=  (i + '0');
            url += ".png";
            vbtnPtr[i]->setIcon(QIcon(url));
        }
    }
}

//---------------Function
void MusicList::setControlsLayout()
{


    operObjLayout->setMargin(0);
    operObjLayout->setSpacing(0);
    operObjLayout->addWidget(playPage);
    operObjLayout->setCurrentIndex(0);

    musicListMainLayout->setMargin(0);
    musicListMainLayout->setSpacing(0);
    musicListMainLayout->addLayout(operNavLayout);
    musicListMainLayout->addLayout(operObjLayout);


}

void MusicList::setControlsForm()
{
    playListBtn->setFixedSize(25,25);
    playListBtn->setIconSize(QSize(25,25));
    playListBtn->setIcon(QIcon(":/img/item03.png"));
    playListBtn->setCursor(QCursor(Qt::PointingHandCursor));

    cloudBtn->setFixedSize(25,25);
    cloudBtn->setIconSize(QSize(25,25));
    cloudBtn->setIcon(QIcon(":/img/item10.png"));
    cloudBtn->setCursor(QCursor(Qt::PointingHandCursor));

    downloadBtn->setFixedSize(25,25);
    downloadBtn->setIconSize(QSize(25,25));
    downloadBtn->setIcon(QIcon(":/img/item04.png"));
    downloadBtn->setCursor(QCursor(Qt::PointingHandCursor));

    phoneBtn->setFixedSize(25,25);
    phoneBtn->setIconSize(QSize(25,25));
    phoneBtn->setIcon(QIcon(":/img/item01.png"));
    phoneBtn->setCursor(QCursor(Qt::PointingHandCursor));

    searchBtn->setFixedSize(25,25);
    searchBtn->setIconSize(QSize(25,25));
    searchBtn->setIcon(QIcon(":/img/item02.png"));
    searchBtn->setCursor(QCursor(Qt::PointingHandCursor));

    this->setWindowFlags(Qt::FramelessWindowHint);
}

void MusicList::setControlsStyle()
{
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255,255,255,20));
    this->setPalette(palette);

    QFile file(QString(":/qss/musicList.qss"));
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
}

void MusicList::connectSlot()
{
    connect(cloudBtn, &QPushButton::clicked, this, &MusicList::musicListItemSwitch);
    connect(phoneBtn, &QPushButton::clicked, this, &MusicList::musicListItemSwitch);
    connect(searchBtn, &QPushButton::clicked, this, &MusicList::musicListItemSwitch);
    connect(playListBtn, &QPushButton::clicked, this, &MusicList::musicListItemSwitch);
}
