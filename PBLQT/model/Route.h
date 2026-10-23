#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <iostream>

using namespace std;

class Route
{
private:
    string routeId;
    string fromStationId;
    string toStationId;

    double distance;
    int travelTime;

    string status;

public:
     
    Route()
    {
        distance = 0;
        travelTime = 0;
        status = "ACTIVE";
    }

     
    Route(
        string id,
        string from,
        string to,
        double d,
        int time,
        string st
    )
    {
        routeId = id;
        fromStationId = from;
        toStationId = to;

        distance = d;
        travelTime = time;

        status = st;
    }

     
    string getRouteId() const
    {
        return routeId;
    }

    string getFromStationId() const
    {
        return fromStationId;
    }

    string getToStationId() const
    {
        return toStationId;
    }

    double getDistance() const
    {
        return distance;
    }

    int getTravelTime() const
    {
        return travelTime;
    }

    string getStatus() const
    {
        return status;
    }

     
    void setFromStationId(const string& id)
    {
        fromStationId = id;
    }

    void setToStationId(const string& id)
    {
        toStationId = id;
    }

    void setDistance(double d)
    {
        if (d > 0)
        {
            distance = d;
        }
    }

    void setTravelTime(int time)
    {
        if (time > 0)
        {
            travelTime = time;
        }
    }

    void setStatus(const string& st)
    {
        status = st;
    }

     
    void displayInfo() const
    {
        cout << routeId << " | "
             << fromStationId << " -> "
             << toStationId << " | "
             << distance << " km | "
             << travelTime << " phút | "
             << status << "\n";
    }
};

#endif