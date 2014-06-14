//////////////////////////////////////////////////////////////////////////
// Error.h
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

typedef enum
{
	ERROR_OK = 0,
	ERROR_NULLPOINTER,
	ERROR_NULLFILEPOINTER,
	ERROR_INVALIDSIZE,
	ERROR_INVALIDINDEX,
	ERROR_FOPEN_FAIL,
	// Player.c
	ERROR_INVALID_PLAYERCOUNT,
	ERROR_INVALID_CHECKRCOUNT,
	ERROR_PLAYERIDNOTFOUND,
	// Save.c
	ERROR_INVALIDSAVEGAME,
	ERROR_UNABLETOCREATESAVEGAME,

} MSGERROR;

#define ERRCALL(i) { if ((err = (i))!=ERROR_OK) { return ErrorHandler(err); }}

MSGERROR ErrorHandler(MSGERROR msg);