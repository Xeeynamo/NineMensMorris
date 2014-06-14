//////////////////////////////////////////////////////////////////////////
// NineMensMorris.h
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

#pragma once
#define _USE_32BIT_TIME_T
#include <windows.h>
#include <stdio.h>
#include "ProjectSettings.h"
#include "Graphics.h"

#include "TextSettings.h"
#include "Settings.h"
#include "TopTen.h"

// Stati del gioco
typedef enum
{
	GAME_MAINMENU		= 0,
	GAME_NEWGAME		= 1,
	GAME_LOADGAME		= 2,
	GAME_SETTINGS		= 3,
	GAME_TOPTEN			= 4,
	GAME_INSTRUCTIONS	= 5,
	GAME_EXIT			= 6,

	GAME_BEGIN			= 10,
	GAME_GOERROR		= -1
} GAME_STATE;

#define TEXT_DEFAULT 7
#define TEXT_FILES 8

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);