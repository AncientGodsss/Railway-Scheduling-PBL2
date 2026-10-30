#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <string>
#include <limits>
#include "DoublyLinkedList.h"
#include "MinHeap.h"
using namespace std;

struct Edge
{
    string to;
    double distance;
    int travelTime;
    Edge() : to(""), distance(0), travelTime(0)
    {
    }
    Edge(const string& target, double valueDistance, int valueTime)
        : to(target), distance(valueDistance), travelTime(valueTime)
    {
    }
};

struct Vertex
{
    string id;
    Edge* edges;
    int edgeCount;
    int edgeCapacity;
    Vertex() : id(""), edgeCount(0), edgeCapacity(4)
    {
        edges = new Edge[edgeCapacity];
    }
    Vertex(const string& value) : id(value), edgeCount(0), edgeCapacity(4)
    {
        edges = new Edge[edgeCapacity];
    }
    Vertex(const Vertex& other) : id(other.id), edgeCount(other.edgeCount), edgeCapacity(other.edgeCapacity)
    {
        edges = new Edge[edgeCapacity];
        for (int i = 0; i < edgeCount; ++i)
            edges[i] = other.edges[i];
    }
    Vertex& operator=(const Vertex& other)
    {
        if (this != &other)
        {
            delete[] edges;
            id = other.id;
            edgeCount = other.edgeCount;
            edgeCapacity = other.edgeCapacity;
            edges = new Edge[edgeCapacity];
            for (int i = 0; i < edgeCount; ++i)
                edges[i] = other.edges[i];
        }
        return *this;
    }
    ~Vertex()
    {
        delete[] edges;
    }
    void addEdge(const Edge& edge)
    {
        if (edgeCount == edgeCapacity)
        {
            edgeCapacity *= 2;
            Edge* temp = new Edge[edgeCapacity];
            for (int i = 0; i < edgeCount; ++i)
                temp[i] = edges[i];
            delete[] edges;
            edges = temp;
        }
        edges[edgeCount++] = edge;
    }
    bool removeEdge(const string& target)
    {
        for (int i = 0; i < edgeCount; ++i)
        {
            if (edges[i].to == target)
            {
                for (int j = i; j < edgeCount - 1; ++j)
                    edges[j] = edges[j + 1];
                --edgeCount;
                return true;
            }
        }
        return false;
    }
    Edge* findEdge(const string& target)
    {
        for (int i = 0; i < edgeCount; ++i)
            if (edges[i].to == target)
                return &edges[i];
        return nullptr;
    }
};

struct PathResult
{
    bool found;
    double distance;
    int travelTime;
    StringList path;
    PathResult() : found(false), distance(0), travelTime(0)
    {
    }
};

class Graph
{
private:
    Vertex* vertices;
    int vertexCount;
    int vertexCapacity;
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);

    void ensureCapacity()
    {
        if (vertexCount < vertexCapacity)
            return;
        vertexCapacity *= 2;
        Vertex* temp = new Vertex[vertexCapacity];
        for (int i = 0; i < vertexCount; ++i)
            temp[i] = vertices[i];
        delete[] vertices;
        vertices = temp;
    }
    Vertex* findVertex(const string& id)
    {
        for (int i = 0; i < vertexCount; ++i)
            if (vertices[i].id == id)
                return &vertices[i];
        return nullptr;
    }
    const Vertex* findVertex(const string& id) const
    {
        for (int i = 0; i < vertexCount; ++i)
            if (vertices[i].id == id)
                return &vertices[i];
        return nullptr;
    }
    int findIndex(const string& id) const
    {
        for (int i = 0; i < vertexCount; ++i)
            if (vertices[i].id == id)
                return i;
        return -1;
    }
public:
    Graph() : vertexCount(0), vertexCapacity(8)
    {
        vertices = new Vertex[vertexCapacity];
    }
    ~Graph()
    {
        delete[] vertices;
    }
    void clear()
    {
        delete[] vertices;
        vertexCount = 0;
        vertexCapacity = 8;
        vertices = new Vertex[vertexCapacity];
    }

    bool addVertex(const string& id)
    {
        if (findVertex(id) != nullptr)
            return false;
        ensureCapacity();
        vertices[vertexCount++] = Vertex(id);
        return true;
    }
    bool removeVertex(const string& id)
    {
        int index = findIndex(id);
        if (index < 0)
            return false;
        for (int i = index; i < vertexCount - 1; ++i)
            vertices[i] = vertices[i + 1];
        --vertexCount;
        for (int i = 0; i < vertexCount; ++i)
            vertices[i].removeEdge(id);
        return true;
    }
    bool addUndirectedEdge(const string& first, const string& second, double distance, int time)
    {
        Vertex* a = findVertex(first);
        Vertex* b = findVertex(second);
        if (first == second || a == nullptr || b == nullptr || distance <= 0 || time <= 0)
            return false;
        if (a->findEdge(second) != nullptr)
            return false;
        a->addEdge(Edge(second, distance, time));
        b->addEdge(Edge(first, distance, time));
        return true;
    }
    bool removeUndirectedEdge(const string& first, const string& second)
    {
        Vertex* a = findVertex(first);
        Vertex* b = findVertex(second);
        bool removedA = a != nullptr && a->removeEdge(second);
        bool removedB = b != nullptr && b->removeEdge(first);
        return removedA || removedB;
    }
    bool updateUndirectedEdge(const string& first, const string& second, double distance, int time)
    {
        Vertex* a = findVertex(first);
        Vertex* b = findVertex(second);
        if (a == nullptr || b == nullptr)
            return false;

        Edge* edgeA = a->findEdge(second);
        Edge* edgeB = b->findEdge(first);
        if (edgeA == nullptr || edgeB == nullptr)
            return false;
        edgeA->distance = edgeB->distance = distance;
        edgeA->travelTime = edgeB->travelTime = time;
        return true;
    }
    void display() const
    {
        cout << "\n===== MANG LUOI DUONG SAT =====\n";
        for (int i = 0; i < vertexCount; ++i)
        {
            cout << vertices[i].id << " -> ";
            for (int j = 0; j < vertices[i].edgeCount; ++j)
            {
                const Edge& edge = vertices[i].edges[j];
                cout << edge.to << "(" << edge.distance << "km," << edge.travelTime << "p) ";
            }
            cout << "\n";
        }
    }
    PathResult dijkstra(const string& start, const string& target, bool byDistance) const
    {
        PathResult result;
        int startIndex = findIndex(start);
        int targetIndex = findIndex(target);
        if (startIndex < 0 || targetIndex < 0)
            return result;
        double infinity = numeric_limits<double>::max();
        double* cost = new double[vertexCount];
        double* totalDistance = new double[vertexCount];
        int* totalTime = new int[vertexCount];
        string* previous = new string[vertexCount];
        for (int i = 0; i < vertexCount; ++i)
        {
            cost[i] = infinity;
            totalDistance[i] = 0;
            totalTime[i] = 0;
            previous[i] = "";
        }
        cost[startIndex] = 0;
        DijkstraMinHeap heap;
        heap.push(DijkstraNode(start, 0));
        while (!heap.isEmpty())
        {
            DijkstraNode current;
            heap.pop(current);
            int currentIndex = findIndex(current.id);
            if (currentIndex < 0 || current.cost > cost[currentIndex])
                continue;
            const Vertex& vertex = vertices[currentIndex];
            for (int i = 0; i < vertex.edgeCount; ++i)
            {
                const Edge& edge = vertex.edges[i];
                int nextIndex = findIndex(edge.to);
                double weight = edge.travelTime;
                if (byDistance)
                    weight = edge.distance;
                double newCost = current.cost + weight;
                if (nextIndex >= 0 && newCost < cost[nextIndex])
                {
                    cost[nextIndex] = newCost;
                    previous[nextIndex] = current.id;
                    totalDistance[nextIndex] = totalDistance[currentIndex] + edge.distance;
                    totalTime[nextIndex] = totalTime[currentIndex] + edge.travelTime;
                    heap.push(DijkstraNode(edge.to, newCost));
                }
            }
        }
        if (cost[targetIndex] != infinity)
        {
            result.found = true;
            result.distance = totalDistance[targetIndex];
            result.travelTime = totalTime[targetIndex];
            string current = target;
            while (!current.empty())
            {
                result.path.pushFront(current);
                if (current == start)
                    break;
                int index = findIndex(current);
                if (index < 0)
                    current = "";
                else
                    current = previous[index];
            }
        }
        delete[] cost;
        delete[] totalDistance;
        delete[] totalTime;
        delete[] previous;
        return result;
    }
};
#endif
