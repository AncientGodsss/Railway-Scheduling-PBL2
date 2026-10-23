#ifndef QUEUE_H
#define QUEUE_H
#include <string>
using std::string;
struct QueueNode {
    string data;
    QueueNode* next;
    QueueNode(const string& value) : data(value), next(nullptr) {}
};
class StringQueue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int size;
public:
    StringQueue() : frontNode(nullptr), rearNode(nullptr), size(0) {}
    ~StringQueue() { clear(); }
    StringQueue(const StringQueue&) = delete;
    StringQueue& operator=(const StringQueue&) = delete;
    bool isEmpty() const { return frontNode == nullptr; }
    int getSize() const { return size; }
    void enqueue(const string& value) {
        QueueNode* node = new QueueNode(value);
        if (rearNode == nullptr) frontNode = rearNode = node;
        else { rearNode->next = node; rearNode = node; }
        ++size;
    }
    bool dequeue(string& value) {
        if (frontNode == nullptr) return false;
        QueueNode* temp = frontNode;
        value = temp->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr) rearNode = nullptr;
        delete temp;
        --size;
        return true;
    }
    bool peek(string& value) const {
        if (frontNode == nullptr) return false;
        value = frontNode->data;
        return true;
    }
    void clear() {
        while (frontNode != nullptr) {
            QueueNode* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
        rearNode = nullptr;
        size = 0;
    }
};
#endif
