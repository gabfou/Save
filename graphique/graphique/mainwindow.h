#pragma once

#include "ui_mainwindow.h"
#include "le.h"

#include "grouptree.h"

//class barref;
class tableshow;
class overview;

#include "project.h"

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
    int showmod = 0;
    QString namecurrent;
    QDockWidget *groupdock = NULL;
    QTabWidget *cw;
public slots:
    void updateproject();
    void screenshootcurrent();
private slots:
    void showproject();
    void sendproject();
    void addquestion();
    void addproject();
    void addproject2();
    void addperson();
    void addperson2();
    void addquestion2();
    void checksqlconexion();
    void openproject();
    void openproject2(QListWidgetItem *);
    void convert_to_xlsx();
    void addgroupe();
    void addgroupe2();
    void modechange(bool checked);
    void sendproject_ref();
    void refmodechange(bool checked);
    void changescope();
    void changescope2();
    void showbarchartref();
    void configproject();
private:
    Ui::MainWindow *ui;
    project *current;
    QWindow *addprojectwindow;
    QLineEdit *nametmp;
    QLineEdit *prenametmp;
    QLineEdit *emailtmp;
    tableshow *table = NULL;
    grouptree *groupboxtmp;
//    barref *d_chart;
    int currentgref = 0;
    QRadioButton *radiobuttontmp;
    overview *ov = NULL;

    void sendprojectauxi(QString str);
    void addock();
};

    