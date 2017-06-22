#include "mainwindow.h"
#include <QApplication>
#include "le.h"

void warning(QString error)
{
    QLabel *warning = new QLabel(error);
    warning->show();
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
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysql-etudemurano.alwaysdata.net");
    db.setDatabaseName("etudemurano_project");
    db.setUserName("127008_johann");
    db.setPassword("t4x5akda");
    if (!db.open())
        warning("imposible de se connecter à la base de donnée" + db.lastError().text());
    else
        qDebug("conection sql set");
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
