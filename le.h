#ifndef LE_H
#define LE_H

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
#include <QTWidgets/QMessageBox>
//#include <QtGui/QMessageBox>
#include <QDialog>
#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <fstream>
#include <QComboBox>
//#include <random>
#include <time.h>
#include <QTreeWidget>
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "xlsxworksheet.h"
#include <QColor>
#include <QSpinBox>
//#include <qwt_plot_renderer.h>
//#include <qwt_plot_canvas.h>
//#include <qwt_plot_multi_barchart.h>
//#include <qwt_column_symbol.h>
//#include <qwt_plot_histogram.h>
//#include <qwt_plot_layout.h>
//#include <qwt_legend.h>
//#include <qwt_scale_draw.h>
//#include <qwt_plot.h>
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

# define BUFF_SIZE 4096
# define PATH "../../server/server/TextFile1.txt"

class question;
class group;
class project;

typedef struct  s_groupref
{
	QString		 name;
	QList<QString>  list;
	int			 total = 0;
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
t_groupref syntheselistgroup(QList<t_groupref> listg, int nbcolumn);
void gen_random(char *s, const int len);
void sendmail(QString mail, QString body);
int addgroup(QString nameproject, QString name, int groupparent, int type, project *p);
void	supgroup(QString nameproject, int id, vector<group> &g);
void	supquest(QString nameproject, int id);
int	addquestion(project *p, QString name, int groupid, QString type, int note, QString description, int qgroupid);
//global
extern bool g_ref;
#endif // LE_H
