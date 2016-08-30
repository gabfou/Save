#ifndef MENUCONFIGPERSON_H
#define MENUCONFIGPERSON_H

#include "le.h"

class project;
class grouptree;
class MainWindow;

class menuconfigperson : public QWidget
{
	project *p;
	QDockWidget *groupdock;
	grouptree *groupbox;
public:
    menuconfigperson(project *p, MainWindow *m);
};

#endif // MENUCONFIGPERSON_H
