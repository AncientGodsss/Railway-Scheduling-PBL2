#ifndef MIN_HEAP_H
#define MIN_HEAP_H
#include <string>
using std::string;
struct DijkstraNode {
    string id;
    double cost;
    DijkstraNode() : id(""), cost(0) {}
    DijkstraNode(const string& value, double valueCost) : id(value), cost(valueCost) {}
};
class DijkstraMinHeap {
private:
    DijkstraNode* data;
    int size;
    int capacity;
    void ensureCapacity() {
        if (size < capacity) return;
        int newCapacity = capacity * 2;
        DijkstraNode* temp = new DijkstraNode[newCapacity];
        for (int i = 0; i < size; ++i) temp[i] = data[i];
        delete[] data;
        data = temp;
        capacity = newCapacity;
    }
    void swapNodes(DijkstraNode& first, DijkstraNode& second) {
        DijkstraNode temp = first;
        first = second;
        second = temp;
    }
    void moveUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (data[parent].cost <= data[index].cost) break;
            swapNodes(data[parent], data[index]);
            index = parent;
        }
    }
    void moveDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;
            if (left < size && data[left].cost < data[smallest].cost) smallest = left;
            if (right < size && data[right].cost < data[smallest].cost) smallest = right;
            if (smallest == index) break;
            swapNodes(data[index], data[smallest]);
            index = smallest;
        }
    }
public:
    DijkstraMinHeap(int initialCapacity = 16) : size(0), capacity(initialCapacity) {
        data = new DijkstraNode[capacity];
    }
    ~DijkstraMinHeap() { delete[] data; }
    bool isEmpty() const { return size == 0; }
    int getSize() const { return size; }
    void push(const DijkstraNode& value) {
        ensureCapacity();
        data[size] = value;
        moveUp(size);
        ++size;
    }
    bool pop(DijkstraNode& value) {
        if (size == 0) return false;
        value = data[0];
        data[0] = data[size - 1];
        --size;
        if (size > 0) moveDown(0);
        return true;
    }
};
#endif
