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
    void sup_retour_chariot();
    void noms_to_description();
    void showtableau_brut();
    void newtemplateq();
    void addtemplateq();
    void newtemplatep();
    void addtemplatep();
private:
    MainWindow *m;
	QTabWidget *tab;
	void configeneral();
	void configgroupe();
	QString name;
    project *p;
};

#endif // MENUCONFIGPROJECT_H
