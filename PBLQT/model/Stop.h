#ifndef STOP_H
#define STOP_H

#include <iostream>
#include <string>
#include "TimeUtils.h"

using namespace std;

class Stop
{
private:
    string stationId;

    int order;
    int arrivalTime;
    int departureTime;

public:
     
    Stop()
    {
        order = 0;
        arrivalTime = 0;
        departureTime = 0;
    }

     
    Stop(
        string id,
        int o,
        int arrival,
        int departure
    )
    {
        stationId = id;
        order = o;
        arrivalTime = arrival;
        departureTime = departure;
    }

     
     
     

    string getStationId() const
    {
        return stationId;
    }

    int getOrder() const
    {
        return order;
    }

    int getArrivalTime() const
    {
        return arrivalTime;
    }

    int getDepartureTime() const
    {
        return departureTime;
    }

     
     
     

    void setStationId(const string& id)
    {
        stationId = id;
    }

    void setOrder(int o)
    {
        if (o > 0)
        {
            order = o;
        }
    }

    void setArrivalTime(int time)
    {
        if (time >= 0)
        {
            arrivalTime = time;
        }
    }

    void setDepartureTime(int time)
    {
        if (time >= 0)
        {
            departureTime = time;
        }
    }

     
     
     

    bool isValidTime() const
    {
        return departureTime >= arrivalTime;
    }

     
     
     

    void displayInfo() const
    {
        cout << "Ga: " << stationId
             << " | Thu tu: " << order
             << " | Den: " << TimeUtils::minutesToTime(arrivalTime)
             << " | Di: " << TimeUtils::minutesToTime(departureTime)
             << "\n";
    }
};

#endif