#include "mainwindow.h"
#include <QApplication>
#include "../../server/server/server.h"
#include "le.h"

bool g_ref = 0;

void warning(QString error)
{
    qDebug() << error;
}

string	replacespace(string name)
{
    int i = -1;

    while (name[++i])
    {
        if (name[i] == ' ')
            name[i] = '_';
    }
    return (name);
}

void createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("mysql-johann.alwaysdata.net");
    db.setDatabaseName("johann_project");
    db.setUserName("johann");
    db.setPassword("t4x5akda");
    if (!db.open())
    {
        qDebug() << db.lastError().text();
    }
    else
    {
        qDebug("conection sql set");
    }
}

int main(int argc, char *argv[])
{
    //send_mail();
    srand(time(NULL));
    QApplication a(argc, argv);
    createConnection();
    MainWindow w;
    w.show();
    return a.exec();
}
