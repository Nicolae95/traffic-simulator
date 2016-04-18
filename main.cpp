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

#define INCREASE_SPAWN_VELOCITY 1
#define DECREASE_SPAWN_VELOCITY 2

int counter;

void onNewCycle(Car *carIAH,Car *carOAH,Car *carIBH,Car *carOBH, Car *carIAV, Car *carOAV, Car *carIBV, Car *carOBV)
{
	//remove old !!!
	mainController->removeAllCars();
	if (carIAH)
		mainController->createBcar(carIAH->direction == RIGHT, carIAH->direction == LEFT);
	if (carIBH)
		mainController->createDcar(carIBH->direction == RIGHT, carIAH->direction == LEFT);
	if (carIAV)
		mainController->createAcar(carIAH->direction == RIGHT, carIAH->direction == LEFT);
	if (carIBV)
		mainController->createCcar(carIBH->direction == RIGHT, carIAH->direction == LEFT);
	
	if (carOAH)
		mainController->createBcar(carIAH->direction == RIGHT, carIAH->direction == LEFT);
	if (carOBH)
		mainController->createDcar(carIBH->direction == RIGHT, carIAH->direction == LEFT);
	if (carOAV)
		mainController->createAcar(carIAH->direction == RIGHT, carIAH->direction == LEFT);
	if (carOBV)
		mainController->createCcar(carIBH->direction == RIGHT, carIAH->direction == LEFT);
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
<<<<<<< HEAD


		RegisterHotKey(hWnd, INCREASE_SPAWN_VELOCITY, MOD_CONTROL, 0x51);

		RegisterHotKey(hWnd, DECREASE_SPAWN_VELOCITY, MOD_CONTROL, 0x41);
		
		///375 px wdth 

		//Gnerate Objects
		mainController->createAcar();
=======
>>>>>>> af3d9f3425355e4ce36e3688baa9286483366d08

		break;
	case WM_LBUTTONDOWN: {
		mainController->switchTraficLightColor();
	}
	case WM_HOTKEY:
		switch (wParam)
		{
		case INCREASE_SPAWN_VELOCITY:
			core.increaseRandomSpeed();
			break;
		case DECREASE_SPAWN_VELOCITY:
			core.decreaseRandomSpeed();
			break;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case TIMER_ELAPSE:
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
	case WM_MOUSEWHEEL: {
		int mouseWheel = (short)HIWORD(wParam);
		mouseWheel > 0 ? core.increaseSpeed() : core.decreaseSpeed();
	}
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

	case WM_GETMINMAXINFO: {
		MINMAXINFO *mmi = (MINMAXINFO *)lParam;
		mmi->ptMinTrackSize.x = WINDOW_WIDTH;
		mmi->ptMinTrackSize.y = WINDOW_HEIGHT;
		return 0; 
	}
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
