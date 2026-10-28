#ifndef EARLIEST_STRATEGY_H
#define EARLIEST_STRATEGY_H

#include "SchedulingStrategy.h"

class EarliestStrategy : public SchedulingStrategy
{
public:
    bool higher(const Schedule& first, const Schedule& second) const override
    {
        long long firstTime = TimeUtils::toAbsoluteMinutes(first.getDepartureDate(), first.getDepartureTime());
        long long secondTime = TimeUtils::toAbsoluteMinutes(second.getDepartureDate(), second.getDepartureTime());
        if (firstTime != secondTime)
        {
            return firstTime < secondTime;
        }

        return first.getPriority() >= second.getPriority();
    }
};

#endif
