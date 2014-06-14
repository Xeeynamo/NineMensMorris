//////////////////////////////////////////////////////////////////////////
// Settings.h
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
#include <stdio.h>
#include "Error.h"

typedef unsigned char boolean;

typedef struct  
{
	int nPlayers;
	int szBoard;
	boolean bTimer;
	boolean bTopten;
} Settings;

/* LoadSettings
 * Carica le impostazioni da un file
 * Parametri:
 *	Settings *settings: puntatore alla struttura contenente le impostazioni
 *  FILE *f: puntatore ad un file correttamente aperto
 */
void LoadSettings(Settings *settings, FILE *f);

/* LoadSettingsFromFile
 * Carica le impostazioni da file effettuando una serie di controlli.
 * Se il file non esiste, ne verrà creato uno nuovo.
 * Parametri:
 *	Settings *settings: puntatore alla struttura contenente le impostazioni
 *  char *filename: nome del file da aprire.
 *	FILE **f: restituisce il puntatore del file correntemente aperto
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR LoadSettingsFromFile(Settings *settings, char *filename, FILE **f);

/* SaveSettings
 * Salva le impostazioni in un file
 * Parametri:
 *	Settings *settings: puntatore alla struttura contenente le impostazioni
 *  FILE *f: puntatore ad un file correttamente aperto
 */
void SaveSettings(Settings *settings, FILE *f);

/* DefaultSettings
 * Carica le impostazioni predefinite. Usato principalmente se LoadSettings non va a buon fine.
 * Parametri:
 *	Settings *settings: puntatore alla struttura contenente le impostazioni
 */
void DefaultSettings(Settings *settings);

/* Settings_GetPlayer
 * Ottiene il numero di giocatori correntemente impostato
 * Parametri:
 *	Settings *settings: puntatore alla struttura contenente le impostazioni
 * Ritorno:
 *	int: Numero di giocatori correntemente impostato
 */
int Settings_GetPlayer(Settings *settings);

/* Settings_SetPlayers
 * Imposta il numero di giocatori
 * Parametri:
 *	Settings *settings: puntatore alla struttura contenente le impostazioni
 *  int players: numero di giocatori da impostare
 */
void Settings_SetPlayers(Settings *settings, int players);

/* Settings_GetPlayer
 * Ottiene la grandezza del campo da gioco correntemente impostata
 * Parametri:
 *	Settings *settings: puntatore alla struttura contenente le impostazioni
 * Ritorno:
 *	int: grandezza del campo da gioco misurata in quadrati concentrici correntemente impostata
 */
int Settings_GetBoardSize(Settings *settings);

/* Settings_SetBoardSize
 * Imposta il numero di giocatori
 * Parametri:
 *	Settings *settings: puntatore alla struttura contenente le impostazioni
 *  int size: grandezza del campo da gioco misurata in quadrati concentrici da impostare
 */
void Settings_SetBoardSize(Settings *settings, int size);

/* Settings_GetTimer
 * Ottiene un valore che indica se il timer è correntemente abilitato o meno
 * Parametri:
 *	Settings *settings: puntatore alla struttura contenente le impostazioni
 * Ritorno:
 *	boolean: valore che indica se il timer è correntemente abilitato o meno
 */
boolean Settings_GetTimer(Settings *settings);

/* Settings_SetPlayers
 * Imposta un valore che indica se il timer è correntemente abilitato o meno
 * Parametri:
 *	Settings *settings: puntatore alla struttura contenente le impostazioni
 *  int enabled: valore che imposta se il timer è correntemente abilitato o meno
 */
void Settings_SetTimer(Settings *settings, boolean enabled);