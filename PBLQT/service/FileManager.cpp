#include "FileManager.h"
#include "../system/RailwaySystem.h"

#include <fstream>
#include <sstream>
#include <string>

using namespace std;

static bool openOutputFile(ofstream& file, const string& path)
{
    file.open(path);
    return file.is_open();
}

static bool inputFileExists(const string& path)
{
    ifstream file(path);
    return file.is_open();
}

static bool readDataLine(istream& input, string& line)
{
    if (!getline(input, line))
    {
        return false;
    }

    bool hasUtf8Bom = line.compare(0, 3, "\xEF\xBB\xBF") == 0;

    if (hasUtf8Bom)
    {
        line = line.substr(3);
    }

    if (!line.empty() && line.back() == '\r')
    {
        line.pop_back();
    }

    return true;
}

static bool loadTrains(RailwaySystem& system, const string& path)
{
    ifstream file(path);

    if (!file.is_open())
    {
        return false;
    }

    string line;

    while (readDataLine(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        string id, name, type, capacity, maxSpeed, status;
        stringstream parser(line);

        getline(parser, id, '|');
        getline(parser, name, '|');
        getline(parser, type, '|');
        getline(parser, capacity, '|');
        getline(parser, maxSpeed, '|');
        getline(parser, status, '|');

        try
        {
            Train* train = new Train(id, name, type, stoi(capacity), stod(maxSpeed), status);

            if (!system.addTrain(train))
            {
                delete train;
            }
        }
        catch (...)
        {
            return false;
        }
    }

    return true;
}

static bool loadStations(RailwaySystem& system, const string& path)
{
    ifstream file(path);

    if (!file.is_open())
    {
        return false;
    }

    string line;

    while (readDataLine(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        string id, name, location, numberOfTracks;
        stringstream parser(line);

        getline(parser, id, '|');
        getline(parser, name, '|');
        getline(parser, location, '|');
        getline(parser, numberOfTracks, '|');

        try
        {
            Station* station = new Station(id, name, location, stoi(numberOfTracks));

            if (!system.addStation(station))
            {
                delete station;
            }
        }
        catch (...)
        {
            return false;
        }
    }

    return true;
}

static bool loadRoutes(RailwaySystem& system, const string& path)
{
    ifstream file(path);

    if (!file.is_open())
    {
        return false;
    }

    string line;

    while (readDataLine(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        string id, fromStation, toStation;
        string distance, travelTime, status;
        stringstream parser(line);

        getline(parser, id, '|');
        getline(parser, fromStation, '|');
        getline(parser, toStation, '|');
        getline(parser, distance, '|');
        getline(parser, travelTime, '|');
        getline(parser, status, '|');

        try
        {
            Route* route = new Route(id, fromStation, toStation, stod(distance), stoi(travelTime), status);

            if (!system.addRoute(route))
            {
                delete route;
            }
        }
        catch (...)
        {
            return false;
        }
    }

    return true;
}

static bool loadSchedules(RailwaySystem& system, const string& path)
{
    ifstream file(path);

    if (!file.is_open())
    {
        return false;
    }

    string line;

    while (readDataLine(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        string id, trainId, departureStation, destinationStation;
        string departureTime, arrivalTime, priority, status, departureDate;
        stringstream parser(line);

        getline(parser, id, '|');
        getline(parser, trainId, '|');
        getline(parser, departureStation, '|');
        getline(parser, destinationStation, '|');
        getline(parser, departureTime, '|');
        getline(parser, arrivalTime, '|');
        getline(parser, priority, '|');
        getline(parser, status, '|');
        getline(parser, departureDate, '|');

        if (departureDate.empty())
        {
            departureDate = "";
        }

        try
        {
            int departure = stoi(departureTime);
            int arrival = stoi(arrivalTime);
            if (arrival <= departure)
                arrival += 24 * 60;

            Schedule* schedule = new Schedule(id, trainId, departureStation, destinationStation, departure, arrival,
                                            stoi(priority), status, departureDate);

            if (!system.addSchedule(schedule))
            {
                delete schedule;
            }
        }
        catch (...)
        {
            return false;
        }
    }

    return true;
}

static bool loadStops(RailwaySystem& system, const string& path)
{
    ifstream file(path);

    if (!file.is_open())
    {
        return false;
    }

    string line;

    while (readDataLine(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        string scheduleId, order, stationId;
        string arrivalTime, departureTime;
        stringstream parser(line);

        getline(parser, scheduleId, '|');
        getline(parser, order, '|');
        getline(parser, stationId, '|');
        getline(parser, arrivalTime, '|');
        getline(parser, departureTime, '|');

        try
        {
            Schedule* schedule = system.findSchedule(scheduleId);
            if (!schedule)
                continue;
            if (stationId == schedule->getDepartureStationId() || stationId == schedule->getDestinationStationId())
                continue;

            int arrival = stoi(arrivalTime);
            int departure = stoi(departureTime);
            while (arrival < schedule->getDepartureTime())
                arrival += 24 * 60;
            while (departure < arrival)
                departure += 24 * 60;

            Stop stop(stationId, stoi(order), arrival, departure);

            system.addStopToSchedule(scheduleId, stop);
        }
        catch (...)
        {
            return false;
        }
    }

    return true;
}
bool FileManager::saveAll(const RailwaySystem& system, const string& folder)
{
    ofstream file;

    if (!openOutputFile(file, folder + "trains.dat"))
    {
        return false;
    }

    for (int i = 0; i < system.trains.getSize(); ++i)
    {
        Train* train = system.trains.getAt(i);
        if (train)
        {
            file << train->getTrainId() << "|" << train->getTrainName() << "|" << train->getTrainType() << "|"
                 << train->getCapacity() << "|" << train->getMaxSpeed() << "|" << train->getStatus() << "\n";
        }
    }
    file.close();

    if (!openOutputFile(file, folder + "stations.dat"))
    {
        return false;
    }

    for (int i = 0; i < system.stations.getSize(); ++i)
    {
        Station* station = system.stations.getAt(i);
        if (station)
        {
            file << station->getStationId() << "|" << station->getStationName() << "|" << station->getLocation()
                 << "|" << station->getNumberOfTracks() << "\n";
        }
    }
    file.close();

    if (!openOutputFile(file, folder + "routes.dat"))
    {
        return false;
    }

    for (int i = 0; i < system.routes.getSize(); ++i)
    {
        Route* route = system.routes.getAt(i);
        if (route)
        {
            file << route->getRouteId() << "|" << route->getFromStationId() << "|" << route->getToStationId() << "|"
                 << route->getDistance() << "|" << route->getTravelTime() << "|" << route->getStatus() << "\n";
        }
    }
    file.close();

    if (!openOutputFile(file, folder + "schedules.dat"))
    {
        return false;
    }

    for (int i = 0; i < system.schedules.getSize(); ++i)
    {
        Schedule* schedule = system.schedules.getAt(i);
        if (schedule)
        {
            file << schedule->getScheduleId() << "|" << schedule->getTrainId() << "|"
                 << schedule->getDepartureStationId() << "|" << schedule->getDestinationStationId() << "|"
                 << schedule->getDepartureTime() << "|" << schedule->getArrivalTime() << "|"
                 << schedule->getPriority() << "|" << schedule->getStatus() << "|" << schedule->getDepartureDate()
                 << "\n";
        }
    }
    file.close();

    if (!openOutputFile(file, folder + "stops.dat"))
    {
        return false;
    }

    for (int i = 0; i < system.schedules.getSize(); ++i)
    {
        Schedule* schedule = system.schedules.getAt(i);
        if (!schedule)
        {
            continue;
        }

        const StopList& stops = schedule->getStops();

        for (int j = 0; j < stops.getSize(); ++j)
        {
            const Stop* stop = stops.get(j);

            if (stop)
            {
                file << schedule->getScheduleId() << "|" << stop->getOrder() << "|" << stop->getStationId() << "|"
                     << stop->getArrivalTime() << "|" << stop->getDepartureTime() << "\n";
            }
        }
    }
    file.close();

    return true;
}

bool FileManager::loadAll(RailwaySystem& system, const string& folder)
{
    if (!inputFileExists(folder + "trains.dat") || !inputFileExists(folder + "stations.dat") ||
        !inputFileExists(folder + "routes.dat") || !inputFileExists(folder + "schedules.dat") ||
        !inputFileExists(folder + "stops.dat"))
    {
        return false;
    }

    system.clearData();

    if (!loadTrains(system, folder + "trains.dat"))
    {
        return false;
    }

    if (!loadStations(system, folder + "stations.dat"))
    {
        return false;
    }

    if (!loadRoutes(system, folder + "routes.dat"))
    {
        return false;
    }

    if (!loadSchedules(system, folder + "schedules.dat"))
    {
        return false;
    }

    if (!loadStops(system, folder + "stops.dat"))
    {
        return false;
    }

    return true;
}
