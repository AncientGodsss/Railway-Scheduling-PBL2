#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
struct QueueNode
{
    T data;
    QueueNode<T>* next;

    QueueNode(const T& value) : data(value), next(nullptr)
    {
    }
};

template <typename T>
class Queue
{
private:
    QueueNode<T>* frontNode;
    QueueNode<T>* rearNode;
    int size;

    Queue(const Queue<T>& other);
    Queue<T>& operator=(const Queue<T>& other);

public:
    Queue() : frontNode(nullptr), rearNode(nullptr), size(0)
    {
    }

    ~Queue()
    {
        clear();
    }

    bool isEmpty() const
    {
        return frontNode == nullptr;
    }

    int getSize() const
    {
        return size;
    }

    void enqueue(const T& value)
    {
        QueueNode<T>* node = new QueueNode<T>(value);

        if (rearNode == nullptr)
            frontNode = rearNode = node;
        else
        {
            rearNode->next = node;
            rearNode = node;
        }

        ++size;
    }

    bool dequeue(T& value)
    {
        if (frontNode == nullptr)
            return false;

        QueueNode<T>* temp = frontNode;
        value = temp->data;
        frontNode = frontNode->next;

        if (frontNode == nullptr)
            rearNode = nullptr;

        delete temp;
        --size;
        return true;
    }

    bool peek(T& value) const
    {
        if (frontNode == nullptr)
            return false;

        value = frontNode->data;
        return true;
    }

    void clear()
    {
        while (frontNode != nullptr)
        {
            QueueNode<T>* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }

        rearNode = nullptr;
        size = 0;
    }
};

#endif
