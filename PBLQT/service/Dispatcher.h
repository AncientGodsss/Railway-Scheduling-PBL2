#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <iostream>
#include <string>

#include "../data_structure/MaxHeap.h"
#include "../data_structure/Queue.h"
#include "../data_structure/Stack.h"
#include "../model/Operation.h"
#include "../model/Schedule.h"
#include "SchedulingStrategy.h"

using namespace std;

class Dispatcher
{
private:
    StringQueue waitingQueue;
    MaxHeap priorityQueue;
    OperationStack history;

    SchedulingStrategy* strategy;

public:
    Dispatcher() : strategy(nullptr)
    {
    }

    void setStrategy(SchedulingStrategy* newStrategy)
    {
        strategy = newStrategy;
    }

    void addWaiting(const string& trainId)
    {
        waitingQueue.enqueue(trainId);

        history.push(Operation("QUEUE", trainId, "Them vao hang cho"));
    }

    void addPriority(const string& trainId, int priority)
    {
        priorityQueue.push(PriorityItem(trainId, priority));

        history.push(Operation("PRIORITY", trainId, "Them vao hang uu tien"));
    }

    string nextTrain()
    {
        PriorityItem priorityItem;

        if (priorityQueue.pop(priorityItem))
        {
            history.push(Operation("DISPATCH", priorityItem.trainId, "Dieu phoi theo uu tien"));

            return priorityItem.trainId;
        }

        string trainId;

        if (waitingQueue.dequeue(trainId))
        {
            history.push(Operation("DISPATCH", trainId, "Lay tu hang cho"));

            return trainId;
        }

        return "";
    }

    void showQueues() const
    {
        if (waitingQueue.isEmpty() && priorityQueue.isEmpty())
        {
            return;
        }

        cout << "\nQueue size=" << waitingQueue.getSize() << ", Priority size=" << priorityQueue.getSize() << "\n";
    }

    void showHistory() const
    {
        cout << "\n===== LICH SU =====\n";

        history.displayTopToBottom();
    }

    bool compare(const Schedule& first, const Schedule& second) const
    {
        if (strategy)
        {
            return strategy->higher(first, second);
        }

        return first.getPriority() > second.getPriority();
    }

    bool shiftSchedule(Schedule& schedule, int minutes)
    {
        if (minutes <= 0)
        {
            return false;
        }

        schedule.shiftSchedule(minutes);

        history.push(Operation("DELAY", schedule.getScheduleId(), "Doi lich +" + to_string(minutes) + " phut"));

        return true;
    }
};

#endif
