#pragma once
#include "classMassive.hpp"
#include "classMenu.hpp"
#include "classDB.hpp"
#include "classMap.hpp"
#include "classStudentChange.hpp"

class birthDate
{
private:
    unsigned short day;
    unsigned short month;
    unsigned short year;
    const int days_in_month[13] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Проверка корректности введенных данных
    bool check_date(unsigned short _day, unsigned short _month, unsigned short _year)
    {
        if (_year > 0 && _year < 9999)
        {
            if (_month > 0 && _month < 13)
            {
                if (_month == 2)
                {
                    int feb = (_year % 4 == 0 && _year % 100 != 0) ? 29 : 28;
                    if (_day > 0 && _day <= feb)
                    {
                        return true;
                    }
                }
                else if (_day > 0 && _day <= days_in_month[_month - 1])
                {
                    return true;
                }
            }
        }
        return false;
    }

    // проверка корректности дня, если нужно поменять ГОД
    bool check_day(unsigned short _day)
    {
        if (month == 2)
        {
            int feb = (year % 4 == 0 && year % 100 != 0) ? 29 : 28;
            if (_day > 0 && _day <= feb)
            {
                return true;
            }
        }
        else if (_day > 0 && _day <= days_in_month[month - 1])
        {
            return true;
        }
        return false;
    }

public:
    birthDate()
    {
        day = 0;
        month = 0;
        year = 0;
    }

    birthDate(unsigned short _day, unsigned short _month, unsigned short _year)
    {
        if (check_date(_day, _month, _year))
        {
            day = _day;
            month = _month;
            year = _year;
        }
    }

    birthDate(const birthDate* date)
    {
        if (check_date(date->day, date->month, date->year))
        {
            day = date->day;
            month = date->month;
            year = date->year;
        }
    }

    bool is_valid(unsigned short _day, unsigned short _month, unsigned short _year)
    {
        return check_date(_day, _month, _year);
    }

    unsigned short getDay()
    {
        return day;
    }

    unsigned short getMonth()
    {
        return month;
    }

    unsigned short getYear()
    {
        return year;
    }

    std::string getDate()
    {
        static char temp[11];
        sprintf(temp, "%02d.%02d.%04d", day, month, year);
        return temp;
    }

    void setDay(unsigned short _day)
    {
        if (check_date(_day, month, year))
        {
            day = _day;
        }
    }

    void setMonth(unsigned short _month)
    {
        if (check_date(day, _month, year))
        {
            month = _month;
        }
    }

    void setYear(unsigned short _year)
    {
        if (check_date(day, month, _year))
        {
            year = _year;
        }
    }

    void setDate(unsigned short _day, unsigned short _month, unsigned short _year)
    {
        if (check_date(_day, _month, _year))
        {
            day = _day;
            month = _month;
            year = _year;
        }
    }

    void operator=(const birthDate &other)
    {
        setDate(other.day, other.month, other.year);
    }
};