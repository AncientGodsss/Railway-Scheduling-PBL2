#ifndef PRIORITY_STRATEGY_H
#define PRIORITY_STRATEGY_H

#include "SchedulingStrategy.h"

class PriorityStrategy : public SchedulingStrategy
{
public:
    bool higher(const Schedule& first, const Schedule& second) const override
    {
        if (first.getPriority() != second.getPriority())
        {
            return first.getPriority() > second.getPriority();
        }

        return first.getDepartureTime() <= second.getDepartureTime();
    }
};

#endif
