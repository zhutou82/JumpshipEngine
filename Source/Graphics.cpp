#include "Graphics.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
//void Graphics::Init(const Vec2f& windowResolution, const std::string& windowName)
//{
//  // Register the window class.
//  const wchar_t CLASS_NAME[] = L"Sample Window Class";
//
//  //WNDCLASS wc = { };
//
//  //wc.lpfnWndProc = WindowProc;
//  //wc.hInstance = hInstance;
//  //wc.lpszClassName = CLASS_NAME;
//  //
//  //HWND hwnd = CreateWindowEx(
//  //  0,                              // Optional window styles.
//  //  CLASS_NAME,                     // Window class
//  //  L"Learn to Program Windows",    // Window text
//  //  WS_OVERLAPPEDWINDOW,            // Window style
//
//  //  // Size and position
//  //  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
//
//  //  NULL,       // Parent window    
//  //  NULL,       // Menu
//  //  hInstance,  // Instance handle
//  //  NULL        // Additional application data
//  //);
//
//  //if (hwnd == NULL)
//  //{
//  //  return 0;
//  //}
//
//  //ShowWindow(hwnd, nCmdShow);
//}
