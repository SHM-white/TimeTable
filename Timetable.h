#pragma once

#include<string>
#include<string_view>
#include<format>
#include<vector>
#include "resource.h"
#include<Windows.h>

//WindowSettings�࣬���ڱ������ã������봰�ڻ�ͼ�йغ���
class WindowSettings {
public:
	WindowSettings(const std::string path)
		:msSettingPath{ path } 
	{
		mGetWindowSettings();
	};
	WindowSettings() = delete;
	int mGetWindowSettings();
	int mGetTextItem(const std::string& Item, std::string& input);
	int mPrintText(HDC& hdc);
	LPMENUITEMINFO mSwitchMenuItemCheck(HWND& hWnd,HMENU& hMenu, DWORD MenuItem);
	int miWindowHeight{ 120 };
	int miWindowWeight{ 250 };
	int miWindowX{ 20 };
	int miWindowY{ 20 };
	int miFontSize{ 25 };
	int miLineDistance{ 25 };
	int miLessonInLine{ 2 };
	std::string msFontName{ "����" };
	std::vector<std::string> msTextFormat{ "error","" };
	std::string msLessonNull{ "��" };
	std::string msLessonInfoFile{ "Lessons.json" };
private:
	std::string msSettingPath{"Config.json"};
	
};
//Lesson�࣬��������γ���Ϣ���������ƣ���ʼʱ�䣬����ʱ��
class Lesson {
public:
	Lesson(std::string s, int b, int e) :sName{ s }, iBeginTime{ b }, iEndTime{ e } {}
	Lesson(Lesson& OtherLesson)
	{
		iBeginTime = OtherLesson.iBeginTime;
		iEndTime = OtherLesson.iEndTime;
		sName = OtherLesson.sName;
	}
	Lesson() {}
	std::string mGetName() {return sName;}
	int mGetBeginTime() {return iBeginTime;}
	int mGetEndTime() {return iEndTime;}
	int mSetValue(const std::string& s, int b, int e) {
		iBeginTime = b;
		iEndTime = e;
		sName = s;
		return 0;
	}
private:
	int iBeginTime{};
	int iEndTime{};
	std::string sName{};
};
//TimeTable�࣬�������ȡ�γ��йصĺ��������ʼ�������ļ�·��
class TimeTable {
public:
	TimeTable() = delete;
	TimeTable(std::string path) : mLessonInfoPath{path} {};
	int mAddLesson(std::string Days,std::string Lesson,std::string sBegin,std::string sEnd);
	int mAddMoreInfo(std::string Days, std::string Info);
	int mGetLesson(std::vector<std::string>& input);
	int mGetTodayMoreInfo(std::vector<std::string>& input);
	std::string mGetCurrentLesson(std::string& LessonNull);
	std::string mGetCurrentTime(const std::string& TextFormat);	
private:
	Lesson CurrentLesson;
	std::string mLessonInfoPath{"Lessons.json"};
	int mTimeToMin(int input);
};
