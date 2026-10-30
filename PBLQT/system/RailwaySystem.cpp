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
    for (int i = 0; i < trains.getSize(); ++i)
        delete trains.getAt(i);
    for (int i = 0; i < stations.getSize(); ++i)
        delete stations.getAt(i);
    for (int i = 0; i < routes.getSize(); ++i)
        delete routes.getAt(i);
    for (int i = 0; i < schedules.getSize(); ++i)
        delete schedules.getAt(i);

    trains.clear();
    stations.clear();
    routes.clear();
    schedules.clear();
    graph.clear();
}

bool RailwaySystem::addTrain(Train* x)
{
    if (!x || x->getTrainId().empty() || x->getTrainName().empty() || x->getTrainType().empty() ||
        x->getCapacity() <= 0 || x->getMaxSpeed() <= 0 || x->getStatus().empty() || trains.contains(x->getTrainId()))
        return false;
    return trains.insert(x->getTrainId(), x);
}

bool RailwaySystem::trainUsed(const string& id) const
{
    for (int i = 0; i < schedules.getSize(); ++i)
    {
        Schedule* s = schedules.getAt(i);
        if (s && s->getTrainId() == id)
            return true;
    }
    return false;
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
    if (!value || trainUsed(id))
        return false;
    delete value;
    return trains.remove(id);
}

bool RailwaySystem::updateTrain(const string& id, const string& name, const string& type, int cap, double speed,
                                const string& status)
{
    Train* x = findTrain(id);
    if (!x || name.empty() || type.empty() || cap <= 0 || speed <= 0 || status.empty())
        return false;
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
    for (int i = 0; i < trains.getSize(); ++i)
    {
        Train* x = trains.getAt(i);
        if (x)
            x->displayInfo();
    }
}

bool RailwaySystem::addStation(Station* x)
{
    if (!x || x->getStationId().empty() || x->getStationName().empty() || x->getNumberOfTracks() <= 0 ||
        stations.contains(x->getStationId()))
        return false;
    if (!graph.addVertex(x->getStationId()))
        return false;
    if (!stations.insert(x->getStationId(), x))
    {
        graph.removeVertex(x->getStationId());
        return false;
    }
    return true;
}

bool RailwaySystem::stationUsed(const string& id) const
{
    for (int i = 0; i < routes.getSize(); ++i)
    {
        Route* r = routes.getAt(i);
        if (r && (r->getFromStationId() == id || r->getToStationId() == id))
            return true;
    }

    for (int i = 0; i < schedules.getSize(); ++i)
    {
        Schedule* s = schedules.getAt(i);
        if (s && (s->getDepartureStationId() == id || s->getDestinationStationId() == id))
            return true;
    }

    return false;
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
    if (!value || stationUsed(id))
        return false;
    graph.removeVertex(id);
    delete value;
    return stations.remove(id);
}

bool RailwaySystem::updateStation(const string& id, const string& name, const string& location, int tracks)
{
    Station* x = findStation(id);
    if (!x || tracks <= 0)
        return false;
    x->setStationName(name);
    x->setLocation(location);
    x->setNumberOfTracks(tracks);
    return true;
}

void RailwaySystem::displayStations() const
{
    cout << "\n===== DANH SACH GA =====\n";
    for (int i = 0; i < stations.getSize(); ++i)
    {
        Station* x = stations.getAt(i);
        if (x)
            x->displayInfo();
    }
}

bool RailwaySystem::addRoute(Route* x)
{
    if (!x || x->getRouteId().empty() || x->getDistance() <= 0 || x->getTravelTime() <= 0 || x->getStatus().empty() ||
        routes.contains(x->getRouteId()))
        return false;
    if (x->getFromStationId() == x->getToStationId())
        return false;
    if (!findStation(x->getFromStationId()) || !findStation(x->getToStationId()))
        return false;
    if (!graph.addUndirectedEdge(x->getFromStationId(), x->getToStationId(), x->getDistance(), x->getTravelTime()))
        return false;
    if (!routes.insert(x->getRouteId(), x))
    {
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
    if (!r)
        return false;
    graph.removeUndirectedEdge(r->getFromStationId(), r->getToStationId());
    delete r;
    return routes.remove(id);
}

bool RailwaySystem::updateRoute(const string& id, double dist, int time, const string& status)
{
    Route* r = findRoute(id);
    if (!r || dist <= 0 || time <= 0)
        return false;
    r->setDistance(dist);
    r->setTravelTime(time);
    r->setStatus(status);
    return graph.updateUndirectedEdge(r->getFromStationId(), r->getToStationId(), dist, time);
}

void RailwaySystem::displayRoutes() const
{
    cout << "\n===== DANH SACH TUYEN =====\n";
    for (int i = 0; i < routes.getSize(); ++i)
    {
        Route* x = routes.getAt(i);
        if (x)
            x->displayInfo();
    }
}

bool RailwaySystem::addSchedule(Schedule* x)
{
    if (!x || x->getScheduleId().empty() || x->getPriority() < 0 || x->getStatus().empty() ||
        x->getDepartureDate().empty())
        return false;

    if (schedules.contains(x->getScheduleId()))
        return false;

    if (!x->isValidTime())
        return false;

    if (!findTrain(x->getTrainId()))
        return false;

    if (!findStation(x->getDepartureStationId()) || !findStation(x->getDestinationStationId()))
        return false;
    if (x->getDepartureStationId() == x->getDestinationStationId())
        return false;

    return schedules.insert(x->getScheduleId(), x);
}

bool RailwaySystem::updateSchedule(const string& id, const Schedule& data)
{
    Schedule* schedule = findSchedule(id);
    if (!schedule || !findTrain(data.getTrainId()) || !findStation(data.getDepartureStationId()) ||
        !findStation(data.getDestinationStationId()) ||
        data.getDepartureStationId() == data.getDestinationStationId() || data.getDepartureDate().empty() ||
        data.getStatus().empty() || data.getPriority() < 0 || !data.isValidTime())
        return false;

    bool routeChanged = schedule->getDepartureStationId() != data.getDepartureStationId() ||
                        schedule->getDestinationStationId() != data.getDestinationStationId();
    int departureShift = data.getDepartureTime() - schedule->getDepartureTime();
    int stopDuration = 0;

    if (!routeChanged)
    {
        const StopList& stops = schedule->getStops();
        for (int i = 0; i < stops.getSize(); ++i)
        {
            const Stop* stop = stops.get(i);
            if (stop)
            {
                stopDuration += stop->getDepartureTime() - stop->getArrivalTime();
                if (stop->getArrivalTime() + departureShift < 0 || stop->getDepartureTime() + departureShift < 0)
                    return false;
            }
        }
    }

    int newArrivalTime = data.getArrivalTime() + stopDuration;
    if (newArrivalTime < 0)
        return false;

    schedule->setTrainId(data.getTrainId());
    schedule->setDepartureStationId(data.getDepartureStationId());
    schedule->setDestinationStationId(data.getDestinationStationId());
    schedule->setDepartureTime(data.getDepartureTime());
    schedule->setArrivalTime(newArrivalTime);
    schedule->setPriority(data.getPriority());
    schedule->setStatus(data.getStatus());
    schedule->setDepartureDate(data.getDepartureDate());

    if (routeChanged)
    {
        schedule->getStops().clear();
    }
    else if (departureShift != 0)
    {
        StopList& stops = schedule->getStops();
        for (int i = 0; i < stops.getSize(); ++i)
        {
            Stop* stop = stops.get(i);
            if (stop)
            {
                stop->setArrivalTime(stop->getArrivalTime() + departureShift);
                stop->setDepartureTime(stop->getDepartureTime() + departureShift);
            }
        }
    }

    return true;
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
    if (!value)
        return false;
    delete value;
    return schedules.remove(id);
}

bool RailwaySystem::addStopToSchedule(const string& scheduleId, const Stop& stop, bool updateTimes)
{
    Schedule* schedule = findSchedule(scheduleId);
    if (!schedule || !findStation(stop.getStationId()))
        return false;

    int stopDuration = stop.getDepartureTime() - stop.getArrivalTime();
    if (updateTimes && stopDuration < 0)
        return false;

    if (!schedule->addStop(stop))
        return false;

    if (updateTimes)
    {
        StopList& stops = schedule->getStops();
        for (int i = 0; i < stops.getSize(); ++i)
        {
            Stop* s = stops.get(i);
            if (s && s->getOrder() > stop.getOrder())
            {
                s->setArrivalTime(s->getArrivalTime() + stopDuration);
                s->setDepartureTime(s->getDepartureTime() + stopDuration);
            }
        }
        schedule->setArrivalTime(schedule->getArrivalTime() + stopDuration);
    }

    return true;
}

bool RailwaySystem::removeStopFromSchedule(const string& scheduleId, int order, bool updateTimes)
{
    Schedule* schedule = findSchedule(scheduleId);
    if (!schedule)
        return false;

    StopList& stops = schedule->getStops();
    const Stop* stop = nullptr;
    for (int i = 0; i < stops.getSize(); ++i)
    {
        const Stop* current = stops.get(i);
        if (current && current->getOrder() == order)
        {
            stop = current;
            break;
        }
    }
    if (!stop)
        return false;

    int stopDuration = stop->getDepartureTime() - stop->getArrivalTime();
    if (!schedule->removeStopByOrder(order))
        return false;

    if (updateTimes)
    {
        for (int i = 0; i < stops.getSize(); ++i)
        {
            Stop* current = stops.get(i);
            if (current && current->getOrder() > order)
            {
                current->setArrivalTime(current->getArrivalTime() - stopDuration);
                current->setDepartureTime(current->getDepartureTime() - stopDuration);
            }
        }
        schedule->setArrivalTime(schedule->getArrivalTime() - stopDuration);
    }

    return true;
}

bool RailwaySystem::updateStopInSchedule(const string& scheduleId, int oldOrder, const Stop& newStop)
{
    Schedule* schedule = findSchedule(scheduleId);
    if (!schedule)
        return false;

    const Stop* oldStop = nullptr;
    const StopList& stops = schedule->getStops();
    for (int i = 0; i < stops.getSize(); ++i)
    {
        const Stop* current = stops.get(i);
        if (current && current->getOrder() == oldOrder)
        {
            oldStop = current;
            break;
        }
    }
    if (!oldStop)
        return false;

    Stop backup = *oldStop;
    if (!removeStopFromSchedule(scheduleId, oldOrder, true))
        return false;

    if (addStopToSchedule(scheduleId, newStop, true))
        return true;

    addStopToSchedule(scheduleId, backup, true);
    return false;
}

void RailwaySystem::displaySchedules() const
{
    cout << "\n===== DANH SACH LICH CHAY =====\n";
    for (int i = 0; i < schedules.getSize(); ++i)
    {
        Schedule* x = schedules.getAt(i);
        if (x)
            x->displaySchedule();
    }
}

void RailwaySystem::displaySchedulesSortedByTime() const
{
    cout << "\n===== LICH CHAY THEO GIO XUAT PHAT (som -> muon) =====\n";

    ScheduleBST bst;

    for (int i = 0; i < schedules.getSize(); ++i)
    {
        Schedule* x = schedules.getAt(i);
        if (x)
            bst.insert(x->getDepartureTime(), x);
    }

    if (bst.isEmpty())
    {
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

    for (int i = 0; i < schedules.getSize(); ++i)
    {
        Schedule* x = schedules.getAt(i);
        if (x)
            bst.insert(x->getPriority(), x);
    }

    if (bst.isEmpty())
    {
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

void RailwaySystem::displayGraph() const
{
    graph.display();
}

PathResult RailwaySystem::shortestPath(const string& start, const string& target, bool byDistance) const
{
    return graph.dijkstra(start, target, byDistance);
}

bool RailwaySystem::hasConflict(const string& a, const string& b, string& reason) const
{
    const Schedule* x = findSchedule(a);
    const Schedule* y = findSchedule(b);
    if (!x || !y)
    {
        reason = "Khong tim thay lich";
        return false;
    }
    if (a == b)
    {
        reason = "Hai ma lich phai khac nhau";
        return false;
    }
    if (detector.sameTrain(*x, *y))
    {
        reason = "Cung tau va thoi gian bi chong lan";
        return true;
    }
    if (detector.sameEndToEndRoute(*x, *y))
    {
        reason = "Cung tuyen va thoi gian bi chong lan";
        return true;
    }
    string segment;
    if (detector.segmentConflict(*x, *y, segment))
    {
        reason = "Cung doan duong: " + segment;
        return true;
    }
    if (detector.stationStopConflict(*x, *y, segment))
    {
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
    if (!x || !y)
        return false;

    string reason;
    if (!hasConflict(a, b, reason))
        return false;

    Schedule* higher = nullptr;
    Schedule* lower = nullptr;

    if (dispatcher.compare(*x, *y))
    {
        higher = x;
        lower = y;
    }
    else
    {
        higher = y;
        lower = x;
    }

    const int BUFFER = 30;
    long long higherArrival = TimeUtils::toAbsoluteMinutes(higher->getDepartureDate(), higher->getArrivalTime());
    long long lowerDeparture = TimeUtils::toAbsoluteMinutes(lower->getDepartureDate(), lower->getDepartureTime());
    int shift = static_cast<int>(higherArrival + BUFFER - lowerDeparture);

    if (shift <= 0)
        shift = BUFFER;

    if (dispatcher.shiftSchedule(*lower, shift))
        return true;

    long long higherDeparture = TimeUtils::toAbsoluteMinutes(higher->getDepartureDate(), higher->getDepartureTime());
    long long lowerArrival = TimeUtils::toAbsoluteMinutes(lower->getDepartureDate(), lower->getArrivalTime());
    int earlyShift = static_cast<int>(higherDeparture - (lowerArrival + BUFFER));
    if (earlyShift > 0 && higher->getDepartureTime() - earlyShift >= 0)
    {

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

int RailwaySystem::getTrainCount() const
{
    return trains.getSize();
}

int RailwaySystem::getStationCount() const
{
    return stations.getSize();
}

int RailwaySystem::getRouteCount() const
{
    return routes.getSize();
}

int RailwaySystem::getScheduleCount() const
{
    return schedules.getSize();
}

Train* RailwaySystem::getTrainAt(int position) const
{
    return trains.getAt(position);
}

Station* RailwaySystem::getStationAt(int position) const
{
    return stations.getAt(position);
}

Route* RailwaySystem::getRouteAt(int position) const
{
    return routes.getAt(position);
}

Schedule* RailwaySystem::getScheduleAt(int position) const
{
    return schedules.getAt(position);
}

bool RailwaySystem::loadAllData(const string& folder)
{
    return FileManager::loadAll(*this, folder);
}

bool RailwaySystem::saveAllData(const string& folder) const
{
    return FileManager::saveAll(*this, folder);
}
