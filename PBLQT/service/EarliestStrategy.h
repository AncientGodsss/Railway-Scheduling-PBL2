#ifndef EARLIEST_STRATEGY_H
#define EARLIEST_STRATEGY_H

#include "SchedulingStrategy.h"

 
 
class EarliestStrategy : public SchedulingStrategy
{
public:
    int score(const Schedule& schedule) const override
    {
        return 1439 - schedule.getDepartureTime();
    }

    bool higher(
        const Schedule& first,
        const Schedule& second
    ) const override
    {
        if (first.getDepartureTime() != second.getDepartureTime())
        {
            return first.getDepartureTime() < second.getDepartureTime();
        }

        return first.getPriority() >= second.getPriority();
    }
};

#endif

