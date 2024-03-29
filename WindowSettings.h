#pragma once

#include<string>
#include<string_view>
#include<format>
#include<vector>
#include "resource.h"
#include<Windows.h>
#include"Lesson.h"
#include"TextFormat.h"
#include "Timetable.h"

//WindowSettings类，用于保存设置，包含与窗口绘图有关函数
class WindowSettings {
public:
	WindowSettings(const std::string path)
		:msSettingPath{ path }
	{
		msLessonNull = std::format("找不到{}", msSettingPath);
		msTextFormat.push_back(TextFormat());
		mGetWindowSettings();
	};
	WindowSettings() = delete;
	int mGetWindowSettings();
	int mGetTextItem(const std::string& Item, std::string& input);
	int mPrintText(HDC& hdc, TimeTable& timetable);
	LPMENUITEMINFO mSwitchMenuItemCheck(HWND& hWnd, HMENU& hMenu, DWORD MenuItem);
	int miWindowHeight{ 120 };
	int miWindowWeight{ 250 };
	int miWindowX{ 20 };
	int miWindowY{ 20 };
	int miLessonInLine{ 1 };
	int miCountDownDayInLine{ 10 };
	std::vector<TextFormat> msTextFormat;
	std::string msLessonNull;
	std::string msLessonInfoFile{ ".\\Lessons.json" };
	COLORREF mcBackGroundColor{ 0x00ffffff };
private:
	tm mCountDownDay;
	std::string msSettingPath{ ".\\Config.json" };
};