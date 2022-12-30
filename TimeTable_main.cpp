// 定义应用程序的入口点。
//
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "framework.h"
#include "Timetable.h"
#include <tchar.h>
#include "include\json\json.h"


#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
TCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
TimeTable timetable("config.json");
HWND hStaticText;
WindowSettings windowsettings;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddLesson(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DialogMore(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    TextView(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ShowAll(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Settings(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。
    timetable.mGetWindowSettings(windowsettings);

    // 初始化全局字符串
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_TIMETABLE20, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TIMETABLE20));

    MSG msg;

    
    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TIMETABLE20));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_TIMETABLE20);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   
   HWND hWnd = CreateWindowA(szWindowClass, szTitle, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION,
       windowsettings.iWindowX, windowsettings.iWindowY, windowsettings.iWindowWeight, windowsettings.iWindowHeight,
       nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //主窗口消息处理函数
    HFONT hfont;
    static std::string Text;
    switch (message)
    {
    case WM_CREATE:
    {
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//默认置顶窗口
        SetTimer(hWnd, IDT_TIMER1, 1000, (TIMERPROC)NULL);//创建时间为1秒的计时器
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    case WM_TIMER:
        switch (wParam)
        {
        case IDT_TIMER1://每秒更新窗口内容
            // process the 1-second timer 
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            return 0;
        }
        break;
    case WM_COMMAND:
        {
        HMENU hMenu = GetMenu(hWnd);
        int wmId = LOWORD(wParam);
        static MENUITEMINFO MenuItemInfo;
        LPMENUITEMINFO lpMenuItemInfo=&MenuItemInfo;
        lpMenuItemInfo->cbSize = sizeof(MENUITEMINFO);
        lpMenuItemInfo->fMask = MIIM_STATE;//只获取菜单项状态（应该）
            // 分析菜单选择:
            switch (wmId)
            {
            case IDC_AbotButton:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_ADD:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ADDLESSON), hWnd, AddLesson);
                break;
            case IDM_TOTOP://切换是否置顶窗口
                GetMenuItemInfo(hMenu, IDM_TOTOP, FALSE, lpMenuItemInfo);//获取当前状态
                if (lpMenuItemInfo->fState & MFS_CHECKED) {//菜单项checked
                    SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                    lpMenuItemInfo->fState = MFS_UNCHECKED;
                }
                else {//菜单项unchecked
                    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                    lpMenuItemInfo->fState = MFS_CHECKED;
                }
                SetMenuItemInfo(hMenu, IDM_TOTOP, FALSE, lpMenuItemInfo);
                break;
            case IDM_SHOWALL:
                ShowWindow(CreateDialog(hInst, MAKEINTRESOURCE(IDD_SHOWALL), hWnd, ShowAll), SW_SHOW);
                //MessageBox(hWnd, TEXT("咕咕咕"), TEXT("咕咕咕"), MB_OK);
                //上方注释用来暂时占位未完成的功能
                break;
            case IDM_SETTINGS:
                MessageBox(hWnd, TEXT("咕咕咕"), TEXT("咕咕咕"), MB_OK);
                //DialogBox(hInst, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, Settings);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_MoreInfo:
                
                ShowWindow(CreateDialog(hInst, MAKEINTRESOURCE(IDD_MOREINFO), hWnd, DialogMore), SW_SHOW);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT://hdc绘图函数
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            hfont = CreateFont(windowsettings.iFontSize, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, CLEARTYPE_QUALITY, 0, windowsettings.sFontName.c_str());
            int y = 2;
            SelectObject(hdc, hfont);
            for (int i = 0; i < windowsettings.sTextFormat.size();i++) {
                Text = timetable.mGetCurrentTime(windowsettings.sTextFormat[i]);
                if (i == (windowsettings.sTextFormat.size() - 1)) {
                    Text += timetable.mGetCurrentLesson();
                }
                TextOut(hdc, 2, y, Text.c_str(), (int)Text.size());
                y += windowsettings.iLineDistance;
            }
            DeleteObject(hfont);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK    DialogMore(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    std::vector<std::string> Infos;
    TCHAR szWeek[16];
    TCHAR szInfo[256];
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        if (timetable.mGetTodayMoreInfo(Infos)) {
            for (auto a : Infos) {
                SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)a.c_str());
            }
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {

        case IDOK:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        case IDC_ADD://检测文本框是否有文本，并存储
            if (GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT2), szWeek, GetWindowTextLengthA(GetDlgItem(hDlg, IDC_EDIT2)) + 1) +
                GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), szInfo, GetWindowTextLengthA(GetDlgItem(hDlg, IDC_EDIT1)) + 1))
            {
                timetable.mAddMoreInfo(szWeek, szInfo);
                MessageBox(hDlg, TEXT("成功"), TEXT("提示"), MB_OK);
                {//刷新列表框内容
                    SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_RESETCONTENT, 0, 0);
                    if (timetable.mGetTodayMoreInfo(Infos)) {
                        for (auto a : Infos) {
                            SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)a.c_str());
                        }
                    }
                }
                break;
            }
            MessageBox(hDlg, TEXT("失败"), TEXT("提示"), MB_OK);
            break;
        case IDC_FLASH:
            SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_RESETCONTENT,0,0);
            if (timetable.mGetTodayMoreInfo(Infos)) {
                for (auto a : Infos) {
                    SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)a.c_str());
                }
            }
            return (INT_PTR)TRUE;
            break;
        default:
            break;
        }
        break;
    }
    return (INT_PTR)FALSE;
};
INT_PTR CALLBACK AddLesson(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    
    TCHAR szLessonName[50]{};
    TCHAR szBeginTime[16]{};
    TCHAR szEndTime[16]{};
    TCHAR szWeek[16]{};
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_ADD:
            if (
                GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT4), szWeek, GetWindowTextLengthA(GetDlgItem(hDlg,IDC_EDIT4))+1)+
                GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), szLessonName, GetWindowTextLengthA(GetDlgItem(hDlg, IDC_EDIT1))+1)+
                GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT2), szBeginTime, GetWindowTextLengthA(GetDlgItem(hDlg, IDC_EDIT2))+1)+
                GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT3), szEndTime, GetWindowTextLengthA(GetDlgItem(hDlg, IDC_EDIT3))+1)
                ) {
                timetable.mAddLesson(szWeek, szLessonName, szBeginTime, szEndTime);
                MessageBox(hDlg, TEXT("成功"), TEXT("提示"), MB_OK);
                break;
            };
            MessageBox(hDlg, TEXT("失败"), TEXT("提示"), MB_OK);
            break;
        case IDOK:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        default:
            break;
        } 
        break;
    }
    return (INT_PTR)FALSE;
};
INT_PTR CALLBACK ShowAll(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::vector<std::string> Lessons;
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        if (timetable.mGetLesson(Lessons)){
            for (auto a : Lessons) {
                SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)a.c_str());
            }
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {

        case IDOK:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        case IDC_FLASH:
            SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_RESETCONTENT, 0, 0);
            if (timetable.mGetLesson(Lessons)){
                for (auto a : Lessons) {
                    SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)a.c_str());
                }
            }
            return (INT_PTR)TRUE;
            break;
        default:
            break;
        }
        break;
    }
    return (INT_PTR)FALSE;
};
INT_PTR CALLBACK Settings(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        default:
            break;
        }
        break;
    }
    return (INT_PTR)FALSE;
};
//以下为暂时没啥用的
INT_PTR CALLBACK TextView(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        default:
            break;
        }
        break;
    }
    return (INT_PTR)FALSE;
};
// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::string About;
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        timetable.mGetAbout(About);
        SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), About.c_str());
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



