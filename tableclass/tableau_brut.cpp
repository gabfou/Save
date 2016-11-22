#include "tableau_brut.h"
#include "data/project.h"
#include "data/fact.h"
#include "data/person.h"
#include "data/question.h"
#include "data/group.h"

tableau_brut::tableau_brut(project *p)
{
    this->setRowCount(p->getNbfactnref() + p->getNbfactref() + 3);
    this->setColumnCount(30 + p->getNbpgeneration() + p->listquestion.size());
	this->setheader(p);
    this->populate(p);
    this->setWindowModality(Qt::ApplicationModal);
}

void tableau_brut::setheader(project *p)
{
    int i = -1;
    int j = -1;
    vector<question>::iterator tmp3 = p->listquestion.begin();

    this->setHorizontalHeaderItem(++i, new QTableWidgetItem("jour"));
    this->setHorizontalHeaderItem(++i, new QTableWidgetItem("groupe"));
    this->setHorizontalHeaderItem(++i, new QTableWidgetItem("noms prenoms"));
    this->setHorizontalHeaderItem(++i, new QTableWidgetItem("email"));
    checklist.clear();
    tmp3 = p->listquestion.begin();
    while (tmp3 != p->listquestion.end())
    {
        if (tmp3->id == -1)
        {
            tmp3++;
            continue ;
        }
        QString namereal = tmp3->getnamereal(p);
        if (checklist.contains(namereal) == 0)
        {
            checklistreal << QVector<int>();
            checklist << namereal;
            this->setHorizontalHeaderItem(++i, new QTableWidgetItem(namereal));
            j++;
        }
        if (j > -1)
            checklistreal[j] << tmp3->id;
        tmp3++;
    }
    this->setHorizontalHeaderItem(++i, new QTableWidgetItem("date"));
}

void tableau_brut::setrow(person &pe, project *p, int k, int it)
{
	group * gtmp = &(p->listgroup[pe.groupid]);
    int i = -1;

    QString group;
    int j = 0;
    while (gtmp->getGeneration() > -1)
	{
        group = gtmp->name + ((j == 0) ? "" : ": ") + group;
        gtmp = &(p->listgroup[gtmp->getParentid()]);
        j++;
    }
    this->setItem(k, ++i, new QTableWidgetItem(QString::number(it)));
    this->setItem(k, ++i, new QTableWidgetItem(group));
    this->setItem(k, ++i, new QTableWidgetItem(pe.name));
	this->setItem(k, ++i, new QTableWidgetItem(pe.email));
    QVector<QVector<int>>::iterator tmp = checklistreal.begin();
    while(tmp != checklistreal.end())
    {
        this->setItem(k, ++i, new QTableWidgetItem(pe.getrep(*tmp, it, p)));
        tmp++;
    }
//	this->setItem(k, ++i, new QTableWidgetItem(f.getDate().c_str()));
}

void tableau_brut::populate(project *p)
{
    qDebug() << "populate";
	vector<person>::iterator ip = p->listp.begin();
    int it;
	int k = -1;

	while(ip != p->listp.end())
	{
        if (ip->id == -1)
        {
            ip++;
            continue ;
        }
        it = -1;
        while(++it < ip->iteration)
            setrow(*ip, p, ++k, it);
		ip++;
	}
    qDebug() << "finpopulate";
}
