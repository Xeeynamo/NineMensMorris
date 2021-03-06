//////////////////////////////////////////////////////////////////////////
// TextSettings.h
// Part of http://github.com/Xeeynamo/NineMensMorris
// Copyright(C) 2014  Luciano Ciccariello (Xeeynamo)
// This file was committed to UniversitÓ degli Studi Aldo Moro, Dipartimento
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

#define MAINMENU_ELEMENTS 6
#define TOPTEN_ELEMENTS 6
#define SETTINGS_ELEMENTS 5
#define EXIT_ELEMENTS 2

/* GetGameText
 * Ottiene una stringa del gioco in base alla categoria e all'indice selezionato.
 * Parametri:
 *	int gamestate: specifica lo stato del gioco
 *  int index: specifica l'indice
 */
char *GetGameText(int gamestate, int index);