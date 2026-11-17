#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <iostream>
#include <string>
#include <sstream>

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
    Queue<string> waitingQueue;
    MaxHeap priorityQueue;
    Stack<Operation> history;

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
            cout << "Hàng chờ hiện đang trống.\n(Không có tàu nào đang phải chờ)\n";
            return;
        }

        cout << "========================================\n";
        cout << "⭐ HÀNG ĐỢI ƯU TIÊN (Priority Queue - MaxHeap) [" << priorityQueue.getSize() << " tàu]:\n";
        if (priorityQueue.isEmpty())
        {
            cout << "  (Trống)\n";
        }
        else
        {
            int pSize = priorityQueue.getSize();
            PriorityItem* items = new PriorityItem[pSize];
            int count = priorityQueue.getItemsSorted(items, pSize);
            for (int i = 0; i < count; ++i)
            {
                cout << "  " << (i + 1) << ". Tàu: " << items[i].trainId 
                     << "  |  Mức ưu tiên: " << items[i].priority << "\n";
            }
            delete[] items;
        }

        cout << "\n----------------------------------------\n";
        cout << "📋 HÀNG CHỜ THÔNG THƯỜNG (Queue - FIFO) [" << waitingQueue.getSize() << " tàu]:\n";
        if (waitingQueue.isEmpty())
        {
            cout << "  (Trống)\n";
        }
        else
        {
            int index = 1;
            for (const QueueNode<string>* cur = waitingQueue.getFrontNode(); cur; cur = cur->next)
            {
                cout << "  " << index++ << ". Tàu: " << cur->data 
                     << "  (Vào trước ra trước)\n";
            }
        }
        cout << "========================================\n";
    }

    void clearQueues()
    {
        waitingQueue.clear();
        priorityQueue.clear();
        history.push(Operation("CLEAR", "", "Xoa toan bo hang cho"));
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

        stringstream ss;
        ss << "Doi lich +" << minutes << " phut";
        history.push(Operation("DELAY", schedule.getScheduleId(), ss.str()));

        return true;
    }
};

#endif
