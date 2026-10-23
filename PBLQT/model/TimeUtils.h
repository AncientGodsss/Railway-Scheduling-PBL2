#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class TimeUtils
{
public:
     
    static int timeToMinutes(const string& time)
    {
        int hour, minute;
        char separator, extra;
        stringstream ss(time);

         
        if (!(ss >> hour >> separator >> minute) || separator != ':' || (ss >> extra))
            return -1;

        if (hour < 0 || hour > 23)
        {
            return -1;
        }

        if (minute < 0 || minute > 59)
        {
            return -1;
        }

        return hour * 60 + minute;
    }

     
    static string minutesToTime(int totalMinutes)
    {
        if (totalMinutes < 0)
        {
            return "INVALID";
        }

        totalMinutes = totalMinutes % (24 * 60);

        int hour = totalMinutes / 60;
        int minute = totalMinutes % 60;

        stringstream ss;

        ss << setfill('0')
           << setw(2)
           << hour
           << ":";

        ss << setfill('0')
           << setw(2)
           << minute;

        return ss.str();
    }

     
    static int getDifference(
        int startTime,
        int endTime
    )
    {
        return endTime - startTime;
    }

     
    static bool isValidTime(int totalMinutes)
    {
        return totalMinutes >= 0
            && totalMinutes < 24 * 60;
    }
};

#endif
