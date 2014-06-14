//////////////////////////////////////////////////////////////////////////
// Game.h
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
#include "NineMensMorris.h"

#include "Gameboard.h"
#include "Player.h"
#include "Settings.h"
#include "TextSettings.h"
#include "TopTen.h"
#include "Savegame.h"

typedef struct  
{
	HDC dcBkgDefault;
	HDC dcBkgMainMenu;
	HDC dcBkgGame;
	HDC dcCheckers;
	HDC dcMaskCheckers;
	HDC dcCursor;

	HPEN penBoard;
	HPEN penLoadSelected;
	HPEN penLoadUnselected;
	HBRUSH brushNode;
} DCPictures;
typedef struct  
{
	int mousex;						// Posizione X del mouse
	int mousey;						// Posizione Y del mouse

	GAME_STATE gamestate;			// Stato del gioco
	short mainCursorPosition;		// Posizione del cursore del menu principale
	short settingsCursorPosition;	// Posizione del cursore nel menu impostazioni
	short instructionsScroll;		// Scrolling delle istruzioni

	GameBoard board;				// Contiene l'intero tabellone del gioco
	Settings settings;				// Contiene le impostazioni del gioco
	TopTen topten;					// Contiene la TopTen
	FILE *fsave;					// Contiene il puntatore verso il file dei salvataggi
	int deleteState;			// Settato ad 1 quando un salvataggio sta per essere eliminato

	int startTimer;				// Timer di gioco
	int infomessage;			// Imposta la durata del messaggio
	int dieplayerevent;			// Indica la causa dell'eliminazione di un giocatore
	int diedplayer;				// Contiene l'ID del giocatore appena eliminato

	int isCheckerSelected;			// Descrive se una pedina è stata selezionata
	int gameMoveCheckerIndex;		// Indice nodo del quadrato
	int gameMoveCheckerPosition;	// Indice quadrato del campo

	int menuTextX;				// Posizione orizzontale del menu principale
	int menuTextRotation;		// Angolazione del menu principale
	int cursorAnimIndex;		// Indice del cursore dell'immagine
	int cursorAnimVerse;		// Indice del verso del cursore dell'immagine

	int loadMenuSelectedSlot;	// Slot di salvataggio correntemente selezionato
	int loadMenuSlotCount;		// Numero di slot di salvataggio presenti
	int loadMenuEffect;			// Effetto del bordo intermittente di Carica partita

	char *strIstr;				// Contiene le istruzioni del gioco in formato testuale

	HWND hWnd;
	DCPictures pictures;
} Game;
typedef enum
{
	INPUTHANDLER_NOTHING = 0,	// Indica che non è stata effettuata nessuna operazione
	INPUTHANDLER_SELECT = 1,	// Indica che è stato selezionato un menu con INVIO
	INPUTHANDLER_BACK = 2,		// Indica che è stato premuto ESC
	INPUTHANDLER_EXIT = 3,		// Indica che si sta per uscire dal gioco
	INPUTHANDLER_SAVE = 4,		// Indica che si sta salvando una partita
	INPUTHANDLER_LOAD = 5,		// Indica che si sta caricando una partita
	INPUTHANDLER_DELETE = 6,	// Indica che è stato premuto il pulsante DEL
	INPUTHANDLER_ERROR = -1,	// Indica che è stato restituito un errore
} INPUTHANDLER_RESULT;

/* Initialize
 * Inizializza il gioco
 * Parametri:
 *	Game: struttura del gioco
 */
void Initialize(Game*);

/* Initialize
 * Carica le risorse del gioco
 * Parametri:
 *	Game: struttura del gioco
 */
void LoadGameResources(Game*);

/* Initialize
 * Cancella le risorse del gioco
 * Parametri:
 *	Game: struttura del gioco
 */
void DeleteGameResources(Game*);

/* Initialize
 * Ottiene lo stato del gioco
 * Parametri:
 *	Game: struttura del gioco
 * Ritorno:
 *	GAME_STATE: stato del gioco
 */
GAME_STATE GetGameState(Game *game);

/* Initialize
 * Imposta lo stato del gioco gioco
 * Parametri:
 *	Game: struttura del gioco
 *	GAME_STATE: stato del gioco
 */
MSGERROR SetGameState(Game *game, GAME_STATE state);

/* GetSettingAsString
 * Ottiene le stringhe di default per le impostazioni
 * Parametri:
 *	char *in: buffer di ingresso
 *  Settings *settings: impostazioni del gioco
 *  int i: indice delle impostazioni
 * Ritorno:
 *	char*: stringa da stampare
 */
char *GetSettingAsString(char *in, Settings *settings, int i);

/* GetPlayerCheckersCount
 * Ottiene il numero di pedine per ogni giocatore
 * Parametri:
 *	int szBoard: grandezza del campo
 *  int nPlayers: numero di giocatori
 * Ritorno:
 *	int: numero di pedine per giocatore
 */
int GetPlayerCheckersCount(int szBoard, int nPlayers);

/* NextRoundHandler
 * Passa al turno successivo
 * Parametri:
 *	Game *game: struttira di gioco
 * Ritorno:
 *	MSGERROR: Messaggio di errore
 */
MSGERROR NextRoundHandler(Game *game);

/* Victory
 * Segna la vittoria e l'aggiunta alla TopTen
 * Parametri:
 *	Game *game: struttira di gioco
 * Ritorno:
 *	MSGERROR: Messaggio di errore
 */
MSGERROR Victory(Game *game);

INPUTHANDLER_RESULT InputHandler(Game *game, unsigned int keyPressed);
boolean MouseHandler(Game *game, unsigned int mousePressed, int x, int y);
void GraphicHandler(Game *game, HDC dc, RECT *rcPaint);