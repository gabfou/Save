#ifndef MENUCONFIGPROJECT_H
#define MENUCONFIGPROJECT_H

#include "le.h"

class project;
class MainWindow;

class menuconfigproject : public QTabWidget
{
public:
	menuconfigproject(QString name, project *p, MainWindow *m);
private:
	QTabWidget *tab;
	void configeneral();
	void configgroupe();
	QString name;
};

#endif // MENUCONFIGPROJECT_H
