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

bool headertableitem::is_in(vector<group> &g, QList<int> listint)
{
    QList<int>::iterator tmp;

    if (type == 1)
    {
        if (g[0].type != this->argg.type)
            return (1);
        if (listint.contains(id))
            return (1);
        return (0);
    }
    if (type == 3)
    {
        if (g[0].type != 0)
            return (1);
        else
        {
            tmp = listint.begin();
            while (tmp != listint.end())
            {
                if (g[(*tmp)].contain(this->argp))
                    return (1);
                tmp++;
            }
            return (0);
        }
    }
    if (type == 2)
    {
        if (g[0].type != 1)
            return (1);
        else
        {
            tmp = listint.begin();
            while (tmp != listint.end())
            {
                if (g[*tmp].contain(this->argq))
                    return (1);
                tmp++;
            }
            return (0);
        }
    }
}
