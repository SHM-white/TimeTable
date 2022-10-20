#pragma warning(disable : 4996)

#include "Timetable.h"
#include <Windows.h>

int TimeTable::mAddTime(std::string Time)
{
    return 0;
}
int TimeTable::mAddLesson(std::string Lesson)
{
    return 0;
}
int TimeTable::mGetTime(size_t count)
{
    return 0;
}

char TimeTable::mGetLesson(size_t count)
{
    return 0;
}

std::string TimeTable::mGetCurrentTime()
{
    time_t timep;
    time(&timep);
    char tmp[256];
    strftime(tmp, sizeof(tmp), "%H:%M:%S", localtime(&timep));
    return std::string(tmp);
}



