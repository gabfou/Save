#include "overview.h"
#include "graph/bargraph.h"
#include "project.h"


overview::overview(project &p)
{
    bargraph(syntheselistgroup(p.getgrouplist("ALL"), p.getListquestion()), p.getListquestion(), this);
}
