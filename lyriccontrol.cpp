
#include <QResizeEvent>

#include "lyriccontrol.h"

LyricControl::LyricControl(QWidget *parent)
    :QWidget(parent)
{
    m_TopLabel = new QLabel(this);
    m_CurrentLabel = new QLabel(this);

    lyricTime = new QTimer;
    lyricLayout = new QVBoxLayout;
    lyricShow = false;
    lyricExit = true;
    lyricPos =0;
    //lyricBtn = new QPushButton;

    m_TopLabel->hide();
    m_CurrentLabel->hide();

    m_TopPropertyAnimation = new QPropertyAnimation(this);
    m_TopPropertyAnimation->setTargetObject(m_TopLabel);
    m_TopPropertyAnimation->setPropertyName("geometry");
    m_TopPropertyAnimation->setDuration(1000);//原来是700

    m_CurrentPropertyAnimation = new QPropertyAnimation(this);
    m_CurrentPropertyAnimation->setTargetObject(m_CurrentLabel);
    m_CurrentPropertyAnimation->setPropertyName("geometry");
    m_CurrentPropertyAnimation->setDuration(1000);

    this->setFixedSize(690,527);



    setControlsLayout();
    setControlsForm();
    //getLyricFile();
    //processContent(allLyric);
    //qDebug() << allLyric;
    //setCurrentText(mLines.at(0)->text);
    connectSlot();

}



LyricControl::~LyricControl()
{

}

void LyricControl::setCurrentText(QString text)
{
    if (m_CurrentLabel->text().isEmpty())
    {
        m_CurrentLabel->setGeometry(0, 0, this->width(), this->height());
        m_TopLabel->setText(text);
        m_CurrentLabel->setText(text);
        if (m_CurrentLabel->isHidden())
            m_CurrentLabel->show();
    }
    else
    {
        QString string = m_CurrentLabel->text();
        m_TopLabel->setText(string);
        m_CurrentLabel->setText(text);

        if (m_CurrentLabel->isHidden())
            m_CurrentLabel->show();
        if (m_TopLabel->isHidden())
            m_TopLabel->show();

        m_TopPropertyAnimation->stop();
        m_CurrentPropertyAnimation->stop();
        m_TopPropertyAnimation->start();
        m_CurrentPropertyAnimation->start();
    }
}

void LyricControl::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();
    int height = event->size().height();

    m_TopPropertyAnimation->setStartValue(QRect(0, 0, width, height));
    m_TopPropertyAnimation->setEndValue(QRect(0, -height, width, height));

    m_CurrentPropertyAnimation->setStartValue(QRect(0, height * 2, width, height));
    m_CurrentPropertyAnimation->setEndValue(QRect(0, 0, width, height));

    return QWidget::resizeEvent(event);
}

bool lyricTimeLessThan(const LyricLine* line1, const LyricLine* line2)
{
    return line1->time < line2->time;
}

void LyricControl::lyricUpdateSignal()
{

}
bool LyricControl::processContent(const QString &content)
{
    if (!mLines.isEmpty()) {
           qDeleteAll(mLines);
           mLines.clear();
           mHasTimer = false;
           emit lyricChanged();
       }

       const QRegExp rx("\\[(\\d+):(\\d+(\\.\\d+)?)\\]"); //用来查找时间标签的正则表达式

       // 步骤1
       int pos = rx.indexIn(content);
       if (pos == -1) {
           QStringList list = content.split('\n', QString::SkipEmptyParts);
           foreach (QString line, list)
               mLines.append(new LyricLine(0, line));

           mHasTimer = false;
       }
       else {
           int lastPos;
           QList<int> timeLabels;
           do {
               // 步骤2
               timeLabels << (rx.cap(1).toInt() * 60 + rx.cap(2).toDouble()) * 1000;
               lastPos = pos + rx.matchedLength();
               pos = rx.indexIn(content, lastPos);
               if (pos == -1) {
                   QString text = content.mid(lastPos).trimmed();
                   foreach (const int& time, timeLabels)
                       mLines.append(new LyricLine(time, text));
                   break;
               }
               // 步骤3
               QString text = content.mid(lastPos, pos - lastPos);
               if (!text.isEmpty()) {
                   foreach (const int& time, timeLabels)
                       mLines.append(new LyricLine(time, text.trimmed()));
                   timeLabels.clear();
               }
           }
           while (true);
           // 步骤4
           qStableSort(mLines.begin(), mLines.end(), lyricTimeLessThan);
           mHasTimer = true;
       }

       if (!mLines.isEmpty()) {
           emit lyricChanged();
           return true;
       }

       return false;
}

int LyricControl::getLineByPosition(const int &millisec, const int &startPos)
{
    if (!mHasTimer || mLines.isEmpty())
        return -1;

    int result = qBound(0, startPos, mLines.size());
    while (result < mLines.size()) {
        if (mLines.at(result)->time > millisec)
            break;

        result++;
    }
    return result - 1;
}

void LyricControl::getLyricFile()
{
    //qDebug() << "正在获取歌词"<< MusicListPlay::playingIndex << MusicListPlay::playUrlList->count();
    QString lrcPath = MusicListPlay::playUrlList->at(MusicListPlay::playingIndex);
    int index = lrcPath.lastIndexOf(".");
    lrcPath = lrcPath.left(index) + ".lrc";
    QFile lrcFile(lrcPath);
    if(!lrcFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_TopLabel->clear();
        m_CurrentLabel->clear();
        mLines.clear();
        m_TopLabel->setText(tr("未找到歌词"));
        lyricExit = false;
        return;
    }
    QTextStream in(&lrcFile);
    allLyric= in.readAll();
    //allLyric.setUnicode;
    lrcFile.close();
    //qDebug() << allLyric;
}

void LyricControl::lyricPlay()
{
    if(MusicPlay::mediaPlayer->state() != QMediaPlayer::PlayingState)
        return;
    getLyricFile();
    processContent(allLyric);
    lyricTime->start();
    if(!lyricExit)
    {
        lyricTime->stop();
        lyricExit = true;
    }





}

void LyricControl::lyricScroll()
{


    //qDebug() << mLines.count();
    //lyricTime->start();
    int pos = MusicPlay::mediaPlayer->position();
    if(getLineByPosition(pos, lyricPos) > 0 && getLineByPosition(pos, lyricPos) != lyricPos && lyricPos<mLines.count())
    {
        lyricPos = getLineByPosition(pos, lyricPos);
        setCurrentText(mLines.at(lyricPos)->text);
    }
}



void LyricControl::setControlsLayout()
{

    m_CurrentLabel->setAlignment(Qt::AlignCenter);
    m_TopLabel->setAlignment(Qt::AlignCenter);
    lyricLayout->setMargin(0);
    lyricLayout->setSpacing(0);
    //lyricLayout->addWidget(//lyricBtn);
    lyricLayout->addWidget(m_TopLabel);
    lyricLayout->addWidget(m_CurrentLabel);
    m_TopLabel->hide();
    m_CurrentLabel->hide();

    this->setLayout(lyricLayout);
}


void LyricControl::setControlsForm()
{
    this->setAutoFillBackground(true);
    //m_CurrentLabel = new QLabel("111");
    m_CurrentLabel->setStyleSheet("QLabel{\
                                  font-family: '黑体';\
                                  font-weight: bold;\
                                  font: 30px;\
                                  color: white;\
                          }");
    m_TopLabel->setStyleSheet("QLabel{\
                              font-family: '黑体';\
                              font-weight: bold;\
                              font: 30px;\
                              color: white;\
                      }");






    //lyricBtn->setFixedSize(690, 40);
    //lyricBtn->setStyleSheet(QString("QPushButton{color: white; font: 18px; font-family: 黑体;background: transparent;outLine: 0px;}"
                                    //"QPushButton:hover{color: #FFFEA1;}"));
    //lyricBtn->setText(tr("歌词"));



}

void LyricControl::connectSlot()
{
    connect(MusicPlay::mediaPlayer,&QMediaPlayer::stateChanged, this, &LyricControl::lyricPlay);
    connect(lyricTime, SIGNAL(timeout()), this, SLOT(lyricScroll()));
}


