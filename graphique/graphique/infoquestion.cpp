#include "infoquestion.h"
#include "question.h"
#include "project.h"
#include "questiontreeitem.h"
#include "grouptreeitem.h"

infoquestion::infoquestion(project *p) : p(p)
{
    QVBoxLayout *vbox = new QVBoxLayout();
    type = new QComboBox();
    type->addItem("Nombre");
    name = new QLineEdit();
    description = new QLineEdit();
    unit = new QLineEdit();
    value = new QSpinBox();
    QPushButton *b_update = new QPushButton("Enregistrer");

    vbox->addWidget(new QLabel("Type"));
    vbox->addWidget(type);
    vbox->addWidget(new QLabel("Name"));
    vbox->addWidget(name);
    vbox->addWidget(new QLabel("Description"));
    vbox->addWidget(description);
    vbox->addWidget(new QLabel("Unitée"));
    vbox->addWidget(unit);
    vbox->addWidget(new QLabel("Valeur"));
    vbox->addWidget(value);
    vbox->addWidget(b_update);

    this->setLayout(vbox);

    //slot

    connect(b_update, SIGNAL(clicked(bool)), this, SLOT(updatebdd()));
}

void infoquestion::updateib(QTreeWidgetItem * item)
{
    if (item == NULL)
    {
        qDebug() << "dsqd";
    }
    else
        qDebug() << item->text(0);
    questiontreeitem *tmp = dynamic_cast<questiontreeitem*>(item);
    grouptreeitem *tmp2 = dynamic_cast<grouptreeitem*>(item);
    if (tmp2)
        qDebug() << "wtf";
    if (tmp == NULL)
        return ;
    else
    {
        qDebug() << "infoquestion updateib dynamic cast fail";
        return ;
    }
    this->q = (p->getquestion(tmp->id));

    type->setCurrentIndex(q->type);
    name->setText(q->name.c_str());
    description->setText(q->sujet);
    unit->setText(q->unit);
//    value->setText(q.value);
}

void infoquestion::updatebdd()
{
    if (!q)
    {
        QLabel *warning = new QLabel("Aucun objet selectioné");
        warning->show();
        return ;
    }
    QSqlQuery query;
    query.prepare(("UPDATE project_" + p->name + "_question Set question=?, type=?, description=? WHERE id=?;").c_str());
    query.addBindValue(name->text());
    query.addBindValue(unit->text());
    query.addBindValue(description->text());
    query.addBindValue(q->id);
    if (!(query.exec()))
        qDebug() << query.lastError();
}
// question &q
