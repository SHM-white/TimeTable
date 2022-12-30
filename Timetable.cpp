#pragma warning(disable : 4996)

#include "Timetable.h"
#include <Windows.h>
#include <fstream>
#include <vector>
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
    return 1;
}

int TimeTable::mAddMoreInfo(std::string Days, std::string Info)
{
    std::fstream os;
    os.open(mConfig_path, std::ios::out | std::ios::in);
    if (!os.is_open()) {
        return 0;
    }
    Json::Reader reader;
    Json::Value root;
    Json::StyledWriter sw;
    reader.parse(os, root);
    root[Days]["Infos"].append(Info);
    os.seekp(std::ios::beg);
    os << sw.write(root);
    os.close();
    return 0;
}

int TimeTable::mGetTextItem(std::string Item,std::string& input)
{
    std::ifstream in(mConfig_path, std::ios::in);
    if (!in.is_open())
    {
        return 0;
    };
    Json::Reader reader;
    Json::Value root;
    if (reader.parse(in, root)) {
        const Json::Value Text = root[Item];
        input = Text.asString();
    }
    return 0;
}

int TimeTable::mTimeToMin(int input)
{
    return (input-input%100)/100*60+input%100;
}

int TimeTable::mGetLesson(std::vector<std::string>& input)
{
    Json::Reader reader;
    Json::Value root;
    std::ifstream in(mConfig_path, std::ios::in);
    if (!in.is_open())
    {
        return 0;
    };
    std::string Days[]{ "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
    if (reader.parse(in, root)) {
        for (auto a : Days) {
            const Json::Value Lessons = root[a]["Lessons"];
            for (unsigned int i = 0; i < Lessons.size(); ++i) {
                std::string result{ a + "   " + Lessons[i][0].asString() + "   " + Lessons[i][1].asString() + "   " + Lessons[i][2].asString() };
                input.push_back(result);
            }
        }
    }
    return 1;
}

int TimeTable::mGetAbout(std::string& input)
{
    std::ifstream in(mConfig_path, std::ios::in);
    if (!in.is_open())
    {
        return 0;
    };
    Json::Reader reader;
    Json::Value root;
    if (reader.parse(in, root)) {
        const Json::Value About = root["About"];
        input=About.asString();        
    }
    return 0;
}

int TimeTable::mGetTodayMoreInfo(std::vector<std::string>& input)
{
    std::ifstream in(mConfig_path, std::ios::in);
    if (!in.is_open())
    {
        return 0;
    };
    Json::Reader reader;
    Json::Value root;
    time_t timep;
    time(&timep);
    char week[256];
    strftime(week, sizeof(week), "%a", localtime(&timep));
    if (reader.parse(in, root)) {
        const Json::Value Infos = root[week]["Infos"];
        for (unsigned int i = 0; i < Infos.size(); ++i) {
            input.push_back(Infos[i].asString());
        }
    }
    return 1;
}

int TimeTable::mGetWindowSettings(WindowSettings& windowsettings)
{
    std::ifstream in(mConfig_path, std::ios::in);
    if (!in.is_open())
    {
        return 0;
    };
    Json::Reader reader;
    Json::Value root;
    if (reader.parse(in, root)) {
        Json::Value Settings = root["Settings"]["Window"];
        windowsettings.iWindowHeight = Settings["Height"].asInt();
        windowsettings.iWindowWeight = Settings["Weight"].asInt();
        windowsettings.iWindowX = Settings["XY"][0].asInt();
        windowsettings.iWindowY = Settings["XY"][1].asInt();
        windowsettings.iFontSize = Settings["FontSize"].asInt();
        windowsettings.iLineDistance = Settings["LineDistance"].asInt();
        windowsettings.iLessonInLine = Settings["LessonInLine"].asInt();
        windowsettings.sFontName = Settings["FontName"].asString();
        windowsettings.sLessonNull = Settings["LessonNull"].asString();
        for (int i = 0; i < (int)Settings["TextFormat"].size(); i++) {
            windowsettings.sTextFormat.push_back(Settings["TextFormat"][i].asString());
        }
    }
    return 0;
}

std::string TimeTable::mGetCurrentLesson(std::string& LessonNull)
{
    time_t timep;
    time(&timep);
    char timeCurrentTime[256];
    strftime(timeCurrentTime, sizeof(timeCurrentTime), "%H%M", localtime(&timep));
    int iCurrentTime = mTimeToMin(atoi(timeCurrentTime));
    if (!((CurrentLesson.mGetBeginTime() <= iCurrentTime) && (iCurrentTime <= CurrentLesson.mGetEndTime()))) {
        Json::Reader reader;
        Json::Value root;
        std::ifstream in(mConfig_path, std::ios::in);
        if (!in.is_open())
        {
            return std::string("无法打开配置文件");
        };
        if (reader.parse(in, root)) {
            char week[16];
            strftime(week, sizeof(week), "%a", localtime(&timep));
            const Json::Value Lessons = root[week]["Lessons"];
            for (unsigned int i = 0; i < Lessons.size(); ++i) {
                std::string sBeginTime = Lessons[i][1].asString();
                std::string sEndTime = Lessons[i][2].asString();
                int iBeginTime = mTimeToMin(atoi(sBeginTime.c_str()));
                int iEndTime = mTimeToMin(atoi(sEndTime.c_str()));
                if ((iBeginTime <= iCurrentTime) && (iEndTime >= iCurrentTime)) {
                    in.close();
                    CurrentLesson.mSetValue(Lessons[i][0].asString(), iBeginTime, iEndTime);
                    return CurrentLesson.mGetName();
                }
            }
            CurrentLesson.mSetValue(LessonNull, 0, 0);
        }
        in.close();
    }
    return CurrentLesson.mGetName();
}

std::string TimeTable::mGetCurrentTime(std::string TextFormat)
{
    time_t timep;
    time(&timep);
    char tmp[256];
    strftime(tmp, sizeof(tmp), TextFormat.c_str(), localtime(&timep));
    return std::string(tmp);
}


