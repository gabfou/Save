#include "menuconfigsondage.h"
#include "mainwindow.h"
#include "grouptree.h"
#include "grouptreeitem.h"
#include "MRichTextEditor/mrichtextedit.h"

// cette classe represente le menu de planification de sondage

menuconfigsondage::menuconfigsondage(MainWindow *m, grouptree *gt) : m(m), gt(gt)
{
    QSqlQuery qry;
    listWidget = new QListWidget();
    QHBoxLayout *hbox = new QHBoxLayout();
    calendar = new QCalendarWidget(this);
    timecalendar = new QDateTimeEdit(this);
    QHBoxLayout *weeklayout = new QHBoxLayout();
    weeklayout->addWidget(listday[0]);
    weeklayout->addWidget(listday[1]);
    weeklayout->addWidget(listday[2]);
    weeklayout->addWidget(listday[3]);
    weeklayout->addWidget(listday[4]);
    weeklayout->addWidget(listday[5]);
    weeklayout->addWidget(listday[6]);
    listday[0]->setChecked(1);
    listday[1]->setChecked(1);
    listday[2]->setChecked(1);
    listday[3]->setChecked(1);
    listday[4]->setChecked(1);
    listday[0]->setAutoExclusive(0);
    listday[1]->setAutoExclusive(0);
    listday[2]->setAutoExclusive(0);
    listday[3]->setAutoExclusive(0);
    listday[4]->setAutoExclusive(0);
    listday[5]->setAutoExclusive(0);
    listday[6]->setAutoExclusive(0);

    if(qry.exec("SELECT begin, id FROM all_etude WHERE project_name='" + m->namecurrent + "';"))
    {
        while (qry.next())
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
    nbiteration->setValue(1);
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

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(listWidget);
    hbox->addLayout(layout, 2);


    QGroupBox *programer = new QGroupBox("Programmer plusieurs sondages");
    QVBoxLayout *programerlayout = new QVBoxLayout();
    programer->setLayout(programerlayout);
    programerlayout->addWidget(timecalendar);
    programerlayout->addLayout(weeklayout);
    programerlayout->addLayout(nbiterationbox);
    programerlayout->addLayout(refbox);
    programerlayout->addLayout(newsupbox);

    layout->addWidget(programer);
    QGroupBox *calendarbox = new QGroupBox("Date du premier sondage");
    QVBoxLayout *layoutcalendar = new QVBoxLayout();
    calendarbox->setLayout(layoutcalendar);
    layoutcalendar->addWidget(calendar);
    hbox->addWidget(calendarbox);

    QGroupBox *mail = new QGroupBox("Mail", this);
    QVBoxLayout *layoutmail = new QVBoxLayout();
    objectmail = new QLineEdit(this);
    textmail = new MRichTextEdit(this);
    textmail->setText("<a href=\"http://etudemurano.alwaysdata.net/directlogin.php__%l__\"><u>PPD_DMI LEAD CHANGE_Online Survey</u></a>");
    layoutmail->addWidget(new QLabel("Objet:"));
    layoutmail->addWidget(objectmail);
    layoutmail->addWidget(new QLabel("Texte:"));
    layoutmail->addWidget(textmail);
    mail->setLayout(layoutmail);
    hbox->addWidget(mail);

    this->setLayout(hbox);

    connect(timecalendar, SIGNAL(dateChanged(QDate)), calendar, SLOT(setSelectedDate(QDate)));
    connect(calendar, SIGNAL(clicked(QDate)), timecalendar, SLOT(setDate(QDate)));
    connect(listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(updatecurrent()));

    timecalendar->setDate(QDate::currentDate());
}

// mise a jour du menu

void menuconfigsondage::updatecurrent()
{
    QSqlQuery qry;

    if (!(qry.exec("SELECT begin, ref, mail, mailobject FROM all_etude WHERE id='" + QString::number(listid[listWidget->currentRow()]) + "';")))
    {
        qDebug() << "updatecurrent menuconfigsondage fail" << qry.lastError();
        return ;
    }
    qry.next();
    timecalendar->setDateTime(qry.value(0).toDateTime());
    refcheck->setChecked(qry.value(1).toBool());
    nbiteration->setValue(1);
    textmail->setText(qry.value(2).toString());
    objectmail->setText(qry.value(3).toString());
}

// supression du sondage

void menuconfigsondage::supsondage()
{
    QSqlQuery qry;

    if (!(qry.exec("DELETE FROM all_etude WHERE id=" + QString::number(listid[listWidget->currentRow()]) + ";")))
        qDebug() << "menu config sondage 2" << qry.lastError();
    listid.erase(listid.begin() + listWidget->currentRow());
    delete listWidget->currentItem();
}

// check si time corespond a un jour valide

static bool notgoodday(QDateTime &time, QRadioButton **listday)
{
    if (listday[0]->isChecked() == 0 && listday[1]->isChecked() == 0
        && listday[2]->isChecked() == 0 && listday[3]->isChecked() == 0
        && listday[4]->isChecked() == 0 && listday[5]->isChecked() == 0
        && listday[6]->isChecked() == 0)
        return (0);
    if (listday[0]->isChecked() && time.date().dayOfWeek() == 1)
        return (0);
    if (listday[1]->isChecked() && time.date().dayOfWeek() == 2)
        return (0);
    if (listday[2]->isChecked() && time.date().dayOfWeek() == 3)
        return (0);
    if (listday[3]->isChecked() && time.date().dayOfWeek() == 4)
        return (0);
    if (listday[4]->isChecked() && time.date().dayOfWeek() == 5)
        return (0);
    if (listday[5]->isChecked() && time.date().dayOfWeek() == 6)
        return (0);
    if (listday[6]->isChecked() && time.date().dayOfWeek() == 7)
        return (0);
    return (1);
}

// ajout d'un sondage

void menuconfigsondage::newsondage()
{
    QSqlQuery qry;
    QDateTime time = QDateTime(timecalendar->dateTime());
    int i;

    i = nbiteration->text().toInt();
    while(--i > -1)
    {
        while (notgoodday(time, listday))
            time.addDays(1);
        (qry.prepare("INSERT INTO all_etude (iteration , project_name , ref , begin, groupid, mail, mailobject) VALUES ( ?, ?, ?, ?, ?, ?, ? );"));
        qry.addBindValue(nbiteration->text());
        qry.addBindValue(m->namecurrent);
        qry.addBindValue(refcheck->isChecked());
        qry.addBindValue(time);
        grouptreeitem *tmp = dynamic_cast<grouptreeitem*>(gt->currentItem());
        if (tmp)
            qry.addBindValue(tmp->getId());
        else
            qry.addBindValue(QVariant(QVariant::Int));
        qry.addBindValue(textmail->toHtml());
        qry.addBindValue(objectmail->text());
        if (!(qry.exec()))
            qDebug() << "menu config sondage 3" << qry.lastError();
        listid << qry.lastInsertId().toInt();
        listWidget->addItem(time.toString());
        time.addDays(1);
    }
}
