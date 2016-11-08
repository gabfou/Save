#include "le.h"
//#include <windows.h>
#include "data/question.h"
#include "smtp.h"

t_groupref syntheselistgroup(QList<t_groupref> listg)
{
	t_groupref ret;

    if (listg.empty())
    {
        qDebug() << "listempty in syntheselistgroup";
        return (ret);
    }

	QList<t_groupref>::iterator  tmp;
    float tabi[listg.begin()->list.size() + 1];
    float tabl[listg.begin()->list.size() + 1];
    //qDebug() << "dsfsdfdsfdsgdg " << listg.begin()->list.size();
    QList<float>::iterator tmp4;
    int i;
    int m = 0;

	ret.name = "synthese";
	tmp = listg.begin();
	while (tmp != listg.end())
	{
		i = 0;
		tmp4 = tmp->list.begin();
		while(tmp4 != tmp->list.end())
		{
			if (m == 0)
			{
				tabi[i] = 0;
				tabl[i] = 0;
			}
            tabi[i] += (*tmp4);
            (tabl[i])++;
			i++;
			tmp4++;
		}
		m++;
		tmp++;
	}
    ret.total = 0;
	i = -1;
    while(++i < listg.begin()->list.size())
	{
		if (tabl[i] != 0)
		{
            float tmp37 = tabi[i] / tabl[i];
            //qDebug() << "test test test" << tmp37;
			ret.total += tmp37;
            ret.list += tmp37;
		}
		else
            ret.list += 0;
	}
	return ret;
}

/*float total(t_groupref g)
{
    int total = 0;
    i = -1;
    while(++i < listg.size() + 1)
        total += tmp37;
    return total;
}*/

void ft_error(string error)
{
	cout << error;
//	Sleep(10000);
	exit(-1);
}

void ft_exit()
{
	exit(0);
}

void gen_random(char *s, const int len)
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i)
    {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	s[len] = 0;
}

QList<int> QStrltoQil(QStringList &src)
{
    QList<int> ret;
    QStringList::iterator i = src.begin();

    while(i != src.end())
    {
        ret.push_back(i->toInt());
        i++;
    }
    return (ret);
}

void sendmail(QString mail, QString body)
{
    QString signature = "<Br/><p><b>MURAnO Conseil</b><Br/>"
                        "www.muranoconseil.com<Br/>"
                        "21, rue Vauthier<Br/>"
                        "92100 Boulogne-Billancourt<Br/>"
                        "<img src=\"http://etudemurano.alwaysdata.net/logomieux.jpg\" alt=\"logo murano\" class = logo></p></html> + \r\n";
    QString username = "etudemurano@alwaysdata.net";
    QString passwd = "t4x5akda";
    QString server = "smtp-etudemurano.alwaysdata.net";
    Smtp	*smtp = new Smtp(username, passwd, server);
    smtp->sendMail("etudemurano@alwaysdata.net", mail, "Etude muranoconseil",  body + signature);
    //delete smtp;
}

QList<int> recupallgroupfils(int groupid, QString project_name)
{
    QSqlQuery qry;
    QList<int> ret;

    ret += groupid;
    qry.prepare('SELECT id FROM project_' + project_name + '_groupe WHERE groupparent = '+ QString::number(groupid) + ";");
    qry.exec();
    while (qry.next())
        ret << recupallgroupfils(qry.value(0).toInt(), project_name);
    return (ret);
}

QString strallgroupfilsforsql(int groupid, QString project_name)
{
    int i = 0;
    QString ret = "";
    QList<int> tabid = recupallgroupfils(groupid, project_name);
    QList<int>::iterator it = tabid.begin();

    while (it != tabid.end())
    {
        if (i == 0)
        {
            ret += "groupid = " + QString::number(*it);
            i++;
        }
        else
            ret += " OR groupid = " +  QString::number(*it);
        it++;
    }
    return (ret);
}
