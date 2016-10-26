#ifndef EMAILVALIDATOR_H
#define EMAILVALIDATOR_H

#include "le.h"

class emailvalidator : public QWidget
{
    QListWidget listmail;
public:
    emailvalidator(project *p);
};

#endif // EMAILVALIDATOR_H
