//////////////////////////////////////////////////////////////////////////
// Player.c
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

#include "Player.h"
#include <stdlib.h>

MSGERROR CreatePlayerList(PlayerList **plist, int count, int checkersCount)
{
	MSGERROR err;
	if (!plist) return ERROR_NULLPOINTER;
	if (checkersCount < MINIMUM_CHECKRS_COUNT) return ERROR_INVALID_CHECKRCOUNT;
	if (count < 1)
	{
		*plist = NULL;
		return ERROR_OK;
	}
	*plist = (PlayerList*)malloc(sizeof(PlayerList));
	(*plist)->player.id = count-1;
	(*plist)->player.tableCheckersCount = checkersCount;
	(*plist)->player.moves = (*plist)->player.boardCheckersCount = 0;
	(*plist)->player.alive = 1;
	ERRCALL(CreatePlayerList(&((*plist)->next), count-1, checkersCount));
	return ERROR_OK;
}
MSGERROR DeletePlayerList(PlayerList *plist)
{
	MSGERROR err;
	PlayerList *next;
	if (plist == NULL) return ERROR_OK;
	next = plist->next;
	free(plist);
	ERRCALL(DeletePlayerList(next));
	return ERROR_OK;
}
MSGERROR GetPlayer(PlayerList *plist, int id, Player **player)
{
	if (!player) return ERROR_NULLPOINTER;
	if (!plist)
	{
		*player = NULL;
		return ERROR_PLAYERIDNOTFOUND;
	}
	if (plist->player.id == id)
	{
		*player = &plist->player;
	}
	else
	{
		return GetPlayer(plist->next, id, player);
	}
	return ERROR_OK;
}
MSGERROR KickPlayer(PlayerList *plist, int id)
{
	MSGERROR err;
	if (!plist) return ERROR_PLAYERIDNOTFOUND;
	if (plist->player.id == id)
	{
		plist->player.alive = 0;
	}
	else
	{
		ERRCALL(KickPlayer(plist->next, id));
	}
	return ERROR_OK;
}