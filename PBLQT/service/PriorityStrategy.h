#ifndef PRIORITY_STRATEGY_H
#define PRIORITY_STRATEGY_H

#include "SchedulingStrategy.h"

 
 
class PriorityStrategy : public SchedulingStrategy
{
public:
    int score(const Schedule& schedule) const override
    {
        return schedule.getPriority();
    }

    bool higher(
        const Schedule& first,
        const Schedule& second
    ) const override
    {
        if (score(first) != score(second))
        {
            return score(first) > score(second);
        }

        return first.getDepartureTime() <= second.getDepartureTime();
    }
};

#endif

