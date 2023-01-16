#pragma once

#include<string>
#include<string_view>
#include<format>
#include<vector>
#include "resource.h"
#include<Windows.h>
#include"Lesson.h"


//TimeTable类，包含与获取课程有关的函数，需初始化配置文件路径
class TimeTable {
public:
	TimeTable() = delete;
	TimeTable(std::string path) : mLessonInfoPath{ path } {};
	int mAddLesson(std::string Days, std::string Lesson, std::string sBegin, std::string sEnd);
	int mAddMoreInfo(std::string Days, std::string Info);
	int mGetLesson(std::vector<std::string>& input);
	int mGetTodayMoreInfo(std::vector<std::string>& input);
	int mImportLessonsFromCsv(const std::string path);
	std::string mGetCurrentLesson(std::string& LessonNull);
	std::string mGetCurrentTime(const std::string& TextFormat);
private:
	Lesson CurrentLesson;
	std::string mLessonInfoPath{ "Lessons.json" };
	int mTimeToMin(int input);
};





