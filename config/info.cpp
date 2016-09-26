#include "info.h"
#include "data/project.h"
#include "data/group.h"

info::info(project *p) : p(p)
{
    vboxinfo = new QVBoxLayout();
    contg = new QWidget();
    infog = new QVBoxLayout();
    infolabel = new QLabel("test");
    descriptiong = new QLineEdit();
    gquestion = new QCheckBox();
    b_update = new QPushButton("Enregistrer");

    vboxinfo->addWidget(infolabel);

    infog->addWidget(new QLabel("description"));
    infog->addWidget(descriptiong);
    infog->addWidget(new QLabel("question tiroir"));
    infog->addWidget(gquestion);
    infog->addWidget(b_update);
    contg->setLayout(infog);
    vboxinfo->addWidget(contg);
    this->setLayout(vboxinfo);
    contg->hide();

    //slot

    connect(b_update, SIGNAL(clicked(bool)), this, SLOT(updatebddg()));
}

void info::updateibg(int id, int type)
{
    if (id == -1)
    {
        init = -1;
        return ;
    }
    init = 1;
    if (type == 0)
        current = &(p->listgroup[id]);
    if (type == 1)
        current = &(p->listqgroup[id]);
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
    addgroup(p, p->name, current->name, current->parentid , current->type, descriptiong->text(), gquestion->isChecked(), ((init) ? current->id : -1));
}
