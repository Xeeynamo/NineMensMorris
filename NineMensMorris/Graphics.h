//////////////////////////////////////////////////////////////////////////
// Graphics.h
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
#include <windows.h>

/* LoadPicture
 * Carica un'immagine in formato BMP
 * Parametri:
 *	char *filename: Puntatore alla stringa che contiene il nome del file da caricare
 * Ritorno:
 *  HDC: Ritorna l'area di disegno che contiene l'immagine
 */
HDC LoadPicture(char *filename);

/* GetCheckersBoardCoord
 * Ottiene le coordinate dei nodi e delle pedine
 * Parametri:
 *	COORD *coord: Puntatore alle coordinate, usato come parametro di uscita
 *	int i: indice della posizione del quadrato corrente del campo
 *  int size: dimensione del quadrato corrente del campo
 */
void GetCheckersBoardCoord(COORD *c, int i, int size);

/* DrawChecker
 * Disegna una pedina
 * Parametri:
 *	HDC dc: L'area di disegno di destinazione
 *	int x: Coordinata X della pedina
 *	int y: Coordinata Y della pedina
 *	int color: Colore della pedina
 *  HDC dcGraphic: Area di disegno della pedina
 *  HDC dcMask: Area di disegno della maschera trasparente della pedina
 */
void DrawChecker(HDC dc, int x, int y, int color, HDC dcGraphic, HDC dcMask);

/* DrawBoard
 * Disegna l'intero tavolo da gioco
 * Parametri:
 *	HDC dc: L'area di disegno di destinazione
 *	int x: Coordinata X del tavolo da gioco
 *	int y: Coordinata Y del tavolo da gioco
 *	int size: Numero di quadrati da stampare
 */
void DrawBoard(HDC dc, int x, int y, int size);

/* DrawSquareBoard
 * Disegna una porzione del campo composta dal quadrato e dagli 8 nodi sui suoi bordi
 * Parametri:
 *	HDC dc: L'area di disegno di destinazione
 *	int x: Coordinata X del quadrato di gioco
 *	int y: Coordinata Y del quadrato di gioco
 *	int width: Larghezza del quadrato di gioco
 *  int nodewidth: Spessore del nodo
 */
void DrawSquareBoard(HDC dc, int x, int y, int boardwidth, int nodewidth);

/* DrawCircle
 * Disegna un cerchio
 * Parametri:
 *	HDC dc: L'area di disegno di destinazione
 *	int x: Coordinata X del cerchio
 *	int y: Coordinata Y del cerchio
 *	int width: Larghezza del cerchio (corrisponde a raggio*2)
 */
void DrawCircle(HDC dc, int x, int y, int width);

/* DrawRectangle
 * Disegna un rettangolo
 * Parametri:
 *	HDC dc: L'area di disegno di destinazione
 *	int x: Coordinata X del rettangolo
 *	int y: Coordinata Y del rettangolo
 *	int width: Larghezza del rettangolo
 *  int height: Altezza del rettangolo
 */
void DrawRectangle(HDC dc, int x, int y, int width, int height);

/* DrawLine
 * Disegna una linea dal punto A al punto B
 * Parametri:
 *	HDC dc: L'area di disegno di destinazione
 *	int x1: Coordinata X del punto A
 *	int y1: Coordinata Y del punto A
 *	int x2: Coordinata X del punto B
 *	int y2: Coordinata Y del punto B
 */
void DrawLine(HDC dc, int x1, int y1, int x2, int y2);

/* PrintText
 * Stampa un determinato testo in una locazione della finestra
 * Parametri:
 *	HDC dc: L'area di disegno di destinazione
 *	int x: Coordinata x di destinazione
 *	int y: Coordinata y di destinazione
 *  char *text: Puntatore al testo da stampare
 */
void PrintText(HDC dc, int x, int y, char *text);

/* SelectFont
 * Seleziona un tipo di carattere
 * Parametri:
 *	HDC dc: L'area di disegno di destinazione
 *	int size: Dimensione del testo
 *	int angle: Angolazione del testo
 *  int bold: dimensione del grassetto
 *  char *fontname: Nome del font
 */
void SelectFont(HDC dc, int size, int angle, int bold, char *fontname);