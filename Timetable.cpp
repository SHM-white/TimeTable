#pragma warning(disable : 4996)

#include "Timetable.h"
#include <Windows.h>
#include "include\json\json.h"

int TimeTable::mAddLesson(int Days,std::string Lesson,std::string Time)
{
    Json::Reader reader;
    Json::Value value;

    return 0;
}

std::string TimeTable::mGetCurrentLesson()
{
    return std::string("1");
}

std::string TimeTable::mGetCurrentTime()
{
    time_t timep;
    time(&timep);
    char tmp[256];
    strftime(tmp, sizeof(tmp), "%H:%M:%S", localtime(&timep));
    return std::string(tmp);
}



