#include "mainwindow.h"
#include "smtp.h"
#include "grouptree.h"
#include "barref.h"
#include "config/menuconfigproject.h"
#include "grouptreeitem.h"
#include "tableclass/tableshow.h"
#include "overview.h"
#include "alltree.h"
#include "config/menuconfigsondage.h"
#include "misc/uploader.h"
#include "graph/comparrefdo.h"
#include "misc/menusondage.h"
#include "misc/emailvalidator.h"
#include "tableclass/tableau_brut.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    string comande;

    ui->setupUi(this);
    this->cw = new QTabWidget();
    this->setCentralWidget(cw);
    this->setWindowTitle("Outils sondage (WIP)");
//	this->setWindowModality(Qt::ApplicationModal);
//	this->current = new project;
//	this->table = new QTableWidget(this);
    // default display

    this->resize(1000, 600);

    // timer

    QTimer *sqlco = new QTimer(this);
    connect(sqlco, SIGNAL(timeout()), this, SLOT(checksqlconexion()));
    sqlco->start(10000);

    //menu

    menu_projet = menuBar()->addMenu("&Projet");
//	QAction *show = menu_projet->addAction("&Triage par individu");
//	show->setCheckable(true);
//	show->setChecked(false);
//	QObject::connect(show, SIGNAL(toggled(bool)), this, SLOT(modechange(bool)));
    QAction *new_projet = menu_projet->addAction("&Nouveaux");
    QObject::connect(new_projet, SIGNAL(triggered()), this, SLOT(addproject()));
    QAction *open_projet = menu_projet->addAction("Ouvrir");
    QObject::connect(open_projet, SIGNAL(triggered()), this, SLOT(openproject()));
    QAction *sup_projet = menu_projet->addAction("Supprimer projet");
    QObject::connect(sup_projet, SIGNAL(triggered()), this, SLOT(supproject()));
    QAction *update = menu_projet->addAction("&Actualiser");
    QObject::connect(update, SIGNAL(triggered()), this, SLOT(updateproject()));
    QAction *configp = menu_projet->addAction("&Configuration projet");
    QObject::connect(configp, SIGNAL(triggered()), this, SLOT(configproject()));

//	QMenu *menu_nouveaux = menuBar()->addMenu("&Ajouter");
//	QAction *new_collaborateur = menu_nouveaux->addAction("&Ajouter un collaborateur");
//	QObject::connect(new_collaborateur, SIGNAL(triggered()), this, SLOT(addperson()));
//	QAction *new_question = menu_nouveaux->addAction("&Ajouter une question");
//	QObject::connect(new_question, SIGNAL(triggered()), this, SLOT(addquestion()));
//	QAction *new_groupe = menu_nouveaux->addAction("&Ajouter un groupe");
//	QObject::connect(new_groupe, SIGNAL(triggered()), this, SLOT(addgroupe()));

    //QMenu *menu_selection = menuBar()->addMenu("&selection");

    menu_outil = menuBar()->addMenu("&Outils");
    QAction *xlsx_convert = menu_outil->addAction("&Convertir en xlsx");
    QObject::connect(xlsx_convert, SIGNAL(triggered()), this, SLOT(convert_to_xlsx()));
    QAction *brute = menu_outil->addAction("&Extraire les donnée brute en xlsx");
    QObject::connect(brute, SIGNAL(triggered()), this, SLOT(extract_brutesimple()));
    QAction *afficheform = menu_outil->addAction("&form creator");
    QObject::connect(afficheform, SIGNAL(triggered()), this, SLOT(formcreator()));
//	QAction *barchartref = menu_outil->addAction("&Graphique comparaison reference-donnée");
//	QObject::connect(barchartref, SIGNAL(triggered()), this, SLOT(showbarchartref()));

    menu_affifchage = menuBar()->addMenu("&Affichage");
    afficherref = menu_affifchage->addAction("&Données de références");
    afficherref->setCheckable(true);
    afficherref->setChecked(false);
    QObject::connect(afficherref, SIGNAL(toggled(bool)), this, SLOT(refmodechange(bool)));
    QAction *afficherval = menu_affifchage->addAction("&Ponderation");
    afficherval->setCheckable(true);
    afficherval->setChecked(false);
    QObject::connect(afficherval, SIGNAL(toggled(bool)), this, SLOT(valmodechange(bool)));
    afficherbasetable = menu_affifchage->addAction("&generer le tableaux par groupe");
    afficherbasetable->setCheckable(true);
    afficherbasetable->setChecked(false);
    QObject::connect(afficherbasetable, SIGNAL(toggled(bool)), this, SLOT(baserep(bool)));
    afficherpers = menu_affifchage->addAction("&generer le tableaux individuelle");
    afficherpers->setCheckable(true);
    afficherpers->setChecked(false);
    QObject::connect(afficherpers, SIGNAL(toggled(bool)), this, SLOT(personrep(bool)));
    afficherglobalrep = menu_affifchage->addAction("&generer le tableaux global");
    afficherglobalrep->setCheckable(true);
    afficherglobalrep->setChecked(false);
    QObject::connect(afficherglobalrep, SIGNAL(toggled(bool)), this, SLOT(globalrep(bool)));

    menu_graphique = menuBar()->addMenu("&Graphique");
    affichergraphiquecompare = menu_graphique->addAction("&generer un graphique de comparaison référence-données");
    affichergraphiquecompare->setCheckable(true);
    affichergraphiquecompare->setChecked(false);
    QObject::connect(affichergraphiquecompare, SIGNAL(toggled(bool)), this, SLOT(graphiquecrd(bool)));

    menu_serveur = menuBar()->addMenu("&Serveur");
    QAction *config_sondage = menu_serveur->addAction("&programer une serie de sondage");
    QObject::connect(config_sondage, SIGNAL(triggered()), this, SLOT(configsondage()));
    QAction *new_sondage = menu_serveur->addAction("&lancer un sondage");
    QObject::connect(new_sondage, SIGNAL(triggered()), this, SLOT(sendproject()));
    QAction *new_sondage_ref = menu_serveur->addAction("&lancer un sondage de reference");
    QObject::connect(new_sondage_ref, SIGNAL(triggered()), this, SLOT(sendproject_ref()));
    QAction *suivirepa = menu_serveur->addAction("&suivi des réponse");
    QObject::connect(suivirepa, SIGNAL(triggered()), this, SLOT(suivirep()));

    QToolBar *toolBarFichier = addToolBar("Fichier");
    QAction *screenshoot = toolBarFichier->addAction("&Imprimer écran");
    QObject::connect(screenshoot, SIGNAL(triggered()), this, SLOT(screenshootcurrent()));
    QAction *infoperson = menu_serveur->addAction("&Excell Info");
    QObject::connect(infoperson, SIGNAL(triggered()), this, SLOT(Excellinfo()));

    menu_projet->actions().at(3)->setEnabled(0);
    menu_projet->actions().at(4)->setEnabled(0);
    menu_outil->setEnabled(0);
    menu_affifchage->setEnabled(0);
    menu_serveur->setEnabled(0);
    menu_graphique->setEnabled(0);
}


void MainWindow::initvar()
{
    this->currentgref = 0;
    this->currentgqref = 0;
    this->iterationmax = 2147483640;
    this->iterationmin = 1;
}

//Sql maintain connexion;

void MainWindow::checksqlconexion()
{
    QSqlQuery qry;

    if(!qry.exec("SELECT 1"))
        createConnection();
}

// ajout de question

void MainWindow::addquestion()
{
    QWidget *win = new QWidget();
    QLabel *Labeljeu = new QLabel("Name :");
    this->nametmp = new QLineEdit;
    Labeljeu->setAlignment(Qt::AlignTop);
    QLabel *Labelsujet = new QLabel("Description :");
    this->emailtmp = new QLineEdit;
    Labelsujet->setAlignment(Qt::AlignTop);
    QLabel *Labelgroup = new QLabel("Groupe :");
    this->groupboxtmp = new grouptree(this, this->current.listgroup);
    Labelgroup->setAlignment(Qt::AlignTop);
    QLabel *Labeltype = new QLabel("Unitée :");
    this->prenametmp = new QLineEdit;
    Labeltype->setAlignment(Qt::AlignTop);
    QLabel *Labelnote = new QLabel("Note :");
    this->radiobuttontmp = new QRadioButton("", this);
    Labelnote->setAlignment(Qt::AlignTop);

    //Boutons
    QPushButton *b_valider = new QPushButton("Valider");
    QPushButton *b_annuler = new QPushButton("Fermer");

    //Connexions aux slots
    connect(b_valider, SIGNAL(clicked()), this, SLOT(addquestion2()));
    connect(b_annuler, SIGNAL(clicked()), win, SLOT(close()));

    //Layout
    QGroupBox *groupbox = new QGroupBox("");

    QGridLayout *layoutFormulaire = new QGridLayout();
    layoutFormulaire->addWidget(Labeljeu, 0, 0);
    layoutFormulaire->addWidget(this->nametmp, 0, 1);
    layoutFormulaire->addWidget(Labelsujet, 1, 0);
    layoutFormulaire->addWidget(this->emailtmp, 1, 1);
    layoutFormulaire->addWidget(Labelgroup, 2, 0);
    layoutFormulaire->addWidget(this->groupboxtmp, 2, 1);
    layoutFormulaire->addWidget(Labeltype, 3, 0);
    layoutFormulaire->addWidget(this->prenametmp, 3, 1);
    layoutFormulaire->addWidget(Labelnote, 4, 0);
    layoutFormulaire->addWidget(this->radiobuttontmp, 4, 1);

    groupbox->setLayout(layoutFormulaire);

    QGridLayout *layout = new QGridLayout();
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(groupbox, 0, 0, 1, 2, Qt::AlignTop);
    layout->addWidget(b_annuler, 1, 0, Qt::AlignLeft);
    layout->addWidget(b_valider, 1, 1, Qt::AlignRight);
    //setLayout(layout);
    win->setLayout(layout);
    win->show();
}

void MainWindow::addquestion2()
{
    QSqlQuery qry;

    qry.prepare( "CREATE TABLE IF NOT EXISTS project_" + this->namecurrent + "_question (id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT, question VARCHAR(30), groupid INTEGER, type VARCHAR(30), note BOOLEAN DEFAULT 1, sujet VARCHAR(300), qgroupid INT DEFAULT 0, typef INT DEFAULT 0)" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    qry.prepare("INSERT INTO project_" + this->namecurrent + "_question (question , groupid , type , note , sujet ) VALUES ( ? , ? , ? , ? , ? );");
    qry.addBindValue(this->nametmp->text());
    qry.addBindValue(QString::number(dynamic_cast<grouptreeitem*>(this->groupboxtmp->currentItem())->getId()));
    qry.addBindValue(this->prenametmp->text());
    qry.addBindValue(((this->radiobuttontmp->isChecked()) ? "1" : "0"));
    qry.addBindValue((this->emailtmp->text()));
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug() << "question insert success!";
}

//ajout de projet

void MainWindow::checkprojectname()
{
    QRegExp regex("^[^,;' ]+$");
    QString name = nametmp->text();

    if (name.contains(regex) == 0)
    {
        buttontmp->setDisabled(1);
        labeltmp->setText("<font color='red'>Le nom du nouveau projet ne peux pas contenir d'espace, de ; de ', et ne peut pas être vide</font>");
    }
    else
    {
        buttontmp->setEnabled(1);
        labeltmp->setText("<font color='black'>Le nom du nouveau projet ne peux pas contenir d'espace, de ; de ', et ne peut pas être vide</font>");
    }
}

void MainWindow::addproject()
{
    labeltmp = new QLabel("Le nom du nouveau projet ne peux pas contenir d'espace, de ; de ', et ne peut pas être vide");
    QWidget *win = new QWidget();
    QLabel *Labeljeu = new QLabel("Name :");
    this->nametmp = new QLineEdit();

    Labeljeu->setAlignment(Qt::AlignTop);

    //Boutons
    buttontmp = new QPushButton("Valider");
    QPushButton *b_annuler = new QPushButton("Annuler");

    //Connexions aux slots
    connect(buttontmp, SIGNAL(clicked()), this, SLOT(addproject2()));
    connect(buttontmp, SIGNAL(clicked()), win, SLOT(close()));
    connect(b_annuler, SIGNAL(clicked()), win, SLOT(close()));

    //timer name error

    timertmp = new QTimer(this);
    connect(timertmp, SIGNAL(timeout()), this, SLOT(checkprojectname()));
    timertmp->start(10);

    //Layout
    QGroupBox *groupbox = new QGroupBox("");

    QGridLayout *layoutFormulaire = new QGridLayout();
    layoutFormulaire->addWidget(Labeljeu, 0, 0);
    layoutFormulaire->addWidget(this->nametmp, 0, 1);

    groupbox->setLayout(layoutFormulaire);

    QGridLayout *layout = new QGridLayout();
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(labeltmp, 1, 0, 1, 2);
    layout->addWidget(groupbox,2, 0, 1, 2, Qt::AlignTop);
    layout->addWidget(b_annuler, 3, 0, Qt::AlignLeft);
    layout->addWidget(buttontmp, 3, 1, Qt::AlignRight);
    //setLayout(layout);
    win->setLayout(layout);
    win->show();
    error = 0;
}

void MainWindow::addproject2()
{
    QSqlQuery qry;

    this->initvar();
    QRegExp regex("^[^,;' ]+$");
    QString name = nametmp->text();

    if (name.contains(regex) == 0)
    {
        if (timertmp)
        {
            delete timertmp;
            timertmp = NULL;
        }
        error = 1;
        addproject();
        return ;
    }

    if ( !qry.exec("CREATE TABLE IF NOT EXISTS project_" + this->nametmp->text() + "_project ("
                " id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                " firstname VARCHAR(30),"
                " lastname VARCHAR(30),"
                " email VARCHAR(90),"
                " groupid INTEGER,"
                " password VARCHAR(1024),"
                " refbool INT DEFAULT 0,"
                " questionbool INT DEfAULT 0,"
                " jour INT DEFAULT 0,"
                " Sugestion TEXT DEFAULT '')") )
        qDebug() << "create project" << qry.lastError();
    else
        qDebug() << "Table created!";

    qry.prepare(" CREATE TABLE IF NOT EXISTS project_" +  this->nametmp->text() + "_question ("
                " id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                " question VARCHAR(30),"
                " groupid INTEGER,"
                " type VARCHAR(30),"
                " note BOOLEAN DEFAULT 1,"
                " sujet TEXT,"
                " qgroupid INT DEFAULT 0,"
                " typef INT DEFAULT 0,"
                " ref_only INT DEFAULT 0,"
                " splitchar TEXT NOT NULL DEFAULT '',"
                " global BOOL NOT NULL DEFAULT 0,"
                " value INT NOT NULL DEFAULT 1,"
                " sujetesti TEXT,"
                " link INT NOT NULL DEFAULT -1)");
    if (!qry.exec())
        qDebug() << "create question" << qry.lastError();

    qry.prepare(" CREATE TABLE IF NOT EXISTS project_" +  this->nametmp->text() + "_groupe ("
                " id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                " groupname VARCHAR(500),"
                " groupparent INTEGER DEFAULT 0,"
                " type BOOLEAN DEFAULT 0,"
                " description TEXT NOT NULL DEFAULT '',"
                " gquestion INT DEFAULT 0)" );
    if (!qry.exec())
        qDebug() << "create groupe" << qry.lastError();

    qry.prepare(" CREATE TABLE IF NOT EXISTS project_" +  this->nametmp->text() + "_reponse ("
                " id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                " idperson INTEGER,"
                " name VARCHAR(100),"
                " time FLOAT,"
                " note INTEGER,"
                " date_info datetime,"
                " iteration INTEGER,"
                " str TEXT NOT NULL DEFAULT '',"
                " idquestion INT NOT NULL DEFAULT -1);" );
    if (!qry.exec())
        qDebug() << "create reponse" << qry.lastError();

    qry.prepare(" CREATE TABLE IF NOT EXISTS project_all_user ("
                " id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                " idperson INTEGER,"
                " email VARCHAR(90),"
                " password VARCHAR(1024),"
                " name_table VARCHAR(200),"
                " date_last_etude datetime,"
                " valid_code varchar(256),"
                " iteration INTEGER NOT NULL DEFAULT 0);" );
    if (!qry.exec())
        qDebug() << "create master table user" << qry.lastError();

    qry.prepare(" CREATE TABLE IF NOT EXISTS all_config ("
                " id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                " project_name VARCHAR(3000),"
                " default_table INTEGER NOT NULL DEFAULT 0);");
    if (!qry.exec())
        qDebug() << "create all config" << qry.lastError();

    qry.prepare(" CREATE TABLE IF NOT EXISTS all_etude ("
                " id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                " begin datetime NOT NULL DEFAULT NOW(),"
                " iteration INTEGER,"
                " groupid INTEGER NOT NULL DEFAULT 0,"
                " project_name VARCHAR(3000),"
                " ref BOOLEAN NOT NULL DEFAULT 0,"
                " iteration_detail TEXT,"
                " intro TEXT,"
                " mail TEXT);" );
    if (!qry.exec())
        qDebug() << "create etude" << qry.lastError();
    qry.prepare(" INSERT INTO all_config ("
                " project_name=?);" );
    if (!qry.exec(this->nametmp->text()))
        qDebug() << "insert all config" << qry.lastError();

    this->current.initoroject(this->nametmp->text());
    //this->current->projectshow(this, this->table, this->currentgref);
    this->namecurrent = this->nametmp->text();
    menu_projet->actions().at(3)->setEnabled(1);
    menu_projet->actions().at(4)->setEnabled(1);
    menu_outil->setEnabled(1);
    menu_affifchage->setEnabled(1);
    menu_serveur->setEnabled(1);
    menu_graphique->setEnabled(1);
    if (timertmp)
    {
        delete timertmp;
        timertmp = NULL;
    }
    this->configproject();
}


// open project


QString name_recuperator(QString str)
{
    QString ret = str.mid(8, str.size() - 16);

    return ret;
}

void MainWindow::openproject()
{
    QSqlQuery qry;
    QListWidget *listWidget = new QListWidget();

    listWidget->setWindowModality(Qt::ApplicationModal);
    if(qry.exec("SELECT table_name FROM INFORMATION_SCHEMA.TABLES WHERE table_name LIKE 'project_%_project'"))
    {
        while(qry.next())
        {
            listWidget->addItem(name_recuperator(qry.value(0).toString()));
        }
    }
    QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)),
                         listWidget, SLOT(close()));
    QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)),
                         this, SLOT(openproject2(QListWidgetItem *)));
    listWidget->show();

}

void MainWindow::openproject2(QListWidgetItem *item)
{
    QSqlQuery qry;

    this->initvar();
    //this->current.initoroject(item->text().toStdString());
//	this->current->projectshow(this, this->table, this->currentgref);
    this->namecurrent = item->text();
    this->updateproject();
    menu_projet->actions().at(3)->setEnabled(1);
    menu_projet->actions().at(4)->setEnabled(1);
    menu_outil->setEnabled(1);
    menu_affifchage->setEnabled(1);
    menu_serveur->setEnabled(1);
    menu_graphique->setEnabled(1);
    //this->addock();
}

void MainWindow::supproject()
{
    QSqlQuery qry;
    QListWidget *listWidget = new QListWidget();

    listWidget->setWindowModality(Qt::ApplicationModal);
    if(qry.exec("SELECT table_name FROM INFORMATION_SCHEMA.TABLES WHERE table_name LIKE 'project_%_project'"))
    {
        while(qry.next())
        {
            listWidget->addItem(name_recuperator(qry.value(0).toString()));
        }
    }
    QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)),
                         this, SLOT(supproject2(QListWidgetItem *)));
    QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)),
                         listWidget, SLOT(close()));
    listWidget->show();
}

void MainWindow::supproject2(QListWidgetItem *item)
{
    QSqlQuery qry;

    if (item->text().compare(namecurrent) == 0)
    {
        return ;
    }
    qry.prepare( "DROP TABLE project_" + item->text() + "_project;" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    qry.prepare( "DROP TABLE project_" + item->text() + "_question;" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    qry.prepare( "DROP TABLE project_" + item->text() + "_reponse;" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    qry.prepare( "DROP TABLE project_" + item->text() + "_groupe;" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    qry.prepare( "DROP TABLE project_" + item->text() + "_etude;" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
}

void MainWindow::addock()
{
    if (groupdock)
        delete groupdock;
    groupdock = new QDockWidget(this);
//    if (alltreetmp)  //sa fait planter je sais pas pk
//        delete alltreetmp;
    this->alltreetmp = new Alltree(this, &(this->current));
    groupdock->setWidget(this->alltreetmp);
    groupdock->show();
    addDockWidget(Qt::LeftDockWidgetArea, groupdock);
//	if (showmod == 0)
//		connect(this->groupboxtmp, SIGNAL(itemClicked(QTreeWidgetItem *, int )), this, SLOT(changescope2()));
//	if (showmod == 2)
//		connect(this->groupboxtmp, SIGNAL(itemClicked(QTreeWidgetItem *, int )), this, SLOT(changescopeq2()));
}



MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::mailperso()
//{
//    QList<person> listp =  this->current.getListallpfils(group);
//    QString body;
//    QSqlQuery qry;
//    body = "<html><p>Dear __%p__,</p>"
//           "<p>This is your daily DMI LEAD CHANGE Timeesheet reminder</p>"
//           "<p>Thank you for taking a few minutes at the end of your day to complete the timesheet:</p>"
//           "<a href=\"http://etudemurano.alwaysdata.net/" + str;

//    QList<person>::iterator i = listp.begin();
//    while (i != listp.end())
//    {
//        sendmail(i->email, body.replace("__%p__", i->firstname), type, qry.value('jour').toInt()) ; // OPTI
//        i++;
//    }
//}

// envoi des mail

void MainWindow::sendprojectauxi(QString str, QList<person> listp, int type)
{
    QString body;
    QString bodyend;
    QSqlQuery qry;
    if (type == 1)
    {
        body = "<p>Dear __%p__,</p>"
                "<p>During the kick-off, we’ve introduced you the methodology of the DMI Lead change  project.  Interview phase is over, we are now moving to the Timesheet phase.</p>"
                "<p>For the next 2 weeks : Monday, the 14th until Friday, the 25th of November, we are kindly asking to fill in your timesheet (see the link down below). This simple task will only take 5 minutes per day.</p>"
                "<p>The objective is to assess your day-to-day workload, and your perception about it :"
                "<ol><li>estimation of your workload on an annual basis (%)</li>"
                "<li>assessment of the time spent and perception of added-value on each task</li>"
                "<li>the actual time you spend on each task (daily basis-minutes)</li></ol></p>"
                "<p>Before filling in the timesheets, you will have to complete the -Estimation- part (items 1&2). The link below will drive you to the survey where you will find the -Estimation- form:</p>"
                "<a href=\"http://etudemurano.alwaysdata.net/" + str;
        bodyend = "\"><u>PPD_DMI LEAD CHANGE_Online Survey</u></a>"
                          "<p>If you encounter any difficulty or have for any question, you can contact me directly on:<ul><li>anais.deframond@muranoconseil.com</li><li>+33 770734938</li></ul></p>"
                          "<p>Thank you in advance for your time and involvement! <p/><p> Best regards,"
                          "<Br/>Anaïs de Framond for the MURANO Team</p>";

    }
    else
    {
        body = "<html><p>Dear __%p__,</p>"
                "<p>This is your daily DMI LEAD CHANGE Timeesheet reminder!</p>"
                       "<p>Thank you for taking a few minutes at the end of your day to complete the timesheet:</p>"
                       "<a href=\"http://etudemurano.alwaysdata.net/" + str;
        bodyend = "\"><u>PPD_DMI LEAD CHANGE_Online Survey</u></a></p>"
                          "<p>If you encounter any difficulty or have for any question, you can contact me directly on:<ul><li>anais.deframond@muranoconseil.com</li><li>+33 770734938</li></ul></p>"
                          "<p>Thank you and see you tomorrow!<Br /> Regards,</p>"
                           "<p>Anaïs for the MURANO Team</p>";

    }
//    QString body = "<p>Bonjour,</p><Br/>"
//                   "<p>Nous effectuons actuellement une mission pour le compte de votre société.</p>"
//                   "<p>Dans ce cadre, le cabinet Murano vous donne la parole !</p>"
//                   "<p>Merci de prendre quelques minutes de votre temps pour répondre à notre questionnaire :</p>"
//                   "<a href=\"etudemurano.alwaysdata.net/" + str;
//    QString bodyend = "\"><u>ACCEDER AU QUESTIONNAIRE</u></a></p>"
//                      "<p>Si vous avez des questions ou des difficultés avec le lien, n’hésitez pas à nous contacter.</p><Br/>"
//                      "<p>Nous vous remercions de votre participation !</p>"
//                      "<p>L’équipe MURAnO</p>";

    QList<person>::iterator i = listp.begin();
    while (i != listp.end())
    {
        qry.exec("SELECT questionbool FROM project_" + this->namecurrent + "_project WHERE id=" + QString::number(i->id) + ";");
        QString bodytmp = (body + "?p=" + QString::number(i->id) + "&s=" + namecurrent + bodyend);
        qry.next();
        sendmail(i->email, bodytmp.replace("__%p__", i->firstname), type, qry.value(0).toInt()) ; // OPTI
        i++;
    }
}

void MainWindow::sendproject(){emailvalidator *emailv = new emailvalidator(this, 0);emailv->show();}

void MainWindow::sendproject_ref(){emailvalidator *emailv = new emailvalidator(this, 1);emailv->show();}

void MainWindow::mailSent(QString status)
{
    (void)status;
}

//recuperation des donnee en ligne

void MainWindow::select_first_table()
{
    if (current.default_table == 0)
        afficherbasetable->trigger();
    if (current.default_table == 1)
        afficherpers->trigger();
    if (current.default_table == 2)
        afficherpers->trigger();
}

void MainWindow::updateproject()
{
    if (this->ov)
        affichergraphiquecompare->trigger();
    if (this->table)
        afficherbasetable->trigger();
    if (this->tableg)
        afficherglobalrep->trigger();
    if (this->tablep)
        afficherpers->trigger();
    if (this->crd)
        affichergraphiquecompare->trigger();

    this->current.initoroject(this->namecurrent);

    select_first_table();
    this->addock();

    if (this->current.getNbfactnref() == 0)
    {
        this->menu_affifchage->actions().at(0)->setVisible(0);
        afficherref->trigger();
    }
    else
        this->menu_affifchage->actions().at(0)->setVisible(1);
}

//void MainWindow::messageErreur(QNetworkReply::NetworkError)
//{
//	QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
//	QMessageBox::critical(this, "Erreur", "Erreur lors du chargement. Vérifiez votre connexion internet ou réessayez plus tard <br /><br /> Code de l'erreur : <br /><em>" + r->errorString() + "</em>");
//}

void MainWindow::extract_brutesimple()
{
    QSqlQuery qry;
    QWidget *w = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    listWidgettmp = new QListWidget();
    QPushButton *valider = new QPushButton();

    listWidgettmp->setWindowModality(Qt::ApplicationModal);
    if(qry.exec("SELECT table_name FROM INFORMATION_SCHEMA.TABLES WHERE table_name LIKE 'project_%_project'"))
    {
        while(qry.next())
        {
            QListWidgetItem* item = new QListWidgetItem(name_recuperator(qry.value(0).toString()), listWidgettmp);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
        }
    }
    QObject::connect(valider, SIGNAL(clicked(bool)), this, SLOT(extract_brutesimple2()));
    QObject::connect(valider, SIGNAL(clicked(bool)), w, SLOT(close()));
    layout->addWidget(listWidgettmp);
    layout->addWidget(valider);
    w->setLayout(layout);
    w->show();
    qDebug() << "sqjhd";
}

void MainWindow::extract_brutesimple2()
{
    QTableWidget *tmp = new QTableWidget();
    QSqlQuery qry;
    QString qry_prep;
    QListWidgetItem * item;
    int i = -1;
    int y = 0;

    while (item = listWidgettmp->item(++i))
    {
        qDebug() << item->text();
        qDebug() << "dsd";
        if (item->checkState())
        {
            qDebug() << "dsd 2";
            if (y)
                qry_prep += "UNION ";
            qry_prep += "SELECT groupe.groupname, firstname, lastname, iteration, date_info, qgroupe.groupname, question, time, str "
                        "FROM project_" + item->text() + "_reponse AS reponse, "
                        "project_" + item->text() + "_project AS person, "
                        "project_" + item->text() + "_question AS question, "
                        "project_" + item->text() + "_groupe AS qgroupe, "
                        "project_" + item->text() + "_groupe AS groupe "
                        "WHERE reponse.idperson = person.id "
                        "AND reponse.idquestion = question.id "
                        "AND question.qgroupid = qgroupe.id "
                        "AND person.groupid = groupe.id ";
            y++;
        }
    }
    qDebug() << qry_prep;
    if ( !qry.exec(qry_prep) )
        qDebug() << "qry table_brut_simple fail" << qry.lastError();
    else
        qDebug() << "qry table_brut_simple createf!";
    tmp->setRowCount(qry.numRowsAffected() + 2);
    tmp->setColumnCount(10);


    y = -1;
    while (qry.next())
    {
        tmp->setItem(++y, 0, new QTableWidgetItem(qry.value(0).toString()));
        tmp->setItem(y, 1, new QTableWidgetItem(qry.value(1).toString()));
        tmp->setItem(y, 2, new QTableWidgetItem(qry.value(2).toString()));
        tmp->setItem(y, 3, new QTableWidgetItem(qry.value(3).toString()));
        tmp->setItem(y, 4, new QTableWidgetItem(qry.value(4).toString()));
        tmp->setItem(y, 5, new QTableWidgetItem(qry.value(5).toString()));
        tmp->setItem(y, 6, new QTableWidgetItem(qry.value(6).toString()));
        tmp->setItem(y, 7, new QTableWidgetItem(qry.value(7).toString()));
        tmp->setItem(y, 8, new QTableWidgetItem(qry.value(8).toString()));
//        tmp->setItem(y, 10, new QTableWidgetItem(qry.value(9).toInt()));
    }
    //tmp->show();
    QString fichier = QFileDialog::getSaveFileName(this, "Destination", "Save", "Excell files (*.xlsx)");
    tab_to_fichier(fichier, tmp);
    delete listWidgettmp;
    delete tmp;
}

void MainWindow::convert_to_xlsx()
{
    tableshow * tmp = NULL;
    if (this->cw->currentWidget() == this->table)
        tmp = table;
    else if (this->cw->currentWidget() == this->tableg)
        tmp = tableg;
    else if (this->cw->currentWidget() == this->tablep)
        tmp = tablep;
    else
        warning("no table selected");
    QString fichier = QFileDialog::getSaveFileName(this, "Destination", "Save", "Excell files (*.xlsx)");
    if (tmp)
        tab_to_fichier(fichier, tmp);
    else
        //QMessageBox::Warning(this, tr("warning"), tr("aucun projet selectioné"));
        qDebug() << "no project selected";
}

void	MainWindow::modechange(bool checked)
{
    this->showmod = (checked) ? 1 : 0;
    this->updateproject();
}

void	MainWindow::refmodechange(bool checked)
{
    ref = (checked) ? 1 : 0;
    current.ref = ref;
    //this->table->updateall();
    emit refchanged(checked);
    this->table->showtable(currentgref, currentgqref);
}

void	MainWindow::valmodechange(bool checked)
{
    val = (checked) ? 1 : 0;
    current.val = val;
    emit valchanged(val);
}


void	MainWindow::baserep(bool checked)
{
    if (checked)
    {
        this->table = new tableshow(&(this->current), this, 0);
        this->table->showtable(this->currentgref, this->currentgqref);
        this->cw->addTab(table, "tableaux");
    }
    else if (table)
    {
        delete table;
        table = NULL;
    }
}


void	MainWindow::globalrep(bool checked)
{
    if (checked)
    {
        tableg = new tableshow(&(this->current), this, 2);
        tableg->select(currentgref, currentgqref);
        cw->addTab(tableg, "Tableau global");
    }
    else if (tableg)
    {
        delete tableg;
        tableg = NULL;
    }
}

void	MainWindow::personrep(bool checked)
{
    if (checked)
    {
        tablep = new tableshow(&(this->current), this, 1);
        tablep->select(currentgref, currentgqref);
        cw->addTab(tablep, "Tableau individuel");
    }
    else if (tablep)
    {
        delete tablep;
        tablep = NULL;
    }
}

void MainWindow::graphiquecrd(bool checked)
{
    if (checked)
    {
        this->crd = new Comparrefdo(this, 0);
        this->cw->addTab(this->crd, "Comparaison reference donnée");
    }
    else if (crd)
    {
        delete crd;
        crd = NULL;
    }
}

void	MainWindow::changescope2(QTreeWidgetItem *item)
{
    grouptreeitem *tmp;

    if ((tmp = dynamic_cast<grouptreeitem*>(item)) != NULL)
    {
        this->currentgref = tmp->getId();
        this->current.gref = this->currentgref;
        emit grefchange(currentgref);
//		this->showproject();
    }
}

void	MainWindow::changescopeq2(QTreeWidgetItem *item)
{
    grouptreeitem *tmp;

    if ((tmp = dynamic_cast<grouptreeitem*>(item)) != NULL)
    {
        this->currentgqref = tmp->getId();
        this->current.gqref = this->currentgqref;
        emit gqrefchange(currentgqref);
//		this->showproject();
    }
}

void	MainWindow::showbarchartref()
{
//	d_chart = new barref(NULL, this->current);
//	d_chart->show();
}

void MainWindow::updatetable()
{
    if (table)
    {
        table->reinit(&(current), this);
        table->showtable(currentgref, currentgqref);
    }
}

void	MainWindow::configproject(){menuconfigproject *m = new menuconfigproject(this->namecurrent, &(this->current), this);m->show();}

void	MainWindow::configsondage(){menusondage *m = new menusondage(this);m->show();}

void	MainWindow::screenshootcurrent()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (const QWindow *window = windowHandle())
        screen = window->screen();
    if (!screen)
        qDebug() << "screen init fail";
    QPixmap pixmap = QPixmap();
    pixmap = screen->grabWindow(this->centralWidget()->winId());

    const QString format = "png";
        QString initialPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        if (initialPath.isEmpty())
            initialPath = QDir::currentPath();
        initialPath += tr("/untitled.") + format;

        QFileDialog fileDialog(this, tr("Save As"), initialPath);
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        fileDialog.setFileMode(QFileDialog::AnyFile);
        fileDialog.setDirectory(initialPath);
        QStringList mimeTypes;
        foreach (const QByteArray &bf, QImageWriter::supportedMimeTypes())
            mimeTypes.append(QLatin1String(bf));
        fileDialog.setMimeTypeFilters(mimeTypes);
        fileDialog.selectMimeTypeFilter("image/" + format);
        fileDialog.setDefaultSuffix(format);
        if (fileDialog.exec() != QDialog::Accepted)
            return;
        const QString fileName = fileDialog.selectedFiles().first();
        if (!pixmap.save(fileName))
        {
        //	QMessageBox::warning(this, tr("Save Error"), tr("The image could not be saved to \"%1\".")
        //						 .arg(QDir::toNativeSeparators(fileName)));
            qDebug() << tr("The image could not be saved to \"%1\".").arg(QDir::toNativeSeparators(fileName));
        }
}

void    MainWindow::maxiterationchange(int max)
{
    this->iterationmax = max;
    this->current.iterationmax = max;
    emit maxiterationchanged(max);
}

void    MainWindow::miniterationchange(int min)
{
    this->iterationmin = min;
    this->current.iterationmin = min;
    emit miniterationchanged(min);
}

void	MainWindow::Backroundchange()
{
    QString file = QFileDialog::getSaveFileName(this, "Choisiser une nouvelle image", "~", "Image (*.png)");
    Uploader u;

    u.start(file);
//	QProgressDialog progress("Copying files...", "Abort Copy", 0, u., this);
//	progress.setWindowModality(Qt::WindowModal);

//	for (int i = 0; i < numFiles; i++)
//	{
//		progress.setValue(i);

//		if (progress.wasCanceled())
//			break;
//		... copy one file
//	}
//	progress.setValue(numFiles);
}


void MainWindow::extractor()
{
    tableau_brut *extract = new tableau_brut(&(this->current));
    tab_to_fichier("Save_donne_brute_2.0_18nov.xlsx", extract);
}

void MainWindow::formcreator()
{

}

void MainWindow::suivirep()
{
    QTableWidget *w = new QTableWidget(current.getNbperson() + 1, current.iterationmax + 2);
    vector<person>::iterator itp = current.listp.begin();
    int y = -1;
    int i = -1;
    int *counter2 = new int[current.iterationmax + 2];
    int counter;
    float tmp;
    float counter3 = 0;
    memset(counter2, 0, sizeof(int) * current.iterationmax + 2);

    while (++i < current.iterationmax + 1)
        w->setHorizontalHeaderItem(i, new QTableWidgetItem("jour " + QString::number(i)));
    w->setHorizontalHeaderItem(i, new QTableWidgetItem("Taux de réponse"));
    while (itp != current.listp.end())
    {
        if (itp->id == -1)
        {
            itp++;
            continue ;
        }
        w->setVerticalHeaderItem(++y, new QTableWidgetItem(itp->name));
        i = -1;
        counter = 0;
        while (++i < current.iterationmax + 1)
            w->setItem(y, i, new QTableWidgetItem(itp->time_rep_at_iteration(i, &counter, &(counter2[i]))));
        tmp = (float)counter / (float)(itp->questionbool + 1);
        counter3 += tmp;
        w->setItem(y, i, new QTableWidgetItem(QString::number(tmp * 100) + "%"));
        itp++;
    }

    w->setVerticalHeaderItem(++y, new QTableWidgetItem("taux de réponse"));
    i = -1;
    while (++i < current.iterationmax + 1)
        w->setItem(y, i, new QTableWidgetItem(QString::number((float)counter2[i] / (float)current.getNbperson() * 100) + "%"));
    w->setItem(y, i, new QTableWidgetItem(QString::number(counter3 / (float)current.getNbperson() * 100) + "%"));

    w->resizeColumnsToContents();
    w->resizeRowsToContents();
//    w->setSortingEnabled(true);
    w->show();
    delete[] counter2;
}

QTXLSX_USE_NAMESPACE
void MainWindow::Excellinfo()
{
    vector<person>::iterator it = this->current.listp.begin();
    Document xlsx;
    int y = 0;

    xlsx.write(++y, 1, "firstname");
    xlsx.write(y, 2, "lastname");
    xlsx.write(y, 3, "email");
    xlsx.write(y, 4, "id");
    xlsx.write(y, 5, "project");

    while (it != this->current.listp.end())
    {
        if (it->id == -1)
        {
            it++;
            continue ;
        }
        xlsx.write(++y, 1, it->firstname);
        xlsx.write(y, 2, it->lastname);
        xlsx.write(y, 3, it->email);
        xlsx.write(y, 4, it->id);
        xlsx.write(y, 5, namecurrent);
        it++;
    }
    xlsx.saveAs("infoperson.xlsx");
}
