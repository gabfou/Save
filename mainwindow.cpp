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
    QAction *preview = menu_outil->addAction("&Preview");
    QObject::connect(preview, SIGNAL(triggered()), this, SLOT(affichepreview()));
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

	QToolBar *toolBarFichier = addToolBar("Fichier");
	QAction *screenshoot = toolBarFichier->addAction("&Imprimer écran");
	QObject::connect(screenshoot, SIGNAL(triggered()), this, SLOT(screenshootcurrent()));

	menu_projet->actions().at(3)->setEnabled(0);
	menu_projet->actions().at(4)->setEnabled(0);
	menu_outil->setEnabled(0);
	menu_affifchage->setEnabled(0);
	menu_serveur->setEnabled(0);
    menu_graphique->setEnabled(0);
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

void MainWindow::addproject() // empecher charactere speciaux
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

	QRegExp regex("^[^,;' ]+$");
	QString name = nametmp->text();

	if (name.contains(regex) == 0)
	{
		if (timertmp)
		{
			delete timertmp;
			timertmp == NULL;
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
		timertmp == NULL;
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

	//this->current.initoroject(item->text().toStdString());
	this->currentgref = 0;
	this->currentgqref = 0;
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
//	if (showmod == 0)
//		this->groupboxtmp = new grouptree(this, this->current->listgroup); // a virer
//	if (showmod == 2)
//		this->groupboxtmp = new grouptree(this, this->current->listqgroup); // a virer
//	this->groupboxtmp();
	this->alltreetmp = new Alltree(this, &(this->current));
	groupdock->setWidget(this->alltreetmp);
	groupdock->show();
	addDockWidget(Qt::LeftDockWidgetArea, groupdock);
//	if (showmod == 0)
//		connect(this->groupboxtmp, SIGNAL(itemClicked(QTreeWidgetItem *, int )), this, SLOT(changescope2()));
//	if (showmod == 2)
//		connect(this->groupboxtmp, SIGNAL(itemClicked(QTreeWidgetItem *, int )), this, SLOT(changescopeq2()));
}

//ajout de collaborateur

void MainWindow::addperson()
{
	QWidget *win = new QWidget();
	QLabel *Labelnoms = new QLabel("Noms :");
	this->nametmp = new QLineEdit;
	Labelnoms->setAlignment(Qt::AlignTop);
	QLabel *Labelprenoms = new QLabel("Prenoms");
	this->prenametmp = new QLineEdit;
	Labelprenoms->setAlignment(Qt::AlignTop);
	QLabel *Labelemail = new QLabel("Email :");
	this->emailtmp = new QLineEdit;
	Labelemail->setAlignment(Qt::AlignTop);
	QLabel *Labelgroup = new QLabel("Groupe :");
	this->groupboxtmp = new grouptree(this, this->current.listgroup);
	Labelgroup->setAlignment(Qt::AlignTop);

	//Boutons
	QPushButton *b_valider = new QPushButton("Valider");
	QPushButton *b_annuler = new QPushButton("Fermer");

	//Connexions aux slots
	connect(b_valider, SIGNAL(clicked()), this, SLOT(addperson2()));
	connect(b_annuler, SIGNAL(clicked()), win, SLOT(close()));

	//Layout
	QGroupBox *groupbox = new QGroupBox("Nouveaux collaborateur");

	QGridLayout *layoutFormulaire = new QGridLayout();
	layoutFormulaire->addWidget(Labelnoms, 0, 0);
	layoutFormulaire->addWidget(this->nametmp, 0, 1);
	layoutFormulaire->addWidget(Labelprenoms, 1, 0);
	layoutFormulaire->addWidget(this->prenametmp, 1, 1);
	layoutFormulaire->addWidget(Labelemail, 2, 0);
	layoutFormulaire->addWidget(this->emailtmp, 2, 1);
	layoutFormulaire->addWidget(Labelgroup, 3, 0);
	layoutFormulaire->addWidget(this->groupboxtmp, 3, 1);

	groupbox->setLayout(layoutFormulaire);

	QGridLayout *layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);
	layout->addWidget(groupbox, 0, 0, 1, 2, Qt::AlignTop);
	layout->addWidget(b_annuler, 1, 0, Qt::AlignLeft);
	layout->addWidget(b_valider, 1, 1, Qt::AlignRight);
	win->setLayout(layout);
	win->show();
}

void MainWindow::addperson2()
{
	QSqlQuery qry;
	char mdp[7];

	gen_random(mdp, 6);
	QString mdphash = "poke";
	mdphash += mdp;
	mdphash += "mon";
	qry.prepare( "INSERT INTO project_" + this->namecurrent + "_project (groupid, firstname , lastname , email , password) VALUES ( ? , ? , ? , ? , ? );" );
	qry.addBindValue(QString::number(dynamic_cast<grouptreeitem*>(this->groupboxtmp->currentItem())->getId()));
	qry.addBindValue(this->nametmp->text());
	qry.addBindValue(this->prenametmp->text());
	qry.addBindValue(this->emailtmp->text());
	qry.addBindValue(QCryptographicHash::hash(mdphash.toUtf8(), QCryptographicHash::Sha384).toHex());
	if(!qry.exec() )
		qDebug() << qry.lastError();
	else
	{
		qDebug() << "INSERT success!";
		this->current.addperson(this->nametmp->text(), this->prenametmp->text(), this->emailtmp->text());
	}
}



MainWindow::~MainWindow()
{
	delete ui;
}

// envoi des mail


void MainWindow::sendprojectauxi(QString str, QList<person> listp)
{
    QString body = "<html><p>Hello __%p__,</p>"
                   "<p>During the kick-off meeting, we shared with you the phasing of the project. After the interview step, we are now launching the Time-Sheet phase.</p>"
                   "<p>The main objective of this second phase is to assess your day-to-day workload and evaluate the perception you have on it.</p>"
                   "<p>It will take you 5 minutes per day to fill it, during 2 weeks (from Monday, the14th until Friday, the 25th of November). We will send you a reminder email everyday.</p>"
                   "<p>First of all, you will need you to fill the Estimation part, here is the link bellow:</p>"
                   "<a href=\"http://etudemurano.alwaysdata.net/" + str;
    QString bodyend = "\"><u>PPD_DMI LEAD CHANGE_Online Survey</u></a></p>"
                      "<p>For you information: you cannot start filling the everyday Time-sheet if you don’t  have answered this Estimation part. So please fill it as soon as possible. Thank you.</p><Br/>"
                      "<p>If you encounter any difficulty or have for any question, you can contact me directly on:<br />anais.deframond@muranoconseil.com <br /> +33 770734938</p>"
                      "<p>Thank you in advance for your time and involvement! <Br /> Best regards,</p>";
                      "<p>Anaïs de Framond for the MURANO Team</p>";
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
        QString bodytmp = (body + "?p=" + QString::number(i->id) + "&s=" + namecurrent + bodyend);
        sendmail(i->email, bodytmp.replace("__%p__", i->firstname)) ; // OPTI
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

void MainWindow::convert_to_xlsx()
{
	tableshow * tmp;
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
//		//... copy one file
//	}
//	progress.setValue(numFiles);
}
