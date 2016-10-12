#include "le.h"

QTXLSX_USE_NAMESPACE


QString indextocase(int x, int y)
{
	QString xstr;
	static char tab[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' , 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    while ((x / 26) > 0)
    {
		xstr.push_front(tab[x % 26]);
        x = x / 26;
    }
    //`qDebug() << (xstr + QString::number(y + 1));
	return (xstr + QString::number(y + 1));
}

void tab_to_xlsx(const QTableWidget *table, Document & xlsx)
{
	int x = -1;
	int y = -2;
	QTableWidgetItem *item;

	while (++y < table->rowCount())
	{
		x = -2;
		while (++x < table->columnCount())
		{
			if (x == -1 && y == -1)
				continue ;
			else if (x == -1)
				item = table->verticalHeaderItem(y);
			else if (y == -1)
				item = table->horizontalHeaderItem(x);
			else
				item = table->item(y, x);
			if (item && (x == -1 || y == -1))
				xlsx.write(indextocase(x + 1, y + 1), item->text());
			else if (item)
			{
				xlsx.write(indextocase(x + 1, y + 1), item->text());
				qDebug() << item->text();
			}
			else
				 xlsx.write(indextocase(y + 1, x + 1), "");
		}
	}
	qDebug() << "tab xlsx fin";
}

void tab_to_fichier(const QString name, const QTableWidget *table)
{
	Document xlsx;
	tab_to_xlsx(table, xlsx);

	xlsx.saveAs(name);
	qDebug() << "xlsx fin";
}
