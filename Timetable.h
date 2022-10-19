#pragma once

#include<string>
#include<format>
#include<vector>
#include "resource.h"

class TimeTable {
public:
	TimeTable() = delete;
	TimeTable(std::string path) : mConfig_path{path} {};
	int mAddTime(std::string Time);
	int mAddLesson(std::string Lesson);
	int mGetTime(size_t count);
	char mGetLesson(size_t count);
private:
	std::vector<std::string> mLessons{};
	std::vector<int> mTime{};
	std::string mConfig_path;
	std::string mCurrentLesson;
	std::string mCurrentTime;
	
};