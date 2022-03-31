#pragma once
#include "TimeTable.h"
class New_TimeTable :public TimeTable_file
{
public:
	void DECLARE_DYNAMIC(New_TimeTable);
	enum {
		IDD = IDD_NEW
	};
};