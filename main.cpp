#include "loginterface.h"

#include <QApplication>

#include<QFile>
#include<QDataStream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LogInterface log;
    log.application_ptr = &a;
    log.show();

    return a.exec();

}
