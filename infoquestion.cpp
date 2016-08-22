#include "infoquestion.h"
#include "data/question.h"
#include "data/project.h"
#include "questiontreeitem.h"
#include "grouptreeitem.h"
#include "mainwindow.h"

infoquestion::infoquestion(project *p, MainWindow *m, grouptree *qgroup) : p(p)
{
	QVBoxLayout *vbox = new QVBoxLayout();
	type = new QComboBox();
	type->addItem("Nombre");
	type->addItem("Radio");
	name = new QLineEdit();
	description = new QLineEdit();
	unit = new QLineEdit();
	value = new QSpinBox();
	b_update = new QPushButton("Enregistrer");

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

	cotmp = connect(b_update, SIGNAL(clicked(bool)), this, SLOT(updatebdd()));
}

void infoquestion::updateib(QTreeWidgetItem * item)
{
	questiontreeitem *tmp = dynamic_cast<questiontreeitem*>(item);

	disconnect(cotmp);
	cotmp = connect(b_update, SIGNAL(clicked(bool)), this, SLOT(updatebdd()));
	if (tmp == NULL)
	{
        qDebug() << "infoquestion updateib dynamic cast fail";
        grouptreeitem *tmp2 = dynamic_cast<grouptreeitem*>(item);
        if (tmp2)
            qgroupid = tmp2->getId();
        else
            qDebug() << "infoquestion updateib dynamic cast 2 fail";
		return ;
    }
    grouptreeitem *tmp2 = dynamic_cast<grouptreeitem*>(item->parent());
    qgroupid = tmp2->getId();
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
	name->setText(q->name.c_str());
	description->setText(q->sujet);
	unit->setText(q->unit);
//	value->setText(q.value);
}

void infoquestion::updatebdd()
{
	if (!q && init)
	{
		QLabel *warning = new QLabel("Aucun objet selectioné");
		warning->show();
		return ;
	}
	QSqlQuery query;
	if (init)
		query.prepare(("UPDATE project_" + p->name + "_question Set question=?, type=?, note=?, sujet=?, typef=?, groupid=?, qgroupid=? WHERE id=?;").c_str());
	else
	{
        query.prepare( ("CREATE TABLE IF NOT EXISTS project_" + p->name + "_question (id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT, question VARCHAR(30), groupid INTEGER, type VARCHAR(30), note BOOLEAN DEFAULT 1, sujet VARCHAR(300), qgroupid INT DEFAULT 0, typef INT DEFAULT 0)").c_str() );
		if( !query.exec() )
			qDebug() << query.lastError();
		query.prepare( ("INSERT INTO project_" + p->name + "_question (question, type, note, sujet, typef, groupid, qgroupid) VALUES ( ? , ? , ? , ? , ? , ?, ?);").c_str() );
	}
	query.addBindValue(name->text());
	query.addBindValue(unit->text());
	query.addBindValue("0");
	query.addBindValue(description->text());
	query.addBindValue(type->currentIndex());
	query.addBindValue("0");
	query.addBindValue(qgroupid);
	if (init)
		query.addBindValue(q->id);
	else
	{
		// fonctione pas
		//p->addquestion(name->text().toStdString(), 0, query.lastInsertId().toInt(), type->currentIndex(), description->text(), unit->text());

	}
	if (!(query.exec()))
		qDebug() << query.lastError();
}
// question &q
