#include "tableau_brut.h"
#include "data/project.h"
#include "data/fact.h"
#include "data/person.h"
#include "data/question.h"
#include "data/group.h"

tableau_brut::tableau_brut(project *p)
{
    this->setRowCount(p->getNbfactnref() + p->getNbfactref() + 3);
	this->setColumnCount(30 + p->getNbpgeneration() + p->getNbqgeneration());
	this->setheader(p);
    this->populate(p);
    this->setWindowModality(Qt::ApplicationModal);

}

void tableau_brut::setheader(project *p)
{
    int i = -1;
    int j = -2;

    while(++j < p->getNbpgeneration())
		this->setHorizontalHeaderItem(++i, new QTableWidgetItem("groupe"));
	this->setHorizontalHeaderItem(++i, new QTableWidgetItem("noms prenoms"));
	this->setHorizontalHeaderItem(++i, new QTableWidgetItem("email"));
	this->setHorizontalHeaderItem(++i, new QTableWidgetItem("question"));
	this->setHorizontalHeaderItem(++i, new QTableWidgetItem("reponse"));
	this->setHorizontalHeaderItem(++i, new QTableWidgetItem("date"));
    j = -2;
    while(++j < p->getNbqgeneration())
		this->setHorizontalHeaderItem(++i, new QTableWidgetItem("groupe"));
}

void tableau_brut::setrow(person &pe, fact &f, project *p, int k)
{
    question *q = &(p->listquestion[f.idquestion]);
	group * gtmp = &(p->listgroup[pe.groupid]);
    int i;
    if (p->getNbpgeneration() == -1)
        i = -1;
    else
        i = -1 + p->getNbpgeneration();

    if (q->id == -1)
    {
        qDebug() << "fail tableaux_brut setrow";
        return ;
    }
	while (gtmp->getGeneration() > 0)
	{
		this->setItem(k, gtmp->getGeneration(), new QTableWidgetItem(gtmp->name));
		gtmp = &(p->listgroup[gtmp->getParentid()]);
    }
	this->setItem(k, ++i, new QTableWidgetItem(pe.name));
	this->setItem(k, ++i, new QTableWidgetItem(pe.email));
    this->setItem(k, ++i, new QTableWidgetItem(q->sujet));
    if (f.getTimestr().isEmpty())
        this->setItem(k, ++i, new QTableWidgetItem(QString::number(f.getTime())));
    else
        this->setItem(k, ++i, new QTableWidgetItem(f.getTimestr()));
	this->setItem(k, ++i, new QTableWidgetItem(f.getDate().c_str()));

    gtmp = &(p->listqgroup[q->group]);
	while (gtmp->getGeneration() > 0)
	{
		this->setItem(k, ++i, new QTableWidgetItem(gtmp->name));
		gtmp = &(p->listqgroup[gtmp->getParentid()]);
	}
}

void tableau_brut::populate(project *p)
{
	vector<person>::iterator ip = p->listp.begin();
    QList<fact> f;
    QList<fact>::iterator i;
	int k = -1;

	while(ip != p->listp.end())
	{
        if (ip->id == -1)
        {
            ip++;
            continue ;
        }
        f = ip->getFlist();
        i = f.begin();
        while(i != f.end())
		{
			setrow(*ip, *i, p, ++k);
			i++;
		}
        f = ip->getFlist();
        i = f.begin();
        while(i != f.end())
		{
			setrow(*ip, *i, p, ++k);
			i++;
		}
		ip++;
	}
}
