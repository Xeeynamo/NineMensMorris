//////////////////////////////////////////////////////////////////////////
// ProjectSettings.h
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

// Impostazioni del menu
#define MAINMENU_Y				230				// Posizione del menu Y
#define MAINMENU_DISTANCE		80				// Distanza tra una opzione e l'altra
#define MAINMENU_X_INIT			-180			// Posizione del menu all'apertura del gioco
#define MAINMENU_X_END			+180			// Posizione del menu dopo l'animazione
#define MAINMENU_X_SPEED		9				// Velocità di spostamento del testo durante l'animazione
#define MAINMENU_ANGLE_INIT		-79				// Angolazione iniziale del testo
#define MAINMENU_ANGLE_END		80				// Angolazione del testo dopo l'animazione
#define MAINMENU_ANGLE_SPEED	4				// Velocità di rotazione del testo durante l'animazione
#define MAINMENU_TEXTCOLOR		0x00FFFFFF		// Colore del testo
#define MAINMENU_TEXTWIDTH		30				// Dimensione del testo
#define MAINMENU_TEXTINCLINATION 40				// Inclinazione del testo

// Impostazioni del menu Carica partita
#define LOADGAME_CARDX 60
#define LOADGAME_CARDY 52
#define LOADGAME_CARDWIDTH 300
#define LOADGAME_CARDHEIGHT 120
#define LOADGAME_CARDDISTANCE (LOADGAME_CARDHEIGHT+10)
#define LOADGAME_SLOTCOLORSELECTED		0x000000FF
#define LOADGAME_SLOTCOLORUNSELECTED	0x00000000
#define LOADGAME_SLOTEFFECTLAG			20

// Impostazioni del campo da gioco
#define BOARDGAME_COLOR			0x00FFFFFF		// Colore del campo da gioco
#define BOARDGAME_BORDERWIDTH	2				// Spessore dei bordi del campo da gioco
#define BOARDGAME_NODEWIDTH		12				// Spessore del nodo del campo da gioco
#define BOARDGAME_MINWIDTH		1				// Grandezza minima del campo da gioco
#define BOARDGAME_MAXWIDTH		400				// Grandezza massima del campo da gioco
#define BOARDGAME_POSX			92				// Posizione X del campo da gioco
#define BOARDGAME_POSY			10				// Posizione Y del campo da gioco
#define BOARDGAME_SIZEMIN		1				// Grandezza minima dei quadrati da gioco
#define BOARDGAME_SIZEMAX		8				// Grandezza massima dei quadrati da gioco
#define BOARDGAME_CHECKERSIZE	20				// Grandezza delle pedine da gioco
#define BOARDGAME_MINSIZE		3
#define BOARDGAME_MAXSIZE		15

// Impostazioni dei giocatori
#define PLAYER_MINCOUNT			2
#define PLAYER_MINCHECKERS		3

// Impostazioni delle impostazioni
#define SETTINGS_TITLE_POSX		20
#define SETTINGS_TITLE_POSY		10
#define SETTINGS_POSX			60
#define SETTINGS_POSY			60
#define SETTINGS_DISTANCE		40
#define SETTINGS_TEXTSIZE		26
#define SETTINGS_CONTATOR_POSX1	200
#define SETTINGS_CONTATOR_POSX2	215
#define SETTINGS_CONTATOR_POSX3	270

// Impostazioni della Top 10
#define TOPTEN_COLOR			0x00000000		// Colore dei bordi della topten
#define TOPTEN_POSX				10				// Posizione X della tabella
#define TOPTEN_POSY				50				// Posizione Y della tabella
#define TOPTEN_TOPBAR_HEIGHT	30				// Altezza della barra descrittiva
#define TOPTEN_ENTRY_COUNT		10				// Quantità di elementi nella tabella
#define TOPTEN_ENTRY_HEIGHT		33				// Altezza di un elemento nella tabella
#define TOPTEN_WIDTH_GRADE		90				// Larghezza della lista "Graduatoria"
#define TOPTEN_WIDTH_NAME		250				// Larghezza della lista "Nome"
#define TOPTEN_WIDTH_VICTORIES	130				// Larghezza della lista "Vittorie"
#define TOPTEN_WIDTH_MOVES		130				// Larghezza della lista "Numero mosse"
#define TOPTEN_TABLEWIDTH		(TOPTEN_WIDTH_GRADE+TOPTEN_WIDTH_NAME+TOPTEN_WIDTH_VICTORIES+TOPTEN_WIDTH_MOVES)	// La larghezza totale del tabellone
#define TOPTEN_TABLEHEIGHT		(TOPTEN_TOPBAR_HEIGHT + TOPTEN_ENTRY_COUNT*TOPTEN_ENTRY_HEIGHT)						// L'altezza totale del tabellone

// Nome dei file grafici esterni
#define MAINMENU_FONTNAME			"Times New Roman"
#define RESOURCEFILES_RESOURCEPATH	"./Pictures/"
#define MAINMENU_BACKGROUNDIMAGE	RESOURCEFILES_RESOURCEPATH"mainmenu.bmp"
#define DEFAULT_BACKGROUNDIMAGE		RESOURCEFILES_RESOURCEPATH"defaultbkg.bmp"
#define NEWGAME_BACKGROUNDIMAGE		RESOURCEFILES_RESOURCEPATH"newgame.bmp"
#define CHECKERS_GRAPHIC			RESOURCEFILES_RESOURCEPATH"checkers.bmp"
#define CHECKERS_MASK				RESOURCEFILES_RESOURCEPATH"checkersmask.bmp"
#define CURSORIMAGE					RESOURCEFILES_RESOURCEPATH"cursor.bmp"