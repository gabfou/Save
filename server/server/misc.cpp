#include "le.h"
//#include <windows.h>
#include "question.h"
#include "smtp.h"

t_groupref syntheselistgroup(QList<t_groupref> listg, vector<question> questionlist)
{
    t_groupref ret;
    QList<t_groupref>::iterator  tmp;
    int tabi[questionlist.size() + 1];
    int tabl[questionlist.size() + 1];
    QList<QString>::iterator tmp4;
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
            if (*tmp4 != "NA")
            {
                tabi[i] += (*tmp4).toInt();
                (tabl[i])++;
            }
            i++;
            tmp4++;
        }
        m++;
        tmp++;
    }
    ret.total = 0;
    i = -1;
    while(++i < questionlist.size() + 1)
    {
        if (tabl[i] != 0)
        {
            int tmp37 = tabi[i] / tabl[i];
            ret.total += tmp37;
            ret.list += QString::number(tmp37);
        }
        else
            ret.list += QString::number(0);
    }
    return ret;
}

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

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

void sendmail(QString mail, QString body)
{
    QString username = "etudes@muranoconseil.com";
    QString passwd = "etudes564";
    QString server = "SSL0.OVH.NET";
    Smtp	*smtp = new Smtp(username, passwd, server);
    smtp->sendMail("etudes@muranoconseil.com", mail , "Etude muranoconseil",  body + "\r\n\r\nMURAnO Conseil : Marketing / Retail / Supply Chain");
}

