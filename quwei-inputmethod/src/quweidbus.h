#ifndef QUWEIDBUS_H
#define QUWEIDBUS_H

#include <fcitx-utils/dbus/message.h>
#include <fcitx-utils/dbus/objectvtable.h>

namespace fcitx {
class QuweiEngine;

class quweiDbus : public dbus::ObjectVTable<quweiDbus>
{
public:
    explicit quweiDbus(QuweiEngine *engine);
    void sendPreedit(const std::string &str);
    void sendUserInput(int num);
private:
    QuweiEngine *engine_;
    FCITX_OBJECT_VTABLE_METHOD(sendPreedit, "sendPreedit", "s", "");
    FCITX_OBJECT_VTABLE_SIGNAL(preEdit, "preEdit", "s")
    FCITX_OBJECT_VTABLE_SIGNAL(userInput, "userInput", "i")
};

};

#endif // QUWEIDBUS_H
