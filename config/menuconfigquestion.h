#ifndef MENUCONFIGQUESTION_H
#define MENUCONFIGQUESTION_H

#include "le.h"

// cette classe represente l'onglet "question" dans le menu configuration

class project;
class grouptree;
class MainWindow;

class menuconfigquestion : public QWidget
{
	project *p;
	QDockWidget *groupdock;
	grouptree *groupbox;
public:
	menuconfigquestion(project *p, MainWindow *m);
};

#endif // MENUCONFIGQUESTION_H
