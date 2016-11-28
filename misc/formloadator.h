#ifndef FORMLOADATOR_H
#define FORMLOADATOR_H

#include "le.h"

class formloadator : QScrollArea
{
    Q_OBJECT
public:
    formloadator(bool ref);
    int formcreator(bool ref, group *g, QVBoxLayout *layout, int gid = 0, QVBoxLayout *layoutgquestion = NULL);
};

#endif // FORMLOADATOR_H
