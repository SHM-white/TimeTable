// test_of_time.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma warning(disable : 4996)
#include <iostream>
#include <time.h>
#include "Timetable.h"
#include <Windows.h>
#include <fstream>
#include "include\json\json.h"



int main()
{

    std::string Days;
    std::string Lesson;
    std::string BeginTime;
    std::string EndTime;
    TimeTable timetable("config.json");
    while (true)
    {
        std::cout << "请依次输入星期，课程名，开始时间，结束时间\n";
        std::cin >> Days;
        std::cin >> Lesson;
        std::cin >> BeginTime;
        std::cin >> EndTime;
        timetable.mAddLesson(Days, Lesson, BeginTime,EndTime);
        std::cout << "done\n";
    }
    //std::cout << mGetCurrentLesson();
    return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
