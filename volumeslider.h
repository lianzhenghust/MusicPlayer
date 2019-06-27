#ifndef COLUMNSLIDER_H
#define COLUMNSLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include <QCoreApplication>

class VolumeSlider : public QSlider
{
    Q_OBJECT
public:
    VolumeSlider(QWidget *parent = 0) : QSlider(parent)
    {
    }
protected:
    void mousePressEvent(QMouseEvent *ev);//重写QSlider的mousePressEvent事件
signals:
    void volumeSliderClicked();//自定义的鼠标单击信号，用于捕获并处理
};

#endif // COLUMNSLIDER_H
