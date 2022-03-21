#ifndef STATUSAREA_H
#define STATUSAREA_H

#include <QWidget>
#include "kimpanel.h"

class StatusArea : public QWidget
{
    Q_OBJECT
public:
    explicit StatusArea(Kimpanel *panel, QWidget *parent = nullptr);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:

private:
    bool m_isPressed {false};
    Kimpanel *m_panel;
};

#endif // STATUSAREA_H
