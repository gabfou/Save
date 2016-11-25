#include "info.h"
#include "data/project.h"
#include "data/group.h"
#include "grouptree.h"
#include "mainwindow.h"

void info::prephide()
{
    gquestion->hide();
    gquestionlabel->hide();
    gsettarget->hide();
}

info::info(MainWindow *m) : m(m), p(&(m->current))
{
    vboxinfo = new QVBoxLayout();
    vboxinfo->setAlignment(Qt::AlignTop);
    contg = new QWidget();
    infog = new QVBoxLayout();
    infolabel = new QLabel("");
    name = new QLineEdit();
    descriptiong = new QTextEdit();
    gquestion = new QComboBox(this);
    gsettarget = new QPushButton("Changer le groupe cible des decendants");
    b_update = new QPushButton("Enregistrer");

    vboxinfo->addWidget(infolabel);

    infog->addWidget(new QLabel("name"));
    infog->addWidget(name);
    infog->addWidget(new QLabel("description"));
    infog->addWidget(descriptiong);

    gquestionbox = new QHBoxLayout();
    gquestionlabel = new QLabel("type :");
    gquestion->addItem("Etape");
    gquestion->addItem("Groupe de question");
    gquestion->addItem("Question tiroir (nécessite une question oui/non)");
    gquestionbox->addWidget(gquestionlabel);
    gquestionbox->addWidget(gquestion);
    infog->addWidget(gsettarget);

    infog->addLayout(gquestionbox);

    infog->addWidget(b_update);

    contg->setLayout(infog);
    vboxinfo->addWidget(contg);
    this->setLayout(vboxinfo);
    contg->hide();

    //slot

    connect(gsettarget, SIGNAL(clicked(bool)), this, SLOT(settargetchildquestion()));
    connect(b_update, SIGNAL(clicked(bool)), this, SLOT(updatebddg()));
    prephide();
}

void info::updateibg(int id, int type)
{
    prephide();
    if (id == -1)
    {
        init = -1;
        return ;
    }
    init = 1;
    if (type == 0)
    {
        current = &(p->listgroup[id]);
    }
    if (type == 1)
    {
        gquestion->show();
        gquestionlabel->show();
        gsettarget->show();
        current = &(p->listqgroup[id]);
    }
    gquestion->setCurrentIndex(current->gquestion);
    descriptiong->setText(current->description);
    name->setText(current->name);
    infolabel->setText("groupe");
    contg->show();
}

void info::updatebddg()
{
//    char mdp[7];
//    QString mdphash;

    if (!current)
    {
        QLabel *warning = new QLabel("Aucun objet selectioné");
        warning->show();
        return ;
    }
    sqlo::addgroup(p, p->name, name->text(), current->parentid , current->type, descriptiong->toHtml(), gquestion->currentIndex(), ((init) ? current->id : -1));
}

void info::settargetchildquestion()
{
    grouptree *tmp = new grouptree(m, m->current.listgroup, 2);
    tmp->setWindowModality(Qt::ApplicationModal);
    tmp->show();
    connect(tmp, SIGNAL(selectgroupchange(int)), this, SLOT(settargetchildquestion2(int)));
    connect(tmp, SIGNAL(selectgroupchange(int)), tmp, SLOT(close()));
}

void info::settargetchildquestion2(int id)
{
    qDebug() << id;
    m->current.listqgroup[current->id].changegroupidallqchild(p, id);
}
