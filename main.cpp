#include "mainwindow.h"
#include <QApplication>
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

/*#ifdef Q_WS_WIN
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
#endif*/

//#ifdef Q_WS_MAC
void createConnection()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysql1.paris1.alwaysdata.com");
    db.setDatabaseName("etudemurano_project");
    db.setUserName("127008_johann");
    db.setPassword("t4x5akda");
	if (!db.open())
	{
        qDebug() << db.lastError().text() << "pb conection";
	}
	else
	{
		qDebug("conection sql set");
	}
}
//#endif

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

