#ifndef INFO_H
#define INFO_H

#include "le.h"

class mainwindow;

class info : public QWidget
{
    Q_OBJECT
public:
    info(MainWindow *m);

public slots:
    void updatebddg();
    void updateibg(int id, int type);
protected:
    QLabel      *infolabel;
    QWidget     *contg;
    QVBoxLayout *vboxinfo;
    QVBoxLayout *infog;
    project     *p;
    QComboBox   *gquestion;
    QLabel      *gquestionlabel;
    QPushButton *gsettarget;
    MainWindow  *m;

private slots:
    void settargetchildquestion();
    void settargetchildquestion2(int id);
private:
    QLineEdit   *name;
    QLineEdit   *descriptiong;
    QPushButton *b_update;
    QHBoxLayout *gquestionbox;
    group       *current;
    int init = 0;

    void prephide();
};

#endif // INFO_H
