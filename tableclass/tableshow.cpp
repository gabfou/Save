#include "tableshow.h"
#include "data/project.h"
#include "data/question.h"
#include "data/group.h"
#include "data/person.h"
#include "mainwindow.h"
#include "headertableitem.h"
#include "itemtable.h"
#include "grouptree.h"

void tableshow::preinit()
{
	this->verticalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    this->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
	menuhead = new QMenu(this->horizontalHeader());

	connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(saveqpoint(QPoint)));
	connect(this->horizontalHeader(), SIGNAL(activated(QModelIndex)), this, SLOT(saveqpoint()));

	// Action
	QAction *tmp = new QAction(QString("Modifier"), this->verticalHeader());
	this->verticalHeader()->addAction(tmp);
	connect(tmp, SIGNAL(triggered()), this, SLOT(modifvheader()));

	tmp = new QAction(QString("Modifier"), this->horizontalHeader());
	this->horizontalHeader()->addAction(tmp);
	connect(tmp, SIGNAL(triggered()), this, SLOT(modifhheader()));

	tmp = new QAction(QString("Supprimer"), this->verticalHeader());
	this->verticalHeader()->addAction(tmp);
	connect(tmp, SIGNAL(triggered()), this, SLOT(supvheader()));

	tmp = new QAction(QString("Supprimer"), this->horizontalHeader());
	this->horizontalHeader()->addAction(tmp);
	connect(tmp, SIGNAL(triggered()), this, SLOT(suphheader()));

	connect(m, SIGNAL(gqrefchange(int)), this, SLOT(selectq(int)));
	connect(m, SIGNAL(grefchange(int)), this, SLOT(selectp(int)));
	connect(m, SIGNAL(valchanged(bool)), this, SLOT(updateall()));
	connect(m, SIGNAL(refchanged(bool)), this, SLOT(updateall()));
    connect(m, SIGNAL(miniterationchanged(int)), this, SLOT(updateall()));
    connect(m, SIGNAL(maxiterationchanged(int)), this, SLOT(updateall()));
    if (showmode == 2)
	{
		connect(m, SIGNAL(grefchange(int)), this, SLOT(updateall()));
	}
	//connect(this->horizontalHeader(), SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)), this, SLOT(select()));
}

void tableshow::prepostinit()
{
	this->setSortingEnabled(false);
}

void tableshow::postinit()
{
    this->resizeColumnsToContents();
    this->resizeRowsToContents();
	this->setSortingEnabled(true);
}


tableshow::tableshow (MainWindow *m, project *p, int showmode) : p(p), showmode(showmode), m(m)
{
	this->preinit();
}

tableshow::tableshow(project *p, MainWindow *mainp, int showmode) : showmode(showmode), m(mainp)
{
	this->preinit();
	reinit(p, mainp);
}

void tableshow::sethorizontalheader(QList<headertableitem*> &list, int nc)
{
	int i = 0;
	QList<headertableitem*>::iterator tmp;

	while (i < nc)
		 this->setHorizontalHeaderItem(i++, new headertableitem(p, ""));
	tmp = list.begin();
	while (tmp != list.end())
	{
		this->setHorizontalHeaderItem(i++, *tmp);
		tmp++;
	}
}

void tableshow::setverticalheader(QList<headertableitem*> &listh, int nc)
{
	int i = nc;
	QList<headertableitem*>::iterator tmp;

	tmp = listh.begin();
	while (tmp != listh.end())
	{
		this->setHorizontalHeaderItem(i++, *tmp);
		tmp++;
	}
}

tableshow::tableshow(MainWindow *m, QList<headertableitem*> &listv, QList<headertableitem*> &listh) : m(m)
{
	this->preinit();
	reinit(listv, listh);
}

void tableshow::reinit()
{

	qDebug() << "new tableshow 1";
	if (p->listp.empty() || p->listquestion.empty())
	{
		qDebug() << "listp ou lisquestion vide dans reinit 1";
		return ;
	}
	this->clear();
	this->setRowCount(p->getNbperson() + 2 + p->getNbgroup());
	this->setColumnCount(p->getNbquestion() + 2 /* 2*/);
	this->k = 0;
	this->populate();
}

void tableshow::reinit(QList<headertableitem*> &listv, QList<headertableitem*> &listh)
{
    k = (showmode == 1) ? 1 : 0;
	if (showmode == 2)
		k+= p->getNbqgeneration();
	else
		k+= p->getNbpgeneration();

	qDebug() << "new tableshow 2";
	if (p->listp.empty() || p->listquestion.empty())
	{
		qDebug() << "listp ou lisquestion vide dans reinit 2";
		return ;
	}
	this->clear();
	this->setRowCount(listh.size() + 3);
	this->setColumnCount(listv.size() + 3);
	this->populate();
	setverticalheader(listv, k);
	sethorizontalheader(listh, k);
	this->updateall();
}

//void tableshow::reinit

void tableshow::reinit(project *p, MainWindow *mainp)
{
	QElapsedTimer timerdebug;
	this->p = p;
	int i;

    k = (showmode == 1) ? 1 : 0;
	if (showmode == 2)
		k+= p->getNbqgeneration();
	else
		k+= p->getNbpgeneration();

	qDebug() << "new tableshow 3";
	if (p->listp.empty() || p->listquestion.empty())
	{
		qDebug() << "listp ou lisquestion vide dans reinit 3";
		return ;
	}
	this->clear();
	timerdebug.start();
	if (showmode == 0)
	{
		this->setRowCount(p->getNbperson());
		this->setColumnCount(p->getNbquestion() + k/* 2*/);
	}
	else if (showmode == 2)
	{
		this->setRowCount(p->getNbqgroup());
		this->setColumnCount(p->getNbquestion() + k/* 2*/);
	}
	else if (showmode == 1)
	{
		this->setRowCount(p->getNbperson());
		this->setColumnCount(p->getNbquestion() + k/* 2*/);
	}
	qDebug() << "set size time " << timerdebug.elapsed() <<"ms";
	i = 0;
	timerdebug.start();
	this->populate();
	qDebug() << "populate time " << timerdebug.elapsed() <<"ms";
	timerdebug.start();
	if (showmode == 0)
	{
		this->sethorizontalheader(mainp);
		this->setverticalheader(p->listgroup, 0);
	}
	if (showmode == 1)
	{
		this->sethorizontalheader(mainp);
		this->setverticalheader(p->listp);
	}
	else if (showmode == 2)
	{
		this->sethorizontalheader(mainp);
		this->setverticalheader(p->listqgroup, 0);
	}
	qDebug() << "set header total time " << timerdebug.elapsed() <<"ms";
	this->updateall();
}

void	tableshow::sethorizontalheader(MainWindow *mainp)
{
	Q_UNUSED(mainp);
	QElapsedTimer timerdebug;
	timerdebug.start();
	QList<question> listqchild = p->questiongroupqchildnotopti(0);
	QList<question>::const_iterator tmp2;
	vector<question>::const_iterator tmp3;
	vector<group>::const_iterator tmp;
	int i = k;

	if (showmode == 0 || showmode == 1)
	{
		tmp2 = listqchild.begin();
		if (showmode == 0)
		{
			while (--k > -1)
				this->setHorizontalHeaderItem(k, new headertableitem(p, "Sous groupes"));
		}
		else
		{
            if (--k > -1)
                this->setHorizontalHeaderItem(k, new headertableitem(p, "Noms"));
			while (--k > -1)
				this->setHorizontalHeaderItem(k, new headertableitem(p, "Sous groupes"));
		}
		k = i;
		qDebug() << "horizontal header 1 time 1 " << timerdebug.elapsed() << "ms";
		while (tmp2 != listqchild.end())
		{
            QString questioninfo = tmp2->name;
            if (p->listqgroup[tmp2->qgroupid].gquestion)
                questioninfo = p->listqgroup[tmp2->qgroupid].name + " : " + questioninfo;
            if (tmp2->type == 2)
            {
                questioninfo += "\n";
                QStringList::const_iterator j = tmp2->liststr.begin();
                while(j != tmp2->liststr.end())
                {
                    if (j != tmp2->liststr.begin())
                        questioninfo += " | ";
                    questioninfo += *j;
                    j++;
                }
                questioninfo += " | NA";
            }
            this->setHorizontalHeaderItem(i++, new headertableitem(p, questioninfo, *tmp2, "%"));
			//this->setHorizontalHeaderItem(i++, new QTableWidgetItem(("temps a " + tmp2->name + " reel").c_str()));
			tmp2++;
		}
	}
	else if (showmode == 2)
	{
		tmp3 = p->listquestion.begin();
		while (--k > -1)
			this->setHorizontalHeaderItem(k, new headertableitem(p, "Sous groupes"));
		k = i;
		QStringList checklist;
		while (tmp3 != p->listquestion.end())
		{
			if (tmp3->id > -1 && checklist.contains(tmp3->name) == 0)
			{
				checklist << tmp3->name;
				this->setHorizontalHeaderItem(i++, new headertableitem(p, (tmp3->name), tmp3->name, "%"));
			}
			tmp3++;
		}
	}
	qDebug() << "horizontal header 1 time " << timerdebug.elapsed() << "ms";
}

void	tableshow::setverticalheader(vector<question> &q, int id)
{
    QElapsedTimer timerdebug;
    timerdebug.start();
    int i = -1;
    QList<int>::const_iterator listpg;
    QList<int> listint;
    group * gtmp = NULL;
    //listint << id;

    p->groupqchild(id, listint);
    listpg = listint.begin();
    while (listpg != listint.end())
    {
        QList<question> listq37 = p->listqgroup[*listpg].getListq();
        QList<question>::iterator listqtmp = listq37.begin();
        while (listqtmp != listq37.end())
        {
            gtmp = &(p->listqgroup[((*listqtmp).qgroupid)]);
            if (gtmp == NULL || gtmp->type == -1)
            {
                qDebug() << "setvertical question group fail idgroup=" << *listpg;
                continue ;
            }
            if (p->listp.empty() == true)
                return ;
            int i37 = (gtmp->getGeneration() == -1) ? 0 : gtmp->getGeneration();
            while (gtmp->getGeneration() > 0)
			{
				this->setItem(i, gtmp->getGeneration() - 1, new QTableWidgetItem(gtmp->getName()));
				gtmp = &(p->listqgroup[gtmp->getParentid()]);
			}
			this->setVerticalHeaderItem(i, new headertableitem(p, gtmp->getName(), *listqtmp));
			this->setItem(i++, i37, new QTableWidgetItem(listqtmp->name));
			listqtmp++;
		}
		listpg++;
		//gbox->verticalHeaderItem(i)->setBackgroundColor(gtmp->getColor());
	}
	qDebug() << "vertical header 1 time " << timerdebug.elapsed() << "ms";
}

void	tableshow::setverticalheader(vector<group> &g, int id)
{
	//qDebug() << "ok ";
	int i = 0;
	QList<int>::const_iterator listpg;
	QList<int> listint;
	QElapsedTimer timerdebug;

	timerdebug.start();
	if (g[0].type == 0)
		p->groupchild(id, listint);
	else
		p->groupqchild(id, listint);
	if (p->listp.empty() == true)
	{
		qDebug() << "aucune personne erreur";
		return ;
	}
	listpg = listint.begin();
	while (listpg != listint.end())
	{
		//qDebug() << "listpg" << *listpg << listint.size();
		group * gtmp = &(g[(*listpg)]);

		while (gtmp->getGeneration() > 0)
		{
			this->setItem(i, gtmp->getGeneration() - 1, new QTableWidgetItem(gtmp->getName()));
			//gbox->item(*i, gtmp->getGeneration() - 1)->setBackgroundColor(Qt::red);
			gtmp = &(g[gtmp->getParentid()]);
		}
		this->setVerticalHeaderItem(i++, new headertableitem(p, gtmp->getName(), (g[*listpg])));
		listpg++;
		//gbox->verticalHeaderItem(i)->setBackgroundColor(gtmp->getColor());
	}
	qDebug() << "vertical header 2 time " << timerdebug.elapsed() << "ms";
}

void	tableshow::setverticalheader(vector<person> &p)
{
	int i = 0;
	vector<person>::const_iterator listpg;
//	QList<int> listint;
	QElapsedTimer timerdebug;

	timerdebug.start();
	if (this->p->listp.empty() == true)
	{
		qDebug() << "aucune personne erreur";
		return ;
	}
	listpg = p.begin();
	while (listpg != p.end())
	{
//		qDebug() << "listpg" << *listpg << listint.size();
		if (listpg->id == -1)
		{
			listpg++;
			continue;
		}
		group * gtmp = &(this->p->listgroup[listpg->groupid]);
		if (gtmp->getGeneration() > -1)
			this->setItem(i, gtmp->getGeneration(), new QTableWidgetItem(listpg->name));
		else
		{
			this->setVerticalHeaderItem(i++, new headertableitem(this->p, listpg->name, (*listpg)));
			listpg++;
			continue ;
		}
		while (gtmp->getGeneration() > 0)
		{
			this->setItem(i, gtmp->getGeneration() - 1, new QTableWidgetItem(gtmp->getName()));
			gtmp = &(this->p->listgroup[gtmp->getParentid()]);
		}
		this->setVerticalHeaderItem(i++, new headertableitem(this->p, gtmp->getName(), (*listpg)));
		listpg++;
		//gbox->verticalHeaderItem(i)->setBackgroundColor(gtmp->getColor());
	}
	qDebug() << "vertical header 3 time " << timerdebug.elapsed() << "ms";
}


void	tableshow::populate()
{
	int h = -1;
	int w;

	while (++h < this->rowCount())
	{
		w = -1;
		while (++w < this->columnCount())
			this->setItem(h, w, new itemtable("test h:" + QString::number(h) + " w:" + QString::number(w), p));
	}
}

void	tableshow::selectq(int gqref)
{
	select(m->currentgref, gqref);
}

void	tableshow::selectp(int gref)
{
	select(gref, m->currentgqref);
}

void	tableshow::select(int gref, int gqref)
{
	QList<int> listint;
	QList<int> listqint;

    p->groupchild(gref, listint);
    p->groupqchild(gqref, listqint);
	headertableitem *tmp;

	QElapsedTimer timerdebug;
	timerdebug.start();
	this->prepostinit();
	int h = -1;
	while (++h < this->rowCount())
	{
		tmp = (dynamic_cast<headertableitem*>(this->verticalHeaderItem(h)));
		if (tmp && tmp->is_in(this->p->listgroup , this->p->listqgroup, listint, listqint))
			this->showRow(h);
		else
			this->hideRow(h);
	}

	h = -1;

	while (++h < this->columnCount())
	{
		tmp = (dynamic_cast<headertableitem*>(this->horizontalHeaderItem(h)));
		if (tmp && tmp->is_in(this->p->listgroup, this->p->listqgroup, listint, listqint))
			this->showColumn(h);
		else
			this->hideColumn(h);
	}
	this->postinit();
	qDebug() << "select time " << timerdebug.elapsed() << "ms";
}

void	tableshow::clearheader()
{
	int h = -1;
	int w;

	while (++h < this->rowCount())
		delete (this->verticalHeaderItem(h));
	w = -1;
	while (++w < this->columnCount())
		delete (this->horizontalHeaderItem(h));
}

void	tableshow::showtable(int id, int qid)
{
	this->select(id, qid);
	qDebug() << "showtableshow";
}

void	tableshow::saveqpoint()
{
	lastqpoint = QCursor::pos();
}

void	tableshow::saveqpoint(QPoint qpoint)
{
	qDebug() << "dsad";
	lastqpoint = qpoint;
	menuhead->popup(qpoint);
}

void	tableshow::suphheader()
{
	this->removeColumn(this->columnAt(lastqpoint.x()));
}

void	tableshow::supvheader()
{
	this->removeRow(this->rowAt(lastqpoint.y()));
}

void	tableshow::modifhheader()
{
	headertableitem *headcast = dynamic_cast<headertableitem*>(this->horizontalHeaderItem(this->columnAt(lastqpoint.x())));
	QWidget *provisoire = new QWidget();
	QVBoxLayout *lprovisoire = new QVBoxLayout(provisoire);

	if (headcast)
	{
		QTabWidget *tab = new QTabWidget();
		grouptree *groupboxp = new grouptree(m, p->listgroup, 2);
		tab->addTab(groupboxp, "Personne");
		connect(groupboxp, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), headcast, SLOT(changearg(QTreeWidgetItem *)));
		grouptree *groupboxq = new grouptree(m, p->listqgroup, 2);
		tab->addTab(groupboxq, "Question");
		connect(groupboxq, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), headcast, SLOT(changearg(QTreeWidgetItem *)));
		lprovisoire->addWidget(tab);
		qDebug() << "tableshow::modifitem head";
	}
	else
	{
		qDebug() << "tableshow::modifitem fail";
	}
	provisoire->setLayout(lprovisoire);
	provisoire->show();
}

void	tableshow::modifvheader()
{
	headertableitem *headcast = dynamic_cast<headertableitem*>(this->verticalHeaderItem(this->rowAt(lastqpoint.y())));
	QWidget *provisoire = new QWidget();
	QVBoxLayout *lprovisoire = new QVBoxLayout(provisoire);

	if (headcast)
	{
		QTabWidget *tab = new QTabWidget();
		grouptree *groupboxp = new grouptree(m, p->listgroup, 2);
		tab->addTab(groupboxp, "Personne");
		connect(groupboxp, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), headcast, SLOT(changearg(QTreeWidgetItem *)));
		grouptree *groupboxq = new grouptree(m, p->listgroup, 2);
		tab->addTab(groupboxq, "Question");
		connect(groupboxq, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), headcast, SLOT(changearg(QTreeWidgetItem *)));
		lprovisoire->addWidget(tab);
		this->updateall(); // opti
		qDebug() << "tableshow::modifitem head";
	}
	else
	{
		qDebug() << "tableshow::modifitem fail";
	}
	provisoire->setLayout(lprovisoire);
	provisoire->show();
}

void	tableshow::updateall()
{
	int h = -1;
	int w;
	QElapsedTimer timerdebug;

	qDebug() << "updateall";
	timerdebug.start();
    this->prepostinit();
	while (++h < this->rowCount() + 1)
	{
		w = - 1;
		while (++w < this->columnCount() + 1)
		{
			itemtable *tmp = dynamic_cast<itemtable*>(this->item(h, w));
			if (tmp)
				tmp->update();
		}
	}
	qDebug() << "updateall time " << timerdebug.elapsed() <<"ms";
    this->postinit();
}
