#include "info.h"
#include "data/project.h"
#include "data/group.h"

info::info(project *p) : p(p)
{
    vbox = new QVBoxLayout();
    cont = new QWidget();
    infolabel = new QLabel("");
    descriptiong = new QLineEdit();
    b_update = new QPushButton("Enregistrer");

    vbox->addWidget(infolabel);
    vbox->addWidget(cont);

    vbox->addWidget(new QLabel("description"));
    vbox->addWidget(descriptiong);
    vbox->addWidget(b_update);
    cont->setLayout(vbox);

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
    cont->setLayout(vbox);
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
    addgroup(p, p->name, current->name, current->parentid , current->type, descriptiong->text(), ((init) ? current->id : -1));
}
