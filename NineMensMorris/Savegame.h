//////////////////////////////////////////////////////////////////////////
// Savegame.h
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
#include "Gameboard.h"
#include <stdio.h>
#include <time.h>

#define LASTSAVESLOT 0x7FFFFFFF

typedef struct  
{
	time_t time;
	int boardsize;
	int playercount;
	int currentPlayerID;
	int totalRounds;
} SaveGamePreview;

/* OpenSaveFile
 * Apre o crea il file di salvataggio
 * Parametri:
 *	char *filename: nome del file
 *  FILE **f: puntatore al puntatore del file correttamente aperto
 * Ritorno:
 *	MSGERROR: messaggio di errore
 */
MSGERROR OpenSaveFile(char *filename, FILE **f);

/* SaveSelectSlot
 * Seleziona uno slot di salvataggio
 * Parametri:
 *	int slot: slot del salvataggio
 *  FILE**f: puntatore al file correttamente aperto
 * Ritorno:
 *	MSGERROR: messaggio di errore
 */
MSGERROR SaveSelectSlot(int slot, FILE *f);

/* GetSaveCount
 * Ottiene il numero totale di salvataggi
 * Parametri:
 *	int *count: numero di salvataggi
 *  FILE**f: puntatore al file correttamente aperto
 * Ritorno:
 *	MSGERROR: messaggio di errore
 */
MSGERROR GetSaveCount(int *count, FILE *f);

/* SaveGame
 * Salva la partita
 * Parametri:
 *	GameBoard *board: puntatore al campo da gioco
 *  FILE**f: puntatore al file correttamente aperto
 * Ritorno:
 *	MSGERROR: messaggio di errore
 */
MSGERROR SaveGame(GameBoard *board, FILE *f);

/* LoadGame
 * Carica la partita
 * Parametri:
 *	GameBoard *board: puntatore al campo da gioco
 *  FILE**f: puntatore al file correttamente aperto
 * Ritorno:
 *	MSGERROR: messaggio di errore
 */
MSGERROR LoadGame(GameBoard *board, FILE *f);

/* LoadGamePreview
 * Seleziona uno slot di salvataggio
 * Parametri:
 *	SaveGamePreview*: puntatore alla struttura contenenti le info del file di salvataggio
 *  FILE**f: puntatore al file correttamente aperto
 * Ritorno:
 *	MSGERROR: messaggio di errore
 */
MSGERROR LoadGamePreview(SaveGamePreview*, FILE *f);

/* DeleteSaveGame
 * Cancella una partita di salvataggio
 * Parametri:
 *  FILE**f: puntatore al file correttamente aperto
 * Ritorno:
 *	MSGERROR: messaggio di errore
 */
MSGERROR DeleteSaveGame(FILE *f);