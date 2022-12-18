#pragma once

#include<string>
#include<format>
#include<vector>
//#include "resource.h"
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
	int mSetValue(std::string s, int b, int e) {
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
class TimeTable {
public:
	TimeTable() = delete;
	TimeTable(std::string path) : mConfig_path{path} {};
	int mAddLesson(std::string Days,std::string Lesson,std::string sBegin,std::string sEnd);
	std::string mGetTextFromFile(std::string TextPath);
	std::string mGetLesson(size_t count);
	std::string mGetCurrentLesson();
	std::string mGetCurrentTime();
	
private:
	std::vector<std::string> mLessons{};
	std::vector<int> mTime{};
	std::string mConfig_path;
	std::string mCurrentLesson;
	std::string mCurrentTime;
	int mTimeToMin(int input);
	/*enum Days
	{
		Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday
	};*/
};
