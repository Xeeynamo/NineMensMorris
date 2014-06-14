//////////////////////////////////////////////////////////////////////////
// GameGraphics.c
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

/*char strIstr [] = "Nine Men's Morris è un gioco di strategia per molteplici giocatori.\n"
	"Ad ogni giocatore verranno assegnate nove pedine che saranno inizialmente fuori il tavoliere di gioco.\n"
	"Il tavoliere è composto da tre quadrati base con grandezza decrescente, uno dentro l’altro, che saranno collegati da quattro linee che uniscono i tre quadrati; esse partiranno dalla metà della dimensione della linea più esterna sino alla metà della linea più interna formando una croce.\n"
	"Ogni nodo sarà uno spazio dove le varie pedine potranno essere posizionate. Ogni quadrato quindi avrà otto nodi vuoti, con un totale di 24 nodi.\n"
	"Una volta iniziato il gioco, i giocatori devono posizionare tutte le loro pedine sul tavolo da gioco una alla volta a turno su uno dei nodi non ancora occupati. Il giocatore avrà come obiettivo il tris, ovvero il posizionamento di tre pedine consecutive.\n"
	"Regole:\n"
	"1) Le mosse devono essere alternate tra i giocatori. Non è possibile fare più di una mossa per turno.\n"
	"2) Il giocatore non può piazzare una pedina sopra un’altra pedina già piazzata.\n"
	"3) Le pedine fuori dal campo potranno essere piazzate in qualsiasi locazione libera.\n"
	"4) Finché ci saranno pedine sul campo, non sarà possibile spostare le pedine già piazzate.\n"
	"5) Dopo aver posizionato tutte le pedine fuori il tavoliere, il giocatore potrà spostare una delle sue pedine su uno dei nodi vuoti che gli sono attorno.\n"
	"6) Le pedine possono essere posizionate obliquamente ma esse non valgono come punto; i tris valgono soltanto orizzontalmente e verticalmente.\n"
	"7) Se un giocatore compone un tris, gli verrà data la possibilità di eliminare una pedina avversaria a sua scelta nello stesso turno in cui ha piazzato la pedina.\n"
	"8) Se nel turno precedente è stato fatto un tris, lo stesso giocatore non potrà usare lo stesso tris per eliminare un’altra pedina avversaria.\n"
	"9) E’ possibile muovere una pedina appartenente ad un tris per poi riposizionarla nel punto precedente in un turno successivo per poter fare un altro tris.\n"
	"10) Il giocatore non può saltare un turno: sarà obbligato a muovere una pedina.\n"
	"11) Se non è disponibile nessun nodo vuoto attorno alla pedina che si vuole muovere, essa non potrà essere mossa.\n"
	"12) Se, secondo la regola 11 non è possibile muovere nessuna pedina, il giocatore ha perso.\n"
	"13) Se il giocatore rimuove la terz’ultima pedina dell’avversario, che quindi rimane con due pedine soltanto, esso vince.\n";*/

void DrawBoardCheckers(Game *game, HDC dc, int x, int y)
{
	COORD coord;
	int i, j;
	int distance;
	int size;
	int checkerdata;

	if (GetBoardSize(&game->board, &size) != ERROR_OK) return;
	distance = (BOARDGAME_MAXWIDTH-BOARDGAME_MINWIDTH)/size/2;
	x -= BOARDGAME_CHECKERSIZE/2;
	y -= BOARDGAME_CHECKERSIZE/2;
	for(i=0; i<size; i++)
	{
		for(j=0; j<8; j++)
		{
			GetChecker(&game->board, i, j, &checkerdata);
			if (checkerdata == CHECKER_EMPTY) continue;
			if (game->gameMoveCheckerIndex == i && game->gameMoveCheckerPosition == j)
			{
				if (game->isCheckerSelected == 1 && game->loadMenuEffect++%(LOADGAME_SLOTEFFECTLAG*2) < LOADGAME_SLOTEFFECTLAG)
					continue;
			}
			GetCheckersBoardCoord(&coord, j, BOARDGAME_MAXWIDTH-i*distance*2);
			DrawChecker(dc, x+i*distance + coord.X, y+i*distance + coord.Y, checkerdata, game->pictures.dcCheckers, game->pictures.dcMaskCheckers);
			
		}
	}
}

void GraphicHandler(Game *game, HDC dc, RECT *rcPaint)
{
	int i, j;
	char chbuf[0x100];
	RECT coordText;
	PlayerList *plist;
	Player *player;
	int szBoard;
	int timer;

	switch(game->gamestate)
	{
	case GAME_BEGIN:
		if (game->menuTextX < MAINMENU_X_END) // Transizione del menu
		{
			game->menuTextX += MAINMENU_X_SPEED;
		}
		if (game->menuTextRotation < MAINMENU_ANGLE_END) // Rotazione del menu
		{
			game->menuTextRotation += MAINMENU_ANGLE_SPEED;
		}
		else
		{
			game->gamestate = GAME_MAINMENU;
		}
	case GAME_MAINMENU:
		BitBlt(dc, 0, 0, rcPaint->right, rcPaint->bottom, 0, 0, 0, BLACKNESS);
		SetTextColor(dc, MAINMENU_TEXTCOLOR);
		BitBlt(dc, 0, 0, rcPaint->right, rcPaint->bottom, game->pictures.dcBkgMainMenu, 0, 0, SRCCOPY);
		SelectFont(dc, MAINMENU_TEXTWIDTH, game->menuTextRotation, 8, MAINMENU_FONTNAME);

		// Ciclo che stampa tutte le opzioni del menu
		for(i=0; i<MAINMENU_ELEMENTS; i++)
		{
			j = (i-2+(game->mainCursorPosition-1))%MAINMENU_ELEMENTS;
			if (j < 0) j += MAINMENU_ELEMENTS;
			PrintText(dc, game->menuTextX-(i-2)*MAINMENU_TEXTINCLINATION, MAINMENU_Y+(i-3)*MAINMENU_DISTANCE, GetGameText(GAME_MAINMENU, j));
		}
		SelectFont(dc, 18, 0, 8, MAINMENU_FONTNAME);
		PrintText(dc, 400, rcPaint->bottom - 40, "Developed by Luciano Ciccariello");
		break;
	case GAME_NEWGAME:
		BitBlt(dc, 0, 0, rcPaint->right, rcPaint->bottom, 0, 0, 0, BLACKNESS);
		if (GetBoardSize(&game->board, &szBoard) != ERROR_OK) return;
		BitBlt(dc, 0, 0, rcPaint->right, rcPaint->bottom, game->pictures.dcBkgGame, 0, 0, SRCCOPY);
		SelectObject(dc, game->pictures.penBoard);	// Seleziona il tipo di penna per il tabellone
		SelectObject(dc, game->pictures.brushNode);		// Seleziona il colore dei nodi
		DrawBoard(dc, BOARDGAME_POSX, BOARDGAME_POSY, szBoard);
		DrawBoardCheckers(game, dc, BOARDGAME_POSX, BOARDGAME_POSY);

		GetCurrentPlayerID(&game->board, &j);
		GetPlayerList(&game->board, &plist);
		if (GetPlayer(plist, j, &player) != ERROR_OK) return;
		for(i=0; i<player->tableCheckersCount; i++)
		{
			DrawChecker(dc, 5 + (i%3)*30, 10 + (i/3)*30, j, game->pictures.dcCheckers, game->pictures.dcMaskCheckers);
		}

		SetTextColor(dc, 0x00FFFFFF);
		SelectFont(dc, 18, 0, 10, MAINMENU_FONTNAME);

		GetCurrentPlayerID(&game->board, &j);
		sprintf(chbuf, "%s %i", GetGameText(GetGameState(game), 1), j+1);
		PrintText(dc, (rcPaint->right-BOARDGAME_MAXWIDTH)/2 + BOARDGAME_MAXWIDTH + 4, 25, chbuf);

		GetRoundCount(&game->board, &j);
		sprintf(chbuf, "%s %i", GetGameText(GetGameState(game), 0), j);
		PrintText(dc, (rcPaint->right-BOARDGAME_MAXWIDTH)/2 + BOARDGAME_MAXWIDTH + 4, 5, chbuf);

		if (game->settings.bTimer)
		{
			timer = GetTickCount() - game->startTimer;
			sprintf(chbuf, "%3i:%02i:%02i", (timer/60000), (timer/1000)%60, (timer/10)%100);
			PrintText(dc, (rcPaint->right-BOARDGAME_MAXWIDTH)/2 + BOARDGAME_MAXWIDTH + 4, 55, chbuf);
		}

		if (game->infomessage > 0)
		{
			game->infomessage--;
			sprintf(chbuf, "Giocatore %i: %s", game->diedplayer+1, GetGameText(GetGameState(game), 8 + game->dieplayerevent));
			PrintText(dc, 10, 418, chbuf);
		}
		else if (game->deleteState)
		{
			PrintText(dc, 10, 418, GetGameText(GetGameState(game), 7));
		}
		else if (player->tableCheckersCount > 0)
		{
			PrintText(dc, 10, 418, GetGameText(GetGameState(game), 4));
		}
		else
		{
			if (game->isCheckerSelected)
				PrintText(dc, 10, 418, GetGameText(GetGameState(game), 6));
			else
				PrintText(dc, 10, 418, GetGameText(GetGameState(game), 5));
		}
		break;
	case GAME_LOADGAME:
		BitBlt(dc, 0, 0, rcPaint->right, rcPaint->bottom, 0, 0, 0, WHITENESS);
		BitBlt(dc, 0, 0, rcPaint->right, rcPaint->bottom, game->pictures.dcBkgDefault, 0, 0, SRCCOPY);
		SelectFont(dc, MAINMENU_TEXTWIDTH, 0, 8, MAINMENU_FONTNAME);
		PrintText(dc, SETTINGS_TITLE_POSX, SETTINGS_TITLE_POSY, GetGameText(game->gamestate, 0));

		SelectFont(dc, 18, 0, 8, MAINMENU_FONTNAME);
		GetSaveCount(&game->loadMenuSlotCount, game->fsave);
		if (game->loadMenuSlotCount > 0)
		{
			SaveGamePreview savepreview;

			for(i=0; i<3 && (i+game->loadMenuSelectedSlot) < game->loadMenuSlotCount; i++)
			{
				SaveSelectSlot(game->loadMenuSelectedSlot+i, game->fsave);
				LoadGamePreview(&savepreview, game->fsave);

				if (i == 0)
				{
					game->loadMenuEffect++;
					if (game->loadMenuEffect < LOADGAME_SLOTEFFECTLAG)
						SelectObject(dc, game->pictures.penLoadSelected);
					else if (game->loadMenuEffect < LOADGAME_SLOTEFFECTLAG*2)
						SelectObject(dc, game->pictures.penLoadUnselected);
					else
					{
						game->loadMenuEffect = 0;
						SelectObject(dc, game->pictures.penLoadSelected);
					}
				}
				else SelectObject(dc, game->pictures.penLoadUnselected);
				DrawRectangle(dc, LOADGAME_CARDX, LOADGAME_CARDY + i*LOADGAME_CARDDISTANCE, LOADGAME_CARDWIDTH, LOADGAME_CARDHEIGHT);

				SelectFont(dc, 22, 0, 8, MAINMENU_FONTNAME);
				sprintf(chbuf, "%s %03i", "Slot di salvataggio #", game->loadMenuSelectedSlot+1+i);
				PrintText(dc, LOADGAME_CARDX+8, LOADGAME_CARDY + i*LOADGAME_CARDDISTANCE+8, chbuf);
				SelectFont(dc, 16, 0, 8, MAINMENU_FONTNAME);
				sprintf(chbuf, "%s %s", "Partita salvata il ", ctime(&savepreview.time));
				PrintText(dc, LOADGAME_CARDX+8, LOADGAME_CARDY + i*LOADGAME_CARDDISTANCE+32, chbuf);

				SelectFont(dc, 18, 0, 8, MAINMENU_FONTNAME);
				sprintf(chbuf, "%s %i", "Turno ", savepreview.totalRounds);
				PrintText(dc, LOADGAME_CARDX+8, LOADGAME_CARDY + i*LOADGAME_CARDDISTANCE+56, chbuf);
				sprintf(chbuf, "%s %i/%i", "Turno del giocatore ", savepreview.currentPlayerID+1, savepreview.playercount);
				PrintText(dc, LOADGAME_CARDX+8, LOADGAME_CARDY + i*LOADGAME_CARDDISTANCE+78, chbuf);
				sprintf(chbuf, "%s %i", "Dimensione del campo ", savepreview.boardsize);
				PrintText(dc, LOADGAME_CARDX+8, LOADGAME_CARDY + i*LOADGAME_CARDDISTANCE+98, chbuf);

			}
			SelectFont(dc, 18, 0, 10, MAINMENU_FONTNAME);
			PrintText(dc, 487, 400, "DEL per cancellare");
		}
		else
		{
			PrintText(dc, 40, 90, GetGameText(game->gamestate, 1));
		}
		break;
	case GAME_SETTINGS:
		BitBlt(dc, 0, 0, rcPaint->right, rcPaint->bottom, 0, 0, 0, WHITENESS);
		BitBlt(dc, 0, 0, rcPaint->right, rcPaint->bottom, game->pictures.dcBkgDefault, 0, 0, SRCCOPY);
		SelectFont(dc, MAINMENU_TEXTWIDTH, 0, 8, MAINMENU_FONTNAME);
		PrintText(dc, SETTINGS_TITLE_POSX, SETTINGS_TITLE_POSY, GetGameText(game->gamestate, 0));
		for(i=0; i<SETTINGS_ELEMENTS-1; i++)
		{
			SelectFont(dc, SETTINGS_TEXTSIZE, 0, 2, MAINMENU_FONTNAME);
			PrintText(dc, SETTINGS_POSX, SETTINGS_POSY + SETTINGS_DISTANCE*i, GetGameText(game->gamestate, i+1));
			SelectFont(dc, MAINMENU_TEXTWIDTH, 0, 9, MAINMENU_FONTNAME);
			if (game->cursorAnimVerse == 1 || game->settingsCursorPosition != i)
			{
				PrintText(dc, SETTINGS_POSX + SETTINGS_CONTATOR_POSX1, SETTINGS_POSY + SETTINGS_DISTANCE*i, "<");
				PrintText(dc, SETTINGS_POSX + SETTINGS_CONTATOR_POSX3, SETTINGS_POSY + SETTINGS_DISTANCE*i, ">");
			}

			SelectFont(dc, SETTINGS_TEXTSIZE, 0, 0, MAINMENU_FONTNAME);
			coordText.left = SETTINGS_POSX + SETTINGS_CONTATOR_POSX2;
			coordText.top = SETTINGS_POSY + SETTINGS_DISTANCE*i;
			coordText.right = SETTINGS_POSX + SETTINGS_CONTATOR_POSX3;
			coordText.bottom = coordText.top + SETTINGS_DISTANCE;
			DrawText(dc, GetSettingAsString(chbuf, &game->settings, i), -1, &coordText, DT_CENTER);
		}
		GdiTransparentBlt(dc, SETTINGS_POSX-32, SETTINGS_POSY + SETTINGS_DISTANCE*game->settingsCursorPosition+4, 20, 20, game->pictures.dcCursor, 0, (game->cursorAnimIndex/2)*20, 20, 20, 0xFF00FF);
		if ((game->cursorAnimIndex <= 0 && game->cursorAnimVerse == -1) || game->cursorAnimIndex >= 20) game->cursorAnimVerse *= -1;
		game->cursorAnimIndex += game->cursorAnimVerse;
		break;
	case GAME_TOPTEN:
		BitBlt(dc, 0, 0, rcPaint->right, rcPaint->bottom, 0, 0, 0, WHITENESS);
		BitBlt(dc, 0, 0, rcPaint->right, rcPaint->bottom, game->pictures.dcBkgDefault, 0, 0, SRCCOPY);
		SelectFont(dc, MAINMENU_TEXTWIDTH, 0, 8, MAINMENU_FONTNAME);
		PrintText(dc, SETTINGS_TITLE_POSX, SETTINGS_TITLE_POSY, GetGameText(game->gamestate, 0));

		SelectObject(dc, game->pictures.penLoadUnselected);
		DrawRectangle(dc, TOPTEN_POSX, TOPTEN_POSY, TOPTEN_TABLEWIDTH, TOPTEN_TABLEHEIGHT);
		DrawLine(dc, TOPTEN_POSX, TOPTEN_POSY+TOPTEN_TOPBAR_HEIGHT, TOPTEN_POSX+TOPTEN_TABLEWIDTH, TOPTEN_POSY+TOPTEN_TOPBAR_HEIGHT);

		SelectFont(dc, 18, 0, 2, MAINMENU_FONTNAME);
		// Stampa dei testi e delle linee che separano le sezioni
		coordText.left = TOPTEN_POSX;
		coordText.top = TOPTEN_POSY;
		coordText.right = coordText.left + TOPTEN_WIDTH_GRADE;
		coordText.bottom = coordText.top + TOPTEN_TOPBAR_HEIGHT;
		MoveToEx(dc, coordText.right, TOPTEN_POSY, NULL);
		LineTo(dc, coordText.right, TOPTEN_POSY + TOPTEN_TABLEHEIGHT);
		DrawText(dc, GetGameText(game->gamestate, 1), -1, &coordText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		coordText.left += TOPTEN_WIDTH_GRADE;
		coordText.right += TOPTEN_WIDTH_NAME;
		MoveToEx(dc, coordText.right, TOPTEN_POSY, NULL);
		LineTo(dc, coordText.right, TOPTEN_POSY + TOPTEN_TABLEHEIGHT);
		DrawText(dc, GetGameText(game->gamestate, 2), -1, &coordText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		coordText.left += TOPTEN_WIDTH_NAME;
		coordText.right += TOPTEN_WIDTH_VICTORIES;
		MoveToEx(dc, coordText.right, TOPTEN_POSY, NULL);
		LineTo(dc, coordText.right, TOPTEN_POSY + TOPTEN_TABLEHEIGHT);
		DrawText(dc, GetGameText(game->gamestate, 3), -1, &coordText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		
		coordText.left += TOPTEN_WIDTH_VICTORIES;
		coordText.right += TOPTEN_WIDTH_MOVES;
		MoveToEx(dc, coordText.right, TOPTEN_POSY, NULL);
		LineTo(dc, coordText.right, TOPTEN_POSY + TOPTEN_TABLEHEIGHT);
		DrawText(dc, GetGameText(game->gamestate, 5), -1, &coordText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		// Stampa delle linee che suddividono gli elementi della tabella
		for(i=0; i<TOPTEN_ENTRY_COUNT; i++)
		{
			MoveToEx(dc, TOPTEN_POSX, TOPTEN_POSY + TOPTEN_TOPBAR_HEIGHT + TOPTEN_ENTRY_HEIGHT*i, NULL);
			LineTo(dc, TOPTEN_POSX + TOPTEN_TABLEWIDTH, TOPTEN_POSY + TOPTEN_TOPBAR_HEIGHT + TOPTEN_ENTRY_HEIGHT*i);
		}

		for(i=0; i<TOPTEN_ENTRY_COUNT; i++)
		{
			TopTen_Entry *entry;
			entry = GetTopTenEntry(&game->topten, i);
			coordText.left = TOPTEN_POSX;
			coordText.top = TOPTEN_POSY + TOPTEN_TOPBAR_HEIGHT + (i*TOPTEN_ENTRY_HEIGHT);
			coordText.right = coordText.left + TOPTEN_WIDTH_GRADE;
			coordText.bottom = coordText.top + TOPTEN_ENTRY_HEIGHT;
			_itoa(i+1, chbuf, 10);
			DrawText(dc, chbuf, -1, &coordText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			coordText.left += TOPTEN_WIDTH_GRADE;
			coordText.right += TOPTEN_WIDTH_NAME;
			DrawText(dc, entry->name, -1, &coordText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			coordText.left += TOPTEN_WIDTH_NAME;
			coordText.right += TOPTEN_WIDTH_VICTORIES;
			_itoa(entry->wins, chbuf, 10);
			DrawText(dc, chbuf, -1, &coordText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			coordText.left += TOPTEN_WIDTH_VICTORIES;
			coordText.right += TOPTEN_WIDTH_MOVES;
			_itoa(entry->moves, chbuf, 10);
			DrawText(dc, chbuf, -1, &coordText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
		break;
	case GAME_INSTRUCTIONS:
		BitBlt(dc, 0, 0, rcPaint->right, rcPaint->bottom, 0, 0, 0, WHITENESS);
		BitBlt(dc, 0, 0, rcPaint->right, rcPaint->bottom, game->pictures.dcBkgDefault, 0, 0, SRCCOPY);
		SelectFont(dc, MAINMENU_TEXTWIDTH, 0, 8, MAINMENU_FONTNAME);
		PrintText(dc, SETTINGS_TITLE_POSX, SETTINGS_TITLE_POSY, GetGameText(game->gamestate, 0));
		SelectFont(dc, 18, 0, 8, MAINMENU_FONTNAME);
		// Istruzioni
		coordText.left = 10;
		coordText.top = game->instructionsScroll;
		coordText.right = rcPaint->right-10;
		coordText.bottom = rcPaint->bottom-20;
		{
			HDC dcTemp;
			HBITMAP hBmp;
			dcTemp = CreateCompatibleDC(dc);
			hBmp = CreateCompatibleBitmap(dc, rcPaint->right-20, rcPaint->bottom-80);
			SelectObject(dcTemp, hBmp);
			DeleteObject(hBmp);
			
			BitBlt(dcTemp, 0, 0, rcPaint->right-20, rcPaint->bottom-80, dc, coordText.left, 50, WHITENESS);
			DrawText(dcTemp, game->strIstr, -1, &coordText, DT_WORDBREAK);
			BitBlt(dc, coordText.left, 50, rcPaint->right-20, rcPaint->bottom-80, dcTemp, 0, 0, SRCAND);
			DeleteDC(dcTemp);
		}
	}

	if (game->gamestate == GAME_LOADGAME || game->gamestate == GAME_INSTRUCTIONS)
	{
		SelectFont(dc, 18, 0, 10, MAINMENU_FONTNAME);
		PrintText(dc, 10, 418, GetGameText(TEXT_DEFAULT, 4));
	}
	if (game->gamestate != GAME_BEGIN && game->gamestate != GAME_MAINMENU)
	{
		SelectFont(dc, 18, 0, 10, MAINMENU_FONTNAME);
		PrintText(dc, 515, 418, GetGameText(TEXT_DEFAULT, 3));
	}
}