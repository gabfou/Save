#include "infoquestion.h"
#include "data/question.h"
#include "data/project.h"
#include "questiontreeitem.h"
#include "grouptreeitem.h"
#include "mainwindow.h"
#include "misc/listedit.h"

void infoquestion::prephide()
{
    unit->hide();
    unitlabel->hide();
    selectlistlabel->hide();
    selectlist->hide();
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
}

infoquestion::infoquestion(project *p, MainWindow *m, int con) : info(p), m(m)
{
	QVBoxLayout *vbox = new QVBoxLayout();
    contq = new QWidget();
    hbox = new QHBoxLayout();
	type = new QComboBox();
	type->addItem("Nombre");
	type->addItem("Radio");
    type->addItem("Select");
    type->setCurrentIndex(1);
	name = new QLineEdit();
	description = new QLineEdit();
	unit = new QLineEdit();
	value = new QSpinBox();
    ref_only = new QCheckBox("A poser qu'une seul fois");
	b_update = new QPushButton("Enregistrer");
    selectlist = new listedit();
    selectlistlabel = new QLabel("option");
    unitlabel = new QLabel("Unitée");
    groupbox = new grouptree(m, p->listgroup, 0);
    groupbox->headerItem()->setText(0, "Groupe cible");

	vbox->addWidget(new QLabel("Type"));
	vbox->addWidget(type);
	vbox->addWidget(new QLabel("Noms"));
	vbox->addWidget(name);
	vbox->addWidget(new QLabel("Description"));
	vbox->addWidget(description);
    vbox->addWidget(selectlistlabel);
    vbox->addWidget(selectlist);
    vbox->addWidget(unitlabel);
	vbox->addWidget(unit);
    vbox->addWidget(ref_only);
    vbox->addWidget(new QLabel("Valeur"));
    vbox->addWidget(value);
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
		this->q = new question(p->getquestion(tmp->id));
	}
    type->setCurrentIndex(q->type);
    name->setText(q->name);
	description->setText(q->sujet);
	unit->setText(q->unit);
    groupbox->setcurrentgroup(q->group);
    ref_only->setChecked(q->ref_only);
//    listchar =
//	value->setText(q.value);
}

question infoquestion::getquestioncopy()
{
    question ret = question(name->text(), dynamic_cast<grouptreeitem*>(groupbox->currentItem())->getId(), -1,
                              qgroupid, description->text(), unit->text(), type->currentIndex(),
                              selectlist->getlstr().join(" "),value->text().toInt(), ref_only->isChecked());
    return (ret);
}

void infoquestion::updatebdd()
{
	if (!q && init)
	{
		QLabel *warning = new QLabel("Aucun objet selectioné");
		warning->show();
		return ;
	}
    addquestion(p, name->text(), dynamic_cast<grouptreeitem*>(groupbox->currentItem())->getId(),
                unit->text(), 0, description->text(), qgroupid, type->currentIndex(), ref_only->isChecked(),
                selectlist->getlstr().join(" "), value->text().toInt(), ((init) ? q->id : -1));

}
// question &q
