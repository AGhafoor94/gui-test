#include <Windows.h>

LRESULT CALLBACK MainWindow(HWND handle_window, UINT message, WPARAM w_param, LPARAM l_param);
unsigned short InitialiseWindow(HINSTANCE *handle_instance);
void AddButtonStyles(HWND handle_window, LPCWSTR window_name, LPWSTR text, int length_of_text, COLORREF colour);

int WINAPI wWinMain(HINSTANCE handle_instance, HINSTANCE previousInstance, LPWSTR lpCommandLine, int n_command_show)
{
    // cl windows.c user32.lib kernel32.lib gdi32.lib
    // MessageBoxExW(0, L"Test\n", L"Testing\n", MB_OK, 0);
    unsigned short register_class = InitialiseWindow(&handle_instance);
    if(register_class == 0){
        return 1;
    }
    // CreateWindowW(lpClassName,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,hInstance,lpParam)
    // HWND handleWindow = CreateWindowW(L"Window\0", L"Hi\0", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, handleInstance, 0);
    
    HWND handle_window = CreateWindowExW(0L, L"Window", L"Hello", (0x00000000L | 0x00C00000L | 0x00080000L | 0x00040000L | 0x00020000L | 0x00010000L), 100, 100,500, 500, NULL, NULL, handle_instance, 0);
    // HWND button_window = CreateWindowExW(0L, L"BUTTON", L"Click", WS_TABSTOP | WS_VISIBLE| WS_CHILD| BS_DEFPUSHBUTTON | BS_OWNERDRAW, 10, 10, 100, 100, handle_window, (HMENU)101, 0, NULL);
    ShowWindow(handle_window, n_command_show); 
    UpdateWindow(handle_window);
    MSG message = {0};

    while (GetMessageW(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return 0;
}
unsigned short InitialiseWindow(HINSTANCE *handle_instance)
{
    WNDCLASSEXW window_class = {0};
    window_class.cbSize = sizeof(WNDCLASSEX);
    window_class.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    window_class.lpfnWndProc = MainWindow;
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    window_class.lpszMenuName = L"Hi";
    window_class.lpszClassName = L"Window";
    window_class.hIconSm = NULL;
    window_class.hInstance = *handle_instance;
    window_class.hIcon = NULL;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    return RegisterClassExW(&window_class);
}
LRESULT CALLBACK MainWindow(HWND handle_window, UINT message, WPARAM w_param, LPARAM l_param)
{
    LRESULT result = 0;
    switch (message)
    {
        case WM_CREATE:
            {
                // HWND button_window = CreateWindowExW(0L, L"BUTTON", L"Click", WS_TABSTOP | WS_VISIBLE| WS_CHILD| BS_DEFPUSHBUTTON | BS_OWNERDRAW, 10, 10, 100, 100, handle_window, (HMENU)101, 0, NULL);
                // HDC button_handle = GetDC(button_window);
                // LPDRAWITEMSTRUCT p_item_struct = (LPDRAWITEMSTRUCT) l_param;
                // HBRUSH brush = CreateSolidBrush(RGB(252,120,31));
                // SelectObject(button_handle, brush);
                
                CreateWindowExW(0L, L"BUTTON", L"Click", WS_TABSTOP | WS_VISIBLE| WS_CHILD| BS_DEFPUSHBUTTON | BS_OWNERDRAW, 10, 10, 100, 100, handle_window, (HMENU)101, 0, NULL);
                CreateWindowExW(0L, L"BUTTON", L"Other", WS_TABSTOP | WS_VISIBLE| WS_CHILD| BS_DEFPUSHBUTTON | BS_OWNERDRAW, 150, 10, 250, 100, handle_window, (HMENU)102, 0, NULL);
                
            }
            break;
        case WM_ACTIVATEAPP:
            {
                
                // UpdateWindow(handle_window);

                OutputDebugString("WM_ACTIVATEAPP");
                result = 0;
            }
            break;
        case WM_PAINT:
            {
                // LPDRAWITEMSTRUCT pItemStruct = (LPDRAWITEMSTRUCT) lParam;
                PAINTSTRUCT paint_struct = {0};
                RECT rectangle = {0};
                HDC handle_window_hdc = BeginPaint(handle_window, &paint_struct);
                GetClientRect(handle_window, &rectangle);
                FillRect(handle_window_hdc,&rectangle,CreateSolidBrush(RGB(245,245,245)));
                EndPaint(handle_window, &paint_struct);
                result = 0;
            }
            break;
        case WM_DRAWITEM:
            {
                AddButtonStyles(handle_window, L"Click", L"Click Here", 11, RGB(252,120,31));
                AddButtonStyles(handle_window, L"Other", L"Testing Window", 15, RGB(121,220,31)); 
            }
            break;
        
        case WM_COMMAND:
            {
                OutputDebugString("WM_COMMAND\n");
                switch(LOWORD(w_param)){
                    case 101:
                        {
                            SendMessageW(handle_window, WM_CLOSE, w_param,l_param);
                        }
                        break;
                    case 102:
                        {
                            SendMessageW(handle_window, WM_CLOSE, w_param,l_param);
                        }
                        break;
                }
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
            result = DefWindowProc(handle_window, message, w_param, l_param);
    }
    return result;
}

void AddButtonStyles(HWND handle_window, LPCWSTR window_name, LPWSTR text, int length_of_text, COLORREF colour) {
    RECT rectangle = {0};
    HWND button_window = FindWindowExW(handle_window, NULL, L"BUTTON", window_name);
    GetClientRect(button_window,&rectangle);
    HDC button_hdc = GetDC(button_window);
    FillRect(button_hdc, &rectangle, CreateSolidBrush(colour)); 
    // SetBkColor(button_hdc, RGB(0,0,0));
    SetBkMode(button_hdc, TRANSPARENT);
    DrawTextExW(button_hdc,text,length_of_text,&rectangle,DT_CENTER | DT_VCENTER | DT_SINGLELINE,NULL);
    DeleteObject(button_hdc);
    DeleteObject(button_window);
}