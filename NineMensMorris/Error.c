//////////////////////////////////////////////////////////////////////////
// Error.c
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

#include <stdio.h>
#include <windows.h>
#include "Error.h"

char *msg_error[] =
{
	"",
	"Puntatore nullo",
	"Puntatore a file nullo",
	"Grandezza non valida",
	"Indice non valido",
	"Impossibile aprire il file",
	"Player count non valido",
	"Checker count non valido",
	"ID del giocatore non trovato",
	"Salvataggio non valido",
	"Impossibile salvare il gioco",
};

MSGERROR ErrorHandler(MSGERROR msg)
{
	FILE *f;
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);

	printf("ERROR: %s.\n", msg_error[msg]);
	return msg;
}