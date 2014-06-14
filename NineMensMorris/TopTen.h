//////////////////////////////////////////////////////////////////////////
// TopTen.h
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
#include <windows.h>
#include "Error.h"
#define TOPTEN_COUNT 10

typedef struct  
{
	char name[20];
	int wins;
	int moves;
} TopTen_Entry;
typedef TopTen_Entry TopTen[TOPTEN_COUNT];

/* GetTopTenEntry
 * Ottiene l'elemento della topten specificato tramite indice.
 * Parametri:
 *	TopTen *topten: puntatore alla struttura contenente la topten
 *	int index: indice da 0 a TOPTEN_COUNT-1
 * Ritorno:
 * TopTen_Entry*: puntatore alla struttura dell'elemento della topten richiesto.
 */
TopTen_Entry *GetTopTenEntry(TopTen *topten, int index);

/* AddTopTenEntry
 * Aggiunge un elemento nella topten.
 * Parametri:
 *	TopTen *topten: puntatore alla struttura contenente la topten
 *	TopTen_Entry *entry: puntatore all'elemento da inserire che verrà copiato nella topten
 */
boolean AddTopTenEntry(TopTen *topten, TopTen_Entry *entry);

/* SortTopTen
 * Ordina la topten
 * Parametri:
 *	TopTen *topten: puntatore alla struttura contenente la topten
 */
void SortTopTen(TopTen *topten);

/* ResetTopTen
 * Resetta la topten.
 * Parametri:
 *	TopTen *topten: puntatore alla struttura contenente la topten
 */
void ResetTopTen(TopTen *topten);

/* LoadTopTen
 * Carica la top ten da file
 * Parametri:
 *	TopTen *topten: puntatore alla struttura contenente la topten
 *	FILE *f: Puntatore ad un file correttamente aperto
 */
void LoadTopTen(TopTen *topten, FILE *f);

/* SaveTopTen
 * Carica la top ten da file
 * Parametri:
 *	TopTen *topten: puntatore alla struttura contenente la topten
 *	FILE *f: Puntatore ad un file correttamente aperto
 */
void SaveTopTen(TopTen *topten, FILE *f);

/* LoadTopTenFromFile
 * Carica la top ten da file effettuando una serie di controlli.
 * Se il file non esiste, ne verrà creato uno nuovo.
 * Parametri:
 *	TopTen *topten: puntatore alla struttura contenente la topten
 *  char *filename: nome del file da aprire.
 *	FILE **f: restituisce il puntatore del file correntemente aperto
 * Ritorno:
 *	ERROR: codice di errore
 */
MSGERROR LoadTopTenFromFile(TopTen *topten, char *filename, FILE **f);