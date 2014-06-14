//////////////////////////////////////////////////////////////////////////
// Settings.c
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

#include "Settings.h"

void LoadSettings(Settings *settings, FILE *f)
{
	fseek(f, 0, SEEK_SET);
	fread(settings, 1, sizeof(Settings), f);
}
MSGERROR LoadSettingsFromFile(Settings *settings, char *filename, FILE **f)
{
	if (!f) return ERROR_NULLFILEPOINTER;
	if (!settings) return ERROR_NULLPOINTER;
	if (!filename) return ERROR_NULLPOINTER;
	*f = fopen(filename, "r+b");
	if (!*f)
	{
		DefaultSettings(settings);
		*f = fopen(filename, "w+b");
		if (!*f) return ERROR_FOPEN_FAIL;
	}
	else LoadSettings(settings, *f);
	return ERROR_OK;
}
void SaveSettings(Settings *settings, FILE *f)
{
	fseek(f, 0, SEEK_SET);
	fwrite(settings, 1, sizeof(Settings), f);
}
void DefaultSettings(Settings *settings)
{
	settings->nPlayers = 2;
	settings->szBoard = 3;
	settings->bTimer = 1;
	settings->bTopten = 1;
}
int Settings_GetPlayer(Settings *settings)
{
	return settings->nPlayers;
}
void Settings_SetPlayers(Settings *settings, int players)
{
	settings->nPlayers = players;
}
int Settings_GetBoardSize(Settings *settings)
{
	return settings->szBoard;
}
void Settings_SetBoardSize(Settings *settings, int size)
{
	settings->szBoard = size;
}
boolean Settings_GetTimer(Settings *settings)
{
	return settings->bTimer;
}
void Settings_SetTimer(Settings *settings, boolean enabled)
{
	settings->bTimer = enabled;
}