#include "stdafx.h"
#include "main.h"
#include "Sprite.h"
#include "MainController.h"
#include "Core.h"
Sprite *backgorund;


MainController *mainController;

#define FPS 50
#define INTERVAL 1000/FPS
#define FPS_PER_TRANSACTION 50

#define INCREASE_SPEED 0
#define DECREASE_SPEED 1
#define GENERATE_CAR 1

int counter;
float delta;

void onNewCycle(Car *carIAH,Car *carOAH,Car *carIBH,Car *carOBH, Car *carIAV, Car *carOAV, Car *carIBV, Car *carOBV)
{
	//remove old !!!

	//create new ones ! check for null
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT 	ps;
	HDC hdc;
    switch (message)
    {
	case WM_CREATE:
		SetTimer(hWnd, TIMER_ELAPSE, INTERVAL, (TIMERPROC)NULL);
		mainController = new MainController(hInst,hWnd);
		
		///375 px wdth 

		//Gnerate Objects
		mainController->createAcar();

		break;
	case WM_LBUTTONDOWN: {
		mainController->switchTraficLightColor();
	}
	case WM_TIMER:
		switch (wParam)
		{
		case TIMER_ELAPSE:
			delta = counter*1.0/FPS_PER_TRANSACTION;
			counter++;
			if (counter > FPS_PER_TRANSACTION)
			{
				core.nextStep();
				onNewCycle(
					*(core.horizontalRoad._inputA.begin()),
					*(core.horizontalRoad._outputA.begin()),
					*(core.horizontalRoad._inputB.begin()),
					*(core.horizontalRoad._outputB.begin()),
					*(core.verticalRoad._inputA.begin()),
					*(core.verticalRoad._outputA.begin()),
					*(core.verticalRoad._inputB.begin()),
					*(core.verticalRoad._outputB.begin())
				);
				if (core.iterator == 0)
					mainController->switchTraficLightColor();
				counter = 0;
			}
			RECT rect;
			GetClientRect(hWnd, &rect);
			///Update all here
			mainController->update();
			InvalidateRect(hWnd, &rect, false);			
			break;
		}
		break;
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
    case WM_PAINT:
        {
			hdc = BeginPaint(hWnd, &ps);
			mainController->render(ps,hdc);
			EndPaint(hWnd, &ps);		
			break;
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
