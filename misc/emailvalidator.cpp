#include "emailvalidator.h"
#include "data/project.h"
#include "grouptree.h"
#include "mainwindow.h"

void emailvalidator::init(int group)
{
    QList<person>::iterator i;

    listp = m->current.getListallpfils(group);
    listmail->clear();

    i = listp.begin();
    while (i != listp.end())
    {
        listmail->addItem(i->name + " (" + i->email + ")");
        i++;
    }
    groupid = group;
}

emailvalidator::emailvalidator(MainWindow *m, int ref) : m(m), ref(ref) // opti listp en vector
{

    QHBoxLayout *hbox = new QHBoxLayout();
    QVBoxLayout *vbox = new QVBoxLayout();
    QVBoxLayout *layout = new QVBoxLayout();

    grouptree *gt = new grouptree(m, m->current.listgroup, 2);
    listmail = new QListWidget(this);

    init(0);
    QPushButton *send = new QPushButton("Envoyer");
    connect(send, SIGNAL(pressed()), this, SLOT(send()));
    connect(send, SIGNAL(pressed()), this, SLOT(close()));
    QPushButton *close = new QPushButton("Annuler");
    connect(close, SIGNAL(pressed()), this, SLOT(close()));
    QHBoxLayout *sendanulbox = new QHBoxLayout();
    sendanulbox->addWidget(send);
    sendanulbox->addWidget(close);

    vbox->addWidget(listmail);

    hbox->addWidget(gt, 1);
    hbox->addLayout(vbox, 3);
    layout->addLayout(hbox);
    layout->addLayout(sendanulbox);

//    listmail->addItems(m->current.sendproject(0));

    connect(gt, SIGNAL(selectgroupchange(int)), this, SLOT(init(int)));

    this->setLayout(layout);
}


void emailvalidator::send()
{
    QSqlQuery qry;

    //m->current.getgrouplist(groupid);
    if (ref)
        qry.prepare("UPDATE project_" + m->namecurrent + "_project SET refbool = refbool + 1 WHERE 1";// + strallgroupfilsforsql(groupid, m->namecurrent) + ";");
    else
         qry.prepare( "UPDATE project_" + m->namecurrent + "_project SET questionbool = questionbool + 1 WHERE 1;";// + strallgroupfilsforsql(groupid, m->namecurrent) + ";");
    if(!qry.exec() )
        qDebug() << "emailvalidator send" << qry.lastError();
    else
        m->sendprojectauxi("directlogin.php", listp);
}
