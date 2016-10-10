#include "le.h"
#include "data/project.h"
#include "data/person.h"
#include "data/group.h"
#include "data/question.h"

QTXLSX_USE_NAMESPACE

void createquestiontemplate(project *p)
{
    Document xlsx;
    int x = 0;
    int y = 1;
    int j = -1;
    const int nbg = p->getNbqgeneration();

    qDebug() <<"dsf";
    while(++j < nbg)
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

        while (gtmp->getGeneration() > 0)
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
    if (xlsx.saveAs(p->name + "_question.xlsx") == 0)
        qDebug() << "erreur create question template";
    qDebug() <<p->name + "_question";
}

void recupquestiontemplate(QString name, project *p)
{
    Document xlsx = Document(name);
    int x;
    int y = 1;
    int lastgid = -1;
    int nbg = 0;
    QString oldg;


    while ((nbg < 5) || (xlsx.read(1, nbg).toString().compare("question") != 0 && xlsx.read(1, nbg).toString().compare("") != 0))
       nbg++;
    while (xlsx.read(++y, nbg).toString().compare("") != 0)
    {
        x = -1;
        oldg = "ALL";
        while (++x < nbg)
        {
            lastgid = p->addgroup(xlsx.read(y, x).toString(), oldg);
            oldg = xlsx.read(y, x).toString();
        }
        x--;
        p->addquestion(xlsx.read(y, ++x).toString(), 0, lastid, lastgid, xlsx.read(y, ++x).toString(), "",
                       p->mtypeqinv(xlsx.read(y, ++x).toString()), xlsx.read(y, ++x).toString(), xlsx.read(y, ++x).toString(),
                       xlsx.read(y, ++x).toString(), 0);
    }
}
