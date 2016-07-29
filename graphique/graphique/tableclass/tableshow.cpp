#include "tableshow.h"
#include "project.h"
#include "question.h"
#include "group.h"
#include "person.h"
#include "mainwindow.h"
#include "headertableitem.h"
#include "itemtable.h"
#include "argtableitem.tpp"

tableshow::tableshow(project * p, MainWindow *main) : p(p)
{
    int i = (main->showmod == 0) ? 0 : 1;
    i+= p->getNbgeneration();
    int k = i;
    int j = -1;

    qDebug() << "new tableshow";
    main->setCentralWidget(this);
    //this->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    if (p->listp.empty() || p->listquestion.empty())
        return ;
    this->clear();
    this->setRowCount(p->getNbperson() * 2 + p->getNbgroup() * 2);
    this->setColumnCount(p->getNbquestion() + i /* 2*/);
    this->k = i;
    i = 0;
    this->populate();
    if (main->showmod == 0)
    {
        this->sethorizontalheader(main);
        this->setverticalheader(p->listgroup, 0);
    }
    else if (main->showmod == 2)
    {
        this->sethorizontalheader(main);
        this->setverticalheader(p->listquestion, 0);
    }
    this->updateall();
}

void    tableshow::sethorizontalheader(MainWindow *main)
{
    vector<question>::const_iterator tmp2;
    int i = (main->showmod == 1) ? 1 : 0;
    i+= p->getNbgeneration();

    if (main->showmod == 0 || main->showmod == 1)
    {
        tmp2 = p->listquestion.begin();
        if (main->showmod == 0)
        {
            while (--k > -1)
                this->setHorizontalHeaderItem(k, new headertableitem("Sous groupe"));
        }
        else
        {
            this->setHorizontalHeaderItem(--k, new headertableitem("Noms"));
            while (--k > -1)
                this->setHorizontalHeaderItem(k, new headertableitem("Sous groupe"));
        }
        //k = i;
        while (tmp2 != p->listquestion.end())
        {
            this->setHorizontalHeaderItem(i++, new headertableitem(("Moyenne " + tmp2->name + "").c_str(), *tmp2, "%"));
            //this->setHorizontalHeaderItem(i++, new QTableWidgetItem(("temps a " + tmp2->name + " reel").c_str()));
            tmp2++;
        }
    }
    /*else if (main->showmod == 2)
    {
        tmp2 = p->list.begin();
        if (main->showmod == 0)
        {
            while (--k > -1)
                this->setHorizontalHeaderItem(k, new headertableitem("Sous groupe"));
        }
        else
        {
            this->setHorizontalHeaderItem(--k, new headertableitem("Noms"));
            while (--k > -1)
                this->setHorizontalHeaderItem(k, new headertableitem("Sous groupe"));
        }
        //k = i;
        while (tmp2 != p->listquestion.end())
        {
            this->setHorizontalHeaderItem(i++, new headertableitem(("Moyenne " + tmp2->name + "").c_str(), *tmp2, "%"));
            //this->setHorizontalHeaderItem(i++, new QTableWidgetItem(("temps a " + tmp2->name + " reel").c_str()));
            tmp2++;
        }
    }*/
}

void    tableshow::setverticalheader(vector<question> &q, int id)
{
    int i = -1;
    QList<int>::const_iterator listpg;
    QList<int> listint;
    //listint << id;
    p->groupqchild(id, listint);

    listpg = listint.begin();
    qDebug() << "questionheader";
    while (listpg != listint.end())
    {
        group * gtmp = &(p->listqgroup[(q[(*listpg)]).qgroupid]);
        if (p->listp.empty() == true)
            return ;
        while (gtmp->getGeneration() > 0)
        {
            this->setItem(i, gtmp->getGeneration() - 1, new QTableWidgetItem(gtmp->getName().c_str()));
            //gbox->item(*i, gtmp->getGeneration() - 1)->setBackgroundColor(Qt::red);
            gtmp = &(p->listqgroup[gtmp->getParentid()]);
        }
        this->setVerticalHeaderItem(i++, new headertableitem(gtmp->getName().c_str(), (q[(*listpg)])));
        listpg++;
        //gbox->verticalHeaderItem(i)->setBackgroundColor(gtmp->getColor());
    }
    qDebug() << "questionheaderend";
}

void    tableshow::setverticalheader(vector<group> &g, int id)
{
    int i = -1;
    QList<int>::const_iterator listpg;
    QList<int> listint;
    //listint << id;
    p->groupchild(id, listint);

    listpg = listint.begin();
    while (listpg != listint.end())
    {
        group * gtmp = &(g[(*listpg)]);
        if (p->listp.empty() == true)
            return ;
        while (gtmp->getGeneration() > 0)
        {
            this->setItem(i, gtmp->getGeneration() - 1, new QTableWidgetItem(gtmp->getName().c_str()));
            //gbox->item(*i, gtmp->getGeneration() - 1)->setBackgroundColor(Qt::red);
            gtmp = &(g[gtmp->getParentid()]);
        }
        this->setVerticalHeaderItem(i++, new headertableitem(gtmp->getName().c_str(), (g[*listpg])));
        listpg++;
        //gbox->verticalHeaderItem(i)->setBackgroundColor(gtmp->getColor());
    }
}

void    tableshow::populate()
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

void    tableshow::select(int gref)
{
    QList<int> listint;
    p->groupchild(gref, listint);
    headertableitem *tmp;
    int h = -1;

    while (++h < this->rowCount())
    {
        tmp = (dynamic_cast<headertableitem*>(this->verticalHeaderItem(h)));
        if (tmp && listint.contains(tmp->id))
            this->showRow(h);
        else
            this->hideRow(h);
    }
//    int w = -1;
}

void    tableshow::clearheader()
{
    int h = -1;
    int w;

    while (++h < this->rowCount())
        delete (this->verticalHeaderItem(h));
    w = -1;
    while (++w < this->columnCount())
        delete (this->horizontalHeaderItem(h));
}

void	tableshow::showtable(MainWindow *main, int k, int id, int i)
{
    QList<int>::const_iterator listpg;
    QList<int> listint;
    p->groupchild(id, listint);

/*    this->clear(); // changer system
    this->populate();
    this->sethorizontalheader(main);
    this->setverticaleheader(p->listgroup, id);
    this->updateall();*/
    this->select(id);
    qDebug() << "showtableshow";
    /*listpg = listint.begin();
    while (listpg != listint.end())
    {
        if (main->showmod == 1)
            this->listgroup[(*listpg)].show(this, &i, this->listgroup, this->k);
        else
            this->listgroup[(*listpg)].showgroup(this, &i, this->listquestion, this->listgroup, this->k);
        listpg++;
    }*/
}

void    tableshow::updateall()
{
    int h = -1;
    int w;

    qDebug() << "updateall";
    while (++h < this->rowCount())
    {
        w = this->k - 1;
        while (++w < this->columnCount())
        {
            itemtable *tmp = dynamic_cast<itemtable *>(this->item(h, w));
            if (tmp)
                tmp->update();
        }
    }
}

