// 课程表.cpp : 定义应用程序的入口点。
//
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include "framework.h"
#include "TimeTable.h"
#include "New.h"
//#include <string>
//#undef UNICODE
#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HFONT hf = CreateFont(16,                                                 //   nHeight 
    0,                                                   //   nWidth 
    0,                                                   //   nEscapement 
    0,                                                   //   nOrientation 
    FW_BOLD,                                       //   nWeight 
    FALSE,                                           //   bItalic 
    FALSE,                                           //   bUnderline 
    0,                                                   //   cStrikeOut 
    DEFAULT_CHARSET,                       //   nCharSet 
    OUT_DEFAULT_PRECIS,                 //   nOutPrecision 
    CLIP_DEFAULT_PRECIS,               //   nClipPrecision 
    DEFAULT_QUALITY,                       //   nQuality 
    DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily 
    TEXT("微软雅黑"));
// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    MAIN(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    NEW(HWND, UINT, WPARAM, LPARAM);

//void PrintMainWindow(HWND hwnd, HWND* hChild, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));
    //HACCEL hAccelTable = LoadAccelerators(hInstance, 0);

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
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY);
    //wcex.lpszMenuName = 0;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   HWND hWnd = CreateWindow(szWindowClass, L"课程表",
       WS_OVERLAPPEDWINDOW, 40, 25, 250, 58, NULL, NULL, hInstance, NULL);
   //HWND hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAIN), GetDesktopWindow(),WndProc);

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
    switch (message)
    {
    /*static HWND      hChild[1];
    HDC                   hdc;
    PAINTSTRUCT     ps;
    RECT                   rect;
    static int             cxChar, cyChar;*/
    case WM_CREATE:
    {
        HWND hdlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAIN), hWnd, (DLGPROC)MAIN);
        // 显示对话框
        ShowWindow(hdlg, SW_SHOWNA);
        //PrintMainWindow(hWnd, hChild, lParam);
        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_NEW:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_NEW), hWnd, NEW);
                break;
            case IDM_MAIN:
               ShowWindow(CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAIN), hWnd, (DLGPROC)MAIN), SW_SHOW);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...

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

// “关于”框的消息处理程序。
INT_PTR CALLBACK MAIN(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        char buf[128];
        SendMessage(GetDlgItem(hDlg, IDC_LIST), LB_ADDSTRING, 0, (LPARAM)L"星期|序号 |    1    |    2    |    3    |    4    |    5    |    6    |    7    |    8    |    9    |    10    |    11    |    12    |");
        SetFocus(GetDlgItem(hDlg, IDC_LIST));
        ifstream cofig_file;
        cofig_file.open("cofig.txt");
        while (cofig_file.getline(buf,128,'\n')) {
            SendMessage(GetDlgItem(hDlg, IDC_LIST), LB_ADDSTRING, 0, buf);
            for (int i = 0; i < 128 ; i++) {
                buf[i] = NULL;
            };
        };
        return (INT_PTR)TRUE;
        break;
    };
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_FLASH:
            DestroyWindow(hDlg);
            break;
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hDlg);
        //PostQuitMessage(0);
        break;
    };
    return (INT_PTR)FALSE;
};
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
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
};
INT_PTR CALLBACK NEW(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            int x{};
            if (IsDlgButtonChecked(hDlg, IDC_RADIO1)== BST_CHECKED) {
                x = 1;
            };
            if (IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED) {
                x = 2;
            };
            if (IsDlgButtonChecked(hDlg, IDC_RADIO3) == BST_CHECKED) {
                x = 3;
            };
            if (IsDlgButtonChecked(hDlg, IDC_RADIO4) == BST_CHECKED) {
                x = 4;
            };
            if (IsDlgButtonChecked(hDlg, IDC_RADIO5) == BST_CHECKED) {
                x = 5;
            };
            if (IsDlgButtonChecked(hDlg, IDC_RADIO6) == BST_CHECKED) {
                x = 6;
            };
            if (IsDlgButtonChecked(hDlg, IDC_RADIO7) == BST_CHECKED) {
                x = 7;
            };

           // int x=500;
            //int Length = GetWindowTextLength(GetDlgItem(hDlg, IDC_EDIT1));
            ofstream cofig_file;
            cofig_file.open("cofig.txt", ios::app);
            int a = GetWindowTextLength(GetDlgItem(hDlg, IDC_EDIT1));
            if (!(cofig_file.fail()||a==0|| a >90)) {
                TCHAR text[100];
                GetWindowText(GetDlgItem(hDlg, IDC_EDIT1), text, 100);
                cofig_file << x << " ";
                //cofig_file.put((char)text);
                for (int i = 0; i < a; i++) {
                    cofig_file<<(char)text[i] ;
                };
                cofig_file << endl;
                

                
                //MessageBox(hDlg, text, L"", MB_OK);
                //MessageBox(hDlg, (char)text, L"", MB_OK);
                MessageBox(hDlg, L"Successful", L"", MB_OK);
                cofig_file.close();
            }
            else {
                MessageBox(hDlg,L"Failed", L"", MB_OK);
            };
            return (INT_PTR)TRUE;
            break;
        }
            
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        case IDDONE:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        };
    default:
        break;
    };
    return(INT_PTR)FALSE;
};
TimeTable_file::TimeTable_file() {
    
};
/*TimeTable_file::~TimeTable_file() {}
void TimeTable_file::ResetTimeTable(HWND hDlg)
{
    char text[200];
    GetWindowText(GetDlgItem(hDlg, IDC_EDIT1),(LPWSTR)text,200);
    fstream cofig_file("cofig.txt");
    if (!cofig_file.fail()) {
        cofig_file << text;
        cofig_file.close();
    };
};*/
//TimeTable_Date::TimeTable_Date() {};
/*void PrintMainWindow(HWND hwnd, HWND* hChild, LPARAM lParam) {
    hChild[IDD_MAIN] = CreateWindow(TEXT("edit"), NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        0, 0, 0, 0,
        hwnd, (HMENU)IDD_MAIN, hInst, NULL);
};*/
//void LoadTimeTable() {

//}