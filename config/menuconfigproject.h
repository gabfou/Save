#ifndef MENUCONFIGPROJECT_H
#define MENUCONFIGPROJECT_H

#include "le.h"

class project;
class MainWindow;

class menuconfigproject : public QTabWidget
{
    Q_OBJECT
public:
    menuconfigproject(QString name, project *p, MainWindow *m);
private slots:
    void showsql();
private:
	QTabWidget *tab;
	void configeneral();
	void configgroupe();
	QString name;
};

#endif // MENUCONFIGPROJECT_H
