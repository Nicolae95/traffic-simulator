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
float delta;

void onNewCycle(Car *carIAH,Car *carOAH,Car *carIBH,Car *carOBH, Car *carIAV, Car *carOAV, Car *carIBV, Car *carOBV)
{
	//remove old !!!
	mainController->removeAllCars();
	if (carIAH)
		mainController->createBcar(carIAH->direction == LEFT, carIAH->direction == RIGHT,carIAH->animateAparition);
	if (carIBH)
		mainController->createDcar(carIBH->direction == RIGHT, carIBH->direction == LEFT, carIBH->animateAparition);
	if (carIAV)
		mainController->createAcar(carIAV->direction == LEFT, carIAV->direction == RIGHT, carIAV->animateAparition);
	if (carIBV)
		mainController->createCcar(carIBV->direction == RIGHT, carIBV->direction == LEFT, carIBV->animateAparition);
	
	if (carOAH)
		mainController->createBOcar(carOAH->direction == RIGHT, carOAH->direction == LEFT);
	if (carOBH)
		mainController->createDOcar(carOBH->direction == LEFT, carOBH->direction == RIGHT);
	if (carOAV)
		mainController->createAOcar(carOAV->direction == RIGHT, carOAV->direction == LEFT);
	if (carOBV)
		mainController->createCOcar(carOBV->direction == LEFT, carOBV->direction == RIGHT);
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
		RegisterHotKey(hWnd, INCREASE_SPAWN_VELOCITY, MOD_CONTROL, 0x51);

		RegisterHotKey(hWnd, DECREASE_SPAWN_VELOCITY, MOD_CONTROL, 0x41);
		
		break;
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
			delta = counter*1.0 / FPS_PER_TRANSACTION;
			if(delta > 0.5)
			{

				mainController->setPHA(core.horizontalRoad.crossingA);
				mainController->setPHB(core.horizontalRoad.crossingB);
				mainController->setPVA(core.verticalRoad.crossingA);
				mainController->setPVB(core.verticalRoad.crossingB);
			}
			if (counter > FPS_PER_TRANSACTION)
			{
				mainController->setPHA(false);
				mainController->setPHB(false);
				mainController->setPVA(false);
				mainController->setPVB(false);
				core.nextStep();
				std::list<Car*>::iterator HOA = core.horizontalRoad._outputA.begin();
				HOA++;
				std::list<Car*>::iterator HOB = core.horizontalRoad._outputB.begin();
				HOB++;
				std::list<Car*>::iterator VOA = core.verticalRoad._outputA.begin();
				VOA++;
				std::list<Car*>::iterator VOB = core.verticalRoad._outputB.begin();
				VOB++;
				onNewCycle(
					*(core.horizontalRoad._inputA.begin()),
					*(HOA),
					*(core.horizontalRoad._inputB.begin()),
					*(HOB),
					*(core.verticalRoad._inputA.begin()),
					*(VOA),
					*(core.verticalRoad._inputB.begin()),
					*(VOB)
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
