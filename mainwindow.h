#pragma once

#include "ui_mainwindow.h"
#include "le.h"

//class barref;
class tableshow;
class overview;
class Alltree;
class Comparrefdo;
class grouptree;

#include "data/project.h"

//class grouptree;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void mailSent(QString status);
    int showmod = 1;
	QString namecurrent;
	QDockWidget *groupdock = NULL;
	QTabWidget *cw;
    project current;
    int ref = 0;
    int val = 0;
	tableshow *table = NULL;
    tableshow *tableg = NULL;
    tableshow *tablep = NULL;
	int currentgref = 0;
    int currentgqref = 0;
    int iterationmax = 2147483640;
    int iterationmin = 1;
    void updatetable();
    void sendprojectauxi(QString str, QList<person> listp, int type = 0);
public slots:
	void updateproject();
    void screenshootcurrent();
    void changescopeq2(QTreeWidgetItem *item);
    void Backroundchange();
    void miniterationchange(int min);
    void maxiterationchange(int max);
    void extractor();
    void Excellinfo();
private slots:
    //void showproject();
	void sendproject();
	void addquestion();
	void addproject();
	void addproject2();
	void addquestion2();
	void checksqlconexion();
	void openproject();
	void openproject2(QListWidgetItem *);
	void convert_to_xlsx();
//	void addgroupe();
//	void addgroupe2();
	void modechange(bool checked);
    void sendproject_ref();
	void refmodechange(bool checked);
    void changescope2(QTreeWidgetItem *item);
	void showbarchartref();
    void configproject();
    void valmodechange(bool checked);
    void globalrep(bool checked);
    void configsondage();
    void personrep(bool checked);
    void supproject();
    void supproject2(QListWidgetItem *item);
    void checkprojectname();
    void baserep(bool checked);
    void graphiquecrd(bool checked);
    void formcreator();
    void extract_brutesimple2();
    void extract_brutesimple();
    void suivirep();
private:
	Ui::MainWindow *ui;
	QWindow *addprojectwindow;
	QLineEdit *nametmp;
	QLineEdit *prenametmp;
	QLineEdit *emailtmp;
    QTimer *timertmp;
    QLabel *labeltmp;
    QPushButton *buttontmp;
    QListWidget *listWidgettmp;

    Alltree *alltreetmp = NULL;
    grouptree *groupboxtmp;
//	barref *d_chart;
	QRadioButton *radiobuttontmp;
	overview *ov = NULL;
    Comparrefdo *crd = NULL;
    QMenu *menu_affifchage;
    QMenu *menu_outil;
    QMenu *menu_projet;
    QMenu *menu_serveur;
    QMenu *menu_graphique;
    int error = 0;
    QAction *afficherglobalrep;
    QAction *afficherpers;
    QAction *afficherbasetable;
    QAction *affichergraphiquecompare;
    QAction *afficherref;
	void addock();

    void select_first_table();
    void initvar();
signals:
     void grefchange(int gref);
     void gqrefchange(int gqref);
     void valchanged(bool val);
     void refchanged(bool ref);
     void maxiterationchanged(int max);
     void miniterationchanged(int min);
};

	
