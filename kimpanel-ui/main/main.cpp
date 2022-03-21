
#include <QApplication>

#include "inputPanel.h"
#include "statusarea.h"

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    Kimpanel *panel =  new Kimpanel;
    InputPanel edit(panel);
    StatusArea area(panel);
    area.show();
    return a.exec();
}
