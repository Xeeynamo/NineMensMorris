//////////////////////////////////////////////////////////////////////////
// Player.h
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
#include "Error.h"

#define MINIMUM_PLAYER_COUNT 2
#define MINIMUM_CHECKRS_COUNT 3
#define PLAYER_NAME_MAXSIZE 20
typedef char PlayerName[PLAYER_NAME_MAXSIZE];

typedef struct  
{
	short id;						// ID del giocatore
	short tableCheckersCount;		// Numero di pedine fuori il tavolo da gioco
	short boardCheckersCount;		// Numero di pedine dentro il tavolo da gioco
	short moves;					// Numero di mosse del giocatore
	short alive;					// 1 se il giocatore è in gioco, 0 se è stato eliminato
} Player;
typedef struct _PlayerList
{
	Player player;				// Struttura contenente il giocatore
	struct _PlayerList *next;	// Puntatore verso il prossimo elemento della lista
} PlayerList;

/* CreatePlayerList
 * Crea la lista dei giocatori che verrà usata in una nuova partita.
 * Parametri:
 *	PlayerList *plist: puntatore ad una lista dei giocatori correttamente inizializzata.
 *	int count: numero di giocatori
 *  int checkersCount: numero di pedine assegnate ad ogni giocatore
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR CreatePlayerList(PlayerList **plist, int count, int checkersCount);

/* DeletePlayerList
 * Cancella la lista di giocatori deallocandola dalla memoria.
 * Parametri:
 *	PlayerList *plist: puntatore ad una lista dei giocatori correttamente inizializzata.
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR DeletePlayerList(PlayerList *plist);

/* GetPlayer
 * Ottiene un giocatore in base all'ID specificato.
 * Parametri:
 *	PlayerList *plist: puntatore ad una lista dei giocatori correttamente inizializzata.
 *	int id: ID del giocatore da cercare
 *  Player *player: puntatore alla struttura contenente le informazioni del giocatore
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR GetPlayer(PlayerList *plist, int id, Player **player);

/* KickPlayer
 * Esclude un giocatore dal gioco in base all'ID specificato
 * Parametri:
 *	PlayerList *plist: puntatore ad una lista dei giocatori correttamente inizializzata.
 *	int id: ID del giocatore da cercare
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR KickPlayer(PlayerList *plist, int id);