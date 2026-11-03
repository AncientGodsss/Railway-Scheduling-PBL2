#ifndef STACK_H
#define STACK_H

template <typename T>
struct StackNode
{
    T data;
    StackNode<T>* next;

    StackNode(const T& value) : data(value), next(nullptr)
    {
    }
};

template <typename T>
class Stack
{
private:
    StackNode<T>* topNode;
    int size;

    Stack(const Stack<T>& other);
    Stack<T>& operator=(const Stack<T>& other);

public:
    Stack() : topNode(nullptr), size(0)
    {
    }

    ~Stack()
    {
        clear();
    }

    bool isEmpty() const
    {
        return topNode == nullptr;
    }

    int getSize() const
    {
        return size;
    }

    void push(const T& value)
    {
        StackNode<T>* node = new StackNode<T>(value);
        node->next = topNode;
        topNode = node;
        ++size;
    }

    bool pop(T& value)
    {
        if (topNode == nullptr)
            return false;

        StackNode<T>* temp = topNode;
        value = temp->data;
        topNode = topNode->next;
        delete temp;
        --size;
        return true;
    }

    bool peek(T& value) const
    {
        if (topNode == nullptr)
            return false;

        value = topNode->data;
        return true;
    }

    void displayTopToBottom() const
    {
        StackNode<T>* current = topNode;
        while (current != nullptr)
        {
            current->data.display();
            current = current->next;
        }
    }

    void clear()
    {
        while (topNode != nullptr)
        {
            StackNode<T>* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
        size = 0;
    }
};

#endif
