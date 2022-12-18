#pragma warning(disable : 4996)

#include "Timetable.h"
#include <Windows.h>
#include <fstream>
#include "include\json\json.h"

int TimeTable::mAddLesson(std::string week,std::string Lesson,std::string sBegin,std::string sEnd)
{
    Json::Reader reader;
    Json::Value root;
    Json::StyledWriter sw;
    std::fstream os;
    Json::Value Current;
    os.open(mConfig_path, std::ios::out | std::ios::in);
    if (!os.is_open()) {
        return 0;
    }
    
    Current.append(Lesson);
    Current.append(sBegin);
    Current.append(sEnd);
    reader.parse(os, root);
    root[week]["Lessons"].append(Current);
    os.seekp(std::ios::beg);
    os << sw.write(root);
    os.close();
    return 0;
}

std::string TimeTable::mGetTextFromFile(std::string TextPath)
{
    std::fstream file(TextPath, std::ios::in);
    file.get();
    return std::string();
}

int TimeTable::mTimeToMin(int input)
{
    return (input-input%100)/100*60+input%100;
}

std::string TimeTable::mGetLesson(size_t count)
{
    return std::string();
}

std::string TimeTable::mGetCurrentLesson()
{

    Json::Reader reader;
    Json::Value root;
    std::ifstream in(mConfig_path, std::ios::in);
    static Lesson CurrentLesson;
    time_t timep;
    time(&timep);
    char week[256];
    char timeCurrentTime[256];
    strftime(week, sizeof(week), "%a", localtime(&timep));
    strftime(timeCurrentTime, sizeof(timeCurrentTime), "%H%M", localtime(&timep));
    int iCurrentTime = mTimeToMin(atoi(timeCurrentTime));
    if (!in.is_open())
    {
        return std::string("无法打开配置文件");
    };
    if (!((CurrentLesson.mGetBeginTime() < iCurrentTime) && (iCurrentTime < CurrentLesson.mGetEndTime()))) {
        if (reader.parse(in, root)) {
            const Json::Value Lessons = root[week]["Lessons"];
            for (unsigned int i = 0; i < Lessons.size(); ++i) {
                std::string sBeginTime = Lessons[i][1].asString();
                std::string sEndTime = Lessons[i][2].asString();
                int iBeginTime = mTimeToMin(atoi(sBeginTime.c_str()));
                int iEndTime = mTimeToMin(atoi(sEndTime.c_str()));
                if ((iBeginTime < iCurrentTime) && (iEndTime > iCurrentTime)) {
                    in.close();
                    CurrentLesson.mSetValue(Lessons[i][0].asString(),iBeginTime, iEndTime);
                    break;
                }
            }
        } 
    }
    in.close();
    return CurrentLesson.mGetName();
}

std::string TimeTable::mGetCurrentTime()
{
    time_t timep;
    time(&timep);
    char tmp[256];
    strftime(tmp, sizeof(tmp), "%a-%H:%M:%S", localtime(&timep));
    return std::string(tmp);
}
