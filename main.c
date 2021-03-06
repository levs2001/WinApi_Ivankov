#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include "file_reader.h"
#include "viewer_comps.h"
#include "scrolling.h"
#include "mymenu.h"


LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[ ] = _T("SaskovViewer");
TCHAR szMyMenu[ ] = _T("MyMenu");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow) {
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_OWNDC;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = szMyMenu;
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = CreateSolidBrush(RGB(255,255,255));//(HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               szClassName,       /* Title Text */
               WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0)) {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT paintStruct;

    // ????????? ???????, ?? ????? ????? ????? ?????????? ???????? ? ???
    static viewer_t viewerStatic;

    switch (message) {                /* handle the messages */
    case WM_CREATE: {
        InitViewer(&viewerStatic, hwnd);
    }
    break;
    case WM_SIZE: {
        ResizeViewer(&viewerStatic, hwnd);
        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;
    case WM_KEYDOWN: {
        ProcessKeyDownViewer(&viewerStatic, hwnd, wParam);
    }
    break;
    case WM_VSCROLL: {
        ProcessVscrollViewer(&viewerStatic, hwnd, wParam);
    }
    break;
    case WM_HSCROLL: {
        ProcessHscrollViewer(&viewerStatic, hwnd, wParam);
    }
    break;
    case WM_MOUSEWHEEL: {
        ProcessMouseWheel(&viewerStatic, hwnd, wParam);
    }
    break;
    case WM_PAINT: {
        BeginPaint(hwnd, &paintStruct);
        ShowViewer(&viewerStatic, GetDC(hwnd));
        EndPaint(hwnd, &paintStruct);
    }
    break;
    case WM_DESTROY: {
        ClearViewer(&viewerStatic);
        PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
    }
    break;
    case WM_COMMAND: {
        switch(LOWORD(wParam)) {
        case IDM_OPEN: {
            char filename[MAX_PATH];
            if(OpenFileDlg(hwnd, filename)) {
                CloseFileInViewer(&viewerStatic);
                SendFileInViewer(&viewerStatic, filename);
                ResizeViewer(&viewerStatic, hwnd);
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        }
        case IDM_CLOSE: {
            CloseFileInViewer(&viewerStatic);
            // Resize ? ?????? ?????? ????? ??? ????, ????? ???????? ????????? ?????????? ? ?????? ??????????????? ??????????
            ResizeViewer(&viewerStatic, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case IDM_WRAP_OFF: {
            WrapOffViewer(&viewerStatic);
            ResizeViewer(&viewerStatic, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case IDM_WRAP_ON: {
            WrapOnViewer(&viewerStatic);
            ResizeViewer(&viewerStatic, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case IDM_EXIT: {
            ClearViewer(&viewerStatic);
            PostQuitMessage(0);
            break;
        }
        }
    }
    break;

    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }


    return 0;
}
