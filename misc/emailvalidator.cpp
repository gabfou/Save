#include "emailvalidator.h"
#include "data/project.h"

emailvalidator::emailvalidator(project *p)
{
    QStringList listmail = p->sendproject(0);;
}
