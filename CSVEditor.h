#pragma once

#include<string>
#include<string_view>
#include<format>
#include<vector>
#include "resource.h"
#include<Windows.h>
#include"Lesson.h"

class CSVEditor
{
public:
	CSVEditor() = default;
	CSVEditor(const std::string Path) {
		mSetFilePath(Path);
	}
	int mSetFilePath(const std::string Path) {
		mCsvPath = Path;
	}
	int mGetCsvData();
	//read:[line][order]
	const std::vector<std::string>& operator[](int line);
private:
	std::vector<std::string> line;
	std::vector<std::vector<std::string>> data;
	std::string mCsvPath;
};

