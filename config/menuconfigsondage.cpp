#include "menuconfigsondage.h"
#include "mainwindow.h"

menuconfigsondage::menuconfigsondage(MainWindow *m) : m(m)  // opti list a la place de vector pour listid ?
{
    QSqlQuery qry;
    listWidget = new QListWidget();
    QHBoxLayout *hbox = new QHBoxLayout();

    if(qry.exec("SELECT begin, id FROM all_etude WHERE project_name='" + m->namecurrent + "';"))
    {
        while(qry.next())
        {
            listWidget->addItem(qry.value(0).toString());
            listid << qry.value(1).toInt();
        }
    }
    else
        qDebug() << "menu config sondage 1" << qry.lastError();

    QHBoxLayout *nbiterationbox = new QHBoxLayout();
    nbiterationbox->addWidget(new QLabel("Nombre de sondage:"));
    nbiteration =  new QSpinBox();
    nbiterationbox->addWidget(nbiteration);

    QHBoxLayout *refbox = new QHBoxLayout();
    refbox->addWidget(new QLabel("lancer un sondage de reference ?"));
    refcheck =  new QCheckBox();
    refbox->addWidget(refcheck);

    QPushButton *newsondage = new QPushButton("nouveaux");
    connect(newsondage, SIGNAL(pressed()), this, SLOT(newsondage()));
    QPushButton *supsondage = new QPushButton("supprimer");
    connect(supsondage, SIGNAL(pressed()), this, SLOT(supsondage()));

    QHBoxLayout *newsupbox = new QHBoxLayout();
    newsupbox->addWidget(newsondage);
    newsupbox->addWidget(supsondage);
//    connect(listWidget, SIGNAL)

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(listWidget);
//    layout->addLayout(nbiterationbox);
//    layout->addLayout(refbox);
//    layout->addLayout(newsupbox);
    hbox->addLayout(layout, 2);


    QGroupBox programer = new QGroupBox("Programmer plusieurs sondages");
    QVBoxLayout *programerlayout = new QVBoxLayout();
    programer.setLayout(programerlayout);
    programerlayout->addLayout(nbiterationbox);
    programerlayout->addLayout(refbox);
    programerlayout->addLayout(newsupbox);

    hbox->addWidjet(programer);

    this->setLayout(hbox);
}

void menuconfigsondage::supsondage()
{
    QSqlQuery qry;

    if(!(qry.exec("DELETE FROM all_etude WHERE id=" + QString::number(listid[listWidget->currentRow()]) + ";")))
        qDebug() << "menu config sondage 2" << qry.lastError();
    listid.erase(listid.begin() + listWidget->currentRow());
    delete listWidget->currentItem();
}

void menuconfigsondage::newsondage()
{
    QSqlQuery qry;

    (qry.prepare("INSERT INTO all_etude (iteration , project_name , ref ) VALUES ( ?, ?, ? );"));
    qry.addBindValue(nbiteration->text());
    qry.addBindValue(m->namecurrent);
    qry.addBindValue(refcheck->isChecked());
    if (!(qry.exec()))
        qDebug() << "menu config sondage 3" << qry.lastError();
    listid << qry.lastInsertId().toInt();
    listWidget->addItem(QDate::currentDate().toString());
}
