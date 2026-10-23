#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <iostream>

using namespace std;

class Train
{
private:
    string id;
    string name;
    string type;

    int capacity;
    double maxSpeed;

    string status;

public:
     
    Train()
    {
        capacity = 0;
        maxSpeed = 0;
        status = "INACTIVE";
    }

     
    Train(
        string i,
        string n,
        string t,
        int c,
        double s,
        string st
    )
    {
        id = i;
        name = n;
        type = t;
        capacity = c;
        maxSpeed = s;
        status = st;
    }

    string getTrainId() const
    {
        return id;
    }

    string getTrainName() const
    {
        return name;
    }

    string getTrainType() const
    {
        return type;
    }

    int getCapacity() const
    {
        return capacity;
    }

    double getMaxSpeed() const
    {
        return maxSpeed;
    }

    string getStatus() const
    {
        return status;
    }

    void setTrainName(const string& x)
    {
        name = x;
    }

    void setTrainType(const string& x)
    {
        type = x;
    }

    void setCapacity(int x)
    {
        if (x > 0)
        {
            capacity = x;
        }
    }

    void setMaxSpeed(double x)
    {
        if (x > 0)
        {
            maxSpeed = x;
        }
    }

    void setStatus(const string& x)
    {
        status = x;
    }

    void displayInfo() const
    {
        cout << id << " | "
             << name << " | "
             << type << " | "
             << capacity << " cho | "
             << maxSpeed << " km/h | "
             << status << "\n";
    }
};

#endif