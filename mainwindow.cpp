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
#include "misc/emailvalidator.h"
#include "misc/menugestionjour.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) // initialization
{
    ui->setupUi(this);
    this->cw = new QTabWidget();
    this->setCentralWidget(cw);
    this->setWindowTitle("Outils sondage");

    this->resize(1000, 600);

    // on creer la premiere conection

    createConnection();

    // mise en place du timer qui verifie qu'on est encore connecté

    QTimer *sqlco = new QTimer(this);
    connect(sqlco, SIGNAL(timeout()), this, SLOT(checksqlconexion()));
    sqlco->start(10000);

    // initialisation des menu

    menu_projet = menuBar()->addMenu("&Projet");
    QAction *new_projet = menu_projet->addAction("&Nouveaux");
    QObject::connect(new_projet, SIGNAL(triggered()), this, SLOT(addproject()));
    QAction *open_projet = menu_projet->addAction("Ouvrir");
    QObject::connect(open_projet, SIGNAL(triggered()), this, SLOT(openproject()));
    QAction *sup_projet = menu_projet->addAction("Supprimer projet");
    QObject::connect(sup_projet, SIGNAL(triggered()), this, SLOT(supproject()));
    QAction *configp = menu_projet->addAction("&Configuration projet");
    QObject::connect(configp, SIGNAL(triggered()), this, SLOT(configproject()));

    menu_outil = menuBar()->addMenu("&Outils");
    QAction *xlsx_convert = menu_outil->addAction("&Convertir en xlsx");
    QObject::connect(xlsx_convert, SIGNAL(triggered()), this, SLOT(convert_to_xlsx()));
    QAction *brute = menu_outil->addAction("&Extraire les donnée brute en xlsx");
    QObject::connect(brute, SIGNAL(triggered()), this, SLOT(extract_brutesimple()));

    menu_affifchage = menuBar()->addMenu("&Affichage");
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

    menu_serveur = menuBar()->addMenu("&Serveur et mail");
    QAction *config_sondage = menu_serveur->addAction("&Programer une série de sondage");
    QObject::connect(config_sondage, SIGNAL(triggered()), this, SLOT(configsondage()));
    QAction *suivirepa = menu_serveur->addAction("&suivi des réponse");
    QObject::connect(suivirepa, SIGNAL(triggered()), this, SLOT(suivirep()));
    QAction *Gestionjour = menu_serveur->addAction("&Gestion des jour");
    QObject::connect(Gestionjour, SIGNAL(triggered()), this, SLOT(gestionjour()));

    QToolBar *toolBarFichier = addToolBar("Fichier");
    QAction *screenshoot = toolBarFichier->addAction("&Imprimer écran");
    QObject::connect(screenshoot, SIGNAL(triggered()), this, SLOT(screenshootcurrent()));
    QAction *infoperson = menu_serveur->addAction("&Excell Info");
    QObject::connect(infoperson, SIGNAL(triggered()), this, SLOT(Excellinfo()));

    //on grise les menu au quelle on doit pas acceder en attendant d'ouvrir un projet

    menu_projet->actions().at(3)->setEnabled(0);
    menu_outil->setEnabled(0);
    menu_affifchage->setEnabled(0);
    menu_serveur->setEnabled(0);
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

//menu d'ajout de projet

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

//menu d'ajout de projet phase 2

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
                " question VARCHAR(100),"
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
    qry.prepare(" INSERT INTO all_config (project_name) VALUES ( ? );" );
    qry.addBindValue(this->nametmp->text());
    if (!qry.exec())
        qDebug() << "insert all config" << qry.lastError();

    this->current.initoroject(this->nametmp->text());
    //this->current->projectshow(this, this->table, this->currentgref);
    this->namecurrent = this->nametmp->text();
    menu_projet->actions().at(3)->setEnabled(1);
    menu_outil->setEnabled(1);
    menu_affifchage->setEnabled(1);
    menu_serveur->setEnabled(1);
    //menu_graphique->setEnabled(1);
    if (timertmp)
    {
        delete timertmp;
        timertmp = NULL;
    }
    this->configproject();
}

QString name_recuperator(QString str)
{
    QString ret = str.mid(8, str.size() - 16);

    return ret;
}

// menu d'ouverture de project

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

// menu d'ouverture de project phase 2

void MainWindow::openproject2(QListWidgetItem *item)
{
    QSqlQuery qry;

    this->initvar();
    this->namecurrent = item->text();
    this->updateproject();
    menu_projet->actions().at(3)->setEnabled(1);
    menu_outil->setEnabled(1);
    menu_affifchage->setEnabled(1);
    menu_serveur->setEnabled(1);
    //menu_graphique->setEnabled(1);
    //this->addock();
}
// menu de supression de project

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

// menu de supression de project phase 2

void MainWindow::supproject2(QListWidgetItem *item)
{
    strtmp = item->text();
    QWidget *win = new QWidget();
    QGridLayout *layout = new QGridLayout(win);
    QPushButton *oui = new QPushButton("Oui", win);
    QPushButton *non = new QPushButton("Non", win);

    layout->addWidget(new QLabel("Voulez vous supprimer définitivement le projet " + strtmp + "?"), 0, 0, 1, 2);
    layout->addWidget(oui, 1, 0, 1, 1);
    layout->addWidget(non, 1, 1, 1, 1);
    connect(oui, SIGNAL(clicked(bool)), this, SLOT(supproject3()));
    connect(oui, SIGNAL(clicked(bool)), win, SLOT(close()));
    connect(non, SIGNAL(clicked(bool)), win, SLOT(close()));
    win->show();
}

// menu de supression de project phase 3

void MainWindow::supproject3()
{
    QSqlQuery qry;

    if (strtmp.compare(namecurrent) == 0)
    {
        return ;
    }
    qry.prepare( "DROP TABLE project_" + strtmp + "_project;" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    qry.prepare( "DROP TABLE project_" + strtmp + "_question;" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    qry.prepare( "DROP TABLE project_" + strtmp + "_reponse;" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    qry.prepare( "DROP TABLE project_" + strtmp + "_groupe;" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    qry.prepare( "DROP TABLE project_" + strtmp + "_etude;" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
}

// ajout du menu de gauche (groupe personne iteration)

void MainWindow::addock()
{
    if (groupdock)
        delete groupdock;
    groupdock = new QDockWidget(this);
    this->alltreetmp = new Alltree(this, &(this->current));
    groupdock->setWidget(this->alltreetmp);
    groupdock->show();
    addDockWidget(Qt::LeftDockWidgetArea, groupdock);
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
                "<a href=\"http://muranoconseil.com/survey/" + str;
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

void MainWindow::gestionjour()
{
    menugestionjour *tmp = new menugestionjour(this);
    tmp->setWindowModality(Qt::ApplicationModal);
    tmp->show();
}

void MainWindow::sendproject(){emailvalidator *emailv = new emailvalidator(this, 0);emailv->show();}

void MainWindow::sendproject_ref(){emailvalidator *emailv = new emailvalidator(this, 1);emailv->show();}

void MainWindow::mailSent(QString status)
{
    (void)status;
}

void MainWindow::select_first_table()
{
    if (current.default_table == 0)
        afficherbasetable->trigger();
    if (current.default_table == 1)
        afficherpers->trigger();
    if (current.default_table == 2)
        afficherpers->trigger();
}

//demande de mise a jour de l'affichage (valeur a l'interieur des tableaux)

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
}

// menu d'extraction des données sql brute

void MainWindow::extract_brutesimple()
{
    QSqlQuery qry;
    QWidget *w = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    listWidgettmp = new QListWidget();
    QPushButton *valider = new QPushButton("Valider");

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
}

// menu d'extraction des données sql brute phase 2

void MainWindow::extract_brutesimple2()
{
    QTableWidget *tmp = new QTableWidget();
    QSqlQuery qry;
    QString qry_prep;
    QListWidgetItem * item;
    int i = -1;
    int y = 0;

    // creation du tableaux

    while ((item = listWidgettmp->item(++i)))
    {
        if (item->checkState())
        {
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
    if ( !qry.exec(qry_prep) )
        qDebug() << "qry table_brut_simple fail" << qry.lastError();
    else
        qDebug() << "qry table_brut_simple created!";
    tmp->setRowCount(qry.numRowsAffected() + 2);
    tmp->setColumnCount(10);

    tmp->setItem(++y, 0, new QTableWidgetItem("groupe"));
    tmp->setItem(y, 1, new QTableWidgetItem("firstname"));
    tmp->setItem(y, 2, new QTableWidgetItem("lastname"));
    tmp->setItem(y, 3, new QTableWidgetItem("iteration"));
    tmp->setItem(y, 4, new QTableWidgetItem("date_info"));
    tmp->setItem(y, 5, new QTableWidgetItem("groupe question"));
    tmp->setItem(y, 6, new QTableWidgetItem("question"));
    tmp->setItem(y, 7, new QTableWidgetItem("reponse nombre"));
    tmp->setItem(y, 8, new QTableWidgetItem("reponse texte"));
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
    }
    QString fichier = QFileDialog::getSaveFileName(this, "Destination", "Save", "Excell files (*.xlsx)");

    // conversion du tableau em xlsx

    tab_to_fichier(fichier, tmp);
    delete listWidgettmp;
    delete tmp;
}

// conversion du tableaux actuel en xlsx

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
        warning("aucun projet selectioné");
}

void	MainWindow::modechange(bool checked)
{
    this->showmod = (checked) ? 1 : 0;
    this->updateproject();
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
        this->table->showtable(this->currentgref, this->currentgqref, iterationmin, iterationmax);
        this->cw->addTab(table, "tableaux");
    }
    else if (table)
    {
        delete table;
        table = NULL;
    }
}


// ajout des different tableaux de donner a la fenetre principale

void	MainWindow::globalrep(bool checked)
{
    if (checked)
    {
        tableg = new tableshow(&(this->current), this, 2);
        tableg->select(currentgref, currentgqref, iterationmin, this->iterationmax);
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
        tablep->select(currentgref, currentgqref, iterationmin, iterationmax);
        cw->addTab(tablep, "Tableau individuel");
    }
    else if (tablep)
    {
        delete tablep;
        tablep = NULL;
    }
}

// ajout du graphique (pas utilisé)

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

// changement du groupe de personne pris en compte

void	MainWindow::changescope2(QTreeWidgetItem *item)
{
    grouptreeitem *tmp;

    if ((tmp = dynamic_cast<grouptreeitem*>(item)) != NULL)
    {
        this->currentgref = tmp->getId();
        this->current.gref = this->currentgref;
        emit grefchange(currentgref);
    }
}

// changement du groupe de question pris en compte

void	MainWindow::changescopeq2(QTreeWidgetItem *it`em)
{
    grouptreeitem *tmp;

    if ((tmp = dynamic_cast<grouptreeitem*>(item)) != NULL)
    {
        this->currentgqref = tmp->getId();
        this->current.gqref = this->currentgqref;
        emit gqrefchange(currentgqref);
    }
}

// anci

void MainWindow::updatetable()
{
    if (table)
    {
        table->reinit(&(current), this);
        table->showtable(currentgref, currentgqref, iterationmin, iterationmax);
    }
}

// ouvre le menu de config general

void	MainWindow::configproject(){menuconfigproject *m = new menuconfigproject(this->namecurrent, &(this->current), this);m->show();}

// ouvre le menu de configuration des sondage

void	MainWindow::configsondage(){menusondage *m = new menusondage(this);m->show();}

// prend une capture d ecran de la fenetre courante

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
            warning(tr("The image could not be saved to \"%1\".").arg(QDir::toNativeSeparators(fileName)));
}

// change le l'iteration max pris en compte

void    MainWindow::maxiterationchange(int max)
{
    this->iterationmax = max;
    this->current.iterationmax = max;
    emit maxiterationchanged(max);
}

// change le l'iteration min pris en compte

void    MainWindow::miniterationchange(int min)
{
    this->iterationmin = min;
    this->current.iterationmin = min;
    emit miniterationchanged(min);
}

// void	MainWindow::Backroundchange()
// {
//     QString file = QFileDialog::getSaveFileName(this, "Choisiser une nouvelle image", "~", "Image (*.png)");
//     Uploader u;

//     u.start(file);
// //	QProgressDialog progress("Copying files...", "Abort Copy", 0, u., this);
// //	progress.setWindowModality(Qt::WindowModal);

// //	for (int i = 0; i < numFiles; i++)
// //	{
// //		progress.setValue(i);

// //		if (progress.wasCanceled())
// //			break;
// //		... copy one file
// //	}
// //	progress.setValue(numFiles);
// }

// extraction brut

void MainWindow::extractor()
{
    tableau_brut *extract = new tableau_brut(&(this->current));
    tab_to_fichier("Save_donne_brute_2.0_18nov.xlsx", extract);
}

void MainWindow::formcreator()
{

}

// ouvre le menu du suivi des reponses

void MainWindow::suivirep()
{
    QTableWidget *w = new QTableWidget(current.getNbperson() + 1, current.iterationmax + 2);
    vector<person>::iterator itp = current.listp.begin();
    int y = -1;
    int i = -1;
    int *counter2 = new int[current.questionboolmax + 2];
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
        w->setItem(y, i, new QTableWidgetItem(QString::number(tmp * 100, 'g',  4) + "%"));
        itp++;
    }

    w->setVerticalHeaderItem(++y, new QTableWidgetItem("taux de réponse"));
    i = -1;
    while (++i < current.iterationmax + 1)
        w->setItem(y, i, new QTableWidgetItem(QString::number((float)counter2[i] / (float)current.getNbperson() * 100, 'g', 4) + "%"));
    w->setItem(y, i, new QTableWidgetItem(QString::number(counter3 / (float)current.getNbperson() * 100) + "%", 4));

    w->resizeColumnsToContents();
    w->resizeRowsToContents();
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
    QString fichier = QFileDialog::getSaveFileName(this, "Destination", "Save", "Excell files (*.xlsx)");
    xlsx.saveAs(fichier);
}
