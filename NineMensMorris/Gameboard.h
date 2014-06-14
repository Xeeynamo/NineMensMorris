//////////////////////////////////////////////////////////////////////////
// Gameboard.h
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
#include "Player.h"

typedef int SquareBoard[8];

typedef struct 
{
	int totalRounds;
	int boardSize;
	int curPlayerID;
	int countPlayer;
	SquareBoard *board;
	PlayerList *playerList;
} GameBoard;
typedef enum
{
	CHECKERSTATE_SUCCESS = 0,
	CHECKERSTATE_ALREADYUSED = 1,
	CHECKERSTATE_TRIS = 2,
	CHECKERSTSTE_EMPTY = 3,
	CHECKERTATE_SELF = 4,
	CHECKERSTATE_NOMOVE = 5,
	CHECKERSTATE_VICTORY = 6,
	CHECKERSTATE_DEADLOCK = 7,
} CheckerState;
typedef enum
{
	BOARDPOS_TOPLEFT		= 0,
	BOARDPOS_TOPCENTER		= 1,
	BOARDPOS_TOPRIGHT		= 2,
	BOARDPOS_CENTERLEFT		= 3,
	BOARDPOS_CENTERRIGHT	= 4,
	BOARDPOS_BOTTOMLEFT		= 5,
	BOARDPOS_BOTTOMCENTER	= 6,
	BOARDPOS_BOTTOMRIGHT	= 7
} GameBoardPosition;
typedef enum
{
	AROUNDPOS_NULL	= -1,
	AROUNDPOS_UP	= 0,
	AROUNDPOS_DOWN	= 1,
	AROUNDPOS_LEFT	= 2,
	AROUNDPOS_RIGHT	= 3
} GameBoardAround;

#define CHECKER_EMPTY -1
#define CHECKER_INVALID -2

/* CreateBoard
 * Crea il tabellone da gioco, inizializza tutti i nodi vuoti e resetta il contatore dei turni.
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *	int size: dimensione del campo da gioco. Per dimensione si intende il numero di quadrati concentrici.
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR CreateBoard(GameBoard *board, int size);

/* DestroyBoard
 * Distrugge il tabellone da gioco precedentemente allocato con CreateBoard.
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR DestroyBoard(GameBoard *board);

/* GetBoardSize
 * Ottiene il numero di quadrati concentrici del campo da gioco.
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 * Ritorno
 *	int: dimensione del campo da gioco. Per dimensione si intende il numero di quadrati concentrici.
 *		 Se è 0 significa che il campo da gioco non è stato creato.
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR GetBoardSize(GameBoard *board, int *size);

/* SetBoardSize
 * Imposta il numero di quadrati concentrici del campo da gioco.
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *	int size: dimensione del campo da gioco. Per dimensione si intende il numero di quadrati concentrici.
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR SetBoardSize(GameBoard *board, int size);

/* GetSquare
 * Ottiene il puntatore di uno dei quadrati concentrici in base all'indice specificato.
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *	int index: indice del quadrato concentrico.
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR GetBoardSquare(GameBoard *board, int index, SquareBoard **boardsquare);

/* GetCurrentPlayerID
 * Ottiene l'ID del giocatore corrente.
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *	int *id: puntatore all'ID del giocatore corrente
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR GetCurrentPlayerID(GameBoard *board, int *id);

/* GetChecker
 * Ottiene la pedina nella posizione del quadrato specificato.
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *	int index: indice del quadrato concentrico.
 *  int position: posizione nel quadrato. Non deve essere minore di 0 o maggiore di 7
 *  int *data: puntatore ad un intero dove verrà inserito il valore della pedina
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR GetChecker(GameBoard *board, int index, int position, int *data);

/* SetChecker
 * Imposta la pedina in un punto specifico del campo da gioco.
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *	int index: indice del quadrato concentrico.
 *  int position: posizione nel quadrato. Non deve essere minore di 0 o maggiore di 7
 *  int player: giocatore corrente
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR SetChecker(GameBoard *board, int index, int position, int player);

/* PutChecker
 * Imposta la pedina in un punto specifico del campo da gioco;
 * verifica se la posizione corrente è già occupata da un'altra pedina
 * e/o se si è fatto un tris. 
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *	int index: indice del quadrato concentrico.
 *  int position: posizione nel quadrato. Non deve essere minore di 0 o maggiore di 7
 *  int player: giocatore corrente
 *  CheckerState *state: stato dell'operazione di cancellazione. Può ritornare CHECKERSTSTE_SUCCESS o CHECKERSTATE_ALREADYUSED
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR PutChecker(GameBoard *board, int index, int position, int player, CheckerState *state);

/* MoveChecker
 * Muove la pedina corrente da un punto all'altro.
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *	int index: indice del quadrato concentrico.
 *  int position: posizione nel quadrato. Non deve essere minore di 0 o maggiore di 7
 *  int player: giocatore corrente
 *  GameBoardAround move: tipo di movimento
 *  CheckerState *state: stato dell'operazione di cancellazione. Può ritornare CHECKERSTSTE_SUCCESS o CHECKERSTATE_ALREADYUSED
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR MoveChecker(GameBoard *board, int index, int position, int player, GameBoardAround move, CheckerState *state);

/* DeleteChecker
 * Cancella una pedina nella posizione specificata e nel quadrato concentrico specificato.
 * Non è possibile cancellare una pedina non collocata in quel punto (verrà ritornato state=CHECKERSTATE_EMPTY)
 * e non è possibile cancellare la pedina del giocatore corrente (verrà ritornato state=CHECKERSTATE_SELF).
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *	int index: indice del quadrato concentrico.
 *  int position: posizione nel quadrato. Non deve essere minore di 0 o maggiore di 7
 *  int player: giocatore corrente
 *  CheckerState *state: stato dell'operazione di cancellazione. Può ritornare CHECKERSTATE_SUCCESS, CHECKERSTATE_EMPTY o CHECKERSTATE_SELF
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR DeleteChecker(GameBoard *board, int index, int position, int *player, CheckerState *state);

/* CheckerAround
 * Ottiene le pedine attorno alla pedina specificata.
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *	int index: indice del quadrato concentrico.
 *  int position: posizione nel quadrato. Non deve essere minore di 0 o maggiore di 7
 *  int *around: vettore con dimensione maggiore o uguale d 4 dove verranno memorizzate le pedine attorno.
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR CheckerAround(GameBoard *board, int index, int position, int *around);

/* CheckCheckerTris
 * Verifica se la pedina selezionata fa parte di un tris. In esito positivo, il valore state viene posto a CHECKERSTATE_TRIS,
 * altrimenti state non subirà nessun cambiamento.
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *	int index: indice del quadrato concentrico.
 *  int position: posizione nel quadrato. Non deve essere minore di 0 o maggiore di 7
 *  CheckerState *state: stato dell'operazione.
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR CheckCheckerTris(GameBoard *board, int index, int position, CheckerState *state);

/* GetCheckerCount
 * Ottiene il numero di pedine presenti nel campo del giocatore definito.
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *  int player: giocatore corrente su cui si vuole ottenere il numero di pedine
 *  int *count: puntatore al numero di pedine del giocatore definito restituito dalla funzione corrente
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR GetCheckerCount(GameBoard *board, int player, int *count);

/* GetPlayerList
 * Ottiene la lista di giocatori
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone correttamente inizializzato.
 *	PlayerList **plist: puntatore alla lista dei giocatori.
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR GetPlayerList(GameBoard *board, PlayerList **plist);

/* SetPlayerList
 * Imposta la lista di giocatori
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone correttamente inizializzato.
 *	PlayerList *plist: puntatore alla lista dei giocatori.
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR SetPlayerList(GameBoard *board, PlayerList *plist);

/* GetPlayerCount
 * Ottiene il numero di giocatori
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone correttamente inizializzato.
 *	int *count: puntatore alla variabile che conterrà all'uscita della funzione il numero di giocatori correnti
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR GetPlayerCount(GameBoard *board, int *count);

/* GetRoundCount
 * Ottiene il numero di turni dall'inizio della partita sino al momento esatto della chiamata.
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *	int *rounds: puntatore alla struttura contenente il numero di match come parametro di uscita.
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR GetRoundCount(GameBoard *board, int *rounds);

/* NextRound
 * Passa al turno del giocatore successivo
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR NextRound(GameBoard *board);

/* CheckVictory
 * Vede se è avvenuta la vittoria
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *  CheckerState *state: stato dell'operazione.
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR CheckVictory(GameBoard *board, CheckerState *state);

/* CheckFreeze
 * Vede se il giocatore corrente è in stallo
 * Parametri:
 *	GameBoard *board: puntatore alla struttura contenente il tabellone.
 *  CheckerState *state: stato dell'operazione.
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR CheckFreeze(GameBoard *board, CheckerState *state);
