#include "menuconfigquestion.h"
#include "grouptree.h"
#include "data/project.h"
#include "infoquestion.h"

menuconfigquestion::menuconfigquestion(project *p, MainWindow *m) : p(p)
{
	QHBoxLayout *hlayout = new QHBoxLayout(this);

	groupbox = new grouptree(m, p->listqgroup, 1);
	QSizePolicy spgroupbox(QSizePolicy::Preferred, QSizePolicy::Preferred);
	spgroupbox.setHorizontalStretch(1);
	groupbox->setSizePolicy(spgroupbox);
	hlayout->addWidget(groupbox);

    infoquestion *infobox = new infoquestion(p, m, groupbox);
	QSizePolicy spinfobox(QSizePolicy::Preferred, QSizePolicy::Preferred);
	spinfobox.setHorizontalStretch(1);
	infobox->setSizePolicy(spinfobox);
	hlayout->addWidget(infobox);
	connect(groupbox, SIGNAL(itemClicked(QTreeWidgetItem *, int )), infobox, SLOT(updateib(QTreeWidgetItem *)));
}


