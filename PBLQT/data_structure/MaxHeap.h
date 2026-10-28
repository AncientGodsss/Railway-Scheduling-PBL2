#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <string>
using std::string;

struct PriorityItem
{
    string trainId;
    int priority;
    PriorityItem() : trainId(""), priority(0)
    {
    }
    PriorityItem(const string& id, int p) : trainId(id), priority(p)
    {
    }
    bool operator<(const PriorityItem& other) const
    {
        return priority < other.priority;
    }
    bool operator>(const PriorityItem& other) const
    {
        return priority > other.priority;
    }
};

class MaxHeap
{
private:
    PriorityItem* data;
    int size;
    int capacity;
    void ensureCapacity()
    {
        if (size < capacity)
            return;
        int newCap = capacity * 2;
        PriorityItem* temp = new PriorityItem[newCap];
        for (int i = 0; i < size; ++i)
            temp[i] = data[i];
        delete[] data;
        data = temp;
        capacity = newCap;
    }
    void swapVal(PriorityItem& a, PriorityItem& b)
    {
        PriorityItem t = a;
        a = b;
        b = t;
    }
    void up(int i)
    {
        while (i > 0)
        {
            int p = (i - 1) / 2;
            if (data[p].priority >= data[i].priority)
                break;
            swapVal(data[p], data[i]);
            i = p;
        }
    }
    void down(int i)
    {
        while (true)
        {
            int l = 2 * i + 1, r = 2 * i + 2, b = i;
            if (l < size && data[l].priority > data[b].priority)
                b = l;
            if (r < size && data[r].priority > data[b].priority)
                b = r;
            if (b == i)
                break;
            swapVal(data[i], data[b]);
            i = b;
        }
    }

public:
    explicit MaxHeap(int cap = 16) : size(0), capacity(cap)
    {
        data = new PriorityItem[capacity];
    }
    ~MaxHeap()
    {
        delete[] data;
    }
    bool isEmpty() const
    {
        return size == 0;
    }
    void push(const PriorityItem& x)
    {
        ensureCapacity();
        data[size] = x;
        up(size);
        ++size;
    }
    bool pop(PriorityItem& x)
    {
        if (size == 0)
            return false;
        x = data[0];
        data[0] = data[size - 1];
        --size;
        if (size)
            down(0);
        return true;
    }
    const PriorityItem& top() const
    {
        return data[0];
    }
    int getSize() const
    {
        return size;
    }
};

#endif
