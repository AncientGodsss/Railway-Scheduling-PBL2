#ifndef STACK_H
#define STACK_H
#include "../model/Operation.h"
#include <functional>
struct OperationNode {
    Operation data;
    OperationNode* next;
    OperationNode(const Operation& value) : data(value), next(nullptr) {}
};
class OperationStack {
private:
    OperationNode* topNode;
    int size;
public:
    OperationStack() : topNode(nullptr), size(0) {}
    ~OperationStack() { clear(); }
    OperationStack(const OperationStack&) = delete;
    OperationStack& operator=(const OperationStack&) = delete;
    bool isEmpty() const { return topNode == nullptr; }
    int getSize() const { return size; }
    void push(const Operation& value) {
        OperationNode* node = new OperationNode(value);
        node->next = topNode;
        topNode = node;
        ++size;
    }
    bool pop(Operation& value) {
        if (topNode == nullptr) return false;
        OperationNode* temp = topNode;
        value = temp->data;
        topNode = topNode->next;
        delete temp;
        --size;
        return true;
    }
    bool peek(Operation& value) const {
        if (topNode == nullptr) return false;
        value = topNode->data;
        return true;
    }
    void forEachTopToBottom(const std::function<void(const Operation&)>& visit) const {
        OperationNode* current = topNode;
        while (current != nullptr) {
            visit(current->data);
            current = current->next;
        }
    }
    void clear() {
        while (topNode != nullptr) {
            OperationNode* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
        size = 0;
    }
};
#endif
