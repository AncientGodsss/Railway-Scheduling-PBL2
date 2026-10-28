#ifndef CONFLICT_DETECTOR_H
#define CONFLICT_DETECTOR_H

#include <string>
#include "../model/Schedule.h"

using std::string;

class ConflictDetector
{
private:
    bool overlap(long long firstStart, long long firstEnd, long long secondStart, long long secondEnd) const
    {
        bool firstStartsBeforeSecondEnds = firstStart < secondEnd;
        bool secondStartsBeforeFirstEnds = secondStart < firstEnd;
        return firstStartsBeforeSecondEnds && secondStartsBeforeFirstEnds;
    }

    long long absoluteTime(const Schedule& schedule, int time) const
    {
        return TimeUtils::toAbsoluteMinutes(schedule.getDepartureDate(), time);
    }

public:
    bool sameTrain(const Schedule& first, const Schedule& second) const
    {
        if (first.getTrainId() != second.getTrainId())
        {
            return false;
        }

        long long firstDeparture = absoluteTime(first, first.getDepartureTime());
        long long firstArrival = absoluteTime(first, first.getArrivalTime());
        long long secondDeparture = absoluteTime(second, second.getDepartureTime());
        long long secondArrival = absoluteTime(second, second.getArrivalTime());
        return overlap(firstDeparture, firstArrival, secondDeparture, secondArrival);
    }

    bool sameEndToEndRoute(const Schedule& first, const Schedule& second) const
    {
        bool sameDirection = first.getDepartureStationId() == second.getDepartureStationId() &&
                            first.getDestinationStationId() == second.getDestinationStationId();

        bool oppositeDirection = first.getDepartureStationId() == second.getDestinationStationId() &&
                                first.getDestinationStationId() == second.getDepartureStationId();

        if (!sameDirection && !oppositeDirection)
        {
            return false;
        }

        long long firstDeparture = absoluteTime(first, first.getDepartureTime());
        long long firstArrival = absoluteTime(first, first.getArrivalTime());
        long long secondDeparture = absoluteTime(second, second.getDepartureTime());
        long long secondArrival = absoluteTime(second, second.getArrivalTime());
        return overlap(firstDeparture, firstArrival, secondDeparture, secondArrival);
    }

    bool segmentConflict(const Schedule& first, const Schedule& second, string& segment) const
    {
        const StopList& firstStops = first.getStops();
        const StopList& secondStops = second.getStops();
        int firstPointCount = firstStops.getSize() + 2;
        int secondPointCount = secondStops.getSize() + 2;

        for (int i = 0; i + 1 < firstPointCount; ++i)
        {
            string firstStartId;
            int firstStartTime;
            if (i == 0)
            {
                firstStartId = first.getDepartureStationId();
                firstStartTime = first.getDepartureTime();
            }
            else
            {
                firstStartId = firstStops.get(i - 1)->getStationId();
                firstStartTime = firstStops.get(i - 1)->getDepartureTime();
            }

            string firstEndId;
            int firstEndTime;
            bool reachesFirstDestination = i + 1 == firstPointCount - 1;
            if (reachesFirstDestination)
            {
                firstEndId = first.getDestinationStationId();
                firstEndTime = first.getArrivalTime();
            }
            else
            {
                firstEndId = firstStops.get(i)->getStationId();
                firstEndTime = firstStops.get(i)->getArrivalTime();
            }

            for (int j = 0; j + 1 < secondPointCount; ++j)
            {
                string secondStartId;
                int secondStartTime;
                if (j == 0)
                {
                    secondStartId = second.getDepartureStationId();
                    secondStartTime = second.getDepartureTime();
                }
                else
                {
                    secondStartId = secondStops.get(j - 1)->getStationId();
                    secondStartTime = secondStops.get(j - 1)->getDepartureTime();
                }

                string secondEndId;
                int secondEndTime;
                bool reachesSecondDestination = j + 1 == secondPointCount - 1;
                if (reachesSecondDestination)
                {
                    secondEndId = second.getDestinationStationId();
                    secondEndTime = second.getArrivalTime();
                }
                else
                {
                    secondEndId = secondStops.get(j)->getStationId();
                    secondEndTime = secondStops.get(j)->getArrivalTime();
                }

                bool sameDirection = firstStartId == secondStartId && firstEndId == secondEndId;

                bool oppositeDirection = firstStartId == secondEndId && firstEndId == secondStartId;

                long long firstSegmentStart = absoluteTime(first, firstStartTime);
                long long firstSegmentEnd = absoluteTime(first, firstEndTime);
                long long secondSegmentStart = absoluteTime(second, secondStartTime);
                long long secondSegmentEnd = absoluteTime(second, secondEndTime);
                bool timeOverlapped = overlap(firstSegmentStart, firstSegmentEnd, secondSegmentStart, secondSegmentEnd);

                if ((sameDirection || oppositeDirection) && timeOverlapped)
                {
                    segment = firstStartId + "-" + firstEndId;

                    return true;
                }
            }
        }

        return false;
    }

    bool stationStopConflict(const Schedule& first, const Schedule& second, string& station) const
    {
        const StopList& firstStops = first.getStops();
        const StopList& secondStops = second.getStops();

        for (int i = 0; i < firstStops.getSize(); ++i)
        {
            const Stop* firstStop = firstStops.get(i);

            if (!firstStop)
            {
                continue;
            }

            for (int j = 0; j < secondStops.getSize(); ++j)
            {
                const Stop* secondStop = secondStops.get(j);

                if (!secondStop)
                {
                    continue;
                }

                bool sameStation = firstStop->getStationId() == secondStop->getStationId();

                long long firstArrival = absoluteTime(first, firstStop->getArrivalTime());
                long long firstDeparture = absoluteTime(first, firstStop->getDepartureTime());
                long long secondArrival = absoluteTime(second, secondStop->getArrivalTime());
                long long secondDeparture = absoluteTime(second, secondStop->getDepartureTime());
                bool timeOverlapped = overlap(firstArrival, firstDeparture, secondArrival, secondDeparture);

                if (sameStation && timeOverlapped)
                {
                    station = firstStop->getStationId();
                    return true;
                }
            }
        }

        return false;
    }

    bool any(const Schedule& first, const Schedule& second) const
    {
        string detail;

        if (sameTrain(first, second))
        {
            return true;
        }

        if (sameEndToEndRoute(first, second))
        {
            return true;
        }

        if (segmentConflict(first, second, detail))
        {
            return true;
        }

        return stationStopConflict(first, second, detail);
    }
};

#endif
