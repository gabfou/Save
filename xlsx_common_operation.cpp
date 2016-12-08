#include "le.h"

QTXLSX_USE_NAMESPACE


QString indextocase(int x, int y)
{
	QString xstr;
	static char tab[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' , 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    if (x == 0)
    {
        xstr.push_front(tab[x % 26]);
    }
    while (x > 0)
    {
		xstr.push_front(tab[x % 26]);
        x = x / 26;
    }
	return (xstr + QString::number(y + 1));
}

void tab_to_xlsx(const QTableWidget *table, Document & xlsx)
{
	int x = -1;
	int y = -2;
    int y2 = -2;
    QTableWidgetItem *item;
    Format format;

    format.setHorizontalAlignment(Format::AlignHCenter);
    format.setVerticalAlignment(Format::AlignVCenter);
    format.setTextWarp(1);

	while (++y < table->rowCount())
	{
        if (y != -1 && table->isRowHidden(y))
            continue;
        y2++;
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
            if (item)
            {
                QVariant tmp = QVariant(item->text());
                if (tmp.convert(QMetaType::QDateTime) == 0)
                {
                    tmp = QVariant(item->text());
                    if (tmp.convert(QMetaType::Int) == 0)
                        tmp = QVariant(item->text());
                }
                if (x == -1 || y == -1)
                    xlsx.write(y2 + 2, x + 2, tmp, format);
                else
                    xlsx.write(y2 + 2, x + 2, tmp, format);
            }
        }
	}
    xlsx.setColumnWidth(xlsx.dimension(), 20);
}

void tab_to_fichier(const QString name, const QTableWidget *table)
{
	Document xlsx;
	tab_to_xlsx(table, xlsx);

	xlsx.saveAs(name);
}
