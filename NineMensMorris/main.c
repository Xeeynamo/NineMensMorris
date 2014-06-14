//////////////////////////////////////////////////////////////////////////
// main.c
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
#include "resource.h"

#define WND_NAME_CLASS "ClasseGioco"
#define WND_NAME_TITLE "Nine Men's Morris"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hWnd;
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = WND_NAME_CLASS;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, "Impossibile registrare la finestra.", "Errore", MB_ICONERROR);
		return -1;
	}
	hWnd = CreateWindow(
		WND_NAME_CLASS,				// Nome classe
		WND_NAME_TITLE,				// Nome della finestra
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,	// Posizione
		634, 474,						// Dimensione
		NULL,							// Finestra padre
		NULL,							// Menu
		hInstance,						// Istanza
		NULL);
	
	if (!hWnd)
	{
		MessageBox(NULL, "Impossibile creare la finestra.", "Errore", MB_ICONERROR);
		return -2;
	};
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int) msg.wParam;
}