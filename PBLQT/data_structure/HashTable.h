#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <string>
using std::string;
class Train;
class Station;
class Route;
class Schedule;

struct PointerHashNode
{
    string key;
    void* value;
    PointerHashNode* next;
    PointerHashNode(const string& valueKey, void* valuePointer) : key(valueKey), value(valuePointer), next(nullptr)
    {
    }
};

class PointerHashTable
{
private:
    PointerHashNode** table;
    int capacity;
    int size;
    PointerHashTable(const PointerHashTable& other);
    PointerHashTable& operator=(const PointerHashTable& other);

    int hashString(const string& key) const
    {
        unsigned long hashValue = 0;
        for (int i = 0; i < static_cast<int>(key.length()); ++i)
        {
            char character = key[i];
            hashValue = hashValue * 131u + static_cast<unsigned char>(character);
        }
        return static_cast<int>(hashValue % capacity);
    }

public:
    PointerHashTable(int initialCapacity = 101) : capacity(initialCapacity), size(0)
    {
        table = new PointerHashNode*[capacity];
        for (int i = 0; i < capacity; ++i)
            table[i] = nullptr;
    }
    ~PointerHashTable()
    {
        clear();
        delete[] table;
    }
    bool insert(const string& key, void* value)
    {
        int index = hashString(key);
        PointerHashNode* current = table[index];
        while (current != nullptr)
        {
            if (current->key == key)
                return false;
            current = current->next;
        }
        PointerHashNode* node = new PointerHashNode(key, value);
        node->next = table[index];
        table[index] = node;
        ++size;
        return true;
    }
    void* search(const string& key) const
    {
        int index = hashString(key);
        PointerHashNode* current = table[index];
        while (current != nullptr)
        {
            if (current->key == key)
                return current->value;
            current = current->next;
        }
        return nullptr;
    }
    bool contains(const string& key) const
    {
        return search(key) != nullptr;
    }
    bool remove(const string& key)
    {
        int index = hashString(key);
        PointerHashNode* current = table[index];
        PointerHashNode* previous = nullptr;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                if (previous == nullptr)
                    table[index] = current->next;
                else
                    previous->next = current->next;
                delete current;
                --size;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }
    int getSize() const
    {
        return size;
    }
    void* getAt(int position) const
    {
        if (position < 0 || position >= size)
            return nullptr;

        int currentPosition = 0;
        for (int i = 0; i < capacity; ++i)
        {
            PointerHashNode* current = table[i];
            while (current != nullptr)
            {
                if (currentPosition == position)
                    return current->value;

                ++currentPosition;
                current = current->next;
            }
        }

        return nullptr;
    }
    void clear()
    {
        for (int i = 0; i < capacity; ++i)
        {
            PointerHashNode* current = table[i];
            while (current != nullptr)
            {
                PointerHashNode* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        size = 0;
    }
};

class TrainHashTable
{
private:
    PointerHashTable data;

public:
    bool insert(const string& key, Train* value)
    {
        return data.insert(key, value);
    }
    Train* search(const string& key) const
    {
        return static_cast<Train*>(data.search(key));
    }
    bool contains(const string& key) const
    {
        return data.contains(key);
    }
    bool remove(const string& key)
    {
        return data.remove(key);
    }
    int getSize() const
    {
        return data.getSize();
    }
    void clear()
    {
        data.clear();
    }
    Train* getAt(int position) const
    {
        return static_cast<Train*>(data.getAt(position));
    }
};

class StationHashTable
{
private:
    PointerHashTable data;

public:
    bool insert(const string& key, Station* value)
    {
        return data.insert(key, value);
    }
    Station* search(const string& key) const
    {
        return static_cast<Station*>(data.search(key));
    }
    bool contains(const string& key) const
    {
        return data.contains(key);
    }
    bool remove(const string& key)
    {
        return data.remove(key);
    }
    int getSize() const
    {
        return data.getSize();
    }
    void clear()
    {
        data.clear();
    }
    Station* getAt(int position) const
    {
        return static_cast<Station*>(data.getAt(position));
    }
};

class RouteHashTable
{
private:
    PointerHashTable data;

public:
    bool insert(const string& key, Route* value)
    {
        return data.insert(key, value);
    }
    Route* search(const string& key) const
    {
        return static_cast<Route*>(data.search(key));
    }
    bool contains(const string& key) const
    {
        return data.contains(key);
    }
    bool remove(const string& key)
    {
        return data.remove(key);
    }
    int getSize() const
    {
        return data.getSize();
    }
    void clear()
    {
        data.clear();
    }
    Route* getAt(int position) const
    {
        return static_cast<Route*>(data.getAt(position));
    }
};

class ScheduleHashTable
{
private:
    PointerHashTable data;

public:
    bool insert(const string& key, Schedule* value)
    {
        return data.insert(key, value);
    }
    Schedule* search(const string& key) const
    {
        return static_cast<Schedule*>(data.search(key));
    }
    bool contains(const string& key) const
    {
        return data.contains(key);
    }
    bool remove(const string& key)
    {
        return data.remove(key);
    }
    int getSize() const
    {
        return data.getSize();
    }
    void clear()
    {
        data.clear();
    }
    Schedule* getAt(int position) const
    {
        return static_cast<Schedule*>(data.getAt(position));
    }
};
#endif
