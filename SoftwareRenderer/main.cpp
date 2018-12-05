#include <windows.h>
#include <windowsx.h>
#include <memory>
#include <string>
#include <iostream>
#pragma comment(lib, "winmm.lib")
using namespace std;


HINSTANCE				g_hInstance;				//实例句柄
static HWND				g_hWnd;					//窗口句柄
string					g_title = "TinyD3D";		//窗口标题
int						g_width = 800;			//窗口大小
int						g_height = 600;


UINT*                   m_pFrameBuffer;
int                     i = 0;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void SetFrameBuffer();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

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
            SetFrameBuffer();
            InvalidateRect(g_hWnd, nullptr, true);
            UpdateWindow(g_hWnd);
        }
    }
    return static_cast<int>(msg.wParam);
}

//颜色ZCFloat3(r,b,g,a)转化为UINT
UINT ColorToUINT(float x, float y, float z)
{
    BYTE red = 255 * x/*  color.w*/;
    BYTE green = 255 * y/* color.w*/;
    BYTE blue = 255 * z /* color.w*/;
    return (UINT)((BYTE)blue | (WORD)((BYTE)green << 8) | (DWORD)((BYTE)red << 16));
}

void SetFrameBuffer(){
    m_pFrameBuffer[12000+i++] = ColorToUINT(1.0f, 1.0f, 1.0f);
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
                          reinterpret_cast<void**>(&m_pFrameBuffer), nullptr, 0)))
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