//////////////////////////////////////////////////////////////////////////
// Graphics.c
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

#include "Graphics.h"
#include "ProjectSettings.h"
#include <stdio.h>

// Funzioni di caricamento
HDC LoadPicture(char *filename)
{
	HDC dc;
	HBITMAP hBmp;
	dc = CreateCompatibleDC(NULL);
	hBmp = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	SelectObject(dc, hBmp);
	DeleteObject(hBmp);
	return dc;
}
// Funzioni di locazione
void GetCheckersBoardCoord(COORD *c, int i, int size)
{
	if (!c) return;
	switch(i)
	{
	case 0:
		c->X = 0;
		c->Y = 0;
		break;
	case 1:
		c->X = size/2;
		c->Y = 0;
		break;
	case 2:
		c->X = size;
		c->Y = 0;
		break;
	case 3:
		c->X = 0;
		c->Y = size/2;
		break;
	case 4:
		c->X = size;
		c->Y = size/2;
		break;
	case 5:
		c->X = 0;
		c->Y = size;
		break;
	case 6:
		c->X = size/2;
		c->Y = size;
		break;
	case 7:
		c->X = size;
		c->Y = size;
		break;
	}
}
// Funzioni di disegno
void DrawChecker(HDC dc, int x, int y, int color, HDC dcGraphic, HDC dcMask)
{
	HDC dcBuffer;
	HBITMAP bmp;
	char chbuf[2];

	dcBuffer = CreateCompatibleDC(dc);
	bmp = CreateCompatibleBitmap(dc, BOARDGAME_CHECKERSIZE, BOARDGAME_CHECKERSIZE);
	SelectObject(dcBuffer, bmp);
	DeleteObject(bmp);

	BitBlt(dcBuffer, 0, 0, BOARDGAME_CHECKERSIZE, BOARDGAME_CHECKERSIZE, dcMask, 0, 0, SRCCOPY);
	BitBlt(dcBuffer, 0, 0, BOARDGAME_CHECKERSIZE, BOARDGAME_CHECKERSIZE, dcGraphic, (color%10)*BOARDGAME_CHECKERSIZE, 0, SRCAND);
	//BitBlt(dc, x, y, BOARDGAME_CHECKERSIZE, BOARDGAME_CHECKERSIZE, dcBuffer, 0, 0, SRCCOPY);
	GdiTransparentBlt(dc, x, y, BOARDGAME_CHECKERSIZE, BOARDGAME_CHECKERSIZE, dcBuffer, 0, 0, BOARDGAME_CHECKERSIZE, BOARDGAME_CHECKERSIZE, 0);

	DeleteDC(dcBuffer);

	if (color >= 10)
	{
		sprintf(chbuf, "%c", 'A'+(color-10)/10);
		PrintText(dc, x+5, y+2, chbuf);
	}
}
void DrawBoard(HDC dc, int x, int y, int size)
{
	int i;
	int distance;
	if (size < BOARDGAME_SIZEMIN) size = BOARDGAME_SIZEMIN;
	distance = (BOARDGAME_MAXWIDTH-BOARDGAME_MINWIDTH)/size/2;
	for(i=0; i<size; i++)
	{
		DrawSquareBoard(dc, x+i*distance, y+i*distance, BOARDGAME_MAXWIDTH-i*distance*2, BOARDGAME_NODEWIDTH);
	}
	// Linea orizzontale sinistra
	DrawLine(dc, x, y+BOARDGAME_MAXWIDTH/2, x+distance*(size-1), y+BOARDGAME_MAXWIDTH/2);
	// Linea orizzontale destra
	DrawLine(dc, x+BOARDGAME_MAXWIDTH, y+BOARDGAME_MAXWIDTH/2, x+BOARDGAME_MAXWIDTH-distance*(size-1), y+BOARDGAME_MAXWIDTH/2);
	// Linea verticale superiore
	DrawLine(dc, x+BOARDGAME_MAXWIDTH/2, y, x+BOARDGAME_MAXWIDTH/2, y+distance*(size-1));
	// Linea verticale inferiore
	DrawLine(dc, x+BOARDGAME_MAXWIDTH/2, y+BOARDGAME_MAXWIDTH, x+BOARDGAME_MAXWIDTH/2, y+BOARDGAME_MAXWIDTH-distance*(size-1));
}
void DrawSquareBoard(HDC dc, int x, int y, int boardwidth, int nodewidth)
{
	DrawRectangle(dc, x, y, boardwidth, boardwidth);
	DrawCircle(dc, x, y, nodewidth);
	DrawCircle(dc, x+boardwidth/2, y, nodewidth);
	DrawCircle(dc, x+boardwidth, y, nodewidth);
	DrawCircle(dc, x, y+boardwidth, nodewidth);
	DrawCircle(dc, x+boardwidth/2, y+boardwidth, nodewidth);
	DrawCircle(dc, x+boardwidth, y+boardwidth, nodewidth);
	DrawCircle(dc, x, y+boardwidth/2, nodewidth);
	DrawCircle(dc, x+boardwidth, y+boardwidth/2, nodewidth);
}
void DrawCircle(HDC dc, int x, int y, int width)
{
	Ellipse(dc, x-width/2, y-width/2, x+width/2, y+width/2);
}
void DrawRectangle(HDC dc, int x, int y, int width, int height)
{
	MoveToEx(dc, x, y, 0);
	LineTo(dc, x+width, y);
	LineTo(dc, x+width, y+height);
	LineTo(dc, x, y+height);
	LineTo(dc, x, y);
}
void DrawLine(HDC dc, int x1, int y1, int x2, int y2)
{
	MoveToEx(dc, x1, y1, NULL);
	LineTo(dc, x2, y2);
}
void PrintText(HDC dc, int x, int y, char *text)
{
	TextOut(dc, x, y, text, strlen(text));
}
void SelectFont(HDC dc, int size, int angle, int bold, char *fontname)
{
	HFONT fontMenuText = CreateFont(size, 0, angle, 0, bold*100, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_ROMAN, fontname);
	SelectObject(dc, fontMenuText);
	DeleteObject(fontMenuText);
}