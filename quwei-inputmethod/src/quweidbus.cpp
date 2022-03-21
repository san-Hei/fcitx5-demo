#include "quweidbus.h"
#include "dbus_public.h"
#include "quwei.h"

namespace fcitx {
quweiDbus::quweiDbus(QuweiEngine *engine)
    : engine_(engine)
{
    auto dbus = engine->dbus();
    if (!dbus) {
        return;
    }
    auto bus = dbus->call<IDBusModule::bus>();
    bus->addObjectVTable("/quwei", "org.fcitx.Fcitx.quwei", *this);
}

void quweiDbus::sendPreedit(const std::string &str)
{
    preEdit(str);
    std::cout << "sendPreedit: " << str << std::endl;
}

void quweiDbus::sendUserInput(int num)
{
    userInput(num);
    std::cout << "sendUserInput: " << num << std::endl;
}

}
