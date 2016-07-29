#include "headertableitem.h"

QString headertableitem::getFormule() const{return formule;}
void headertableitem::setFormule(const QString &value){formule = value;}

headertableitem::headertableitem(QString str, QString form, int id) : QTableWidgetItem(str), formule(form), id(id)
{

}

headertableitem::headertableitem(QString str, group arg, QString form)
    : QTableWidgetItem(str), type(1), argg(arg), id(arg.id), formule(form)
{
}

headertableitem::headertableitem(QString str, person arg, QString form)
    : QTableWidgetItem(str), type(3), argp(arg), id(arg.id), formule(form)
{
}

headertableitem::headertableitem(QString str, question arg, QString form)
    : QTableWidgetItem(str), type(2), argq(arg), id(arg.id), formule(form)
{
}
