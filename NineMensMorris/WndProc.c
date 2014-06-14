//////////////////////////////////////////////////////////////////////////
// WndProc.c
// Part of http://github.com/Xeeynamo/NineMensMorris
// Copyright(C) 2014  Luciano Ciccariello (Xeeynamo)
// This file was committed to Università degli Studi Aldo Moro, Dipartimento
// di Informatica, course Linguaggi di Programmazione, teacher Fabio
// Abbattista as examination project.
// 
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or(at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110 - 1301, USA.

#include "NineMensMorris.h"
#include "Game.h"

Game game;

// Grafica schermata principale
HDC dcDefaultBackground;
HFONT defaultFont;
// Grafica tabellone
HPEN penClassifica;

// File
FILE *fTopten;
FILE *fSettings;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HDC dcBackBuffer;
	HBITMAP hBackBmp;
	switch (message)
	{
	case WM_MOUSEMOVE:
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		MouseHandler(&game, wParam, LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
		break;
	case WM_CHAR:
		break;
	case WM_KEYDOWN:
		switch(InputHandler(&game, wParam))
		{
		case INPUTHANDLER_LOAD:
			SetGameState(&game, GAME_NEWGAME);
			SaveSelectSlot(game.loadMenuSelectedSlot, game.fsave);
			LoadGame(&game.board, game.fsave);
			break;
		case INPUTHANDLER_DELETE:
			if (MessageBox(hWnd, GetGameText(GetGameState(&game), 2), GetGameText(GetGameState(&game), 3), MB_YESNO) == IDYES)
			{
				SaveSelectSlot(game.loadMenuSelectedSlot, game.fsave);
				DeleteSaveGame(game.fsave);
			}
			break;
		case INPUTHANDLER_SAVE:
			if (MessageBox(hWnd, GetGameText(GetGameState(&game), 2), GetGameText(GetGameState(&game), 3), MB_YESNO) == IDYES)
			{
				SaveSelectSlot(LASTSAVESLOT, game.fsave);
				SaveGame(&game.board, game.fsave);
			}
		case INPUTHANDLER_BACK:
			SetGameState(&game, GAME_MAINMENU);
			break;
		case INPUTHANDLER_EXIT:
			if (MessageBox(hWnd, GetGameText(GAME_EXIT, 0), GetGameText(GAME_EXIT, 1), MB_YESNO) == IDNO)
				return 0;
		case INPUTHANDLER_ERROR:
			DestroyWindow(hWnd);
			break;
		}
	case WM_KEYUP:
		break;
	case WM_PAINT:
		{	
			hdc = BeginPaint(hWnd, &ps);
			dcBackBuffer = CreateCompatibleDC(hdc);
			hBackBmp = CreateCompatibleBitmap(hdc, ps.rcPaint.right, ps.rcPaint.bottom);
			SelectObject(dcBackBuffer, hBackBmp);
			DeleteObject(hBackBmp);
			FillRect(dcBackBuffer, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			SetBkMode(dcBackBuffer, TRANSPARENT);

			GraphicHandler(&game, dcBackBuffer, &ps.rcPaint);

			BitBlt(hdc, 0, 0, ps.rcPaint.right, ps.rcPaint.bottom, dcBackBuffer, 0, 0, SRCCOPY);
			DeleteDC(dcBackBuffer);
			EndPaint(hWnd, &ps);
			break;
		}
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, 0);
		break;
	case WM_SHOWWINDOW:
		SetTimer(hWnd, (UINT_PTR)NULL, 31, NULL);	// Imposta la frequenza di aggiornamento della finestra
		Initialize(&game);
		LoadGameResources(&game);
		game.hWnd = hWnd;

		// Caricamento delle impostazioni
		if (LoadSettingsFromFile(&game.settings, GetGameText(TEXT_FILES, 0), &fSettings) != ERROR_OK)
		{
			MessageBox(hWnd, "Impossibile caricare le impostazioni", GetGameText(TEXT_DEFAULT, 2), MB_ICONERROR);
			PostQuitMessage(0);
		}
		// Caricamento della classifica
		if (LoadTopTenFromFile(&game.topten, GetGameText(TEXT_FILES, 2), &fTopten) != ERROR_OK)
		{
			MessageBox(hWnd, "Impossibile caricare la topten", GetGameText(TEXT_DEFAULT, 2), MB_ICONERROR);
			PostQuitMessage(0);
		}

		// Caricamento della grafica da file esterni
		dcDefaultBackground = LoadPicture(DEFAULT_BACKGROUNDIMAGE);
		// Creazione della penna e del colore del tabellone
		penClassifica = CreatePen(PS_SOLID, BOARDGAME_BORDERWIDTH, TOPTEN_COLOR);
		break;
	case WM_DESTROY:
		// Salva
		SaveTopTen(&game.topten, fTopten);
		SaveSettings(&game.settings, fSettings);
		// Dealloca
		DeleteGameResources(&game);
		DeleteObject(penClassifica);
		// Esci
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		SendMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;

	}
	return 0;
}