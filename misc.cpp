#include "le.h"
//#include <windows.h>
#include "data/question.h"
#include "smtp.h"

t_groupref syntheselistgroup(QList<t_groupref> listg)
{
	t_groupref ret;

    if (listg.empty())
        return (ret);

	QList<t_groupref>::iterator  tmp;
    float tabi[listg.begin()->list.size() + 1];
    float tabl[listg.begin()->list.size() + 1];
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
			ret.total += tmp37;
            ret.list += tmp37;
		}
		else
            ret.list += 0;
	}
	return ret;
}

void ft_error(string error)
{
	cout << error;
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

void sendmail(QString mail, QString body, int type, int it)
{
    QString signature = "<p><b>MURANO Conseil</b><Br/>"
                        "www.muranoconseil.com<Br/>"
                        "21, rue Vauthier<Br/>"
                        "92100 Boulogne-Billancourt<Br/><Br/>"
                        "<img src=\"http://etudemurano.alwaysdata.net/logomail.jpg\" alt=\"logo murano\" style=\"width:120px;height:auto;\"class = logo></p></html>\r\n";
    QString username = "etudes@muranoconseil.com";//"etudemurano@alwaysdata.net";
    QString passwd = "etudes564";//"t4x5akda";
    QString server = "SSL0.OVH.NET";//"smtp-etudemurano.alwaysdata.net";
    Smtp	*smtp = new Smtp(username, passwd, server);
    smtp->sendMail("etudes@muranoconseil.com", mail, (type == 1) ? "PPD_DMI LEAD CHANGE_Timesheet part 1" : "PPD_DMI LEAD CHANGE_Timesheet part 2_day" + QString::number(it),  body + signature);
    //delete smtp;
}

QList<int> recupallgroupfils(int groupid, QString project_name)
{
    QSqlQuery qry;
    QList<int> ret;

    ret += groupid;
    qry.prepare("SELECT id FROM project_" + project_name + '_groupe WHERE groupparent = '+ QString::number(groupid) + ";");
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
