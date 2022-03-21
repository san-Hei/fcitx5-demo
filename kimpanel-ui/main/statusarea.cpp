#include "statusarea.h"
#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QDebug>

StatusArea::StatusArea(Kimpanel *panel, QWidget *parent)
    : QWidget(parent)
    , m_panel(panel)
{
    QPushButton *btn1 = new QPushButton("拼");
    QPushButton *btn2 = new QPushButton();
    QPushButton *btn3 = new QPushButton();
    QPushButton *btn4 = new QPushButton();

    btn1->setFixedSize(30,30);
    btn2->setFixedSize(30,30);
    btn3->setFixedSize(30,30);
    btn4->setFixedSize(30,30);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addWidget(btn4);

    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::X11BypassWindowManagerHint);
    setFocusPolicy(Qt::NoFocus);

    QDesktopWidget* widget = QApplication::desktop();
    setGeometry(widget->width() - 200, widget->height() - 80, 130, 35);

    connect(m_panel, &Kimpanel::propertiesChanged, this, [=](QString key, QString label){
        qDebug() << key;
        if(key == "/Fcitx/im") {
            return ;
        }
        if(key == "/Fcitx/chttrans") {
            if(label == "简体中文") {
                btn2->setText("简");
            } else {
                btn2->setText("繁");
            }
        } else if(key == "/Fcitx/punctuation") {
            if(label == "全角标点") {
                btn3->setIcon(QIcon(":/kimpanel/prefix/punc-active.png"));
            } else {
                btn3->setIcon(QIcon(":/kimpanel/prefix/punc-inactive.png"));
            }
        } else if(key == "/Fcitx/fullwidth") {
            if(label == "全角字符") {
                btn4->setIcon(QIcon(":/kimpanel/prefix/fullwidth-active.png"));
            } else {
                btn4->setIcon(QIcon(":/kimpanel/prefix/fullwidth-inactive.png"));
            }
        }
    });
}

void StatusArea::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_isPressed = true;
}

void StatusArea::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_isPressed = false;
}

void StatusArea::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->x(), event->y());
}
