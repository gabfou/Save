#ifndef INFO_H
#define INFO_H

#include "le.h"

class info : public QWidget
{
    Q_OBJECT
public:
    info(project *p);

public slots:
    void updatebddg();
    void updateibg(int id, int type);
protected:
    QLabel      *infolabel;
    QWidget     *contg;
    QVBoxLayout *vboxinfo;
    QVBoxLayout *infog;
    project     *p;

private:
    QLineEdit *descriptiong;
    QPushButton *b_update;
    group *current;
    int init = 0;

};

#endif // INFO_H
