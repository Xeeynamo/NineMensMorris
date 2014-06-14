//////////////////////////////////////////////////////////////////////////
// GameInput.c
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

#include "Game.h"

INPUTHANDLER_RESULT InputHandler(Game *game, unsigned int keyPressed)
{
	CheckerState state = CHECKERSTATE_NOMOVE;
	GameBoardAround move = AROUNDPOS_NULL;
	switch(GetGameState(game))
	{
	case GAME_MAINMENU:
		if (keyPressed == VK_UP || keyPressed == VK_DOWN)
		{
			game->mainCursorPosition += (keyPressed == VK_DOWN) ? 1 : -1;
			if(game->mainCursorPosition<1) game->mainCursorPosition=6;
			if(game->mainCursorPosition>6) game->mainCursorPosition=1;
		}
		else if(keyPressed==VK_RETURN)
		{	
			if (game->mainCursorPosition == 6)
				return INPUTHANDLER_EXIT;
			if (SetGameState(game, (GAME_STATE)game->mainCursorPosition) == ERROR_INVALID_CHECKRCOUNT)
			{
				MessageBox(game->hWnd, "Numero di giocatori massimo consentito raggiunto. Per favore diminuire il numero di giocatori o aumentare la dimensione del campo.", "Attenzione", MB_ICONWARNING);
				SetGameState(game, GAME_MAINMENU);
			}
			return INPUTHANDLER_SELECT;
		}
		break;
	case GAME_NEWGAME:
		if (game->isCheckerSelected == 1)
		{
			if (keyPressed == VK_UP) move = AROUNDPOS_UP;
			else if (keyPressed == VK_DOWN) move = AROUNDPOS_DOWN;
			else if (keyPressed == VK_LEFT) move = AROUNDPOS_LEFT;
			else if (keyPressed == VK_RIGHT) move = AROUNDPOS_RIGHT;
			if (move != AROUNDPOS_NULL)
			{
				int playerID;
				state = CHECKERSTATE_SUCCESS;
				GetCurrentPlayerID(&game->board, &playerID);
				MoveChecker(&game->board, game->gameMoveCheckerIndex, game->gameMoveCheckerPosition, playerID, move, &state);
				switch(state)
				{
				case CHECKERSTATE_SUCCESS:
					NextRoundHandler(game);
					break;
				case CHECKERSTATE_TRIS:
					game->deleteState = 1;
					break;
				default:
					return INPUTHANDLER_NOTHING;
				}
				game->isCheckerSelected = 0;
			}
		}
		break;
	case GAME_LOADGAME:
		if (keyPressed == VK_UP || keyPressed == VK_DOWN)
		{
			int slotcount;
			if (GetSaveCount(&slotcount, game->fsave) == ERROR_OK)
			{
				game->loadMenuSelectedSlot += (keyPressed == VK_DOWN) ? 1 : -1;
					if(game->loadMenuSelectedSlot<0) game->loadMenuSelectedSlot=0;
				if(game->loadMenuSelectedSlot>=slotcount) game->loadMenuSelectedSlot=slotcount-1;
			}
		}
		else if (keyPressed == VK_DELETE || keyPressed == VK_BACK)
		{
			return INPUTHANDLER_DELETE;
		}
		else if (keyPressed == VK_RETURN)
		{
			return INPUTHANDLER_LOAD;
		}
		break;
	case GAME_SETTINGS:
		if (keyPressed == VK_UP || keyPressed == VK_DOWN)
		{
			game->settingsCursorPosition += (keyPressed == VK_DOWN) ? 1 : -1;
			if (game->settingsCursorPosition < 0) game->settingsCursorPosition = 3;
			if (game->settingsCursorPosition > 3) game->settingsCursorPosition = 0;
		}
		else if (keyPressed == VK_LEFT || keyPressed == VK_RIGHT)
		{
			switch(game->settingsCursorPosition)
			{
			case 0:
				game->settings.nPlayers += (keyPressed == VK_RIGHT) ? 1 : -1;
				if (game->settings.nPlayers < PLAYER_MINCOUNT) game->settings.nPlayers = 2;
				break;
			case 1:
				game->settings.szBoard += (keyPressed == VK_RIGHT) ? 1 : -1;
				if (game->settings.szBoard < BOARDGAME_MINSIZE) game->settings.szBoard = 3;
				else if (game->settings.szBoard > BOARDGAME_MAXSIZE) game->settings.szBoard = BOARDGAME_MAXSIZE;
				break;
			case 2:
				game->settings.bTimer ^= 1;
				break;
			case 3:
				game->settings.bTopten ^= 1;
				break;
			}
		}
		break;
	case GAME_INSTRUCTIONS:
		if (keyPressed == VK_UP || keyPressed == VK_DOWN)
		{
			game->instructionsScroll += (keyPressed == VK_DOWN) ? -10 : +10;
			if (game->instructionsScroll > 0)
				game->instructionsScroll = 0;
		}
		break;
	case GAME_GOERROR:
		return INPUTHANDLER_ERROR;
	}
	if (keyPressed == VK_ESCAPE)
	{
		switch(GetGameState(game))
		{
		case GAME_BEGIN:
			return INPUTHANDLER_NOTHING;
		case GAME_MAINMENU:
			return INPUTHANDLER_EXIT;
		case GAME_NEWGAME:
			return INPUTHANDLER_SAVE;
		}
		return INPUTHANDLER_BACK;
	}
	return INPUTHANDLER_NOTHING;
}