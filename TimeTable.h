#pragma once
#include "resource.h"
#include <fstream>
using namespace std;

/*class TimeTable_Date {
public:
	TimeTable_Date();
};*/
class TimeTable_file {
public:
	TimeTable_file();
	~TimeTable_file();
	//void ResetTimeTable(HWND hDlg);
	char Lessons = NULL;
};