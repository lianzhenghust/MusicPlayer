#include "volumeslider.h"

void VolumeSlider::mousePressEvent(QMouseEvent *ev)
{
    QSlider::mousePressEvent(ev);

    double pos = ev->pos().x() / (double)width();
    setValue(pos * (maximum() - minimum()) + minimum());
    emit volumeSliderClicked();
}
