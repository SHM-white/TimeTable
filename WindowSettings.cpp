#include "WindowSettings.h"
#include "Timetable.h"
#include <Windows.h>
#include <fstream>
#include <vector>
#include "include\json\json.h"
#include<format>
#include<strsafe.h>

//WindowSettings���ʵ�ֺ���
//��ʼ��ʱ��ȡ����
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
        miLessonInLine = Settings["LessonInLine"].asInt();
        msLessonNull = Settings["LessonNull"].asString();
        msLessonInfoFile = Settings["LessonInfoFile"].asString();
        mcBackGroundColor = RGB(Settings["BackGroundColor"][0].asInt(), Settings["BackGroundColor"][1].asInt(), Settings["BackGroundColor"][2].asInt());
        msTextFormat.clear();
        for (int i = 0; i < (int)Settings["TextFormat"].size(); i++) {
            Json::Value Format = Settings["TextFormat"][i];
            TextFormat textformat(Format[2][0].asInt(), Format[2][1].asInt(), Format[3].asInt(), Format[1].asString(), Format[0].asString(), RGB(Format[4][0].asInt(), Format[4][1].asInt(), Format[4][2].asInt()));
            msTextFormat.push_back(textformat);
        }
        miCountDownDayInLine = Settings["CountDownDayInLine"].asInt();
        mCountDownDay.tm_year = Settings["CountDownDay"][0].asInt() - 1900;
        mCountDownDay.tm_mon = Settings["CountDownDay"][1].asInt() - 1;
        mCountDownDay.tm_mday = Settings["CountDownDay"][2].asInt();
        mCountDownDay.tm_hour = Settings["CountDownDay"][3].asInt();
        mCountDownDay.tm_min = Settings["CountDownDay"][4].asInt();
        mCountDownDay.tm_sec = Settings["CountDownDay"][5].asInt();
    }
    return 1;
}
//��ȡ�����ļ���ĳһ���ı�
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
    return 1;
}
//��������������
int WindowSettings::mPrintText(HDC& hdc, TimeTable& timetable)
{
      int i = 1;
      for (TextFormat a : msTextFormat) {
          HFONT hFont = CreateFont(a.miTextSize, 0, 0, 0,0, 0, 0, 0, GB2312_CHARSET, 0, 0, CLEARTYPE_QUALITY, 0, a.msFontName.c_str());
          SelectObject(hdc, hFont);
          SetTextColor(hdc, a.color);
          std::string Text;
          if (i == miLessonInLine) {
              Text = timetable.mGetCurrentTime(a.msTextFormat) + timetable.mGetCurrentLesson(msLessonNull);
          }   
          else if (i == miCountDownDayInLine) {
              Text = timetable.mGetCountDown(mCountDownDay, a.msTextFormat);
          }
          else {
              Text = timetable.mGetCurrentTime(a.msTextFormat);
          }
          TextOut(hdc, a.mpTextLocation.x, a.mpTextLocation.y, Text.c_str(), (int)Text.length());
          SetTextColor(hdc, RGB(0, 0, 0));
          DeleteObject(hFont);
          i++;
      }
      
    return 0;
}
//�л��˵��ѡ״̬
LPMENUITEMINFO WindowSettings::mSwitchMenuItemCheck(HWND& hWnd, HMENU& hMenu, DWORD MenuItem)
{
    static MENUITEMINFO MenuItemInfo;
    LPMENUITEMINFO lpMenuItemInfo = &MenuItemInfo;
    lpMenuItemInfo->cbSize = sizeof(MENUITEMINFO);
    lpMenuItemInfo->fMask = MIIM_STATE;//ֻ��ȡ�˵���״̬��Ӧ�ã�
    GetMenuItemInfo(hMenu, MenuItem, FALSE, lpMenuItemInfo);//��ȡ��ǰ״̬
    if (lpMenuItemInfo->fState & MFS_CHECKED) {//�˵���checked
        lpMenuItemInfo->fState = MFS_UNCHECKED;
    }
    else {//�˵���unchecked
        lpMenuItemInfo->fState = MFS_CHECKED;
    }
    SetMenuItemInfo(hMenu, MenuItem, FALSE, lpMenuItemInfo);
    return lpMenuItemInfo;
}