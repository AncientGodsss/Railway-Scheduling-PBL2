#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include <string>
#include "../model/Stop.h"
using std::string;

struct StopNode
{
    Stop data;
    StopNode* prev;
    StopNode* next;
    StopNode(const Stop& value) : data(value), prev(nullptr), next(nullptr)
    {
    }
};

class StopList
{
private:
    StopNode* head;
    StopNode* tail;
    int size;

public:
    StopList() : head(nullptr), tail(nullptr), size(0)
    {
    }
    ~StopList()
    {
        clear();
    }
    StopList(const StopList& other) : head(nullptr), tail(nullptr), size(0)
    {
        for (int i = 0; i < other.size; ++i)
        {
            const Stop* value = other.get(i);
            if (value != nullptr)
                pushBack(*value);
        }
    }
    StopList& operator=(const StopList& other)
    {
        if (this != &other)
        {
            clear();
            for (int i = 0; i < other.size; ++i)
            {
                const Stop* value = other.get(i);
                if (value != nullptr)
                    pushBack(*value);
            }
        }
        return *this;
    }
    bool isEmpty() const
    {
        return size == 0;
    }
    int getSize() const
    {
        return size;
    }
    void pushBack(const Stop& value)
    {
        StopNode* node = new StopNode(value);
        if (tail == nullptr)
            head = tail = node;
        else
        {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        ++size;
    }
    void insertAt(int index, const Stop& value)
    {
        if (index < 0)
            index = 0;
        if (index >= size)
        {
            pushBack(value);
            return;
        }
        StopNode* current = head;
        for (int i = 0; i < index; ++i)
            current = current->next;
        StopNode* node = new StopNode(value);
        node->next = current;
        node->prev = current->prev;
        if (current->prev != nullptr)
            current->prev->next = node;
        else
            head = node;
        current->prev = node;
        ++size;
    }
    Stop* get(int index)
    {
        if (index < 0 || index >= size)
            return nullptr;
        StopNode* current = head;
        for (int i = 0; i < index; ++i)
            current = current->next;
        return &current->data;
    }
    const Stop* get(int index) const
    {
        if (index < 0 || index >= size)
            return nullptr;
        StopNode* current = head;
        for (int i = 0; i < index; ++i)
            current = current->next;
        return &current->data;
    }
    bool removeAt(int index)
    {
        if (index < 0 || index >= size)
            return false;
        StopNode* current = head;
        for (int i = 0; i < index; ++i)
            current = current->next;
        if (current->prev != nullptr)
            current->prev->next = current->next;
        else
            head = current->next;
        if (current->next != nullptr)
            current->next->prev = current->prev;
        else
            tail = current->prev;
        delete current;
        --size;
        return true;
    }
    void clear()
    {
        while (head != nullptr)
        {
            StopNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }
};

struct StringNode
{
    string data;
    StringNode* prev;
    StringNode* next;
    StringNode(const string& value) : data(value), prev(nullptr), next(nullptr)
    {
    }
};

class StringList
{
private:
    StringNode* head;
    StringNode* tail;
    int size;

public:
    StringList() : head(nullptr), tail(nullptr), size(0)
    {
    }
    ~StringList()
    {
        clear();
    }
    StringList(const StringList& other) : head(nullptr), tail(nullptr), size(0)
    {
        for (int i = 0; i < other.size; ++i)
        {
            const string* value = other.get(i);
            if (value != nullptr)
                pushBack(*value);
        }
    }
    StringList& operator=(const StringList& other)
    {
        if (this != &other)
        {
            clear();
            for (int i = 0; i < other.size; ++i)
            {
                const string* value = other.get(i);
                if (value != nullptr)
                    pushBack(*value);
            }
        }
        return *this;
    }
    bool isEmpty() const
    {
        return size == 0;
    }
    int getSize() const
    {
        return size;
    }
    void pushFront(const string& value)
    {
        StringNode* node = new StringNode(value);
        if (head == nullptr)
            head = tail = node;
        else
        {
            node->next = head;
            head->prev = node;
            head = node;
        }
        ++size;
    }
    void pushBack(const string& value)
    {
        StringNode* node = new StringNode(value);
        if (tail == nullptr)
            head = tail = node;
        else
        {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        ++size;
    }
    string* get(int index)
    {
        if (index < 0 || index >= size)
            return nullptr;
        StringNode* current = head;
        for (int i = 0; i < index; ++i)
            current = current->next;
        return &current->data;
    }
    const string* get(int index) const
    {
        if (index < 0 || index >= size)
            return nullptr;
        StringNode* current = head;
        for (int i = 0; i < index; ++i)
            current = current->next;
        return &current->data;
    }
    bool contains(const string& value) const
    {
        StringNode* current = head;
        while (current != nullptr)
        {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }
    void clear()
    {
        while (head != nullptr)
        {
            StringNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }
};
#endif
