#ifndef PREEDIT_H
#define PREEDIT_H

#include <QObject>
#include "kimpanel.h"
class QLabel;

class InputPanel : public QObject
{
    Q_OBJECT
public:
    explicit InputPanel(Kimpanel *panel, QObject *parent = nullptr);

signals:
    void showinfo();
public slots:
    void showPreEditText(QString str);
    void hidePreEditText(int index);
private:
    QString splitString(const QString &str);
private:
    Kimpanel *kimpanel_;
    static int m_connectionIndex;
    QLabel *label_;
};

#endif // PREEDIT_H
