#ifndef CONFLICT_DETECTOR_H
#define CONFLICT_DETECTOR_H

#include <string>
#include "../model/Schedule.h"

using std::string;

 
class ConflictDetector
{
private:
    bool overlap(
        int firstStart,
        int firstEnd,
        int secondStart,
        int secondEnd
    ) const
    {
        return firstStart < secondEnd && secondStart < firstEnd;
    }

    bool sameDate(
        const Schedule& first,
        const Schedule& second
    ) const
    {
        return first.getDepartureDate() == second.getDepartureDate();
    }

public:
    bool sameTrain(
        const Schedule& first,
        const Schedule& second
    ) const
    {
        if (!sameDate(first, second))
        {
            return false;
        }

        bool sameTrainId =
            first.getTrainId() == second.getTrainId();

        bool timeOverlapped = overlap(
            first.getDepartureTime(),
            first.getArrivalTime(),
            second.getDepartureTime(),
            second.getArrivalTime()
        );

        return sameTrainId && timeOverlapped;
    }

    bool sameEndToEndRoute(
        const Schedule& first,
        const Schedule& second
    ) const
    {
        if (!sameDate(first, second))
        {
            return false;
        }

        bool sameDirection =
            first.getDepartureStationId() == second.getDepartureStationId()
            && first.getDestinationStationId() == second.getDestinationStationId();

        bool oppositeDirection =
            first.getDepartureStationId() == second.getDestinationStationId()
            && first.getDestinationStationId() == second.getDepartureStationId();

        bool timeOverlapped = overlap(
            first.getDepartureTime(),
            first.getArrivalTime(),
            second.getDepartureTime(),
            second.getArrivalTime()
        );

        return (sameDirection || oppositeDirection) && timeOverlapped;
    }

    bool segmentConflict(
        const Schedule& first,
        const Schedule& second,
        string& segment
    ) const
    {
        if (!sameDate(first, second))
        {
            return false;
        }

        const StopList& firstStops = first.getStops();
        const StopList& secondStops = second.getStops();
        int firstPointCount = firstStops.getSize() + 2;
        int secondPointCount = secondStops.getSize() + 2;

        for (int i = 0; i + 1 < firstPointCount; ++i)
        {
            string firstStartId = i == 0
                ? first.getDepartureStationId()
                : firstStops.get(i - 1)->getStationId();
            string firstEndId = i + 1 == firstPointCount - 1
                ? first.getDestinationStationId()
                : firstStops.get(i)->getStationId();
            int firstStartTime = i == 0
                ? first.getDepartureTime()
                : firstStops.get(i - 1)->getDepartureTime();
            int firstEndTime = i + 1 == firstPointCount - 1
                ? first.getArrivalTime()
                : firstStops.get(i)->getArrivalTime();

            for (int j = 0; j + 1 < secondPointCount; ++j)
            {
                string secondStartId = j == 0
                    ? second.getDepartureStationId()
                    : secondStops.get(j - 1)->getStationId();
                string secondEndId = j + 1 == secondPointCount - 1
                    ? second.getDestinationStationId()
                    : secondStops.get(j)->getStationId();
                int secondStartTime = j == 0
                    ? second.getDepartureTime()
                    : secondStops.get(j - 1)->getDepartureTime();
                int secondEndTime = j + 1 == secondPointCount - 1
                    ? second.getArrivalTime()
                    : secondStops.get(j)->getArrivalTime();

                bool sameDirection =
                    firstStartId == secondStartId && firstEndId == secondEndId;

                bool oppositeDirection =
                    firstStartId == secondEndId && firstEndId == secondStartId;

                bool timeOverlapped = overlap(
                    firstStartTime, firstEndTime,
                    secondStartTime, secondEndTime
                );

                if ((sameDirection || oppositeDirection) && timeOverlapped)
                {
                    segment =
                        firstStartId + "-" + firstEndId;

                    return true;
                }
            }
        }

        return false;
    }

    bool stationStopConflict(
        const Schedule& first,
        const Schedule& second,
        string& station
    ) const
    {
        if (!sameDate(first, second))
        {
            return false;
        }

        const auto& firstStops = first.getStops();
        const auto& secondStops = second.getStops();

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

                bool sameStation =
                    firstStop->getStationId() == secondStop->getStationId();

                bool timeOverlapped = overlap(
                    firstStop->getArrivalTime(),
                    firstStop->getDepartureTime(),
                    secondStop->getArrivalTime(),
                    secondStop->getDepartureTime()
                );

                if (sameStation && timeOverlapped)
                {
                    station = firstStop->getStationId();
                    return true;
                }
            }
        }

        return false;
    }

    bool any(
        const Schedule& first,
        const Schedule& second
    ) const
    {
        string detail;

        return sameTrain(first, second)
            || sameEndToEndRoute(first, second)
            || segmentConflict(first, second, detail)
            || stationStopConflict(first, second, detail);
    }
};

#endif

