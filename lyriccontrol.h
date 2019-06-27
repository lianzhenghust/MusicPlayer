#ifndef LYRICCONTROL_H
#define LYRICCONTROL_H


#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>

#include "musiclistplay.h"
#include "playcontrol.h"

class LyricLine
{
public:
    LyricLine(int time, QString text):time(time), text(text){}

    int time;
    QString text;
};


class LyricControl : public QWidget
{
    Q_OBJECT

public:
    LyricControl(QWidget *parent = nullptr);
    ~LyricControl();

    // 设置文字内容
    void setCurrentText(QString text);
    bool processContent(const QString &content);
    int getLineByPosition(const int &millisec, const int &startPos);
    void getLyricFile();
    void lyricPlay();
    QString allLyric;
    QString lyrics;
    QTimer *lyricTime;
    QPushButton *lyricBtn;

    QList<LyricLine*> mLines;
    bool mHasTimer;
    bool lyricShow;
    int lyricPos;
    bool lyricExit;


public slots:
    void lyricScroll();

private:
    QLabel *m_TopLabel;
    QLabel *m_CurrentLabel;

    QPropertyAnimation *m_TopPropertyAnimation;
    QPropertyAnimation *m_CurrentPropertyAnimation;

    QVBoxLayout *lyricLayout;

    void setControlsLayout();
    void setControlsForm();
    void connectSlot();
    void lyricUpdateSignal();

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:
    void lyricChanged();
    void lyricUpdate();


};


#endif // LYRICCONTROL_H
