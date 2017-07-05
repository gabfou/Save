#ifndef LE_H
#define LE_H

#include <QDateTimeEdit>
#include <QPlainTextEdit>
#include <QtSql>
#include <QDockWidget>
#include <Qstring>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QMessageBox>
#include <QTableWidget>
#include <QtNetwork>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QMainWindow>
#include <QScrollArea>
#include <QTableWidget>
#include <QSqlQuery>
#include <QSqlerror>
#include <QString>
#include <QPushButton>
#include <QCheckBox>
#include <QTWidgets/QMessageBox>
#include <stdlib.h>
#include <QDialog>
#include <iostream>
#include <QSlider>
#include <string>
#include <list>
#include <cstdlib>
#include <fstream>
#include <QCalendarWidget>
#include <QComboBox>
#include <QListWidget>
#include <time.h>
#include <QTreeWidget>
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "xlsxworksheet.h"
#include <QColor>
#include <QProgressDialog>
#include <QSpinBox>
#include <QDrag>
#include <QMimeData>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <QFileDialog>
#include <QCryptographicHash>
#include <QRadioButton>
#include <QTabWidget>
#include <QHeaderView>
#include <QScreen>
#include <QByteArray>
#include <QImageWriter>
#include <Qlabel>
#include <QMainWindow>
#include <QWindow>
#include <QPainter>
#include <vector>
#include "sql/sqloperation.h"

class question;
class group;
class project;
class MainWindow;

typedef struct  s_groupref
{
    QString       name;
    QList<float>  list;
    float			 total = 0;
}			   t_groupref;

using namespace std;

void ft_error(string error);
void ft_exit();
int send_mail(void);
string	replacespace(string name);
void createConnection();
void tab_to_fichier(const QString name, const QTableWidget *table);
QXlsx::Document tab_to_xlsx(const QTableWidget &table, QXlsx::Document & xlsx);
QString indextocase(int x, int y);
void warning(QString error);
t_groupref syntheselistgroup(QList<t_groupref> listg);
void gen_random(char *s, const int len);
void sendmail(QString mail, QString body, int type = 0, int it = 0);
QList<int> QStrltoQil(QStringList &src);
void createquestiontemplate(MainWindow *m, project *p);
void recupquestiontemplate(QString name, project *p);
void createpersonnetemplate(MainWindow *m, project *p);
void recuppersonnetemplate(QString name, project *p);
QString strallgroupfilsforsql(int groupid, QString project_name);
QList<int> recupallgroupfils(int groupid, QString project_name);
void warning(QString error);

namespace sqlo
{
    int     addgroup(project *p, QString nameproject, QString name, int groupparent, int type, QString description, int gquestion, int id = -1);
    void	supgroup(QString nameproject, int id, vector<group> &g);
    void	supquest(project *p, QString nameproject, int id);
    int     addquestion(project *p, QString name, int groupid, QString type, int note, QString description, int qgroupid, int typef, int ref_only, QString splitchar, int val, bool global, int id = -1);
    void    sqlupdate(QString tablename, QString colname, QString str, int id);
    void	supperson(project *p, QString nameproject, int id);
    int     addperson(project *p, QString firstname, QString lastname, QString email, int groupid, int refbool, int questionbool, int jour, int id = -1);
    void    sqlupdateintroindex(QString tablename, QString s);
    void    sqlupdateintroref(QString tablename, QString s);
    void    sqlupdateintroreel(QString tablename, QString s);

}

#endif // LE_H
