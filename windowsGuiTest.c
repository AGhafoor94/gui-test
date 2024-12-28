#include <Windows.h>

LRESULT CALLBACK WndProc(HWND handleWindow, UINT message, WPARAM wParam, LPARAM lParam);
unsigned short InitialiseWindow(HINSTANCE *handleInstance);
int WINAPI wWinMain(HINSTANCE handleInstance, HINSTANCE previousInstance, LPWSTR lpCommandLine, int nCommandShow)
{
    // cl windows.c user32.lib
    MessageBoxExW(0, L"Test\n", L"Testing\n", MB_OK, 0);
    unsigned short registerClass = InitialiseWindow(&handleInstance);
    if(registerClass == 0){
        return 1;
    }
    // CreateWindowW(lpClassName,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,hInstance,lpParam)
    // HWND handleWindow = CreateWindowW(L"Window\0", L"Hi\0", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, handleInstance, 0);
    HWND handleWindow = CreateWindowExW(0L, L"Window", L"Hello", (0x00000000L | 0x00C00000L | 0x00080000L | 0x00040000L | 0x00020000L | 0x00010000L), 100, 100,500, 500, NULL, NULL, handleInstance, 0);
    
    ShowWindow(handleWindow, nCommandShow);
    UpdateWindow(handleWindow);
    MSG message = {0};

    while (GetMessageW(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return 0;
}
unsigned short InitialiseWindow(HINSTANCE *handleInstance)
{
    WNDCLASSEXW windowClass = {0};
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    windowClass.lpfnWndProc = WndProc;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    windowClass.lpszMenuName = L"Hi";
    windowClass.lpszClassName = L"Window";
    windowClass.hIconSm = NULL;
    windowClass.hInstance = *handleInstance;
    windowClass.hIcon = NULL;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    return RegisterClassExW(&windowClass);
}
LRESULT CALLBACK WndProc(HWND handleWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    switch (message)
    {
        case WM_COMMAND:
        {
            OutputDebugString("WM_COMMAND\n");
            result = 0;
        }
        break;
        case WM_ACTIVATEAPP:
        {
            HWND buttonHandle = CreateWindowExW(0L, L"BUTTON", L"Click", WS_TABSTOP | WS_VISIBLE| WS_CHILD| BS_DEFPUSHBUTTON, 10, 10, 100, 100, handleWindow, NULL, 0, NULL);
            OutputDebugString("WM_ACTIVATEAPP");
            result = 0;
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT paintStruct = {0};
            RECT rectangle = {0};
            HDC handleDCBeginPaint = BeginPaint(handleWindow, &paintStruct);
            GetClientRect(handleWindow, &rectangle);
            // FillRect(handleDCBeginPaint,&rectangle,0x00A12345);
            EndPaint(handleWindow, &paintStruct);
            result = 0;
        }
        break;
        case WM_DESTROY:
        {
            result = 0;
            PostQuitMessage(0);
        }
        break;
        case WM_CLOSE:
        {
            result = 0;
            PostQuitMessage(0);
        }
        break;
        default:
            result = DefWindowProc(handleWindow, message, wParam, lParam);
    }
    return result;
}
