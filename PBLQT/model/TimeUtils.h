#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class TimeUtils
{
private:
    static bool isLeapYear(int year)
    {
        if (year % 400 == 0)
        {
            return true;
        }

        if (year % 100 == 0)
        {
            return false;
        }

        return year % 4 == 0;
    }

    static int daysInMonth(int month, int year)
    {
        static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && isLeapYear(year))
        {
            return 29;
        }

        return days[month - 1];
    }

public:
    static int timeToMinutes(const string& time)
    {
        int hour, minute;
        char separator, extra;
        stringstream ss(time);

        if (!(ss >> hour >> separator >> minute))
        {
            return -1;
        }

        if (separator != ':' || (ss >> extra))
        {
            return -1;
        }

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

        ss << setfill('0') << setw(2) << hour << ":";

        ss << setfill('0') << setw(2) << minute;

        return ss.str();
    }

    static string minutesToDisplay(int totalMinutes)
    {
        if (totalMinutes < 0)
        {
            return "INVALID";
        }

        int dayOffset = totalMinutes / (24 * 60);
        string result = minutesToTime(totalMinutes);
        if (dayOffset > 0)
        {
            result += " (+" + to_string(dayOffset) + " ngày)";
        }

        return result;
    }

    static int getDifference(int startTime, int endTime)
    {
        if (endTime < startTime)
        {
            endTime += 24 * 60;
        }

        return endTime - startTime;
    }

    static bool isValidTime(int totalMinutes)
    {
        return totalMinutes >= 0;
    }

    static int dateToDayNumber(const string& date)
    {
        int day, month, year;
        char firstSeparator, secondSeparator, extra;
        stringstream ss(date);
        if (!(ss >> day >> firstSeparator >> month >> secondSeparator >> year))
        {
            return -1;
        }

        if (firstSeparator != '/' || secondSeparator != '/' || (ss >> extra))
        {
            return -1;
        }

        if (year < 1 || month < 1 || month > 12)
        {
            return -1;
        }

        if (day < 1 || day > daysInMonth(month, year))
        {
            return -1;
        }

        int result = 0;
        for (int currentYear = 1; currentYear < year; ++currentYear)
        {
            if (isLeapYear(currentYear))
            {
                result += 366;
            }
            else
            {
                result += 365;
            }
        }

        for (int currentMonth = 1; currentMonth < month; ++currentMonth)
        {
            result += daysInMonth(currentMonth, year);
        }

        return result + day - 1;
    }

    static long long toAbsoluteMinutes(const string& date, int minutes)
    {
        int dayNumber = dateToDayNumber(date);
        if (dayNumber < 0 || minutes < 0)
        {
            return -1;
        }

        long long totalDays = dayNumber;
        long long minutesBeforeDate = totalDays * 24 * 60;
        return minutesBeforeDate + minutes;
    }
};

#endif
