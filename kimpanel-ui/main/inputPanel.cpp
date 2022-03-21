#include "inputPanel.h"
#include <QDBusInterface>
#include <QDebug>
#include <QLabel>

int InputPanel::m_connectionIndex = 0;

InputPanel::InputPanel(Kimpanel *panel, QObject *parent)
    : QObject(parent)
    , kimpanel_(panel)
    , label_(new QLabel())
{
    QDBusConnection *conn = new QDBusConnection(QDBusConnection::connectToBus(QDBusConnection::SessionBus, QStringLiteral("org.fcitx.Fcitx5")));
    conn->connect(QString(),
                         QString(),
                         QStringLiteral("org.fcitx.Fcitx.quwei"),
                         QStringLiteral("preEdit"),
                         this,
                         SIGNAL(showPreEditText(QString)));

    conn->connect(QString(),
                         QString(),
                         QStringLiteral("org.fcitx.Fcitx.quwei"),
                         QStringLiteral("userInput"),
                         this,
                         SIGNAL(hidePreEditText(int)));
}

void InputPanel::showPreEditText(QString str)
{

    label_->setWindowFlag(Qt::FramelessWindowHint);
    label_->setWindowFlag(Qt::X11BypassWindowManagerHint);
    label_->setFocusPolicy(Qt::NoFocus);
    label_->setText(splitString(str));
    label_->setGeometry(kimpanel_->spotRect().x(), kimpanel_->spotRect().y() + 20, 300, 30);
    label_->show();
    kimpanel_->spotRect();
    qDebug() << "showPreEditText: " << str;
}

void InputPanel::hidePreEditText(int index)
{
    label_->hide();
}

QString InputPanel::splitString(const QString &str)
{
    QString preedit;
    for(int i = 0; i < str.size(); i++) {
        preedit += QString(i + 1);
        preedit += ": ";
        preedit += str.at(i);
        preedit += " ";
    }
    return preedit;
}



