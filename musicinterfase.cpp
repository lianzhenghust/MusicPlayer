#include "musicinterfase.h"
#include "ui_musicinterfase.h"

/**
 * @author: jingbo
 * @date: 2018/05/14
 * @desc: 音乐主界面框架
 */

MusicInterfase::MusicInterfase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicInterfase)
{
    ui->setupUi(this);
    this->setFixedSize(1000,645);

    //子部件创建
    musicNav = new Navigate;
    resultPreBtn = musicNav->getResultPreBtn();
    skinBtn = musicNav->getSkinBtn();

    miniBtn = musicNav->getMiniBtn();
    closeBtn = musicNav->getCloseBtn();
    customizeSkinBtn = musicNav->getCustomizeSkinBtn();

    musicList = new MusicList;
    musicPlayControl = new PlayControl;


    lyricControl = new LyricControl;

    musicCenterLayout = new QHBoxLayout;
    musicMainLayout = new QVBoxLayout;
    musicNavAndWinControl = new QHBoxLayout;
    setLayout(musicMainLayout);

    themePathList <<":/img/theme1"<<":/img/theme2"<<":/img/defaultheme";


    windowControl = new QHBoxLayout;

    QPalette pal;
    QString imgname = ":/img/defaultheme";
    QPixmap pixmap(imgname);
    pixmap = pixmap.scaled(QSize(1000, 645));
    pal.setBrush(QPalette::Background, QBrush(pixmap));
//    QPainter painter(this);
//    painter.drawPixmap(0,0,this->width(), this->height(), pixmap);
    this->setAutoFillBackground(true);
    this->setPalette(pal);


    musicPlay = new MusicPlay;  //只为生成静态，不使用

//    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);//任务栏使程序最小化
//    setWindowFlags(Qt::FramelessWindowHint);//无边框
    mask = new QWidget;
    setControlsLayout();
    setControlsForm();
    connectSlot();
}

MusicInterfase::~MusicInterfase()
{
    delete ui;
}


void MusicInterfase::showMask()
{
//    mask->setGeometry(0, 0, mask->width(), mask->height());
//    mask->show();
    QPalette pal;
    if(index == themePathList.count())
        index=0;

    QString imgname = themePathList.at(index++);
    QPixmap pixmap(imgname);
    pixmap = pixmap.scaled(QSize(1000, 645));
    pal.setBrush(QPalette::Background, QBrush(pixmap));
//    QPainter painter(this);
//    painter.drawPixmap(0,0,this->width(), this->height(), pixmap);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void MusicInterfase::hideMask()
{
    mask->hide();
}

void MusicInterfase::miniWin()
{
    this->showMinimized();
}

void MusicInterfase::closeWin()
{
    this->close();
}

void MusicInterfase::customizeSkin()
{
    QPalette pal;

    QString imgname = QFileDialog::getOpenFileName(NULL,"添加自定义皮肤",".","*.jpg");
    themePathList.append(imgname);
    QPixmap pixmap(imgname);
    pixmap = pixmap.scaled(QSize(1000, 645));
    pal.setBrush(QPalette::Background, QBrush(pixmap));
//    QPainter painter(this);
//    painter.drawPixmap(0,0,this->width(), this->height(), pixmap);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}


void MusicInterfase::setControlsLayout()
{
    musicCenterLayout->setMargin(0);
    musicCenterLayout->setSpacing(0);
    musicCenterLayout->addWidget(musicList);
    musicCenterLayout->addWidget(lyricControl);

    musicMainLayout->setMargin(0);
    musicMainLayout->setSpacing(0);
    musicMainLayout->addWidget(musicNav);
    musicMainLayout->addLayout(musicCenterLayout);
    musicMainLayout->addWidget(musicPlayControl);
}

void MusicInterfase::setControlsForm()
{
    //--skin
    mask->setFixedSize(1000,645);
    mask->setStyleSheet("QWidget{background-color:rgba(0,0,0,0.4);}");
    mask->setWindowFlags(Qt::FramelessWindowHint);
    mask->setParent(this);
    mask->hide();


    this->setWindowFlags(Qt::FramelessWindowHint);
}

void MusicInterfase::connectSlot()
{
    //--Nav
    connect(skinBtn, &QPushButton::clicked, this, &MusicInterfase::showMask);
    connect(miniBtn, &QPushButton::clicked, this, &MusicInterfase::miniWin);
    connect(closeBtn, &QPushButton::clicked, this, &MusicInterfase::closeWin);
    connect(customizeSkinBtn, &QPushButton::clicked, this, &MusicInterfase::customizeSkin);

}



//---------------------------------protected

void MusicInterfase::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        pressFlag = true;
        beginPos = event->pos();
    }
    QWidget::mousePressEvent(event);
}

void MusicInterfase::mouseMoveEvent(QMouseEvent *event)
{
    if(pressFlag){
        QPoint relPos(QCursor::pos() - beginPos);
        move(relPos);
    }
    QWidget::mouseMoveEvent(event);
}

void MusicInterfase::mouseReleaseEvent(QMouseEvent *event)
{
    pressFlag = false;
    QWidget::mouseReleaseEvent(event);
}
