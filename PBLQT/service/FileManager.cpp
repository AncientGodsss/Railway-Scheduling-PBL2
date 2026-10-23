#include "FileManager.h"
#include "../system/RailwaySystem.h"

#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace
{
    bool openOutputFile(ofstream& file, const string& path)
    {
        file.open(path);
        return file.is_open();
    }

    bool inputFileExists(const string& path)
    {
        ifstream file(path);
        return file.is_open();
    }

     
    bool readDataLine(istream& input, string& line)
    {
        if (!getline(input, line))
        {
            return false;
        }

        bool hasUtf8Bom =
            line.size() >= 3
            && static_cast<unsigned char>(line[0]) == 0xEF
            && static_cast<unsigned char>(line[1]) == 0xBB
            && static_cast<unsigned char>(line[2]) == 0xBF;

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

    bool loadTrains(RailwaySystem& system, const string& path)
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
                Train* train = new Train(
                    id,
                    name,
                    type,
                    stoi(capacity),
                    stod(maxSpeed),
                    status
                );

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

    bool loadStations(RailwaySystem& system, const string& path)
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
                Station* station = new Station(
                    id,
                    name,
                    location,
                    stoi(numberOfTracks)
                );

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

    bool loadRoutes(RailwaySystem& system, const string& path)
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
                Route* route = new Route(
                    id,
                    fromStation,
                    toStation,
                    stod(distance),
                    stoi(travelTime),
                    status
                );

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

    bool loadSchedules(RailwaySystem& system, const string& path)
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
                Schedule* schedule = new Schedule(
                    id,
                    trainId,
                    departureStation,
                    destinationStation,
                    stoi(departureTime),
                    stoi(arrivalTime),
                    stoi(priority),
                    status,
                    departureDate
                );

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

    bool loadStops(RailwaySystem& system, const string& path)
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
                Stop stop(
                    stationId,
                    stoi(order),
                    stoi(arrivalTime),
                    stoi(departureTime)
                );

                system.addStopToSchedule(scheduleId, stop);
            }
            catch (...)
            {
                return false;
            }
        }

        return true;
    }
}

bool FileManager::saveAll(
    const RailwaySystem& system,
    const string& folder
)
{
    ofstream file;

    if (!openOutputFile(file, folder + "trains.txt"))
    {
        return false;
    }

    system.trains.forEach([&](string, Train* train) {
        if (train)
        {
            file << train->getTrainId() << "|"
                 << train->getTrainName() << "|"
                 << train->getTrainType() << "|"
                 << train->getCapacity() << "|"
                 << train->getMaxSpeed() << "|"
                 << train->getStatus() << "\n";
        }
    });
    file.close();

    if (!openOutputFile(file, folder + "stations.txt"))
    {
        return false;
    }

    system.stations.forEach([&](string, Station* station) {
        if (station)
        {
            file << station->getStationId() << "|"
                 << station->getStationName() << "|"
                 << station->getLocation() << "|"
                 << station->getNumberOfTracks() << "\n";
        }
    });
    file.close();

    if (!openOutputFile(file, folder + "routes.txt"))
    {
        return false;
    }

    system.routes.forEach([&](string, Route* route) {
        if (route)
        {
            file << route->getRouteId() << "|"
                 << route->getFromStationId() << "|"
                 << route->getToStationId() << "|"
                 << route->getDistance() << "|"
                 << route->getTravelTime() << "|"
                 << route->getStatus() << "\n";
        }
    });
    file.close();

    if (!openOutputFile(file, folder + "schedules.txt"))
    {
        return false;
    }

    system.schedules.forEach([&](string, Schedule* schedule) {
        if (schedule)
        {
            file << schedule->getScheduleId() << "|"
                 << schedule->getTrainId() << "|"
                 << schedule->getDepartureStationId() << "|"
                 << schedule->getDestinationStationId() << "|"
                 << schedule->getDepartureTime() << "|"
                 << schedule->getArrivalTime() << "|"
                 << schedule->getPriority() << "|"
                 << schedule->getStatus() << "|"
                 << schedule->getDepartureDate() << "\n";
        }
    });
    file.close();

    if (!openOutputFile(file, folder + "stops.txt"))
    {
        return false;
    }

    system.schedules.forEach([&](string, Schedule* schedule) {
        if (!schedule)
        {
            return;
        }

        const auto& stops = schedule->getStops();

        for (int i = 0; i < stops.getSize(); ++i)
        {
            const Stop* stop = stops.get(i);

            if (stop)
            {
                file << schedule->getScheduleId() << "|"
                     << stop->getOrder() << "|"
                     << stop->getStationId() << "|"
                     << stop->getArrivalTime() << "|"
                     << stop->getDepartureTime() << "\n";
            }
        }
    });
    file.close();

    return true;
}

bool FileManager::loadAll(
    RailwaySystem& system,
    const string& folder
)
{
    if (!inputFileExists(folder + "trains.txt") ||
        !inputFileExists(folder + "stations.txt") ||
        !inputFileExists(folder + "routes.txt") ||
        !inputFileExists(folder + "schedules.txt") ||
        !inputFileExists(folder + "stops.txt"))
    {
        return false;
    }

    system.clearData();

    if (!loadTrains(system, folder + "trains.txt"))
    {
        return false;
    }

    if (!loadStations(system, folder + "stations.txt"))
    {
        return false;
    }

    if (!loadRoutes(system, folder + "routes.txt"))
    {
        return false;
    }

    if (!loadSchedules(system, folder + "schedules.txt"))
    {
        return false;
    }

    if (!loadStops(system, folder + "stops.txt"))
    {
        return false;
    }

    return true;
}

