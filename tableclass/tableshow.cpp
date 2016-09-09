#include "tableshow.h"
#include "data/project.h"
#include "data/question.h"
#include "data/group.h"
#include "data/person.h"
#include "mainwindow.h"
#include "headertableitem.h"
#include "itemtable.h"

void tableshow::preinit()
{
    menuhead = new QMenu(this->horizontalHeader());
    this->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->verticalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    this->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setSortingEnabled(true);

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

    connect(this->horizontalHeader(), SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)), this, SLOT(select()));
/*  this->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    this->verticalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    this->verticalHeader()->addAction(modifier);
    connect(this->horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(clicked()));
    connect(this->verticalHeader(), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(clicked()));*/
}

tableshow::tableshow (MainWindow *m, project *p, int ref, int *showmode) : p(p), showmode(showmode), m(m)
{
    this->preinit();
    this->setverticalheader(p->listquestion, 0);
    this->setHorizontalHeaderItem(0, new headertableitem(p, "Sous groupe", p->listgroup[ref], "#ALL(%)"));
    this->updateall();
}

tableshow::tableshow (MainWindow *m, project *p, int *showmode) : p(p), showmode(showmode), m(m)
{
    this->preinit();
}

tableshow::tableshow(project *p, MainWindow *mainp, int *showmode) : showmode(showmode), m(mainp)
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

//    int i = -1;
//    group * gtmp = NULL;

//    tmp = listh.begin();
//    while (tmp != listh.end())
//    {
//        list<question> listq37 = p->listqgroup[(*tmp)->id].getListq();
//        list<question>::iterator listqtmp = listq37.begin();
//        while (listqtmp != listq37.end())
//        {
//            gtmp = &(p->listqgroup[((*listqtmp).qgroupid)]);
//            if (gtmp == NULL || gtmp->type == -1)
//            {
//                qDebug() << "setvertical question group fail idgroup=" << (*tmp)->id;
//                continue ;
//            }
//            if (p->listp.empty() == true)
//                return ;
//            int i37 = (gtmp->getGeneration() == -1) ? 0 : gtmp->getGeneration();
//            while (gtmp->getGeneration() > 0)
//            {
//                this->setItem(i, gtmp->getGeneration() - 1, new QTableWidgetItem(gtmp->getName().c_str()));
//                gtmp = &(p->listqgroup[gtmp->getParentid()]);
//            }
//            this->setVerticalHeaderItem(i++, new headertableitem(gtmp->getName().c_str(), *listqtmp));
//            this->setItem(i, i37, new QTableWidgetItem(listqtmp->name.c_str()));
//            listqtmp++;
//        }
//        tmp++;
//        //gbox->verticalHeaderItem(i)->setBackgroundColor(gtmp->getColor());
//    }
}

tableshow::tableshow(MainWindow *m, QList<headertableitem*> &listv, QList<headertableitem*> &listh) : m(m)
{
    this->preinit();
    reinit(listv, listh);
}

void tableshow::reinit()
{

    qDebug() << "new tableshow";
    if (p->listp.empty() || p->listquestion.empty())
    {
        qDebug() << "listp ou lisquestion vide dans reinit 1";
        return ;
    }
    this->clear();
    this->setRowCount(p->getNbperson() * 2 + p->getNbgroup() * 2);
    this->setColumnCount(p->getNbquestion() + 2 /* 2*/);
    this->k = 0;
    this->populate();
}

void tableshow::reinit(QList<headertableitem*> &listv, QList<headertableitem*> &listh)
{
    int i = ((*showmode) == 0) ? 0 : 1;
    i+= p->getNbgeneration();

    qDebug() << "new tableshow";
    if (p->listp.empty() || p->listquestion.empty())
    {
        qDebug() << "listp ou lisquestion vide dans reinit 2";
        return ;
    }
    this->clear();
    this->setRowCount(p->getNbperson() * 2 + p->getNbgroup() * 2);
    this->setColumnCount(p->getNbquestion() + i /* 2*/);
    this->k = i;
    this->populate();
    setverticalheader(listv, i);
    sethorizontalheader(listh, i);
    this->updateall();
}

void tableshow::reinit(project * p, MainWindow *mainp)
{
    this->p = p;
    int i = (mainp->showmod == 0) ? 0 : 1;
    i+= p->getNbgeneration();

    qDebug() << "new tableshow";
    if (p->listp.empty() || p->listquestion.empty())
    {
        qDebug() << "listp ou lisquestion vide dans reinit 3";
        return ;
    }
    this->clear();
    this->setRowCount(p->getNbperson() * 2 + p->getNbgroup() * 2);
    this->setColumnCount(p->getNbquestion() + i /* 2*/);
    this->k = i;
    i = 0;
    this->populate();
    if (mainp->showmod == 0)
    {
        this->sethorizontalheader(mainp);
        this->setverticalheader(p->listgroup, 0);
    }
    else if (mainp->showmod == 2)
    {
        this->sethorizontalheader(mainp);
        this->setverticalheader(p->listquestion, 0);
    }
    this->updateall();
}

void	tableshow::sethorizontalheader(MainWindow *mainp)
{
    vector<question> listqchild = p->questiongroupqchildnotopti(0);
    vector<question>::const_iterator tmp2;
    vector<group>::const_iterator tmp;
    int i = (mainp->showmod == 1) ? 1 : 0;
    i+= p->getNbgeneration();

    if (mainp->showmod == 0 || mainp->showmod == 1)
    {
        tmp2 = listqchild.begin();
        if (mainp->showmod == 0)
        {
            while (--k > -1)
                this->setHorizontalHeaderItem(k, new headertableitem(p, "Sous groupes"));
        }
        else
        {
            this->setHorizontalHeaderItem(--k, new headertableitem(p, "Noms"));
            while (--k > -1)
                this->setHorizontalHeaderItem(k, new headertableitem(p, "Sous groupes"));
        }
        //k = i;
        while (tmp2 != listqchild.end())
        {
            this->setHorizontalHeaderItem(i++, new headertableitem(p, ("Moyenne " + tmp2->name + ""), *tmp2, "%"));
            //this->setHorizontalHeaderItem(i++, new QTableWidgetItem(("temps a " + tmp2->name + " reel").c_str()));
            tmp2++;
        }
    }
    else if (mainp->showmod == 2)
    {
        tmp = p->listgroup.begin();
        if (mainp->showmod == 0)
        {
            while (--k > -1)
                this->setHorizontalHeaderItem(k, new headertableitem(p, "Sous groupes"));
        }
        else
        {
            this->setHorizontalHeaderItem(--k, new headertableitem(p, "Noms"));
            while (--k > -1)
                this->setHorizontalHeaderItem(k, new headertableitem(p, "Sous groupes"));
        }
        //k = i;
        while (tmp != p->listgroup.end())
        {
            this->setHorizontalHeaderItem(i++, new headertableitem(p, ("Moyenne " + tmp->name + ""), *tmp, "%"));
            //this->setHorizontalHeaderItem(i++, new QTableWidgetItem(("temps a " + tmp2->name + " reel").c_str()));
            tmp++;
        }
    }
}

void	tableshow::setverticalheader(vector<question> &q, int id)
{
    (void)q;
    int i = -1;
    QList<int>::const_iterator listpg;
    QList<int> listint;
    group * gtmp = NULL;
    //listint << id;
    p->groupqchild(id, listint);

    listpg = listint.begin();
    while (listpg != listint.end())
    {
        list<question> listq37 = p->listqgroup[*listpg].getListq();
        list<question>::iterator listqtmp = listq37.begin();
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
}

void	tableshow::setverticalheader(vector<group> &g, int id)
{
    int i = -1;
    QList<int>::const_iterator listpg;
    QList<int> listint;
    qDebug() << id;
    p->groupchild(id, listint);

    listpg = listint.begin();
    while (listpg != listint.end())
    {
        group * gtmp = &(g[(*listpg)]);
        if (p->listp.empty() == true)
            return ;
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
}

void	tableshow::populate()
{
    int h = -1;
    int w;

    while (++h < this->rowCount())
    {
        w = this->k - 1;
        while (++w < this->columnCount())
            this->setItem(h, w, new itemtable("test h:" + QString::number(h) + " w:" + QString::number(w), p));
    }
}

void	tableshow::select(int gref, int gqref)
{
    QList<int> listint;
    QList<int> listqint;

    p->groupqchild(gqref, listqint);
    p->groupchild(gref, listint);
    headertableitem *tmp;

    int h = -1;

    while (++h < this->rowCount())
    {
        tmp = (dynamic_cast<headertableitem*>(this->verticalHeaderItem(h)));
 /*       qDebug() << listint;
        qDebug() << listqint;
        if (!tmp)
            qDebug() << "dynamic_cast<headertableitem*> fail tableshowselect";
        else
            qDebug() << "dynamic_cast<headertableitem*> id = " << tmp->id;*/
        if (tmp && tmp->is_in(this->p->listgroup , this->p->listqgroup, listint, listqint))
            this->showRow(h);
        else
            this->hideRow(h);
    }
    h = -1;

    while (++h < this->columnCount())
    {
        tmp = (dynamic_cast<headertableitem*>(this->horizontalHeaderItem(h)));
/*        qDebug() << listint;
        qDebug() << listqint;
        if (!tmp)
            qDebug() << "dynamic_cast<headertableitem*> fail tableshowselect";
        else
            qDebug() << "dynamic_cast<headertableitem*> id = " << tmp->id;*/
        //listint.contains(tmp->id)
        if (tmp && tmp->is_in(this->p->listgroup, this->p->listqgroup, listint, listqint))
            this->showColumn(h);
        else
            this->hideColumn(h);
    }
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
//	QList<int>::const_iterator listpg;
//	QList<int> listint;
//    if (mainp->showmod == 2)
//        p->groupqchild(id, listint);
//    else
//        p->groupchild(id, listint);

/*	this->clear(); // changer system
    this->populate();
    this->sethorizontalheader(main);
    this->setverticaleheader(p->listgroup, id);
    this->updateall();*/
    this->select(id, qid);
    qDebug() << "showtableshow";
    /*listpg = listint.begin();
    while (listpg != listint.end())
    {
        if (mainp->showmod == 1)
            this->listgroup[(*listpg)].show(this, &i, this->listgroup, this->k);
        else
            this->listgroup[(*listpg)].showgroup(this, &i, this->listquestion, this->listgroup, this->k);
        listpg++;
    }*/
}

void    tableshow::saveqpoint()
{
    lastqpoint = QCursor::pos();
}

void    tableshow::saveqpoint(QPoint qpoint)
{
    qDebug() << "dsad";
    lastqpoint = qpoint;
    menuhead->popup(qpoint);
}

void    tableshow::suphheader()
{
    this->removeColumn(this->columnAt(lastqpoint.x()));
}

void    tableshow::supvheader()
{
    this->removeRow(this->rowAt(lastqpoint.y()));
}

void    tableshow::modifhheader()
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

void    tableshow::modifvheader()
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

//void    tableshow::changearg(QTreeWidgetItem * item)
//{
//    headertableitem *headcast = dynamic_cast<headertableitem*>(item);

//    headcast->changearg(item)
//}

void	tableshow::updateall()
{
    int h = -1;
    int w;

    qDebug() << "updateall";
    while (++h < this->rowCount() + 1)
    {
        w = - 1;
        while (++w < this->columnCount() + 1)
        {
            itemtable *tmp = dynamic_cast<itemtable *>(this->item(h, w));
            if (tmp)
                tmp->update();
        }
    }
}



