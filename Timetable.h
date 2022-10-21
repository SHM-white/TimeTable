#pragma once

#include<string>
#include<format>
#include<vector>
#include "resource.h"

class TimeTable {
public:
	TimeTable() = delete;
	TimeTable(std::string path) : mConfig_path{path} {};
	int mAddLesson(std::string Days,std::string Lesson,std::string Time);
	std::string mGetLesson(size_t count);
	std::string mGetCurrentLesson();
	std::string mGetCurrentTime();

private:
	std::vector<std::string> mLessons{};
	std::vector<int> mTime{};
	std::string mConfig_path;
	std::string mCurrentLesson;
	std::string mCurrentTime;
	/*enum Days
	{
		Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday
	};*/
};
