#include "main.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("HelloWin");
    HWND         hwnd;
    MSG          msg;
    WNDCLASS     wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"),
            szAppName, MB_ICONERROR);
        return 0;
    }
    hwnd = CreateWindow(szAppName,                  // window class name
        TEXT("The packman program"), // window caption
        WS_OVERLAPPEDWINDOW,        // window style
        40,              // initial x position
        40,              // initial y position
        440,              // initial x size
        515,              // initial y size
        NULL,                       // parent window handle
        NULL,                       // window menu handle
        hInstance,                  // program instance handle
        NULL);                     // creation parameters


    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    BG = LoadImage(hInstance, TEXT(".\\pacmanworld.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC         hdc;
    PAINTSTRUCT ps;
    RECT        rect;

    switch (message)
    {
    case WM_CREATE:
        initializeField();
        initializeCreatures();
        gameStatus = THREE;
        SetTimer(hwnd, 1, 10, NULL);
        return 0;

    case WM_KEYDOWN:
        if (GetKeyState(VK_RIGHT) < 0)
        {
            Packman.next_direction = RIGHT;
            if (Packman.current_direction == LEFT) Packman.current_direction = RIGHT;
        }
        if (GetKeyState(VK_LEFT) < 0)
        {
            Packman.next_direction = LEFT;
            if (Packman.current_direction == RIGHT) Packman.current_direction = LEFT;
        }
        if (GetKeyState(VK_UP) < 0)
        {
            Packman.next_direction = UP;
            if (Packman.current_direction == DOWN) Packman.current_direction = UP;
        }
        if (GetKeyState(VK_DOWN) < 0)
        {
            Packman.next_direction = DOWN;
            if (Packman.current_direction == UP) Packman.current_direction = DOWN;
        }
        if (GetKeyState(VK_SPACE) < 0)
        {
            PostQuitMessage(0);
            KillTimer(hwnd, 1);
        }
        if (GetKeyState(VK_ESCAPE) < 0)
        {
            KillTimer(hwnd, 1);
            SendMessage(hwnd, WM_CREATE, 0, 0);
            SendMessage(hwnd, WM_PAINT, 0, 0);
        }
    case WM_SIZE:
        GetClientRect(hwnd, &ClientRect);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);

        virtualDrawing(hdc);

        EndPaint(hwnd, &ps);
        return 0;
    case WM_TIMER:
        InvalidateRect(hwnd, NULL, TRUE);

        packmanDirection();
        movement(&Packman);
        checkSeed();

        for (int i = 0; i < 3; i++)
        {
            randomDirection(&Ghost[i]);
            movement(&Ghost[i]);
        }

        cleverDirection(&Ghost[3]);
        movement(&Ghost[3]);

        checkStatus();
        if ((gameStatus == LOSE) || (gameStatus == WIN)) KillTimer(hwnd, 1);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        KillTimer(hwnd, 1);
        return 0;
    case WM_ERASEBKGND:
        return 1;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

