#ifndef STATION_H
#define STATION_H

#include <string>
#include <iostream>

using namespace std;

class Station
{
private:
    string stationId;
    string stationName;
    string location;

    int numberOfTracks;

public:
     
    Station()
    {
        numberOfTracks = 0;
    }

     
    Station(
        string id,
        string name,
        string loc,
        int tracks
    )
    {
        stationId = id;
        stationName = name;
        location = loc;
        numberOfTracks = tracks;
    }

     
     
     

    string getStationId() const
    {
        return stationId;
    }

    string getStationName() const
    {
        return stationName;
    }

    string getLocation() const
    {
        return location;
    }

    int getNumberOfTracks() const
    {
        return numberOfTracks;
    }

     
     
     

    void setStationName(const string& name)
    {
        stationName = name;
    }

    void setLocation(const string& loc)
    {
        location = loc;
    }

    void setNumberOfTracks(int tracks)
    {
        if (tracks >= 0)
        {
            numberOfTracks = tracks;
        }
    }

     
     
     

    void displayInfo() const
    {
        cout << stationId << " | "
             << stationName << " | "
             << location << " | "
             << numberOfTracks
             << " platforms\n";
    }
};

#endif