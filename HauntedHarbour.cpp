// HauntedHarbour.cpp : Defines the entry point for the application.
//


/**************Customization*********************
death animation for viktor
*/

#include "framework.h"
#include "HauntedHarbour.h"
#include "GraphicsObject.h"
#include "PlayerObject.h"
#include "BackgroundObject.h"
#include "BulletObject.h"
#include "BlockObject.h"
#include "GroundEnemiesObject.h"
#include "AirEnemiesObject.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

PlayerObject viktor;
BackgroundObject ground("Pics/Ground.bmp", 0, 400, 774, 128, 1);
BackgroundObject background("Pics/Background3.jpg", 0, 0, 5118, 800, 0.1);
BlockObject* crates[50];
GroundEnemiesObject* skullCrabs[10];
AirEnemiesObject seaHag(&viktor, 300, 200);



//important variables
int mapPosition = 0; 
HDC offScreenDC; //our buffer for the double buffering 

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                SetScreen(); //used to render our buffer for double buffering
void                DrawScreen(HWND hwnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HAUNTEDHARBOUR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HAUNTEDHARBOUR));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HAUNTEDHARBOUR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HAUNTEDHARBOUR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 700, 580, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   for (int i = 0; i < 50; i++)
   {
       crates[i] = new BlockObject();

       crates[i]->x = 64 * i;
   }

   for (int i = 0; i < 10; i++)
   {
       skullCrabs[i] = new GroundEnemiesObject();

       skullCrabs[i]->x = 30 * i;
   }

   SetTimer(hWnd, 1, 50, NULL); //this sets up our timer, especially how fast it runs

   SetScreen(); //set the target screen for rendering

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

        //this case if for our key presses
    case WM_KEYDOWN:
        //any code we write in here will run as soon as we press a key
        switch (wParam) //wParam represents the current key that we press
        {
        case VK_RIGHT:
            if (viktor.IsJumping())
            {
                viktor.picY = 86;
                viktor.xspeed = 5;
                viktor.currentState = JUMPRIGHT; //tell the program that we're still in mid-air
            }
            else
            {
                viktor.SetMoveRight();
            }
            viktor.stoppedRight = false;
            break;
        case VK_LEFT:
            if (viktor.IsJumping())
            {
                viktor.picY = 146;
                viktor.xspeed = -5;
                viktor.currentState = JUMPLEFT; //tell the program that we're still in mid-air
            }
            else
            {
                viktor.SetMoveLeft();
            }
            viktor.stoppedLeft = false;
            break;

        case VK_UP:
            if (viktor.currentState == MOVERIGHT || viktor.currentState == STANDRIGHT)
            {
                viktor.JumpingRight();
            }
            if (viktor.currentState == MOVELEFT || viktor.currentState == STANDLEFT)
            {
                viktor.JumpingLeft();
            }   
            break;
        case VK_SPACE:
            if (viktor.currentState == STANDRIGHT)
            {
                viktor.ShootingRight();
                viktor.FireBullet(viktor.x + viktor.width, viktor.y, 30, 0);
            }
            if (viktor.currentState == STANDLEFT)
            {
                viktor.ShootingLeft();
                viktor.FireBullet(viktor.x, viktor.y, -30, 0);
            }
            if (viktor.currentState == SHOOTRIGHT || viktor.currentState == MOVERIGHT || viktor.currentState == JUMPRIGHT)
            {
                viktor.FireBullet(viktor.x + viktor.width, viktor.y, 30, 0);
            }
            if (viktor.currentState == SHOOTLEFT || viktor.currentState == MOVELEFT || viktor.currentState == JUMPLEFT)
            {
                viktor.FireBullet(viktor.x, viktor.y, -30, 0);
            }
            break;
        }
        break;

        //all the code runs at the moment we RELEASE a key
    case WM_KEYUP:
        switch (wParam)
        {
            case VK_RIGHT:
                if (!viktor.IsJumping())
                {
                    viktor.SetStandingRight();
                }
                viktor.stoppedRight = true;
                break;
            case VK_LEFT:
                if (!viktor.IsJumping())
                {
                    viktor.SetStandingLeft();
                }
                viktor.stoppedLeft = true;
                break;
            case VK_UP:
                break;
            case VK_SPACE:
                if (viktor.currentState == SHOOTRIGHT)
                {
                    viktor.SetStandingRight();
                }
                else if (viktor.currentState == SHOOTLEFT)
                {
                    viktor.SetStandingLeft();
                }
                break;
        }
        break;

        //this case runs things every frame
    case WM_TIMER:
        viktor.Move();
        seaHag.Move();

        for (int i = 0; i < 10; i++)
        {
            skullCrabs[i]->Move();
            skullCrabs[i]->MoveBullets();
        }

        viktor.MoveBullets();
        seaHag.MoveBullets();

        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                viktor.PlayerBlockCollision(crates[i]);
                viktor.BulletBlockCollision(crates[i]);
                skullCrabs[j]->BulletBlockCollision(crates[i]);
                skullCrabs[j]->BlockCollision(crates[i]);
                seaHag.BulletBlockCollision(crates[i]);
            }
        }

        for (int i = 0; i < 10; i++)
        { 
            if (skullCrabs[i]->isAlive == true)
            {
                viktor.BulletCharacterCollision(skullCrabs[i]);
                skullCrabs[i]->BulletCharacterCollision(&viktor);
            }
           
        }

        if (seaHag.isAlive == true)
        {
            viktor.BulletCharacterCollision(&seaHag);
        }

        PostMessage(hWnd, WM_PAINT, 0, 0);
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            background.Draw(offScreenDC);
            ground.Draw(offScreenDC);

            for (int i = 0; i < 50; i++)
            {
                crates[i]->Draw(offScreenDC);
            }

            viktor.Draw(offScreenDC);

      
              
            

            for (int i = 0; i < 10; i++)
            {
                skullCrabs[i]->Draw(offScreenDC);
                skullCrabs[i]->DrawBullets(offScreenDC);
            }

            viktor.DrawBullets(offScreenDC);

            seaHag.Draw(offScreenDC);
            seaHag.DrawBullets(offScreenDC);

            DrawScreen(hWnd);
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

// Message handler for about box.
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
}

void SetScreen()
{
    HDC hTempDC = GetDC(0);
    HBITMAP offScreenBMP;
    offScreenDC = CreateCompatibleDC(hTempDC);
    offScreenBMP = CreateCompatibleBitmap(hTempDC, 800, 600);
    SelectObject(offScreenDC, offScreenBMP);
    ReleaseDC(0, hTempDC);
}

void DrawScreen(HWND hWnd)
{
    HDC ScreenDC = GetDC(hWnd);
    TransparentBlt(ScreenDC, 0, 0, 700, 580, offScreenDC, 0, 0, 700, 580, RGB(255, 174, 201));
    DeleteDC(ScreenDC);
}
