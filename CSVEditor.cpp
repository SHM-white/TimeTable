#include "CSVEditor.h"
#include "Timetable.h"
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "include\json\json.h"
#include <format>
//#include <iostream>

int CSVEditor::mGetCsvData()
{
    std::fstream in;
	std::string line;
    in.open(mCsvPath, std::ios::in);
    if (!in.is_open()) {
        return 0;
    }
	while (std::getline(in,line)) {
		std::string columElement;
		std::stringstream stream(line);
		data.push_back(std::vector<std::string>());
		while (getline(stream, columElement, ',')) {
			data.back().push_back(columElement);
		}
		//������һ��Ԫ�ء����ڶ�ȡ���һ����Ԫ�ػ�����ѭ��,����a����    ֻ�ܶ�ȡ��a���ճ���û����
		if (!stream && columElement.empty()) {
			data.back().push_back("");
		}
	}
	in.close();
    return 0;
}

const std::vector<std::string>& CSVEditor::operator[](int line)
{
    return data[line];
}
