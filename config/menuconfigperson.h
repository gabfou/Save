#ifndef MENUCONFIGPERSON_H
#define MENUCONFIGPERSON_H

#include "le.h"

// onglet personne du menu de config

class project;
class grouptree;
class MainWindow;

class menuconfigperson : public QWidget
{
	project *p;
    MainWindow *m;
	QDockWidget *groupdock;
	grouptree *groupbox;
public:
    menuconfigperson(project *p, MainWindow *m);
};

#endif // MENUCONFIGPERSON_H
