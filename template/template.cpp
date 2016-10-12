#include "le.h"
#include "data/project.h"
#include "data/person.h"
#include "data/group.h"
#include "data/question.h"

QTXLSX_USE_NAMESPACE

void createquestiontemplate(MainWindow *m, project *p)
{
    Document xlsx;
    int x = -1;
    int y = 1;
    int j = -1;
    const int nbg = p->getNbqgeneration();

    qDebug() <<"dsf";
    while(++j < nbg + 1)
        xlsx.write(indextocase(++x, y), "groupe");
    xlsx.write(indextocase(++x, y), "question");
    xlsx.write(indextocase(++x, y), "description");
    xlsx.write(indextocase(++x, y), "type");
    xlsx.write(indextocase(++x, y), "option");
    xlsx.write(indextocase(++x, y), "val");
    xlsx.write(indextocase(++x, y), "reference");

    vector<question> ql = p->listquestion;
    vector<question>::iterator qli = ql.begin();
    group * gtmp;

    while (qli != ql.end())
    {
        if (qli->id == -1)
        {
            qli++;
            continue ;
        }
        y++;
        x = nbg;
        gtmp = &(p->listqgroup[qli->qgroupid]);

        while (gtmp->getGeneration() > -1)
        {
            xlsx.write(indextocase(gtmp->getGeneration(), y), gtmp->name);
            gtmp = &(p->listqgroup[gtmp->getParentid()]);
        }
        xlsx.write(indextocase(++x, y), qli->name);
        xlsx.write(indextocase(++x, y), qli->sujet);
        xlsx.write(indextocase(++x, y), p->mtypeq[qli->type]);
        xlsx.write(indextocase(++x, y), qli->liststr.join("\n"));
        xlsx.write(indextocase(++x, y), QString::number(qli->val));
        xlsx.write(indextocase(++x, y), QString::number(qli->ref_only));
        qli++;
    }
    QString fichier = QFileDialog::getSaveFileName(0, "Save a file", "~", "Excell files (*.xlsx)");
    if (xlsx.saveAs(fichier) == 0)
        qDebug() << "erreur create question template";
    qDebug() << p->name + "_question";
}

void recupquestiontemplate(QString name, project *p)
{
    Document xlsx(name);
    int x;
    int y = 1;
    int lastgid = -1;
    int nbg = 0;
    QString oldg;

    while (nbg < 50 && xlsx.read(indextocase(nbg, 1)).toString().isEmpty())
        nbg++;
    qDebug() << "hasgdghfasghf 0.1" << nbg;
    while (xlsx.read(indextocase(nbg, 1)).toString().compare("question") != 0 && xlsx.read(indextocase(nbg, 1)).toString().isEmpty() == 0)
       nbg++;
    qDebug() << "hasgdghfasghf" << nbg;
    while (xlsx.read(indextocase(nbg, ++y)).toString().compare("") != 0)
    {
        x = -1;
        oldg = "ALL";
        while (++x < nbg)
        {
            lastgid = p->addqgroup(xlsx.read(indextocase(x, y)).toString(), oldg);
            if (lastgid != -1)
                oldg = xlsx.read(indextocase(x, y)).toString();
        }
        if (lastgid == -1)
        {
            continue ;
        }
        x = nbg;
        p->addquestion(xlsx.read(indextocase(++x, y)).toString(), 0, -1, lastgid, xlsx.read(indextocase(++x, y)).toString(), "",
                       p->mytypqinv(xlsx.read(indextocase(++x, y)).toString()), xlsx.read(indextocase(++x, y)).toString(), xlsx.read(indextocase(++x, y)).toString().toInt(),
                       xlsx.read(indextocase(++x, y)).toString().toInt(), 0);
    }
}
