#include "previewconfig.h"

previewconfig::previewconfig()
{
    QHBoxLayout *layout;
    QTabWidget *preview;
    QWidget *ref;
    QWidget *reel;


    preview->addTab(this->indexinit(), "index");
    //preview->addWidget(ref, "ref");
    //preview->addWidget(reel, "reel");
//    introref->
    layout->addWidget(preview);
    this->setLayout(layout);
}

QWidget *previewconfig::indexinit()
{
    QWidget *ret = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout();

    ret->setLayout(layout);
    return (ret);
}
