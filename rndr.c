#include "rndr.h"

HDC rndrHDC = NULL;

__attribute__((weak)) void draw() {}

LRESULT CALLBACK _rndr_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            rndrHDC = BeginPaint(hwnd, &ps);
            draw();
            EndPaint(hwnd, &ps);
            rndrHDC = NULL;
        } break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int setup(const char* title, int width, int height) {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = _rndr_WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "_";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, "_", title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
