#ifndef NAVIGATE_H
#define NAVIGATE_H

/**
 * @author: jingbo
 * @date: 2018/05/14
 * @desc: 导航栏
 */

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFile>
#include <QDebug>
#include <QGraphicsDropShadowEffect>


#include "musicplay.h"

class Navigate : public QWidget
{
    Q_OBJECT
public:
    explicit Navigate(QWidget *parent = 0);
    QPushButton *getResultPreBtn();
    QPushButton *getSkinBtn();
    QPushButton *getSkinDialogCloseBtn();
    QPushButton *getMiniBtn();
    QPushButton *getCloseBtn();
    QPushButton *getCustomizeSkinBtn();

private:
    QPushButton *navIcon;
    QPushButton *loginBtn;
    QLabel *cut;
    QPushButton *registBtn;
    QPushButton *resultBtn;
    QPushButton *updateBtn;
    QLineEdit *findEdit;
    QPushButton *skinBtn;
    QPushButton *miniBtn;
    QPushButton *closeBtn;
    QPushButton *customizeSkinBtn;

    //----------Layout
    QHBoxLayout *loginRegLayout;
    QHBoxLayout *navMainLayout;

    //----------Function
    void setControlsLayout();
    void setControlsForm();
    void setControlsStyle();


};

#endif // NAVIGATE_H
