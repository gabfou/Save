#include "infoquestion.h"
#include "data/question.h"
#include "data/project.h"
#include "questiontreeitem.h"
#include "grouptreeitem.h"
#include "mainwindow.h"
#include "misc/listedit.h"
#include "misc/listeditwval.h"
#include "grouptree.h"

void infoquestion::prephide()
{
    unit->hide();
    unitlabel->hide();
    selectlistlabel->hide();
    selectlist->hide();
    selectlistval->hide();
}

void infoquestion::typeshow(int type)
{
    this->prephide();
    if (type == 0)
    {
        unitlabel->show();
        unit->show();
    }
    if (type == 1)
    {

    }
    if (type == 2)
    {
        selectlistlabel->show();
        selectlist->show();
    }
    if (type == 3)
    {
        selectlistlabel->show();
        selectlistval->show();
    }
}

infoquestion::infoquestion(project *p, MainWindow *m, int con) : info(p), m(m)
{
	QVBoxLayout *vbox = new QVBoxLayout();
    contq = new QWidget();
    hbox = new QHBoxLayout();
	type = new QComboBox();
	type->addItem("Nombre");
    type->addItem("Oui/non");
    type->addItem("Option");
    type->addItem("Option avec valeur");
    type->setCurrentIndex(1);
	name = new QLineEdit();
	description = new QLineEdit();
	unit = new QLineEdit();
	value = new QSpinBox();
    value->setValue(1);
    ref_only = new QCheckBox("Question unique");
	b_update = new QPushButton("Enregistrer");
    selectlist = new listedit();
    selectlistval = new listeditwval();
    selectlistlabel = new QLabel("Option");
    unitlabel = new QLabel("Unitée");
    changegroup = new QPushButton("Modifier le groupe parrent");
    groupbox = new grouptree(m, p->listgroup, 0);
    groupbox->headerItem()->setText(0, "Groupe cible");

	vbox->addWidget(new QLabel("Type"));
	vbox->addWidget(type);
	vbox->addWidget(new QLabel("Noms"));
	vbox->addWidget(name);
	vbox->addWidget(new QLabel("Description"));
	vbox->addWidget(description);
    vbox->addWidget(selectlistlabel);
    vbox->addWidget(selectlist, 3);
    vbox->addWidget(selectlistval, 1);
    vbox->addWidget(unitlabel);
	vbox->addWidget(unit);
    vbox->addWidget(ref_only);
    vbox->addWidget(new QLabel("Ponderation"));
    vbox->addWidget(value);
    vbox->addWidget(changegroup);
    vbox->addWidget(b_update);
    hbox->addLayout(vbox);
    hbox->addWidget(groupbox);
    contq->setLayout(hbox);
    vboxinfo->addWidget(contq);

    contq->hide();
    this->prephide();

	//slot
    if (con)
        cotmp = connect(b_update, SIGNAL(clicked(bool)), this, SLOT(updatebdd()));
    connect(type, SIGNAL(currentIndexChanged(int)), this, SLOT(typeshow(int)));
    connect(changegroup, SIGNAL(clicked(bool)), this, SLOT(changegroupparent()));
}

void infoquestion::changegroupparent()
{
    grouptree *gt = new grouptree(m, p->listqgroup, 0);

    gt->setWindowModality(Qt::ApplicationModal);
    connect(gt, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(changegroupparent2(QTreeWidgetItem*)));
    connect(gt, SIGNAL(itemClicked(QTreeWidgetItem*,int)), gt, SLOT(close()));
    gt->show();
}

void infoquestion::changegroupparent2(QTreeWidgetItem *item)
{
    grouptreeitem* tmp =  dynamic_cast<grouptreeitem*>(item);

    if (tmp)
    {
        sqlo::addquestion(p, q->name, q->group, q->unit, q->bnote, q->sujet,
                          tmp->getId(), q->type, q->ref_only, q->liststr.join("\n"),
                          q->val, q->global, q->id);
        p->listquestion[q->id].qgroupid = tmp->getId();
        int i = q->id;
        delete q;
        this->q = new question(p->getquestion(i));
    }
}

void infoquestion::setquestionmod(int qgroupid)
{
    contg->hide();
    contq->show();
    this->qgroupid = qgroupid;
}

void infoquestion::updateib(QTreeWidgetItem * item)
{
	questiontreeitem *tmp = dynamic_cast<questiontreeitem*>(item);

    this->updateibg(-1, -1);
    infolabel->setText("");
    this->prephide();
	disconnect(cotmp);
	if (tmp == NULL)
	{
        qDebug() << "infoquestion updateib dynamic cast fail";
        grouptreeitem *tmp2 = dynamic_cast<grouptreeitem*>(item);
        if (tmp2)
        {
            contq->hide();
            this->updateibg(tmp2->getId(), 1);
            qgroupid = tmp2->getId();
        }
        else
        {
            infolabel->setText("Erreur: selection ilisible");
            qDebug() << "infoquestion updateib dynamic cast 2 fail";
        }
		return ;
    }
    cotmp = connect(b_update, SIGNAL(clicked(bool)), this, SLOT(updatebdd()));
    contg->hide();
    contq->show();
    grouptreeitem *tmp2 = dynamic_cast<grouptreeitem*>(item->parent());
    qgroupid = tmp2->getId();
    infolabel->setText("Question");
	if (tmp->id == -1)
	{
		init = 0;
		return ;
	}
	else
	{
		init = 1;
        if (q)
            delete q;
		this->q = new question(p->getquestion(tmp->id));
	}
    type->setCurrentIndex(q->type);
    typeshow(q->type);
    name->setText(q->name);
	description->setText(q->sujet);
	unit->setText(q->unit);
    groupbox->setcurrentgroup(q->group);
    ref_only->setChecked(q->ref_only);
    selectlist->update(q->liststr);
    selectlistval->update(q->liststr);
}

question infoquestion::getquestioncopy()
{
    QString splitchar = (type->currentIndex() == 3) ? selectlistval->getlstr().join("\n") : selectlist->getlstr().join("\n");

    question ret = question(name->text(), dynamic_cast<grouptreeitem*>(groupbox->currentItem())->getId(), -1,
                              qgroupid, description->text(), unit->text(), type->currentIndex(),
                              splitchar, value->text().toInt(), ref_only->isChecked(), 0);
    return (ret);
}

void infoquestion::updatebdd()
{
    QString splitchar = (type->currentIndex() == 3) ? selectlistval->getlstr().join("\n") : selectlist->getlstr().join("\n");
	if (!q && init)
	{
		QLabel *warning = new QLabel("Aucun objet selectioné");
		warning->show();
		return ;
	}
    sqlo::addquestion(p, name->text(), dynamic_cast<grouptreeitem*>(groupbox->currentItem())->getId(),
                unit->text(), 0, description->text(), qgroupid, type->currentIndex(), ref_only->isChecked(),
                splitchar, value->text().toInt(), 0, ((init) ? q->id : -1));

}
// question &q
