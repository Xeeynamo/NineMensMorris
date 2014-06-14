//////////////////////////////////////////////////////////////////////////
// Savegame.c
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

#include "Savegame.h"
#include <stdlib.h>

#define FILESIGN (*((int*)"SAVE"))
#define SLOTSIGN (*((int*)"SLOT"))
#define ENDSIGN (*((int*)"END!"))

MSGERROR OpenSaveFile(char *filename, FILE **f)
{
	int fsign;
	int saveslots;
	if (!filename) return ERROR_NULLPOINTER;
	if (!f) return ERROR_NULLFILEPOINTER;

	*f = fopen(filename, "r+b");
	if (!*f)
	{
		*f = fopen(filename, "w+b");
		if (!*f)
		{
			return ERROR_UNABLETOCREATESAVEGAME;
		}
		saveslots = 0;
		fwrite(&FILESIGN, sizeof(int), 1, *f);
		fwrite(&saveslots, sizeof(saveslots), 1, *f);
	}
	else
	{
		fread(&fsign, sizeof(int), 1, *f);
		if (fsign != FILESIGN)
		{
			fclose(*f);
			return ERROR_INVALIDSAVEGAME;
		}
		fread(&saveslots, sizeof(saveslots), 1, *f);
	}
	return ERROR_OK;
}
MSGERROR GetSaveCount(int *count, FILE *f)
{
	int prevpos;
	if (!count) return ERROR_NULLPOINTER;
	*count = 0;
	if (!f) return ERROR_NULLFILEPOINTER;
	prevpos = ftell(f);
	fseek(f, 4, SEEK_SET);
	fread(count, sizeof(int), 1, f);
	fseek(f, prevpos, SEEK_SET);
	return ERROR_OK;
}
MSGERROR SaveSelectSlot(int slot, FILE *f)
{
	MSGERROR err;
	int i;
	int fPosition;
	int saveslots;
	if (!f) ERROR_NULLFILEPOINTER;

	fseek(f, 8, SEEK_SET);
	ERRCALL(GetSaveCount(&saveslots, f));
	if (slot == 0)									// Se il numero degli slot è 0, ritorna
	{
		return ERROR_OK;
	}
	if (slot > saveslots)							// Se lo slot da selezionare è maggiore del numero totale di salvataggi correnti
	{
		slot = saveslots+1;							// Allora imposta slot uguale a saveslot+1
		fseek(f, 4, SEEK_SET);						// Si posiziona di nuovo al numero di slot totali
		fwrite(&slot, sizeof(slot), 1, f);			// e ne scrive la nuova quantità
		if (saveslots == 0) return ERROR_OK;		// Se non è stato ancora creato nessun salvataggio, allora esce
	}
	for(i=0; i<slot-1; i++)							// Per ogni i da 0 a slot
	{
		fseek(f, 4, SEEK_CUR);
		fread(&fPosition, sizeof(fPosition), 1, f);	// Leggi la dimensione dello slot corrente
		fseek(f, fPosition, SEEK_SET);				// E si sposta nello slot successivo
	}
	return ERROR_OK;
}
MSGERROR SaveGame(GameBoard *board, FILE *f)
{
	int i, j;
	MSGERROR err;
	int boardsize;
	int playercount;
	SquareBoard *squareboard;
	PlayerList *plist;
	Player *player;
	time_t timeVar;
	int fStartPos;
	int fEndPos;

	if (!f) ERROR_NULLFILEPOINTER;

	fwrite(&SLOTSIGN, 4, 1, f);
	fStartPos = ftell(f);
	fseek(f, sizeof(fEndPos), SEEK_CUR);
	// Ottiene i dati da salvare
	ERRCALL(GetBoardSize(board, &boardsize));
	ERRCALL(GetPlayerCount(board, &playercount));
	ERRCALL(GetPlayerList(board, &plist));
	// Dati per l'anteprima di un salvataggio come data ed ora, giocatore corrente, numero giocatori ecc.
	timeVar = time(&timeVar);
	fwrite(&timeVar, sizeof(timeVar), 1, f);
	fwrite(&boardsize, sizeof(boardsize), 1, f);
	fwrite(&playercount, sizeof(playercount), 1, f);
	fwrite(&board->curPlayerID, sizeof(board->curPlayerID), 1, f);
	fwrite(&board->totalRounds, sizeof(board->totalRounds), 1, f);
	// Salva il campo da gioco
	for(i=0; i<boardsize; i++)
	{
		ERRCALL(GetBoardSquare(board, i, &squareboard));
		fwrite(squareboard, sizeof(SquareBoard), 1, f);
	}
	// Salva i giocatori
	for(i=0, j=0; i<playercount; j++)
	{
		if (GetPlayer(plist, j, &player) == ERROR_OK)
		{
			fwrite(player, sizeof(Player), 1, f);
			i++;
		}
	}
	fEndPos = ftell(f);
	fwrite(&ENDSIGN, 4, 1, f);
	fseek(f, fStartPos, SEEK_SET);
	fwrite(&fEndPos, sizeof(fEndPos), 1, f);
	return ERROR_OK;
}
MSGERROR LoadGame(GameBoard *board, FILE *f)
{
	int i;
	MSGERROR err;
	int boardsize;
	int playercount;
	SquareBoard *squareboard;
	PlayerList *plist;
	Player *player;
	time_t timeVar;
	int fEndPos;
	int filesign;

	if (!board) return ERROR_NULLPOINTER;
	if (!f) return ERROR_NULLFILEPOINTER;

	boardsize = -1;

	fread(&filesign, sizeof(SLOTSIGN), 1, f);
	if (filesign != SLOTSIGN)
	{
		return ERROR_INVALIDSAVEGAME;
	}
	fread(&fEndPos, sizeof(fEndPos), 1, f);
	fread(&timeVar, sizeof(timeVar), 1, f);
	fread(&boardsize, sizeof(boardsize), 1, f);
	fread(&playercount, sizeof(playercount), 1, f);

	ERRCALL(CreateBoard(board, boardsize));
	ERRCALL(CreatePlayerList(&board->playerList, playercount, 3));
	ERRCALL(GetPlayerList(board, &plist));

	fread(&board->curPlayerID, sizeof(board->curPlayerID), 1, f);
	fread(&board->totalRounds, sizeof(board->totalRounds), 1, f);

	for(i=0; i<boardsize; i++)
	{
		ERRCALL(GetBoardSquare(board, i, &squareboard));
		fread(squareboard, sizeof(SquareBoard), 1, f);
	}
	for(i=0; i<playercount; i++)
	{
		if (GetPlayer(plist, i, &player) == ERROR_OK)
		{
			fread(player, sizeof(Player), 1, f);
		}
	}
	return ERROR_OK;
}
MSGERROR LoadGamePreview(SaveGamePreview *savegamepreview, FILE *f)
{
	int filesign;
	if (!savegamepreview) return ERROR_NULLPOINTER;
	if (!f) return ERROR_NULLFILEPOINTER;
	fread(&filesign, sizeof(SLOTSIGN), 1, f);
	if (filesign != SLOTSIGN)
	{
		return ERROR_INVALIDSAVEGAME;
	}
	fseek(f, 4, SEEK_CUR);
	fread(savegamepreview, sizeof(SaveGamePreview), 1, f);
	return ERROR_OK;
}
MSGERROR DeleteSaveGame(FILE *f)
{
	MSGERROR err;
	int savecount;
	int nextpos;
	int curpos;
	int diffpos;
	int totalsize;
	void *mem;
	int memsize;

	if (!f) return ERROR_NULLFILEPOINTER;
	curpos = ftell(f);
	ERRCALL(GetSaveCount(&savecount, f));

	fseek(f, 4, SEEK_CUR);
	fread(&nextpos, sizeof(nextpos), 1, f);
	diffpos = nextpos - curpos;
	fseek(f, nextpos, SEEK_SET);
	while(1)
	{
		int sign = 0;
		int pos;

		fread(&sign, sizeof(sign), 1, f);
		if (feof(f))
		{
			totalsize = ftell(f);
			break;
		}
		else if (sign != SLOTSIGN)
		{
			totalsize = ftell(f) - 4;
			break;
		}
		fread(&pos, sizeof(pos), 1, f);
		pos -= diffpos;
		fseek(f, -4, SEEK_CUR);
		fwrite(&pos, sizeof(pos), 1, f);
		fseek(f, pos + diffpos, SEEK_SET);
	}

	memsize = totalsize - nextpos;
	mem = malloc(memsize);
	fseek(f, nextpos, SEEK_SET);
	fread(mem, memsize, 1, f);
	fseek(f, curpos, SEEK_SET);
	fwrite(mem, memsize, 1, f);
	fwrite(&ENDSIGN, 4, 1, f);

	savecount--;
	fseek(f, 4, SEEK_SET);
	fwrite(&savecount, sizeof(savecount), 1, f);
	fflush(f);

	return ERROR_OK;
}