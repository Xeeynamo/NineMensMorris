//////////////////////////////////////////////////////////////////////////
// GameMouse.c
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

boolean CheckMouseCollision(int mousex, int mousey, int objx, int objy, int objw, int objh)
{
	if ((mousex >= objx) && (mousex < (objx+objw)) &&
		(mousey >= objy) && (mousey < (objy+objh)))
		return 1;
	return 0;
}

boolean MouseHandler(Game *game, unsigned int mousePressed, int x, int y)
{
	MSGERROR err;
	COORD coord;
	int i, j;
	int distance;
	int boardsize;
	int checker;
	CheckerState state; 
	int playerID;
	PlayerList *plist;
	Player *player;

	if (!game) return 0;
	switch(game->gamestate)
	{
	case GAME_NEWGAME:
		ERRCALL(GetPlayerList(&game->board, &plist));
		
		GetBoardSize(&game->board, &boardsize);
		distance = (BOARDGAME_MAXWIDTH-BOARDGAME_MINWIDTH)/boardsize/2;
		x += BOARDGAME_CHECKERSIZE/2;
		y += BOARDGAME_CHECKERSIZE/2;

		for(i=0; i<boardsize; i++)
		{
			for(j=0; j<8; j++)
			{
				GetCheckersBoardCoord(&coord, j, BOARDGAME_MAXWIDTH-i*distance*2);
				if (CheckMouseCollision(x, y, BOARDGAME_POSX+i*distance+coord.X, BOARDGAME_POSY+i*distance+coord.Y, 20, 20))
				{
					ERRCALL(GetCurrentPlayerID(&game->board, &playerID));
					ERRCALL(GetPlayerList(&game->board, &plist));
					ERRCALL(GetPlayer(plist, playerID, &player));
					if (game->deleteState == 1)
					{
						ERRCALL(DeleteChecker(&game->board, i, j, &playerID, &state));
						switch(state)
						{
						case CHECKERSTATE_SUCCESS:
							game->deleteState = 0;
							ERRCALL(GetCheckerCount(&game->board, playerID, &checker));
							if (checker < 3)
							{
								game->infomessage = 150;
								game->dieplayerevent = 0;
								game->diedplayer = playerID;
								ERRCALL(KickPlayer(plist, playerID));
								ERRCALL(CheckVictory(&game->board, &state));
								if (state == CHECKERSTATE_VICTORY)
								{
									MessageBox(game->hWnd, "Congratulazioni, hai vinto!", "Vittoria", MB_ICONINFORMATION);
									Victory(game);
									return 0;
								}
							}
							NextRoundHandler(game);
							break;
						}
					}
					else if (player->tableCheckersCount > 0) // Se il numero di pedine fuori il campo è maggiore di 0, allora le sposta nel campo da gioco
					{
						ERRCALL(PutChecker(&game->board, i, j, playerID, &state)); // Imposta una pedina
						switch(state)
						{
						case CHECKERSTATE_ALREADYUSED:
							break;
						case CHECKERSTATE_SUCCESS:
							NextRoundHandler(game);
							break;
						case CHECKERSTATE_TRIS:
							game->deleteState = 1;
							break;
						}
					}
					else // altrimenti muove le pedine già esistenti
					{
						ERRCALL(GetChecker(&game->board, i, j, &checker));
						if (checker != CHECKER_EMPTY) // E' stato selezionato un nodo già occupato
						{
							if (checker == playerID) // Controlla se la pedina selezionata in quel punto appartiene al giocatore che deve prendere la pedina
							{
								game->isCheckerSelected = 1; // Ora che la pedina è stata selezionata, ci si prepara per il movimento
								game->gameMoveCheckerIndex = i;		// Coordinate della pedina selezionata
								game->gameMoveCheckerPosition = j;	// Coordinate della pedina selezionata
							}
						}
					}
					return 1;
				}
			}
		}
		break;
	}
	return 0;
}