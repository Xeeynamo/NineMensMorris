//////////////////////////////////////////////////////////////////////////
// TopTen.c
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

#include "TopTen.h"
#include <stdlib.h>
#include <string.h>

TopTen_Entry *GetTopTenEntry(TopTen *topten, int index)
{
	return &(*topten)[index];
}
boolean AddTopTenEntry(TopTen *topten, TopTen_Entry *entry)
{
	int i, j;
	for(i=0; i<TOPTEN_COUNT; i++)
	{
		if (strcmp((*topten)[i].name, entry->name) == 0)
		{
			(*topten)[i].wins++;
			if (entry->moves < (*topten)[i].moves)
				(*topten)[i].moves = entry->moves;
			SortTopTen(topten);
			return TRUE;
		}
	}
	for(i=0; i<TOPTEN_COUNT; i++)
	{
		if ((*topten)[i].moves > entry->moves || (*topten)[i].moves == 0)
		{
			for(j=TOPTEN_COUNT-1; j>i; j--)
			{
				memcpy(&(*topten)[j], &(*topten)[j-1], sizeof(TopTen_Entry));
			}
			memcpy(&(*topten)[i], entry, sizeof(TopTen_Entry));
			return TRUE;
		}
	}
	return FALSE;
}
void SortTopTen(TopTen *topten)
{
	int i, j, k;

	for(i=0; i<TOPTEN_COUNT-1; i++)
	{
		k = i;
		for(j=i+1; j<TOPTEN_COUNT; j++)
		{
			if ((*topten)[i].moves < (*topten)[j].moves && (*topten)[j].moves != 0)
			{
				k = j;
			}
		}
		if (k != i)
		{
			TopTen_Entry tmp;
			memcpy(&tmp, (*topten)+i, sizeof(TopTen_Entry));
			memcpy((*topten)+i, (*topten)+k, sizeof(TopTen_Entry));
			memcpy((*topten)+k, &tmp, sizeof(TopTen_Entry));
		}
	}
}
void ResetTopTen(TopTen *topten)
{
	int i;
	memset(topten, 0, sizeof(TopTen));
	for(i=0; i<TOPTEN_COUNT; i++)
	{
		(*topten)[i].name[0] = 'N';
		(*topten)[i].name[1] = 'U';
		(*topten)[i].name[2] = 'L';
		(*topten)[i].name[3] = 'L';
	}
}
void LoadTopTen(TopTen *topten, FILE *f)
{
	int i;
	fseek(f, 0, SEEK_SET);
	for(i=0; i<TOPTEN_COUNT; i++)
	{
		fscanf(f, "%s", (*topten)[i].name);
		fscanf(f, "%i", &(*topten)[i].wins);
		fscanf(f, "%i", &(*topten)[i].moves);
	}
	//fread(topten, 1, sizeof(TopTen), f);
}
void SaveTopTen(TopTen *topten, FILE *f)
{
	int i;
	fseek(f, 0, SEEK_SET);
	for(i=0; i<TOPTEN_COUNT; i++)
	{
		fprintf(f, "%s ", (*topten)[i].name);
		fprintf(f, "%i ", (*topten)[i].wins);
		fprintf(f, "%i ", (*topten)[i].moves);
		fprintf(f, "\r\n");
	}
	//fwrite(topten, 1, sizeof(TopTen), f);
}
MSGERROR LoadTopTenFromFile(TopTen *topten, char *filename, FILE **f)
{
	if (!f) return ERROR_NULLFILEPOINTER;
	if (!topten) return ERROR_NULLPOINTER;
	*f = fopen(filename, "r+b");
	if (!*f)
	{
		ResetTopTen(topten);
		*f = fopen(filename, "w+b");
		if (!*f) return ERROR_FOPEN_FAIL;
	}
	else LoadTopTen(topten, *f);
	SortTopTen(topten);
	return ERROR_OK;
}