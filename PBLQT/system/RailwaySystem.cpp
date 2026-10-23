#include "RailwaySystem.h"
#include "../service/FileManager.h"
#include "../service/PriorityStrategy.h"
#include "../service/EarliestStrategy.h"
#include "../data_structure/BST.h"

 
 
 

RailwaySystem::RailwaySystem()
{
    strategy = new PriorityStrategy();
    dispatcher.setStrategy(strategy);
}

RailwaySystem::~RailwaySystem()
{
    clearData();
    delete strategy;
}

void RailwaySystem::clearData()
{
    trains.forEach([](string, Train* x)       { delete x; });
    stations.forEach([](string, Station* x)   { delete x; });
    routes.forEach([](string, Route* x)       { delete x; });
    schedules.forEach([](string, Schedule* x) { delete x; });
    trains.clear();
    stations.clear();
    routes.clear();
    schedules.clear();
    graph.clear();
}

 
 
 

bool RailwaySystem::addTrain(Train* x)
{
    if (!x || x->getTrainId().empty() || x->getTrainName().empty() ||
        x->getTrainType().empty() || x->getCapacity() <= 0 ||
        x->getMaxSpeed() <= 0 || x->getStatus().empty() ||
        trains.contains(x->getTrainId())) return false;
    return trains.insert(x->getTrainId(), x);
}

bool RailwaySystem::trainUsed(const string& id) const
{
    bool used = false;
    schedules.forEach([&](string, Schedule* s) {
        if (s && s->getTrainId() == id) used = true;
    });
    return used;
}

Train* RailwaySystem::findTrain(const string& id)
{
    return trains.search(id);
}

const Train* RailwaySystem::findTrain(const string& id) const
{
    return trains.search(id);
}

bool RailwaySystem::removeTrain(const string& id)
{
    Train* value = trains.search(id);
    if (!value || trainUsed(id)) return false;
    delete value;
    return trains.remove(id);
}

bool RailwaySystem::updateTrain(const string& id, const string& name,
                                const string& type, int cap,
                                double speed, const string& status)
{
    Train* x = findTrain(id);
    if (!x || name.empty() || type.empty() || cap <= 0 ||
        speed <= 0 || status.empty()) return false;
    x->setTrainName(name);
    x->setTrainType(type);
    x->setCapacity(cap);
    x->setMaxSpeed(speed);
    x->setStatus(status);
    return true;
}

void RailwaySystem::displayTrains() const
{
    cout << "\n===== DANH SACH TAU =====\n";
    trains.forEach([](string, Train* x) { if (x) x->displayInfo(); });
}

 
 
 

bool RailwaySystem::addStation(Station* x)
{
    if (!x || x->getStationId().empty() || x->getStationName().empty() ||
        x->getNumberOfTracks() <= 0 || stations.contains(x->getStationId())) return false;
    if (!graph.addVertex(x->getStationId())) return false;
    if (!stations.insert(x->getStationId(), x)) {
        graph.removeVertex(x->getStationId());
        return false;
    }
    return true;
}

bool RailwaySystem::stationUsed(const string& id) const
{
    bool used = false;
    routes.forEach([&](string, Route* r) {
        if (r && (r->getFromStationId() == id || r->getToStationId() == id))
            used = true;
    });
    schedules.forEach([&](string, Schedule* s) {
        if (s && (s->getDepartureStationId() == id || s->getDestinationStationId() == id))
            used = true;
    });
    return used;
}

Station* RailwaySystem::findStation(const string& id)
{
    return stations.search(id);
}

const Station* RailwaySystem::findStation(const string& id) const
{
    return stations.search(id);
}

bool RailwaySystem::removeStation(const string& id)
{
    Station* value = stations.search(id);
    if (!value || stationUsed(id)) return false;
    graph.removeVertex(id);
    delete value;
    return stations.remove(id);
}

bool RailwaySystem::updateStation(const string& id, const string& name,
                                  const string& location, int tracks)
{
    Station* x = findStation(id);
    if (!x || tracks <= 0) return false;
    x->setStationName(name);
    x->setLocation(location);
    x->setNumberOfTracks(tracks);
    return true;
}

void RailwaySystem::displayStations() const
{
    cout << "\n===== DANH SACH GA =====\n";
    stations.forEach([](string, Station* x) { if (x) x->displayInfo(); });
}

 
 
 

bool RailwaySystem::addRoute(Route* x)
{
    if (!x || x->getRouteId().empty() || x->getDistance() <= 0 ||
        x->getTravelTime() <= 0 || x->getStatus().empty() ||
        routes.contains(x->getRouteId())) return false;
    if (x->getFromStationId() == x->getToStationId()) return false;
    if (!findStation(x->getFromStationId()) || !findStation(x->getToStationId())) return false;
    if (!graph.addUndirectedEdge(x->getFromStationId(), x->getToStationId(),
                                  x->getDistance(), x->getTravelTime())) return false;
    if (!routes.insert(x->getRouteId(), x)) {
        graph.removeUndirectedEdge(x->getFromStationId(), x->getToStationId());
        return false;
    }
    return true;
}

Route* RailwaySystem::findRoute(const string& id)
{
    return routes.search(id);
}

bool RailwaySystem::removeRoute(const string& id)
{
    Route* r = routes.search(id);
    if (!r) return false;
    graph.removeUndirectedEdge(r->getFromStationId(), r->getToStationId());
    delete r;
    return routes.remove(id);
}

bool RailwaySystem::updateRoute(const string& id, double dist,
                                int time, const string& status)
{
    Route* r = findRoute(id);
    if (!r || dist <= 0 || time <= 0) return false;
    r->setDistance(dist);
    r->setTravelTime(time);
    r->setStatus(status);
    return graph.updateUndirectedEdge(r->getFromStationId(), r->getToStationId(), dist, time);
}

void RailwaySystem::displayRoutes() const
{
    cout << "\n===== DANH SACH TUYEN =====\n";
    routes.forEach([](string, Route* x) { if (x) x->displayInfo(); });
}

 
 
 

bool RailwaySystem::addSchedule(Schedule* x)
{
    if (!x || x->getScheduleId().empty() || x->getPriority() < 0 ||
        x->getStatus().empty() || x->getDepartureDate().empty()) return false;

     
    if (schedules.contains(x->getScheduleId())) return false;

     
    if (!x->isValidTime()) return false;

     
    if (!findTrain(x->getTrainId())) return false;

     
    if (!findStation(x->getDepartureStationId()) ||
        !findStation(x->getDestinationStationId())) return false;
    if (x->getDepartureStationId() == x->getDestinationStationId()) return false;

    return schedules.insert(x->getScheduleId(), x);
}

Schedule* RailwaySystem::findSchedule(const string& id)
{
    return schedules.search(id);
}

const Schedule* RailwaySystem::findSchedule(const string& id) const
{
    return schedules.search(id);
}

bool RailwaySystem::removeSchedule(const string& id)
{
    Schedule* value = schedules.search(id);
    if (!value) return false;
    delete value;
    return schedules.remove(id);
}

bool RailwaySystem::addStopToSchedule(const string& scheduleId, const Stop& stop)
{
    Schedule* schedule = findSchedule(scheduleId);
    if (!schedule || !findStation(stop.getStationId())) return false;
    return schedule->addStop(stop);
}

void RailwaySystem::displaySchedules() const
{
    cout << "\n===== DANH SACH LICH CHAY =====\n";
    schedules.forEach([](string, Schedule* x) { if (x) x->displaySchedule(); });
}

 
void RailwaySystem::displaySchedulesSortedByTime() const
{
    cout << "\n===== LICH CHAY THEO GIO XUAT PHAT (som -> muon) =====\n";

    ScheduleBST bst;

     
    schedules.forEach([&](string, Schedule* x) {
        if (x) bst.insert(x->getDepartureTime(), x);
    });

    if (bst.isEmpty()) {
        cout << "Chua co lich nao.\n";
        return;
    }

     
    int capacity = schedules.getSize();
    Schedule** result = new Schedule*[capacity];
    int count = bst.getAscending(result, capacity);

    for (int i = 0; i < count; ++i)
    {
        if (result[i])
        {
            result[i]->displaySchedule();
        }
    }

    delete[] result;
}

 
void RailwaySystem::displaySchedulesSortedByPriority() const
{
    cout << "\n===== LICH CHAY THEO DO UU TIEN (cao -> thap) =====\n";

    ScheduleBST bst;

     
    schedules.forEach([&](string, Schedule* x) {
        if (x) bst.insert(x->getPriority(), x);
    });

    if (bst.isEmpty()) {
        cout << "Chua co lich nao.\n";
        return;
    }

     
    int capacity = schedules.getSize();
    Schedule** result = new Schedule*[capacity];
    int count = bst.getDescending(result, capacity);

    for (int i = 0; i < count; ++i)
    {
        if (result[i])
        {
            result[i]->displaySchedule();
        }
    }

    delete[] result;
}

 
 
 

void RailwaySystem::displayGraph() const { graph.display(); }

void RailwaySystem::bfs(const string& start) const { graph.bfs(start); }

void RailwaySystem::dfs(const string& start) const { graph.dfs(start); }

PathResult RailwaySystem::shortestPath(const string& start,
                                       const string& target,
                                       bool byDistance) const
{
    return graph.dijkstra(start, target, byDistance);
}

 
 
 

bool RailwaySystem::hasConflict(const string& a, const string& b,
                                string& reason) const
{
    const Schedule* x = findSchedule(a);
    const Schedule* y = findSchedule(b);
    if (!x || !y) { reason = "Khong tim thay lich"; return false; }
    if (a == b) { reason = "Hai ma lich phai khac nhau"; return false; }
    if (x->getDepartureDate() != y->getDepartureDate()) {
        reason = "Khac ngay khoi hanh nen khong xung dot";
        return false;
    }

    if (detector.sameTrain(*x, *y)) {
        reason = "Cung tau va thoi gian bi chong lan";
        return true;
    }
    if (detector.sameEndToEndRoute(*x, *y)) {
        reason = "Cung tuyen va thoi gian bi chong lan";
        return true;
    }
    string segment;
    if (detector.segmentConflict(*x, *y, segment)) {
        reason = "Cung doan duong: " + segment;
        return true;
    }
    if (detector.stationStopConflict(*x, *y, segment)) {
        reason = "Trung gio dung tai ga: " + segment;
        return true;
    }
    reason = "Khong co xung dot";
    return false;
}

bool RailwaySystem::dispatch(const string& a, const string& b)
{
    Schedule* x = findSchedule(a);
    Schedule* y = findSchedule(b);
    if (!x || !y) return false;

    string reason;
    if (!hasConflict(a, b, reason)) return false;

     
    Schedule* higher = nullptr;
    Schedule* lower  = nullptr;

    if (dispatcher.compare(*x, *y)) { higher = x; lower = y; }
    else                            { higher = y; lower = x; }

     
    const int BUFFER = 30;
    int newDep = higher->getArrivalTime() + BUFFER;
    int shift  = newDep - lower->getDepartureTime();

     
    if (shift <= 0) shift = BUFFER;

     
    if (dispatcher.shiftSchedule(*lower, shift)) return true;

     
    int earlyShift = higher->getDepartureTime() - (lower->getArrivalTime() + BUFFER);
    if (earlyShift > 0 && higher->getDepartureTime() - earlyShift >= 0) {
         
        higher->shiftSchedule(-earlyShift);   
        dispatcher.addWaiting(higher->getTrainId());
        return true;
    }

     
    dispatcher.addWaiting(lower->getTrainId());
    return false;
}

 
void RailwaySystem::setSchedulingStrategy(int type)
{
    SchedulingStrategy* newStrategy = nullptr;

    if (type == 1)
        newStrategy = new PriorityStrategy();
    else if (type == 2)
        newStrategy = new EarliestStrategy();
    else
        return;  

    delete strategy;
    strategy = newStrategy;
    dispatcher.setStrategy(strategy);
}

 
 
 

int RailwaySystem::getTrainCount()    const
{
    int n = 0;
    trains.forEach([&](string, Train*) { ++n; });
    return n;
}

int RailwaySystem::getStationCount()  const
{
    int n = 0;
    stations.forEach([&](string, Station*) { ++n; });
    return n;
}

int RailwaySystem::getRouteCount()    const
{
    int n = 0;
    routes.forEach([&](string, Route*) { ++n; });
    return n;
}

int RailwaySystem::getScheduleCount() const
{
    int n = 0;
    schedules.forEach([&](string, Schedule*) { ++n; });
    return n;
}

 
 
 

bool RailwaySystem::loadAllData(const string& folder)
{
    return FileManager::loadAll(*this, folder);
}

bool RailwaySystem::saveAllData(const string& folder) const
{
    return FileManager::saveAll(*this, folder);
}
