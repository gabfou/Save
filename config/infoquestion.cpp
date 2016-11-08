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
    minlabel->hide();
    maxlabel->hide();
    min->hide();
    max->hide();
    maxenabled->hide();
}

void infoquestion::typeshow(int type)
{
    this->prephide();
    if (type == 0)
    {
        unitlabel->show();
        unit->show();
        minlabel->show();
        maxlabel->show();
        min->show();
        maxenabled->show();
        if (maxenabled->isChecked())
            max->show();
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

infoquestion::infoquestion(project *p, MainWindow *m, int con) : info(m)
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
    ref_only = new QComboBox();
    ref_only->addItem("Estimation et réel");
    ref_only->addItem("Estimation seulement");
    ref_only->addItem("Réel Seulement");
    b_update = new QPushButton("Enregistrer");
    selectlist = new listedit();
    selectlistval = new listeditwval();
    selectlistlabel = new QLabel("Option");
    unitlabel = new QLabel("Unitée");
    changegroup = new QPushButton("Modifier le groupe parrent");
    groupbox = new grouptree(m, p->listgroup, 0);
    groupbox->headerItem()->setText(0, "Groupe cible");

    minmaxbox = new QHBoxLayout();
    min = new QSpinBox(this);
    max = new QSpinBox(this);
    min->setMinimum(0);
    min->setMaximum(1000000);
    max->setMinimum(0);
    max->setMaximum(1000000);
    minlabel = new QLabel("Min:");
    minmaxbox->addWidget(minlabel);
    minmaxbox->addWidget(min);

    QVBoxLayout *maxbox = new QVBoxLayout();
    maxenabled = new QCheckBox(this);
    maxbox->addWidget(maxenabled);
    maxbox->addWidget(max);

    maxlabel = new QLabel("Max:");
    minmaxbox->addWidget(maxlabel);
    minmaxbox->addLayout(maxbox);

	vbox->addWidget(new QLabel("Type"));
	vbox->addWidget(type);
	vbox->addWidget(new QLabel("Noms"));
	vbox->addWidget(name);
	vbox->addWidget(new QLabel("Description"));
	vbox->addWidget(description);
    vbox->addWidget(selectlistlabel);
    vbox->addWidget(selectlist, 3);
    vbox->addWidget(selectlistval, 1);
    vbox->addLayout(minmaxbox);
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
    connect(maxenabled, SIGNAL(clicked(bool)), max, SLOT(setVisible(bool)));
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
    ref_only->setCurrentIndex(q->ref_only);
    selectlist->update(q->liststr);
    selectlistval->update(q->liststr);
    if (type == 0)
    {
        if (q->liststr.size() > 0)
            min->setValue(q->liststr[0].toFloat());
        else
            min->setValue(0);
        if (q->liststr.size() > 1)
        {
            max->setValue(q->liststr[1].toFloat());
            maxenabled->setChecked(1);
        }
        else
        {
            max->setValue(0);
            maxenabled->setChecked(0);
        }
    }
}

question infoquestion::getquestioncopy()
{
    QString splitchar;
    if (type->currentIndex() == 3)
        splitchar = selectlistval->getlstr().join("\n");
    else if (type->currentIndex() == 2)
        splitchar = selectlist->getlstr().join("\n");
    else if (type->currentIndex() == 0)
        splitchar = min->text() + "\n" + ((maxenabled->isChecked()) ? max->text() : "");

    question ret = question(name->text(), dynamic_cast<grouptreeitem*>(groupbox->currentItem())->getId(), -1,
                              qgroupid, description->text(), unit->text(), type->currentIndex(),
                              splitchar, value->text().toInt(), ref_only->currentIndex(), 0);
    return (ret);
}

void infoquestion::updatebdd()
{
    QString splitchar;

    if (type->currentIndex() == 3)
        splitchar = selectlistval->getlstr().join("\n");
    else if (type->currentIndex() == 2)
        splitchar = selectlist->getlstr().join("\n");
    else if (type->currentIndex() == 0)
        splitchar = min->text() + ((maxenabled->isChecked()) ? "\n" + max->text() : "");
	if (!q && init)
	{
		QLabel *warning = new QLabel("Aucun objet selectioné");
		warning->show();
		return ;
	}
    sqlo::addquestion(p, name->text(), dynamic_cast<grouptreeitem*>(groupbox->currentItem())->getId(),
                unit->text(), 0, description->text(), qgroupid, type->currentIndex(), ref_only->currentIndex(),
                splitchar, value->text().toInt(), 0, ((init) ? q->id : -1));

}
// question &q
