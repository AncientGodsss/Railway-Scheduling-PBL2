#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include <iostream>

using namespace std;

class Operation
{
private:
    string action;
    string target;
    string description;

public:
    Operation()
    {
    }

    Operation(string a, string t, string d)
    {
        action = a;
        target = t;
        description = d;
    }

    void display() const
    {
        cout << action << " | " << target << " | " << description << "\n";
    }

    string getAction() const
    {
        return action;
    }

    string getTargetId() const
    {
        return target;
    }

    string getDescription() const
    {
        return description;
    }
};

#endif