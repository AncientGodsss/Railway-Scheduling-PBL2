#ifndef RAILWAY_SYSTEM_H
#define RAILWAY_SYSTEM_H

#include <iostream>
#include <string>
#include "../model/Train.h"
#include "../model/Station.h"
#include "../model/Route.h"
#include "../model/Schedule.h"
#include "../service/Dispatcher.h"
#include "../service/ConflictDetector.h"
#include "../data_structure/HashTable.h"
#include "../data_structure/Graph.h"

using namespace std;

class FileManager;

class RailwaySystem
{
private:
    TrainHashTable trains;
    StationHashTable stations;
    RouteHashTable routes;
    ScheduleHashTable schedules;

    Graph graph;
    Dispatcher dispatcher;
    ConflictDetector detector;
    SchedulingStrategy* strategy;

    RailwaySystem(const RailwaySystem& other);
    RailwaySystem& operator=(const RailwaySystem& other);

    bool trainUsed(const string& id) const;
    bool stationUsed(const string& id) const;
    void clearData();

public:
    RailwaySystem();
    ~RailwaySystem();
    bool addTrain(Train* x);
    bool removeTrain(const string& id);
    Train* findTrain(const string& id);
    const Train* findTrain(const string& id) const;
    bool updateTrain(const string& id, const string& name, const string& type, int cap, double speed,
                     const string& status);
    void displayTrains() const;

    bool addStation(Station* x);
    bool removeStation(const string& id);
    Station* findStation(const string& id);
    const Station* findStation(const string& id) const;
    bool updateStation(const string& id, const string& name, const string& location, int tracks);
    void displayStations() const;

    bool addRoute(Route* x);
    bool removeRoute(const string& id);
    Route* findRoute(const string& id);
    bool updateRoute(const string& id, double dist, int time, const string& status);
    void displayRoutes() const;

    bool addSchedule(Schedule* x);
    bool updateSchedule(const string& id, const Schedule& data);
    bool removeSchedule(const string& id);
    bool addStopToSchedule(const string& scheduleId, const Stop& stop, bool updateTimes = false);
    bool removeStopFromSchedule(const string& scheduleId, int order, bool updateTimes = false);
    bool updateStopInSchedule(const string& scheduleId, int oldOrder, const Stop& newStop);
    Schedule* findSchedule(const string& id);
    const Schedule* findSchedule(const string& id) const;
    void displaySchedules() const;

    void displaySchedulesSortedByTime() const;
    void displaySchedulesSortedByPriority() const;

    void displayGraph() const;
    PathResult shortestPath(const string& start, const string& target, bool byDistance) const;

    bool hasConflict(const string& a, const string& b, string& reason) const;
    bool dispatch(const string& a, const string& b);

    void setSchedulingStrategy(int type);

    int getTrainCount() const;
    int getStationCount() const;
    int getRouteCount() const;
    int getScheduleCount() const;

    Train* getTrainAt(int position) const;
    Station* getStationAt(int position) const;
    Route* getRouteAt(int position) const;
    Schedule* getScheduleAt(int position) const;

    Dispatcher& getDispatcher()
    {
        return dispatcher;
    }

    bool loadAllData(const string& folder = "data/");
    bool saveAllData(const string& folder = "data/") const;

    friend class FileManager;
};

#endif
