#pragma warning(disable : 4996)

#include "Timetable.h"
#include <Windows.h>
#include <fstream>
#include "include\json\json.h"

int TimeTable::mAddLesson(std::string Days,std::string Lesson,std::string Time)
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
    Current.append(Time);
    Current.append(Lesson);
    reader.parse(os, root);
    root[Days]["Lessons"].append(Current);
    os.seekp(std::ios::beg);
    os << sw.write(root);
    os.close();
    return 0;
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
    std::string CurrentLesson;
    time_t timep;
    time(&timep);
    char tmp[256];
    char tmp2[256];
    strftime(tmp, sizeof(tmp), "%a", localtime(&timep));
    strftime(tmp2, sizeof(tmp2), "%H%M", localtime(&timep));
    if (!in.is_open())
    {
        return std::string("");
    };

    if (reader.parse(in, root)) {
        const Json::Value Lessons = root[tmp]["Lessons"];
        for (unsigned int i = 0; i < Lessons.size(); ++i) {
            std::string sBeginTime = Lessons[i][0].asString();
            int iBeginTime = atoi(sBeginTime.c_str());
            int tmp3 = atoi(tmp2);
            bool a = iBeginTime < tmp3&& iBeginTime + 45 > tmp3;
            if (a) {
                in.close();
                return std::string(Lessons[i][1].asString());
            }
        }
    }
    in.close();
    return std::string("暂未获取");
}

std::string TimeTable::mGetCurrentTime()
{
    time_t timep;
    time(&timep);
    char tmp[256];
    strftime(tmp, sizeof(tmp), "%a-%H:%M:%S", localtime(&timep));
    return std::string(tmp);
}
