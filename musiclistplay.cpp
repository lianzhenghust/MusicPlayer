#include "playcontrol.h"

/**
 * @author: jingbo
 * @date: 2018/05/16
 * @desc: 音乐列表-播放列表
 */


MusicListPlay::MusicListPlay(QWidget *parent) : QWidget(parent)
{

    defaultListBtn = new QPushButton;
    MusicListPlay::item = nullptr;
    MusicListPlay::defaultPlayList = new QListView;


    //playcontrol = new PlayControl;

    musicListPlayMainLayout = new QVBoxLayout;


    setControlsLayout();
    setControlsForm();
    setControlsStyle();
    connectSlot();

}

QStringList *MusicListPlay::playUrlList = new QStringList;
int MusicListPlay::playingIndex = 0;
QStandardItemModel *MusicListPlay::model = new QStandardItemModel();
bool MusicListPlay::autoPlay = true;
bool MusicListPlay::playAnother = false;


void MusicListPlay::isShowList()
{
    QPushButton *senderBtn = qobject_cast<QPushButton *>(sender());
    if(senderBtn == defaultListBtn){
        if(isShowDefault){
            defaultPlayList->hide();
            isShowDefault = false;
            defaultListBtn->setIcon(QIcon(":/img/hideList.png"));
        }
        else{
            defaultPlayList->show();
            defaultPlayList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            isShowDefault = true;
            defaultListBtn->setIcon(QIcon(":/img/showList.png"));
        }
    }
}

void MusicListPlay::showContextMenu(QPoint )
{
//    if(!((defaultPlayList->selectionModel()->selectedIndexes()).empty()))
//        {

            //qDebug()<<"show_contextmenu1";
            QMenu *cmenu = new QMenu(MusicListPlay::defaultPlayList);
            MusicListPlay::nowPlay = cmenu->addAction("播放");
            addMusic = cmenu->addAction("添加歌曲");
            deleteMusic = cmenu->addAction("删除歌曲");
            changeOrder = cmenu->addAction("下一首播放");
            clearList = cmenu->addAction("清空列表");

            cmenu->setStyleSheet(
                        " QMenu {\
                                        background-color: white; /* sets background of the menu 设置整个菜单区域的背景色，我用的是白色：white*/\
                                        border: 1px solid white;/*整个菜单区域的边框粗细、样式、颜色*/\
                                    }\
                                    QMenu::item {\
                                        /* sets background of menu item. set this to something non-transparent\
                                            if you want menu color and menu item color to be different */\
                                        background-color: transparent;\
                                        padding:8px 16px;/*设置菜单项文字上下和左右的内边距，效果就是菜单中的条目左右上下有了间隔*/\
                                        margin:0px 0px;/*设置菜单项的外边距*/\
                                        border-bottom:1px solid #DBDBDB;/*为菜单项之间添加横线间隔*/\
                                    }\
                                    QMenu::item:selected { /* when user selects item using mouse or keyboard */\
                                                           color:black;\
                                                           background-color:rgb(236, 242, 245);/*这一句是设置菜单项鼠标经过选中的样式*/\
                                    }\
                                   QMenu::item:pressed {\
                                       color:black;\
                                       background-color:rgb(233, 227, 227);\
                                   }"

                            );


            connect(addMusic, SIGNAL(triggered(bool)), this, SLOT(addMusicSlot()));
            connect(deleteMusic, SIGNAL(triggered(bool)), this, SLOT(deleteMusicSlot()));
            connect(changeOrder, SIGNAL(triggered(bool)), this, SLOT(changeOrderSlot()));
            connect(nowPlay,SIGNAL(triggered(bool)), this, SLOT(nowPlaySlot()));
            connect(clearList,SIGNAL(triggered(bool)), this, SLOT(clearListSlot()));
            cmenu->exec(QCursor::pos());//在当前鼠标位置显示

            //cmenu->exec(pos)是在viewport显示

            //把选中的清除
            MusicListPlay::defaultPlayList->selectionModel()->clear();
//        }
}

void MusicListPlay::nowPlaySlot()
{

//    qDebug() << MusicListPlay::playingIndex;
    if(MusicListPlay::playUrlList->empty())
        return;
    MusicListPlay::playingIndex = MusicListPlay::defaultPlayList->currentIndex().row();
//    qDebug() << "修改后的索引值" << MusicListPlay::playingIndex;
    MusicListPlay::playAnother = true;
    //PlayControcl::isPlay = false;
//    begin = true;
//    pauseMusicSlot();
    //MusicPlay::setPlayUrl(playUrlList->at(playingIndex));
    //emit MusicPlay::mediaPlayer->stateChanged(QMediaPlayer::StoppedState);
//    if(MusicPlay::mediaPlayer->state() == QMediaPlayer::PlayingState)
      MusicPlay::mediaPlayer->stop();
//    else
//    {
//        MusicPlay::setPlayUrl(playUrlList->at(playingIndex));
//        MusicPlay::play();
//    }
}



void MusicListPlay::addMusicSlot()
{
    QStringList filePath = QFileDialog::getOpenFileNames(NULL,"添加歌曲",".","*.mp3");
    int j=0;
    while(j<filePath.count())
    {
        bool flag = true;
        int index = filePath.at(j).lastIndexOf('/');
        int index1 = filePath.at(j).lastIndexOf(".");
        QString fileName = filePath.at(j).mid(index + 1, index1-index-1);
        QString infoPre = "";
        infoPre.resize(5, QChar(32));
        MusicListPlay::item = new QStandardItem(infoPre + fileName);
        int rows = MusicListPlay::model->rowCount();
        for(int i=0; i<rows; i++)
        {
            if(MusicListPlay::playUrlList->at(i) == filePath.at(j))
            {
                flag = false;
            }
        }
        if(flag == false)
        {
            flag = true;
            j++;
            continue;
        }
        MusicListPlay::playUrlList->append(filePath.at(j));
        MusicListPlay::model->appendRow(MusicListPlay::item);
        j++;
    }

}

void MusicListPlay::deleteMusicSlot()
{
    int row = MusicListPlay::defaultPlayList->currentIndex().row();
    //qDebug() << row;
    MusicListPlay::model->removeRow(row);
    MusicListPlay::playUrlList->removeAt(row);
}

void MusicListPlay::changeOrderSlot()
{
    if(!MusicListPlay::playUrlList->isEmpty())
    {
        int row = MusicListPlay::defaultPlayList->currentIndex().row();
        QString filePath = MusicListPlay::playUrlList->at(row);
        QString playingFilePath = MusicListPlay::playUrlList->at(MusicListPlay::playingIndex);
        MusicListPlay::playUrlList->removeAt(row);
        for(int i=0; i<MusicListPlay::playUrlList->count(); i++)
        {
            if(MusicListPlay::playUrlList->at(i) == playingFilePath)
                MusicListPlay::playingIndex = i;
        }
        MusicListPlay::playUrlList->insert(MusicListPlay::playingIndex+1, filePath);

    }

}

void MusicListPlay::clearListSlot()
{
    MusicListPlay::model->clear();
    MusicListPlay::playUrlList->clear();
}
void MusicListPlay::setControlsLayout()
{
    musicListPlayMainLayout->setMargin(0);
    musicListPlayMainLayout->setSpacing(0);
    musicListPlayMainLayout->addWidget(defaultListBtn);
    musicListPlayMainLayout->addWidget(defaultPlayList);
//    musicListPlayMainLayout->addWidget(recentListBtn);
//    musicListPlayMainLayout->addWidget(recentPlayList);
    musicListPlayMainLayout->addStretch();
    setLayout(musicListPlayMainLayout);
}

void MusicListPlay::setControlsForm()
{
    defaultListBtn->setFixedSize(310,40);
    defaultListBtn->setIconSize(QSize(16,16));
    defaultListBtn->setIcon(QIcon(":/img/hideList.png"));
    defaultListBtn->setText(tr("默认列表"));
    defaultListBtn->setStyleSheet("border-bottom: 1px solid rgba(255, 255, 255, 10%)");
    isShowDefault = false;





    defaultPlayList->setModel(model);
    defaultPlayList->setContextMenuPolicy(Qt::CustomContextMenu);
    defaultPlayList->setFixedHeight(512);
    defaultPlayList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    defaultPlayList->hide();
    defaultPlayList->setStyleSheet("border-bottom: 1px solid rgba(255, 255, 255, 10%)");
    defaultPlayList->setSpacing(0);



    this->setWindowFlags(Qt::FramelessWindowHint);
}

void MusicListPlay::setControlsStyle()
{
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255,255,255,0));
    this->setPalette(palette);

    QFile file(QString(":/qss/musicListPlay.qss"));
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
}

void MusicListPlay::connectSlot()
{
    connect(defaultListBtn, &QPushButton::clicked, this, &MusicListPlay::isShowList);
    connect(MusicListPlay::defaultPlayList, SIGNAL(customContextMenuRequested(QPoint)),
                this, SLOT(showContextMenu(QPoint)));

}
