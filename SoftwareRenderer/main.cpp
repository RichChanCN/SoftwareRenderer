#include <windows.h>
#include <windowsx.h>
#include <memory>
#include <string>
#include <iostream>
#include <time.h>
#pragma comment(lib, "winmm.lib")
#include "SRDevice.h"
#include "My3DApp.h"
using namespace std;

#define NEED_CONSOLE

HINSTANCE				g_hInstance;				//实例句柄
static HWND				g_hWnd;					//窗口句柄
string					g_title = "SRdemo";		//窗口标题
int						g_width = 800;			//窗口大小
int						g_height = 600;

DWORD g_startFrameTime = 0;
DWORD g_curFrameTime = 0;

SRDevice                *g_device;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
#ifdef NEED_CONSOLE
    AllocConsole();
    FILE* stream;
    freopen_s(&stream, "CON", "r", stdin);//重定向输入流
    freopen_s(&stream, "CON", "w", stdout);//重定向输入流

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
#endif

    //模拟显示器设备
    g_device = new SRDevice(g_width, g_height);
    //app
    My3DApp myApp = My3DApp(g_device);

    //窗口类结构体
    WNDCLASSEX wcex;
    wcex.cbClsExtra = 0;
    wcex.cbSize = sizeof(wcex);
    wcex.cbWndExtra = 0;
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wcex.hIconSm = wcex.hIcon;
    wcex.hInstance = g_hInstance;
    wcex.lpfnWndProc = WndProc; //窗口回调函数
    wcex.lpszClassName = g_title.c_str();
    wcex.lpszMenuName = nullptr;
    wcex.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wcex))
        return 0;

    RECT rc = { 0, 0, 800, 600 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

    HWND g_hWnd = CreateWindowEx(WS_EX_APPWINDOW, g_title.c_str(), g_title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, g_hInstance, nullptr);

    if (!g_hWnd)
    {
        MessageBox(nullptr, "create window failed!", "error", MB_OK);
        return 0;
    }

    ShowWindow(g_hWnd, nShowCmd);
    g_startFrameTime = GetTickCount();

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            g_curFrameTime = GetTickCount();
            g_curFrameTime = g_curFrameTime - g_startFrameTime;
            myApp.render(g_curFrameTime);
            InvalidateRect(g_hWnd, nullptr, true);
            UpdateWindow(g_hWnd);
        }
    }

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    //双缓冲绘图
    static BITMAPINFO s_bitmapInfo;
    static HDC s_hdcBackbuffer;			//后缓冲设备句柄	
    static HBITMAP s_hBitmap;
    static HBITMAP s_hOldBitmap;
    static void* s_pData;

    switch (message)
    {
    case WM_CREATE:
    {
                      //初始化设备无关位图header
                      BITMAPINFOHEADER bmphdr = { 0 };
                      bmphdr.biSize = sizeof(BITMAPINFOHEADER);
                      bmphdr.biWidth = g_width;
                      bmphdr.biHeight = -g_height;
                      bmphdr.biPlanes = 1;
                      bmphdr.biBitCount = 32;
                      bmphdr.biSizeImage = g_height * g_width * 4;
                      //创建后缓冲区
                      //先创建一个内存dc
                      s_hdcBackbuffer = CreateCompatibleDC(nullptr);
                      //获得前置缓冲区dc
                      HDC hdc = GetDC(hWnd);
                      if (!(s_hBitmap = CreateDIBSection(nullptr, (PBITMAPINFO)&bmphdr, DIB_RGB_COLORS,
                          reinterpret_cast<void**>(&g_device->getFrameBuffer()), nullptr, 0)))
                      {
                          MessageBox(nullptr, "create dib section failed!", "error", MB_OK);
                          return 0;
                      }
                      //将bitmap装入内存dc
                      s_hOldBitmap = (HBITMAP)SelectObject(s_hdcBackbuffer, s_hBitmap);
                      //释放dc
                      ReleaseDC(hWnd, hdc);
    }
        break;
    case WM_PAINT:
    {
                     hdc = BeginPaint(hWnd, &ps);
                     //把backbuffer内容传到frontbuffer
                     BitBlt(ps.hdc, 0, 0, g_width, g_height, s_hdcBackbuffer, 0, 0, SRCCOPY);
                     EndPaint(hWnd, &ps);
    }
        break;
    case WM_DESTROY:
        SelectObject(s_hdcBackbuffer, s_hOldBitmap);
        DeleteDC(s_hdcBackbuffer);
        DeleteObject(s_hOldBitmap);
        PostQuitMessage(0);
        break;

        //禁止背景擦除 防止闪烁
    case WM_ERASEBKGND:
        return true;
        break;
        //鼠标事件
        //鼠标被按下时
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
        return 0;

        //鼠标释放时
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
        return 0;

        //鼠标移动时
    case WM_MOUSEMOVE:
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}