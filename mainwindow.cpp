#include "mainwindow.h"
#include "smtp.h"
#include <QMessageBox>
#include "data/project.h"
#include "grouptree.h"
#include "barref.h"
#include "config/menuconfigproject.h"
#include "grouptreeitem.h"
#include "tableclass/tableshow.h"
#include "overview.h"
#include "alltree.h"
#include "config/menuconfigsondage.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	string comande;

	ui->setupUi(this);
	this->cw = new QTabWidget();
	this->setCentralWidget(cw);
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
//	QAction *barchartref = menu_outil->addAction("&Graphique comparaison reference-donnée");
//	QObject::connect(barchartref, SIGNAL(triggered()), this, SLOT(showbarchartref()));

	menu_affifchage = menuBar()->addMenu("&Affichage");
	QAction *afficherref = menu_affifchage->addAction("&Données de références");
	afficherref->setCheckable(true);
	afficherref->setChecked(false);
	QObject::connect(afficherref, SIGNAL(toggled(bool)), this, SLOT(refmodechange(bool)));
	QAction *afficherval = menu_affifchage->addAction("&Ponderation");
	afficherval->setCheckable(true);
	afficherval->setChecked(false);
	QObject::connect(afficherval, SIGNAL(toggled(bool)), this, SLOT(valmodechange(bool)));
	QAction *afficherglobalrep = menu_affifchage->addAction("&generer le tableaux global");
	afficherglobalrep->setCheckable(true);
	afficherglobalrep->setChecked(false);
	QObject::connect(afficherglobalrep, SIGNAL(toggled(bool)), this, SLOT(globalrep(bool)));
	QAction *afficherpers = menu_affifchage->addAction("&generer le tableaux individuel");
	afficherpers->setCheckable(true);
	afficherpers->setChecked(false);
	QObject::connect(afficherpers, SIGNAL(toggled(bool)), this, SLOT(personrep(bool)));

	menu_serveur = menuBar()->addMenu("&Serveur");
	QAction *config_sondage = menu_serveur->addAction("&nouveaux sondage");
	QObject::connect(config_sondage, SIGNAL(triggered()), this, SLOT(configsondage()));

	QToolBar *toolBarFichier = addToolBar("Fichier");
	QAction *screenshoot = toolBarFichier->addAction("&Imprimer écran");
	QObject::connect(screenshoot, SIGNAL(triggered()), this, SLOT(screenshootcurrent()));

	menu_projet->actions().at(2)->setEnabled(0);
	menu_projet->actions().at(3)->setEnabled(0);
	menu_outil->setEnabled(0);
	menu_affifchage->setEnabled(0);
	menu_serveur->setEnabled(0);
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

void MainWindow::addproject() // empecher charactere speciaux
{
	QLabel *description = new QLabel("Le nom du nouveau projet ne peux pas contenir d'espace, de ; et '");
	QWidget *win = new QWidget();
	QLabel *Labeljeu = new QLabel("Name :");
	this->nametmp = new QLineEdit;
	Labeljeu->setAlignment(Qt::AlignTop);

	//Boutons
	QPushButton *b_valider = new QPushButton("Valider");
	QPushButton *b_annuler = new QPushButton("Annuler");

	//Connexions aux slots
	connect(b_valider, SIGNAL(clicked()), this, SLOT(addproject2()));
	connect(b_valider, SIGNAL(clicked()), win, SLOT(close()));
	connect(b_annuler, SIGNAL(clicked()), win, SLOT(close()));

	//Layout
	QGroupBox *groupbox = new QGroupBox("");

	QGridLayout *layoutFormulaire = new QGridLayout();
	layoutFormulaire->addWidget(Labeljeu, 0, 0);
	layoutFormulaire->addWidget(this->nametmp, 0, 1);

	groupbox->setLayout(layoutFormulaire);

	QGridLayout *layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);
	layout->addWidget(description, 0, 0, 1, 2);
	layout->addWidget(groupbox, 1, 0, 1, 2, Qt::AlignTop);
	layout->addWidget(b_annuler, 2, 0, Qt::AlignLeft);
	layout->addWidget(b_valider, 2, 1, Qt::AlignRight);
	//setLayout(layout);
	win->setLayout(layout);
	win->show();
}

void MainWindow::addproject2()
{
	QSqlQuery qry;

	if( !qry.exec("CREATE TABLE IF NOT EXISTS project_" + this->nametmp->text() + "_project ("
				" id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
				" firstname VARCHAR(30),"
				" lastname VARCHAR(30),"
				" email VARCHAR(90),"
				" groupid INTEGER,"
				" password VARCHAR(1024),"
				" refbool BOOLEAN DEFAULT 0,"
				" questionbool BOOLEAN DEfAULT 0)") )
		qDebug() << "create project" << qry.lastError();
	else
		qDebug() << "Table created!";

	qry.prepare( ("CREATE TABLE IF NOT EXISTS project_" +  this->nametmp->text() + "_question ("
				" id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
				" question VARCHAR(30),"
				" groupid INTEGER,"
				" type VARCHAR(30),"
				" note BOOLEAN DEFAULT 1,"
				" sujet VARCHAR(300),"
				" qgroupid INT DEFAULT 0,"
				" typef INT DEFAULT 0,"
				" ref_only INT DEFAULT 0,"
				" splitchar VARCHAR(3000) NOT NULL DEFAULT '',"
				" global BOOL NOT NULL DEFAULT 0,"
				" value INT NOT NULL DEFAULT -1)") );
	if(!qry.exec())
		qDebug() << "create question" << qry.lastError();

	qry.prepare( "CREATE TABLE IF NOT EXISTS project_" +  this->nametmp->text() + "_groupe ("
				" id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
				" groupname VARCHAR(500),"
				" groupparent INTEGER DEFAULT 0,"
				" type BOOLEAN DEFAULT 0,"
				" description VARCHAR(300) NOT NULL DEFAULT '',"
				" gquestion INT DEFAULT 0)" );
	if(!qry.exec())
		qDebug() << "create groupe" << qry.lastError();

	qry.prepare( "CREATE TABLE IF NOT EXISTS project_" +  this->nametmp->text() + "_reponse ("
				" id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
				" idperson INTEGER,"
				" name VARCHAR(100),"
				" time INTEGER,"
				" note INTEGER,"
				" date_info datetime,"
				" iteration INTEGER,"
				" str VARCHAR(100) NOT NULL DEFAULT '',"
				" idquestion INT NOT NULL DEFAULT -1);" );
	if(!qry.exec())
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
	if(!qry.exec())
		qDebug() << "create master table user" << qry.lastError();

	qry.prepare(" CREATE TABLE IF NOT EXISTS project_" +  this->nametmp->text() + "_etude ("
				" id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
				" begin datetime NOT NULL DEFAULT NOW(),"
				" iteration INTEGER,"
				" groupid INTEGER NOT NULL DEFAULT 0,"
				" iteration_detail VARCHAR(3000));" );
	if(!qry.exec())
		qDebug() << "create all etude" << qry.lastError();

	qry.prepare(" CREATE TABLE IF NOT EXISTS all_etude ("
				" id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
				" begin datetime NOT NULL DEFAULT NOW(),"
				" iteration INTEGER,"
				" groupid INTEGER NOT NULL DEFAULT 0,"
				" project_name VARCHAR(3000),"
				" ref BOOLEAN NOT NULL DEFAULT 0,"
				" iteration_detail VARCHAR(3000));" );
	if(!qry.exec())
		qDebug() << "create etude" << qry.lastError();

	this->current.initoroject(this->nametmp->text());
	//this->current->projectshow(this, this->table, this->currentgref);
	this->namecurrent = this->nametmp->text();
	menu_projet->actions().at(2)->setEnabled(1);
	menu_projet->actions().at(3)->setEnabled(1);
	menu_outil->setEnabled(1);
	menu_affifchage->setEnabled(1);
	menu_serveur->setEnabled(1);

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
	menu_projet->actions().at(2)->setEnabled(1);
	menu_projet->actions().at(3)->setEnabled(1);
	menu_outil->setEnabled(1);
	menu_affifchage->setEnabled(1);
	menu_serveur->setEnabled(1);

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
	//this->addock();
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

void MainWindow::sendprojectauxi(QString str)
{
	QSqlQuery qry;
	Q_UNUSED(str);

/*	QString body = "Bonjour dans le cadre de notre études veuillez repondre au formulaire à l'adresse suivante : ";
	QStringList listmail;

//	this->updateproject();
//	body.append(this->namecurrent);
//	body.append("&");
	// body.append(this->current->postquestion("ALL"));
	listmail = this->current.sendproject();
	QString bodytmp;
	int i = 0;
	while (i < listmail.size())
	{
		qDebug() << listmail.at(i);
		bodytmp = body + "\r\n";// + "person__person=" + listmail.at(i + 1) + "&";
		sendmail(listmail.at(i), bodytmp); // OPTI
		i += 2;
	}*/
	qry.prepare( " INSERT INTO all_etude (iteration , groupid , project_name) VALUES ( ? , ? , ? );");
	qry.addBindValue(1);
	qry.addBindValue(0);
	qry.addBindValue(this->current.name);
	if(!qry.exec())
		qDebug() << qry.lastError();
}

void MainWindow::sendproject()
{
	QSqlQuery qry;

	qry.prepare( "UPDATE project_" + this->namecurrent + "_project SET questionbool = 1 WHERE 1;");
	if(!qry.exec() )
		qDebug() << qry.lastError();
	else
		this->sendprojectauxi("login.php");
}

void MainWindow::sendproject_ref()
{
	QSqlQuery qry;

	qry.prepare( "UPDATE project_" + this->namecurrent + "_project SET refbool = 1 WHERE 1;");
	if(!qry.exec() )
		qDebug() << qry.lastError();
	else
		this->sendprojectauxi("login.php");
}

void MainWindow::mailSent(QString status)
{
	(void)status;
//	if(status == "Message sent")
//		QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

//recuperation des donnee en ligne

void MainWindow::updateproject()
{
	this->current.initoroject(this->namecurrent);
	if (this->ov == NULL)
	{
		this->ov = new overview(this, &(this->current), this->currentgref, &(this->showmod));//, "overview";
		this->cw->addTab(this->ov, "resumé");
	}
	if (this->table)
		delete this->table;
	if (this->tableg)
	{
		delete this->tableg;
		tableg = NULL;
	}
	if (this->tablep)
	{
		delete this->tablep;
		tablep = NULL;
	}
	this->table = new tableshow(&(this->current), this, 0);
	this->table->showtable(this->currentgref, this->currentgqref);
	this->cw->addTab(table, "tableaux");
	delete this->ov;
	this->ov = NULL;
	this->addock();

	if (this->current.getNbfactnref() == 0)
	{
		this->menu_affifchage->actions().at(0)->setVisible(0);
		refmodechange(1);
	}
	else
		this->menu_affifchage->actions().at(0)->setVisible(1);
}

//void MainWindow::messageErreur(QNetworkReply::NetworkError)
//{
//	QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
//	QMessageBox::critical(this, "Erreur", "Erreur lors du chargement. Vérifiez votre connexion internet ou réessayez plus tard <br /><br /> Code de l'erreur : <br /><em>" + r->errorString() + "</em>");
//}

#include <QApplication>
#include <QMessageBox>

void MainWindow::convert_to_xlsx()
{
	QString fichier = QFileDialog::getSaveFileName(this, "Open a file", QString());
	if (this->table)
		tab_to_fichier(fichier, this->table);
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

void	MainWindow::configproject(){menuconfigproject *m = new menuconfigproject(this->namecurrent, &(this->current), this);m->show();}

void	MainWindow::configsondage(){menuconfigsondage *m = new menuconfigsondage(this);m->show();}

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
		if (!pixmap.save(fileName)) {
		//	QMessageBox::warning(this, tr("Save Error"), tr("The image could not be saved to \"%1\".")
		//						 .arg(QDir::toNativeSeparators(fileName)));
			qDebug() << tr("The image could not be saved to \"%1\".").arg(QDir::toNativeSeparators(fileName));
		}
}
