//////////////////////////////////////////////////////////////////////////
// Gameboard.c
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

#include "GameBoard.h"
#include <stdlib.h>
#include <string.h>

MSGERROR CreateBoard(GameBoard *board, int size)
{
	MSGERROR err;
	ERRCALL(SetBoardSize(board, size));
	ERRCALL(GetBoardSize(board, &size));
	board->board = (SquareBoard*)malloc(size * sizeof(SquareBoard));
	memset(board->board, 0xFF, size * sizeof(SquareBoard));
	board->curPlayerID = 0;
	board->totalRounds = 0;
	board->playerList = NULL;
	return ERROR_OK;
}
MSGERROR DestroyBoard(GameBoard *board)
{
	MSGERROR err;
	ERRCALL(SetBoardSize(board, 0));
	free(board->board);
	return ERROR_OK;
}
MSGERROR GetBoardSize(GameBoard *board, int *size)
{
	if (!board) return ERROR_NULLPOINTER;
	if (board->boardSize == 0) return ERROR_INVALIDSIZE;
	*size = board->boardSize;
	return ERROR_OK;
}
MSGERROR SetBoardSize(GameBoard *board, int size)
{
	if (!board) return ERROR_NULLPOINTER;
	if (size < 0) return ERROR_INVALIDSIZE;
	board->boardSize = size;
	return ERROR_OK;
}

MSGERROR GetBoardSquare(GameBoard *board, int index, SquareBoard **boardsquare)
{
	if (!board) return ERROR_NULLPOINTER;
	if (!boardsquare) return ERROR_NULLPOINTER;
	if (index >= board->boardSize || index < 0) return ERROR_INVALIDINDEX;
	*boardsquare = &board->board[index];
	return ERROR_OK;
}
MSGERROR GetCurrentPlayerID(GameBoard *board, int *id)
{
	if (!board) return ERROR_NULLPOINTER;
	if (!id) return ERROR_NULLPOINTER;
	*id = board->curPlayerID;
	return ERROR_OK;
}
MSGERROR GetChecker(GameBoard *board, int index, int position, int *checkerdata)
{
	MSGERROR err;
	SquareBoard *squareBoard;
	if (!checkerdata) return ERROR_NULLPOINTER;
	ERRCALL(GetBoardSquare(board, index, &squareBoard));
	*checkerdata = (*squareBoard)[position];
	return ERROR_OK;
}
MSGERROR SetChecker(GameBoard *board, int index, int position, int player)
{
	MSGERROR err;
	SquareBoard *squareBoard;
	if (position >= 8) return ERROR_INVALIDINDEX;
	ERRCALL(GetBoardSquare(board, index, &squareBoard));
	(*squareBoard)[position] = player;
	return ERROR_OK;
}
MSGERROR PutChecker(GameBoard *board, int index, int position, int playerID, CheckerState *state)
{
	MSGERROR err;
	PlayerList *plist;
	Player *player;
	int data;
	if (!state) return ERROR_NULLPOINTER;
	ERRCALL(GetChecker(board, index, position, &data));
	if (data != CHECKER_EMPTY)
	{
		*state = CHECKERSTATE_ALREADYUSED;
		return ERROR_OK;
	}
	ERRCALL(GetPlayerList(board, &plist));
	ERRCALL(GetPlayer(plist, playerID, &player));
	if (player->tableCheckersCount > 0)
	{
		player->tableCheckersCount--;
		player->boardCheckersCount++;
	}
	ERRCALL(SetChecker(board, index, position, playerID));
	*state = CHECKERSTATE_SUCCESS;
	ERRCALL(CheckCheckerTris(board, index, position, state));
	return ERROR_OK;
}
MSGERROR MoveChecker(GameBoard *board, int index, int position, int playerID, GameBoardAround move, CheckerState *state)
{
	MSGERROR err;
	PlayerList *plist;
	Player *player;
	int around[4];
	ERRCALL(CheckerAround(board, index, position, around));
	if (around[move] == CHECKER_EMPTY)
	{
		int fakeplayer = CHECKER_EMPTY;
		*state = CHECKERSTATE_SUCCESS;
		ERRCALL(DeleteChecker(board, index, position, &fakeplayer, state));
		if (*state != CHECKERSTATE_SUCCESS) return ERROR_OK;
		ERRCALL(GetPlayerList(board, &plist));
		ERRCALL(GetPlayer(plist, playerID, &player));
		player->boardCheckersCount++;
		switch(move)
		{
		case AROUNDPOS_UP:
			switch(position)
			{
			case BOARDPOS_BOTTOMLEFT:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_CENTERLEFT, playerID));
				break;
			case BOARDPOS_BOTTOMRIGHT:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_CENTERRIGHT, playerID));
				break;
			case BOARDPOS_CENTERLEFT:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_TOPLEFT, playerID));
				break;
			case BOARDPOS_CENTERRIGHT:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_TOPRIGHT, playerID));
				break;
			case BOARDPOS_TOPCENTER:
				ERRCALL(SetChecker(board, --index, position = BOARDPOS_TOPCENTER, playerID));
				break;
			case BOARDPOS_BOTTOMCENTER:
				ERRCALL(SetChecker(board,++ index, position = BOARDPOS_BOTTOMCENTER, playerID));
				break;
			}
			break;
		case AROUNDPOS_DOWN:
			switch(position)
			{
			case BOARDPOS_TOPLEFT:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_CENTERLEFT, playerID));
				break;
			case BOARDPOS_TOPRIGHT:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_CENTERRIGHT, playerID));
				break;
			case BOARDPOS_CENTERLEFT:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_BOTTOMLEFT, playerID));
				break;
			case BOARDPOS_CENTERRIGHT:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_BOTTOMRIGHT, playerID));
				break;
			case BOARDPOS_TOPCENTER:
				ERRCALL(SetChecker(board, ++index, position = BOARDPOS_TOPCENTER, playerID));
				break;
			case BOARDPOS_BOTTOMCENTER:
				ERRCALL(SetChecker(board, --index, position = BOARDPOS_BOTTOMCENTER, playerID));
				break;
			}
			break;
		case AROUNDPOS_LEFT:
			switch(position)
			{
			case BOARDPOS_TOPRIGHT:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_TOPCENTER, playerID));
				break;
			case BOARDPOS_TOPCENTER:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_TOPLEFT, playerID));
				break;
			case BOARDPOS_BOTTOMRIGHT:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_BOTTOMCENTER, playerID));
				break;
			case BOARDPOS_BOTTOMCENTER:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_BOTTOMLEFT, playerID));
				break;
			case BOARDPOS_CENTERLEFT:
				ERRCALL(SetChecker(board, --index, position = BOARDPOS_CENTERLEFT, playerID));
				break;
			case BOARDPOS_CENTERRIGHT:
				ERRCALL(SetChecker(board, ++index, position = BOARDPOS_CENTERRIGHT, playerID));
				break;
			}
			break;
		case AROUNDPOS_RIGHT:
			switch(position)
			{
			case BOARDPOS_TOPLEFT:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_TOPCENTER, playerID));
				break;
			case BOARDPOS_TOPCENTER:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_TOPRIGHT, playerID));
				break;
			case BOARDPOS_BOTTOMLEFT:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_BOTTOMCENTER, playerID));
				break;
			case BOARDPOS_BOTTOMCENTER:
				ERRCALL(SetChecker(board, index, position = BOARDPOS_BOTTOMRIGHT, playerID));
				break;
			case BOARDPOS_CENTERLEFT:
				ERRCALL(SetChecker(board, ++index, position = BOARDPOS_CENTERLEFT, playerID));
				break;
			case BOARDPOS_CENTERRIGHT:
				ERRCALL(SetChecker(board, --index, position = BOARDPOS_CENTERRIGHT, playerID));
				break;
			}
			break;
		}
		ERRCALL(CheckCheckerTris(board, index, position, state));
	}
	else
	{
		*state = CHECKERSTATE_NOMOVE;
	}
	return ERROR_OK;
}
MSGERROR DeleteChecker(GameBoard *board, int index, int position, int *playerID, CheckerState *state)
{
	MSGERROR err;
	int checker;
	PlayerList *plist;
	Player *player;
	if (!state) return ERROR_NULLPOINTER;
	ERRCALL(GetChecker(board, index, position, &checker));
	if (checker != CHECKER_EMPTY)
	{
		if (checker == *playerID)
		{
			*state = CHECKERTATE_SELF;
			return ERROR_OK;
		}
		ERRCALL(GetPlayerList(board, &plist));
		switch(err = GetPlayer(plist, checker, &player))
		{
		case ERROR_OK:
			player->boardCheckersCount--;
			break;
		case ERROR_PLAYERIDNOTFOUND:
			checker = *playerID;
			break;
		default:
			ERRCALL(err);
		}
		*playerID = checker;
		ERRCALL(SetChecker(board, index, position, CHECKER_EMPTY));
		*state = CHECKERSTATE_SUCCESS;
		return ERROR_OK;
	}
	*state = CHECKERSTSTE_EMPTY;
	return ERROR_OK;
}
MSGERROR CheckerAround(GameBoard *board, int index, int position, int *around)
{
	MSGERROR err;
	int boardSize;
	if (!around) return ERROR_NULLPOINTER;
	if (position >= 8) return ERROR_INVALIDINDEX;
	ERRCALL(GetBoardSize(board, &boardSize));
	if (index >= boardSize) ERROR_INVALIDINDEX;
	
	switch(position)
	{
	case BOARDPOS_TOPLEFT:
		around[AROUNDPOS_UP] = CHECKER_INVALID;
		ERRCALL(GetChecker(board, index, BOARDPOS_CENTERLEFT, &around[AROUNDPOS_DOWN]));
		around[AROUNDPOS_LEFT] = CHECKER_INVALID;
		ERRCALL(GetChecker(board, index, BOARDPOS_TOPCENTER, &around[AROUNDPOS_RIGHT]));
		break;
	case BOARDPOS_TOPRIGHT:
		around[AROUNDPOS_UP] = CHECKER_INVALID;
		ERRCALL(GetChecker(board, index, BOARDPOS_CENTERRIGHT, &around[AROUNDPOS_DOWN]));
		ERRCALL(GetChecker(board, index, BOARDPOS_TOPCENTER, &around[AROUNDPOS_LEFT]));
		around[AROUNDPOS_RIGHT] = CHECKER_INVALID;
		break;
	case BOARDPOS_CENTERLEFT:
		ERRCALL(GetChecker(board, index, BOARDPOS_TOPLEFT, &around[AROUNDPOS_UP]));
		ERRCALL(GetChecker(board, index, BOARDPOS_BOTTOMLEFT, &around[AROUNDPOS_DOWN]));
		if (index == 0) around[AROUNDPOS_LEFT] = CHECKER_INVALID;
		else ERRCALL(GetChecker(board, index-1, BOARDPOS_CENTERLEFT, &around[AROUNDPOS_LEFT]));
		if (index + 1 == boardSize) around[AROUNDPOS_RIGHT] = CHECKER_INVALID;
		else ERRCALL(GetChecker(board, index+1, BOARDPOS_CENTERLEFT, &around[AROUNDPOS_RIGHT]));
		break;
	case BOARDPOS_CENTERRIGHT:
		ERRCALL(GetChecker(board, index, BOARDPOS_TOPRIGHT, &around[AROUNDPOS_UP]));
		ERRCALL(GetChecker(board, index, BOARDPOS_BOTTOMRIGHT, &around[AROUNDPOS_DOWN]));
		if (index + 1 == boardSize) around[AROUNDPOS_LEFT] = CHECKER_INVALID;
		else ERRCALL(GetChecker(board, index+1, BOARDPOS_CENTERRIGHT, &around[AROUNDPOS_LEFT]));
		if (index == 0) around[AROUNDPOS_RIGHT] = CHECKER_INVALID;
		else ERRCALL(GetChecker(board, index-1, BOARDPOS_CENTERRIGHT, &around[AROUNDPOS_RIGHT]));
		break;
	case BOARDPOS_BOTTOMLEFT:
		ERRCALL(GetChecker(board, index, BOARDPOS_CENTERLEFT, &around[AROUNDPOS_UP]));
		around[AROUNDPOS_DOWN] = CHECKER_INVALID;
		around[AROUNDPOS_LEFT] = CHECKER_INVALID;
		ERRCALL(GetChecker(board, index, BOARDPOS_BOTTOMCENTER, &around[AROUNDPOS_RIGHT]));
		break;
	case BOARDPOS_BOTTOMRIGHT:
		ERRCALL(GetChecker(board, index, BOARDPOS_CENTERRIGHT, &around[AROUNDPOS_UP]));
		around[AROUNDPOS_DOWN] = CHECKER_INVALID;
		ERRCALL(GetChecker(board, index, BOARDPOS_BOTTOMCENTER, &around[AROUNDPOS_LEFT]));
		around[AROUNDPOS_RIGHT] = CHECKER_INVALID;
		break;
	case BOARDPOS_TOPCENTER:
		if (index == 0) around[AROUNDPOS_UP] = CHECKER_INVALID;
		else ERRCALL(GetChecker(board, index-1, BOARDPOS_TOPCENTER, &around[AROUNDPOS_UP]));
		if (index + 1 == boardSize) around[AROUNDPOS_DOWN] = CHECKER_INVALID;
		else ERRCALL(GetChecker(board, index+1, BOARDPOS_TOPCENTER, &around[AROUNDPOS_DOWN]));
		ERRCALL(GetChecker(board, index, BOARDPOS_TOPLEFT, &around[AROUNDPOS_LEFT]));
		ERRCALL(GetChecker(board, index, BOARDPOS_TOPRIGHT, &around[AROUNDPOS_RIGHT]));
		break;
	case BOARDPOS_BOTTOMCENTER:
		if (index + 1 == boardSize) around[AROUNDPOS_UP] = CHECKER_INVALID;
		else ERRCALL(GetChecker(board, index+1, BOARDPOS_BOTTOMCENTER, &around[AROUNDPOS_UP]));
		if (index == 0) around[AROUNDPOS_DOWN] = CHECKER_INVALID;
		else ERRCALL(GetChecker(board, index-1, BOARDPOS_BOTTOMCENTER, &around[AROUNDPOS_DOWN]));
		ERRCALL(GetChecker(board, index, BOARDPOS_BOTTOMLEFT, &around[AROUNDPOS_LEFT]));
		ERRCALL(GetChecker(board, index, BOARDPOS_BOTTOMRIGHT, &around[AROUNDPOS_RIGHT]));
		break;
	}
	return ERROR_OK;
}
MSGERROR CheckCheckerTris(GameBoard *board, int index, int position, CheckerState *state)
{
	MSGERROR err;
	int checkerToCheck;
	int around[4];
	if (!state) return ERROR_NULLPOINTER;
	ERRCALL(GetChecker(board, index, position, &checkerToCheck));
	if (checkerToCheck == CHECKER_EMPTY)
	{
		*state = CHECKERSTSTE_EMPTY;
		return ERROR_OK;
	}
	switch(position)
	{
	case BOARDPOS_TOPLEFT:
		GetChecker(board, index, BOARDPOS_TOPCENTER, &around[0]);
		GetChecker(board, index, BOARDPOS_TOPRIGHT, &around[1]);
		GetChecker(board, index, BOARDPOS_CENTERLEFT, &around[2]);
		GetChecker(board, index, BOARDPOS_BOTTOMLEFT, &around[3]);
		break;
	case BOARDPOS_TOPRIGHT:
		GetChecker(board, index, BOARDPOS_TOPLEFT, &around[0]);
		GetChecker(board, index, BOARDPOS_TOPCENTER, &around[1]);
		GetChecker(board, index, BOARDPOS_CENTERRIGHT, &around[2]);
		GetChecker(board, index, BOARDPOS_BOTTOMRIGHT, &around[3]);
		break;
	case BOARDPOS_BOTTOMLEFT:
		GetChecker(board, index, BOARDPOS_TOPLEFT, &around[0]);
		GetChecker(board, index, BOARDPOS_CENTERLEFT, &around[1]);
		GetChecker(board, index, BOARDPOS_BOTTOMCENTER, &around[2]);
		GetChecker(board, index, BOARDPOS_BOTTOMRIGHT, &around[3]);
		break;
	case BOARDPOS_BOTTOMRIGHT:
		GetChecker(board, index, BOARDPOS_TOPRIGHT, &around[0]);
		GetChecker(board, index, BOARDPOS_CENTERRIGHT, &around[1]);
		GetChecker(board, index, BOARDPOS_BOTTOMLEFT, &around[2]);
		GetChecker(board, index, BOARDPOS_BOTTOMCENTER, &around[3]);
		break;
	case BOARDPOS_TOPCENTER:
		ERRCALL(CheckerAround(board, index, position, around));
		if (around[AROUNDPOS_UP] == CHECKER_INVALID) GetChecker(board, index+2, position, &around[AROUNDPOS_UP]);
 		if (around[AROUNDPOS_DOWN] == CHECKER_INVALID) GetChecker(board, index-2, position, &around[AROUNDPOS_DOWN]);
		break;
	case BOARDPOS_CENTERLEFT:
		ERRCALL(CheckerAround(board, index, position, around));
		if (around[AROUNDPOS_LEFT] == CHECKER_INVALID) GetChecker(board, index+2, position, &around[AROUNDPOS_LEFT]);
 		if (around[AROUNDPOS_RIGHT] == CHECKER_INVALID) GetChecker(board, index-2, position, &around[AROUNDPOS_RIGHT]);
		break;
	case BOARDPOS_CENTERRIGHT:
		ERRCALL(CheckerAround(board, index, position, around));
		if (around[AROUNDPOS_LEFT] == CHECKER_INVALID) GetChecker(board, index-2, position, &around[AROUNDPOS_LEFT]);
 		if (around[AROUNDPOS_RIGHT] == CHECKER_INVALID) GetChecker(board, index+2, position, &around[AROUNDPOS_RIGHT]);
		break;
	case BOARDPOS_BOTTOMCENTER:
		ERRCALL(CheckerAround(board, index, position, around));
		if (around[AROUNDPOS_UP] == CHECKER_INVALID) GetChecker(board, index-2, position, &around[AROUNDPOS_UP]);
 		if (around[AROUNDPOS_DOWN] == CHECKER_INVALID) GetChecker(board, index+2, position, &around[AROUNDPOS_DOWN]);
		break;
	}
	if (around[AROUNDPOS_UP] == checkerToCheck && around[AROUNDPOS_DOWN] == checkerToCheck ||
		around[AROUNDPOS_LEFT] == checkerToCheck && around[AROUNDPOS_RIGHT] == checkerToCheck)
	{
		*state = CHECKERSTATE_TRIS;
	}
	else
	{
		*state = CHECKERSTATE_SUCCESS;
	}
	return ERROR_OK;
}
MSGERROR GetCheckerCount(GameBoard *board, int playerID, int *count)
{
	MSGERROR err;
	Player *player;
	PlayerList *plist;
	ERRCALL(GetPlayerList(board, &plist));
	ERRCALL(GetPlayer(plist, playerID, &player));
	*count = player->boardCheckersCount + player->tableCheckersCount;
	return ERROR_OK;
}
MSGERROR GetPlayerList(GameBoard *board, PlayerList **plist)
{
	if (!board) return ERROR_NULLPOINTER;
	if (!plist) return ERROR_NULLPOINTER;
	*plist = board->playerList;
	return ERROR_OK;
}
MSGERROR SetPlayerList(GameBoard *board, PlayerList *plist)
{
	if (!board) return ERROR_NULLPOINTER;
	if (!plist) return ERROR_NULLPOINTER;
	board->playerList = plist;
	return ERROR_OK;
}
MSGERROR GetPlayerCount(GameBoard *board, int *count)
{
	MSGERROR err;
	PlayerList *plist;
	if (!count) return ERROR_NULLPOINTER;
	ERRCALL(GetPlayerList(board, &plist));
	(*count) = 0;
	while(plist)
	{
		(*count)++;
		plist = plist->next;
	}
	return ERROR_OK;
}
MSGERROR GetRoundCount(GameBoard *board, int *rounds)
{
	if (!board) return ERROR_NULLPOINTER;
	if (!rounds) return ERROR_NULLPOINTER;
	*rounds = board->totalRounds;
	return ERROR_OK;
}
MSGERROR NextRound(GameBoard *board)
{
	MSGERROR err;
	int i;
	int countPlayer;
	PlayerList *plist;
	Player *player;

	board->totalRounds++;
	ERRCALL(GetPlayerList(board, &plist));
	ERRCALL(GetCurrentPlayerID(board, &i));
	ERRCALL(GetPlayer(plist, i, &player));
	ERRCALL(GetPlayerCount(board, &countPlayer));
	player->moves++;
	for(i=0; i<countPlayer; i++)
	{
		switch(err = GetPlayer(plist, ++board->curPlayerID, &player))
		{
		case ERROR_OK:
			if (player->alive)
				return ERROR_OK;
			continue;
		case ERROR_PLAYERIDNOTFOUND:
			if (board->curPlayerID >= countPlayer)
				board->curPlayerID = -1;
			break;
		default:
			ERRCALL(err);
		}
	}
	return ERROR_OK;
}
MSGERROR CheckVictory(GameBoard *board, CheckerState *state)
{
	MSGERROR err;
	int playersAlive;
	int playersCount;
	PlayerList *plist;
	Player *player;
	ERRCALL(GetPlayerCount(board, &playersCount));
	ERRCALL(GetPlayerList(board, &plist));
	playersCount--;
	for(playersAlive = 0; playersCount>=0; playersCount--)
	{
		ERRCALL(GetPlayer(plist, playersCount, &player));
		if (player->alive) playersAlive++;
	}
	*state = playersAlive > 1 ? CHECKERSTATE_SUCCESS : CHECKERSTATE_VICTORY;
	return ERROR_OK;
}
MSGERROR CheckFreeze(GameBoard *board, CheckerState *state)
{
	MSGERROR err;
	int i, j, k;
	int szBoard;
	int around[4];
	int playerID;
	int checker;
	PlayerList *plist;
	Player *player;
	SquareBoard *square;

	*state = CHECKERSTATE_SUCCESS;
	ERRCALL(GetCurrentPlayerID(board, &playerID));
	ERRCALL(GetPlayerList(board, &plist));
	ERRCALL(GetPlayer(plist, playerID, &player));
	if (player->boardCheckersCount == 0) return ERROR_OK;
	if (player->tableCheckersCount > 0) return ERROR_OK;
	ERRCALL(GetBoardSize(board, &szBoard));
	for(i=0; i<szBoard; i++)
	{
		ERRCALL(GetBoardSquare(board, i, &square));
		for(j=0; j<8; j++)
		{
			ERRCALL(GetChecker(board, i, j, &checker));
			if (checker != playerID) continue;
			ERRCALL(CheckerAround(board, i, j, around));
			for(k=0; k<4; k++)
			{
				if (around[k] == CHECKER_EMPTY)
				{
					return ERROR_OK;
				}
			}
		}
	}
	*state = CHECKERSTATE_DEADLOCK;
	return ERROR_OK;
}