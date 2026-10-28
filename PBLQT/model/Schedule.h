#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include <iostream>

#include "../data_structure/DoublyLinkedList.h"
#include "TimeUtils.h"
#include "Stop.h"

using namespace std;

class Schedule
{
private:
    string scheduleId;
    string trainId;

    string departureStationId;
    string destinationStationId;

    int departureTime;
    int arrivalTime;

    int priority;
    string status;
    string departureDate;

    StopList stops;

public:
    Schedule()
    {
        departureTime = 0;
        arrivalTime = 0;
        priority = 0;
        status = "SCHEDULED";
        departureDate = "";
    }

    Schedule(string id, string tId, string departureId, string destinationId, int departure, int arrival, int p,
             string st, string depDate = "")
    {
        scheduleId = id;
        trainId = tId;

        departureStationId = departureId;
        destinationStationId = destinationId;

        departureTime = departure;
        arrivalTime = arrival;

        priority = p;
        status = st;
        departureDate = depDate;
    }

    string getDepartureDate() const
    {
        return departureDate;
    }
    void setDepartureDate(const string& d)
    {
        departureDate = d;
    }

    string getScheduleId() const
    {
        return scheduleId;
    }

    string getTrainId() const
    {
        return trainId;
    }

    string getDepartureStationId() const
    {
        return departureStationId;
    }

    string getDestinationStationId() const
    {
        return destinationStationId;
    }

    int getDepartureTime() const
    {
        return departureTime;
    }

    int getArrivalTime() const
    {
        return arrivalTime;
    }

    int getPriority() const
    {
        return priority;
    }

    string getStatus() const
    {
        return status;
    }

    StopList& getStops()
    {
        return stops;
    }

    const StopList& getStops() const
    {
        return stops;
    }

    void setTrainId(const string& id)
    {
        trainId = id;
    }

    void setDepartureStationId(const string& id)
    {
        departureStationId = id;
    }

    void setDestinationStationId(const string& id)
    {
        destinationStationId = id;
    }

    void setDepartureTime(int time)
    {
        if (time >= 0)
        {
            departureTime = time;
        }
    }

    void setArrivalTime(int time)
    {
        if (time >= 0)
        {
            arrivalTime = time;
        }
    }

    void setPriority(int p)
    {
        priority = p;
    }

    void setStatus(const string& st)
    {
        status = st;
    }

    bool addStop(const Stop& stop)
    {
        if (stop.getOrder() <= 0 || stop.getStationId().empty())
            return false;
        if (!stop.isValidTime())
            return false;
        if (!TimeUtils::isValidTime(stop.getArrivalTime()) || !TimeUtils::isValidTime(stop.getDepartureTime()))
            return false;
        if (stop.getArrivalTime() < departureTime || stop.getDepartureTime() > arrivalTime)
            return false;

        for (int i = 0; i < stops.getSize(); ++i)
        {
            const Stop* s = stops.get(i);
            if (s && (s->getOrder() == stop.getOrder() || s->getStationId() == stop.getStationId()))
            {
                return false;
            }
        }
        int position = 0;
        while (position < stops.getSize())
        {
            const Stop* current = stops.get(position);
            if (current && stop.getOrder() < current->getOrder())
                break;
            ++position;
        }
        stops.insertAt(position, stop);
        return true;
    }

    bool removeStopByOrder(int order)
    {
        for (int i = 0; i < stops.getSize(); ++i)
        {
            const Stop* s = stops.get(i);
            if (s && s->getOrder() == order)
            {
                return stops.removeAt(i);
            }
        }
        return false;
    }

    bool isValidTime() const
    {
        return TimeUtils::dateToDayNumber(departureDate) >= 0 && TimeUtils::isValidTime(departureTime) &&
               TimeUtils::isValidTime(arrivalTime) && arrivalTime > departureTime;
    }

    int getDuration() const
    {
        return arrivalTime - departureTime;
    }

    int getStopCount() const
    {
        return stops.getSize();
    }

    void shiftSchedule(int minutes)
    {
        departureTime += minutes;
        arrivalTime += minutes;

        for (int i = 0; i < stops.getSize(); ++i)
        {
            Stop* s = stops.get(i);
            if (s)
            {
                s->setArrivalTime(s->getArrivalTime() + minutes);
                s->setDepartureTime(s->getDepartureTime() + minutes);
            }
        }
    }

    void displaySchedule() const
    {
        cout << "----------------------------------------\n";
        cout << "Ma lich   : " << scheduleId << "\n";
        cout << "Ma tau    : " << trainId << "\n";
        cout << "Ga di     : " << departureStationId << "\n";
        cout << "Ga den    : " << destinationStationId << "\n";
        cout << "Gio di    : " << TimeUtils::minutesToDisplay(departureTime) << "\n";
        cout << "Gio den   : " << TimeUtils::minutesToDisplay(arrivalTime) << "\n";
        cout << "Thoi gian : " << getDuration() << " phut\n";
        cout << "Uu tien   : " << priority << "\n";
        cout << "Trang thai: " << status << "\n";
        cout << "So diem dung: " << stops.getSize() << "\n";
        cout << "----------------------------------------\n";
    }

    void displayScheduleWithStops() const
    {
        displaySchedule();

        if (stops.getSize() == 0)
        {
            cout << "  (Chua co diem dung nao)\n";
            return;
        }

        cout << "  Danh sach diem dung:\n";
        for (int i = 0; i < stops.getSize(); ++i)
        {
            const Stop* s = stops.get(i);
            if (s)
            {
                cout << "  [" << s->getOrder() << "] ";
                s->displayInfo();
            }
        }
        cout << "----------------------------------------\n";
    }
};

#endif
