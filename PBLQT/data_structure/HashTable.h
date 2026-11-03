#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>

using std::string;

template <typename T>
struct HashNode
{
    string key;
    T value;
    HashNode<T>* next;

    HashNode(const string& valueKey, const T& valueData) : key(valueKey), value(valueData), next(nullptr)
    {
    }
};

template <typename T>
class HashTable
{
private:
    HashNode<T>** table;
    int capacity;
    int size;

    HashTable(const HashTable<T>& other);
    HashTable<T>& operator=(const HashTable<T>& other);

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
    HashTable(int initialCapacity = 101) : capacity(initialCapacity), size(0)
    {
        table = new HashNode<T>*[capacity];
        for (int i = 0; i < capacity; ++i)
            table[i] = nullptr;
    }

    ~HashTable()
    {
        clear();
        delete[] table;
    }

    bool insert(const string& key, const T& value)
    {
        int index = hashString(key);
        HashNode<T>* current = table[index];

        while (current != nullptr)
        {
            if (current->key == key)
                return false;
            current = current->next;
        }

        HashNode<T>* node = new HashNode<T>(key, value);
        node->next = table[index];
        table[index] = node;
        ++size;
        return true;
    }

    T search(const string& key) const
    {
        int index = hashString(key);
        HashNode<T>* current = table[index];

        while (current != nullptr)
        {
            if (current->key == key)
                return current->value;
            current = current->next;
        }

        return T();
    }

    bool contains(const string& key) const
    {
        int index = hashString(key);
        HashNode<T>* current = table[index];

        while (current != nullptr)
        {
            if (current->key == key)
                return true;
            current = current->next;
        }

        return false;
    }

    bool remove(const string& key)
    {
        int index = hashString(key);
        HashNode<T>* current = table[index];
        HashNode<T>* previous = nullptr;

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

    T getAt(int position) const
    {
        if (position < 0 || position >= size)
            return T();

        int currentPosition = 0;
        for (int i = 0; i < capacity; ++i)
        {
            HashNode<T>* current = table[i];
            while (current != nullptr)
            {
                if (currentPosition == position)
                    return current->value;

                ++currentPosition;
                current = current->next;
            }
        }

        return T();
    }

    void clear()
    {
        for (int i = 0; i < capacity; ++i)
        {
            HashNode<T>* current = table[i];
            while (current != nullptr)
            {
                HashNode<T>* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        size = 0;
    }
};

#endif
