#ifndef BST_H
#define BST_H
#include "../model/Schedule.h"

struct ScheduleBSTNode
{
    int key;
    Schedule* schedule;
    ScheduleBSTNode* left;
    ScheduleBSTNode* right;

    ScheduleBSTNode(int valueKey, Schedule* valueSchedule)
    {
        key = valueKey;
        schedule = valueSchedule;
        left = nullptr;
        right = nullptr;
    }
};

class ScheduleBST
{
private:
    ScheduleBSTNode* root;

    ScheduleBSTNode* insertNode(ScheduleBSTNode* node, int key, Schedule* schedule)
    {
        if (node == nullptr)
        {
            return new ScheduleBSTNode(key, schedule);
        }

        if (key < node->key)
        {
            node->left = insertNode(node->left, key, schedule);
        }
        else
        {
            node->right = insertNode(node->right, key, schedule);
        }

        return node;
    }

    void putAscending(ScheduleBSTNode* node, Schedule** result, int capacity, int& count) const
    {
        if (node == nullptr || count >= capacity)
        {
            return;
        }

        putAscending(node->left, result, capacity, count);

        if (count < capacity)
        {
            result[count] = node->schedule;
            count++;
        }

        putAscending(node->right, result, capacity, count);
    }

    void putDescending(ScheduleBSTNode* node, Schedule** result, int capacity, int& count) const
    {
        if (node == nullptr || count >= capacity)
        {
            return;
        }

        putDescending(node->right, result, capacity, count);

        if (count < capacity)
        {
            result[count] = node->schedule;
            count++;
        }

        putDescending(node->left, result, capacity, count);
    }

    void deleteTree(ScheduleBSTNode* node)
    {
        if (node == nullptr)
        {
            return;
        }

        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    ScheduleBST()
    {
        root = nullptr;
    }

    ~ScheduleBST()
    {
        deleteTree(root);
    }

    void insert(int key, Schedule* schedule)
    {
        root = insertNode(root, key, schedule);
    }

    int getAscending(Schedule** result, int capacity) const
    {
        int count = 0;
        putAscending(root, result, capacity, count);
        return count;
    }

    int getDescending(Schedule** result, int capacity) const
    {
        int count = 0;
        putDescending(root, result, capacity, count);
        return count;
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }
};

#endif
