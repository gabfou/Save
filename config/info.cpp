#include "info.h"
#include "data/project.h"
#include "data/group.h"

void info::prephide()
{
    gquestion->hide();
    gquestionlabel->hide();
}

info::info(project *p) : p(p)
{
    vboxinfo = new QVBoxLayout();
    vboxinfo->setAlignment(Qt::AlignTop);
    contg = new QWidget();
    infog = new QVBoxLayout();
    infolabel = new QLabel("");
    descriptiong = new QLineEdit();
    gquestion = new QCheckBox();
    b_update = new QPushButton("Enregistrer");

    vboxinfo->addWidget(infolabel);

    infog->addWidget(new QLabel("description"));
    infog->addWidget(descriptiong);

    gquestionbox = new QHBoxLayout();
    gquestionlabel = new QLabel("question tiroir :");
    gquestionbox->addWidget(gquestionlabel);
    gquestionbox->addWidget(gquestion, Qt::AlignLeft);
    infog->addLayout(gquestionbox);

    infog->addWidget(b_update);

    contg->setLayout(infog);
    vboxinfo->addWidget(contg);
    this->setLayout(vboxinfo);
    contg->hide();

    //slot

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
        current = &(p->listqgroup[id]);
    }
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
    sqlo::addgroup(p, p->name, current->name, current->parentid , current->type, descriptiong->text(), gquestion->isChecked(), ((init) ? current->id : -1));
}
