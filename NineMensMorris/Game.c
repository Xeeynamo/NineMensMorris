//////////////////////////////////////////////////////////////////////////
// Game.c
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

void Initialize(Game *game)
{
	FILE *f;
	int fsize;

	if (!game) return;
	game->isCheckerSelected = 0;
	game->deleteState = 0;
	SetGameState(game, GAME_BEGIN);
	OpenSaveFile(GetGameText(TEXT_FILES, 1), &game->fsave);

	f = fopen(GetGameText(TEXT_FILES, 3), "r+b");
	if (f)
	{
		fseek(f, 0, SEEK_END);
		fsize = ftell(f);
		rewind(f);
		game->strIstr = (char*)malloc(fsize+1);
		fread(game->strIstr, fsize, 1, f);
		game->strIstr[fsize] = 0;
		fclose(f);
	}
}
void LoadGameResources(Game *game)
{
	game->pictures.dcBkgDefault = LoadPicture(DEFAULT_BACKGROUNDIMAGE);
	game->pictures.dcBkgMainMenu = LoadPicture(MAINMENU_BACKGROUNDIMAGE);
	game->pictures.dcBkgGame = LoadPicture(NEWGAME_BACKGROUNDIMAGE);
	game->pictures.dcCheckers = LoadPicture(CHECKERS_GRAPHIC);
	game->pictures.dcMaskCheckers = LoadPicture(CHECKERS_MASK);
	game->pictures.dcCursor = LoadPicture(CURSORIMAGE);

	game->pictures.penBoard = CreatePen(PS_SOLID, BOARDGAME_BORDERWIDTH, BOARDGAME_COLOR);
	game->pictures.penLoadSelected = CreatePen(PS_SOLID, BOARDGAME_BORDERWIDTH, LOADGAME_SLOTCOLORSELECTED);
	game->pictures.penLoadUnselected = CreatePen(PS_SOLID, BOARDGAME_BORDERWIDTH, LOADGAME_SLOTCOLORUNSELECTED);
	game->pictures.brushNode = CreateSolidBrush(BOARDGAME_COLOR);
}
void DeleteGameResources(Game *game)
{
	if (game->strIstr) free(game->strIstr);
	game->strIstr = NULL;

	DeleteDC(game->pictures.dcBkgDefault);
	DeleteDC(game->pictures.dcBkgMainMenu);
	DeleteDC(game->pictures.dcBkgGame);
	DeleteDC(game->pictures.dcCheckers);
	DeleteDC(game->pictures.dcMaskCheckers);
	DeleteDC(game->pictures.dcCursor);

	DeleteObject(game->pictures.penBoard);
	DeleteObject(game->pictures.penLoadSelected);
	DeleteObject(game->pictures.penLoadUnselected);
	DeleteObject(game->pictures.brushNode);
}
GAME_STATE GetGameState(Game *game)
{
	return game->gamestate;
}
MSGERROR SetGameState(Game *game, GAME_STATE state)
{
	MSGERROR err;
	PlayerList *plist;
	if (GetGameState(game) == state) return ERROR_OK;

	if (GetGameState(game) == GAME_NEWGAME)
	{
		GetPlayerList(&game->board, &plist);
		DeletePlayerList(plist);
		DestroyBoard(&game->board);
	}

	switch(state)
	{
	case GAME_BEGIN:
		DefaultSettings(&game->settings);
		ResetTopTen(&game->topten);

		game->mainCursorPosition = 1;
		game->settingsCursorPosition = 0;
		game->menuTextX = MAINMENU_X_INIT;
		game->menuTextRotation = MAINMENU_ANGLE_INIT;
		game->cursorAnimIndex = 0;
		game->cursorAnimVerse = 1;
		break;
	case GAME_NEWGAME:
		ERRCALL(CreateBoard(&game->board, game->settings.szBoard));
		ERRCALL(GetPlayerList(&game->board, &plist));
		switch(err = CreatePlayerList(&plist, game->settings.nPlayers, GetPlayerCheckersCount(game->settings.szBoard, game->settings.nPlayers)))
		{
		case ERROR_OK:
			break;
		case ERROR_INVALID_CHECKRCOUNT:
			return ERROR_INVALID_CHECKRCOUNT;
		default:
			ERRCALL(err);
		}
		ERRCALL(SetPlayerList(&game->board, plist));
		game->deleteState = 0;
		game->startTimer = GetTickCount();
		break;
	case GAME_LOADGAME:
		game->loadMenuSelectedSlot = 0;
		break;
	}
	game->gamestate = state;
	return ERROR_OK;
}
char *GetSettingAsString(char *in, Settings *settings, int i)
{
	switch(i)
	{
	case 0:
		_itoa(settings->nPlayers, in, 10);
		break;
	case 1:
		_itoa(settings->szBoard, in, 10);
		break;
	case 2:
		strcpy(in, settings->bTimer ? GetGameText(TEXT_DEFAULT, 0) :GetGameText(TEXT_DEFAULT, 1));
		break;
	case 3:
		strcpy(in, settings->bTopten ? GetGameText(TEXT_DEFAULT, 0) : GetGameText(TEXT_DEFAULT, 1));
		break;
	}
	return in;
}
int GetPlayerCheckersCount(int szBoard, int nPlayers)
{
	int checkersCount;
	if (nPlayers > 0)
	{
		checkersCount = ((szBoard*8)-1)/nPlayers;
		if (checkersCount >= PLAYER_MINCHECKERS)
			return checkersCount;
	}
	return 0;
}

MSGERROR NextRoundHandler(Game *game)
{
	CheckerState state;
	MSGERROR err;
	ERRCALL(NextRound(&game->board));
	ERRCALL(CheckFreeze(&game->board, &state));
	if (state == CHECKERSTATE_DEADLOCK)
	{
		PlayerList *plist;
		int playerID;

		ERRCALL(GetCurrentPlayerID(&game->board, &playerID));
		ERRCALL(GetPlayerList(&game->board, &plist));
		ERRCALL(NextRoundHandler(game));
		ERRCALL(KickPlayer(plist, playerID));
		game->infomessage = 150;
		game->dieplayerevent = 1;
		game->diedplayer = playerID;
	}
	return ERROR_OK;
}
MSGERROR Victory(Game *game)
{
	MSGERROR err;
	if (game->settings.bTopten)
	{
		TopTen_Entry entry;
		PlayerList *plist;
		Player *player;
		int playerID;
		ERRCALL(GetCurrentPlayerID(&game->board, &playerID));
		ERRCALL(GetPlayerList(&game->board, &plist));
		ERRCALL(GetPlayer(plist, playerID, &player));

		sprintf(entry.name, "Giocatore%i", playerID+1);
		entry.moves = player->moves;
		entry.wins = 1;

		if (AddTopTenEntry(&game->topten, &entry))
		{
			ERRCALL(SetGameState(game, GAME_TOPTEN));
			return ERROR_OK;
		}
	}
	ERRCALL(SetGameState(game, GAME_MAINMENU));
	return ERROR_OK;
}