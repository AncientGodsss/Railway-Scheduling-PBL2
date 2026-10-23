#ifndef SCHEDULING_STRATEGY_H
#define SCHEDULING_STRATEGY_H

#include "../model/Schedule.h"

 
class SchedulingStrategy
{
public:
    virtual int score(const Schedule& schedule) const = 0;

    virtual bool higher(
        const Schedule& first,
        const Schedule& second
    ) const = 0;

    virtual ~SchedulingStrategy() = default;
};

#endif

