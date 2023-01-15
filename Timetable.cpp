
#include "Timetable.h"
#include <Windows.h>
#include <fstream>
#include <vector>
#include "include\json\json.h"

//TimeTable类的实现函数
int TimeTable::mAddLesson(std::string week,std::string Lesson,std::string sBegin,std::string sEnd)
{
    Json::Reader reader;
    Json::Value root;
    Json::StyledWriter sw;
    std::fstream os;
    Json::Value Current;
    os.open(mLessonInfoPath, std::ios::out | std::ios::in);
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
    os.open(mLessonInfoPath, std::ios::out | std::ios::in);
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

int TimeTable::mTimeToMin(int input)
{
    return (input-input%100)/100*60+input%100;
}

int TimeTable::mGetLesson(std::vector<std::string>& input)
{
    Json::Reader reader;
    Json::Value root;
    std::ifstream in(mLessonInfoPath, std::ios::in);
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

int TimeTable::mGetTodayMoreInfo(std::vector<std::string>& input)
{
    std::ifstream in(mLessonInfoPath, std::ios::in);
    if (!in.is_open())
    {
        return 0;
    };
    Json::Reader reader;
    Json::Value root;
    std::string week{ mGetCurrentTime("%a") };
    if (reader.parse(in, root)) {
        const Json::Value Infos = root[week]["Infos"];
        for (unsigned int i = 0; i < Infos.size(); ++i) {
            input.push_back(Infos[i].asString());
        }
    }
    return 1;
}

std::string TimeTable::mGetCurrentLesson(std::string& LessonNull)
{
    std::string timeCurrentTime{ mGetCurrentTime("%H%M") };
    int iCurrentTime = mTimeToMin(atoi(timeCurrentTime.c_str()));
    if (!((CurrentLesson.mGetBeginTime() <= iCurrentTime) && (iCurrentTime <= CurrentLesson.mGetEndTime()))) {
        Json::Reader reader;
        Json::Value root;
        std::ifstream in(mLessonInfoPath, std::ios::in);
        if (!in.is_open())
        {
            return std::string("无法打开配置文件");
        };
        if (reader.parse(in, root)) {
            std::string week{ mGetCurrentTime("%a") };
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

std::string TimeTable::mGetCurrentTime(const std::string& TextFormat)
{
    time_t timep;
    time(&timep);
    char tmp[256];
    tm structm;
    localtime_s(&structm, &timep);
    strftime(tmp, sizeof(tmp), TextFormat.c_str(), &structm);
    return std::string(tmp);
}

//WindowSettings类的实现函数
int WindowSettings::mGetWindowSettings()
{
    std::ifstream in(msSettingPath, std::ios::in);
    if (!in.is_open())
    {
        return 0;
    };
    Json::Reader reader;
    Json::Value root;
    if (reader.parse(in, root)) {
        Json::Value Settings = root["Settings"]["Window"];
        miWindowHeight = Settings["WindowSize"][1].asInt();
        miWindowWeight = Settings["WindowSize"][0].asInt();
        miWindowX = Settings["WindowLocation"][0].asInt();
        miWindowY = Settings["WindowLocation"][1].asInt();
        miFontSize = Settings["FontSize"].asInt();
        miLineDistance = Settings["LineDistance"].asInt();
        miLessonInLine = Settings["LessonInLine"].asInt();
        msFontName = Settings["FontName"].asString();
        msLessonNull = Settings["LessonNull"].asString();
        msLessonInfoFile = Settings["LessonInfoFile"].asString();
        msTextFormat.clear();
        for (int i = 0; i < (int)Settings["TextFormat"].size(); i++) {
            msTextFormat.push_back(Settings["TextFormat"][i].asString());
        }
    }
    return 0;
}

int WindowSettings::mGetTextItem(const std::string& Item, std::string& input)
{
    std::ifstream in(msSettingPath, std::ios::in);
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

int WindowSettings::mPrintText(HDC& hdc)
{
    return 0;
}

LPMENUITEMINFO WindowSettings::mSwitchMenuItemCheck(HWND& hWnd, HMENU& hMenu,DWORD MenuItem)
{
    static MENUITEMINFO MenuItemInfo;
    LPMENUITEMINFO lpMenuItemInfo = &MenuItemInfo;
    lpMenuItemInfo->cbSize = sizeof(MENUITEMINFO);
    lpMenuItemInfo->fMask = MIIM_STATE;//只获取菜单项状态（应该）
    GetMenuItemInfo(hMenu, MenuItem, FALSE, lpMenuItemInfo);//获取当前状态
    if (lpMenuItemInfo->fState & MFS_CHECKED) {//菜单项checked
        lpMenuItemInfo->fState = MFS_UNCHECKED;
    }
    else {//菜单项unchecked
        lpMenuItemInfo->fState = MFS_CHECKED;
    }
    SetMenuItemInfo(hMenu, MenuItem, FALSE, lpMenuItemInfo);
    return lpMenuItemInfo;
}
