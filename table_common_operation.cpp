#include "le.h"

void add_to_widjet_item(int x, int y, QTableWidget *gbox, int nb)
{
    QTableWidgetItem *item = gbox->currentItem();

    if (item)
    {}
    else
        gbox->setItem(x, y, new QTableWidgetItem(QString::number(nb)));
}
