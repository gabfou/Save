#ifndef ARGTABLEITEM_H
#define ARGTABLEITEM_H

#include "le.h"
#include "headeredit.h"

template<typename T>
class argtableitem : public QTableWidgetItem
{
public:
	argtableitem(QString str, T *arg) : arg(arg), QTableWidgetItem(str)
	{

	}
	T *arg;
	int id;
};

#endif // ARGTABLEITEM_H
