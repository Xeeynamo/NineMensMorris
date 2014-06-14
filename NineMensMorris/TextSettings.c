//////////////////////////////////////////////////////////////////////////
// TextSettings.c
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

#include "NineMensMorris.h"

char *text_mainmenu[MAINMENU_ELEMENTS] =
{
	"Nuova partita",
	"Carica partita",
	"Impostazioni",
	"Top 10",
	"Istruzioni",
	"Esci",
};
const char *text_newgame[] =
{
	"Turno",
	"Giocatore",
	"Stai per uscire dalla partita.\nVuoi salvare la partita prima di tornare al menu principale?",
	"Conferma salvataggio",
	"Inserisci una pedina sul tavolo da gioco.",
	"Sposta una pedina selezionandola.",
	"Ora muovi una delle quattro freccie sulla tua tastiera.",
	"Tris effettuato. Cancella una pedina avversaria!",
	"Senza pedine sufficienti. Eliminato!",
	"Senza possibilità di muoversi. Eliminato!"
};
const char *text_loadgame[] =
{
	"Carica partita",
	"Al momento non esiste nessuna partita di salvataggio",
	"Sei sicuro di voler cancellare questa partita di salvataggio?",
	"Rimozione slot di salvataggio"
};
const char *text_settings[SETTINGS_ELEMENTS] =
{
	"Impostazioni",
	"Numero giocatori",
	"Grandezza campo",
	"Visualizza timer",
	"Abilita classifica"
};
const char *text_topten[TOPTEN_ELEMENTS] =
{
	"Top 10",
	"Posizione",
	"Nome",
	"Vittorie",
	"Sconfitte",
	"N. Mosse"
};
const char *text_istruzioni[] =
{
	"Istruzioni"
};
const char *text_exit[EXIT_ELEMENTS] =
{
	"Sei sicuro di voler uscire?",
	"Conferma uscita"
};
const char *text_defaults[] =
{
	"Si",
	"No",
	"Errore",
	"ESC per uscire",
	"Premi SU o GIU sulla tastiera per scorrere",
};
const char *text_files[] =
{
	"SETTINGS.BIN",
	"SAVES.BIN",
	"TOPTEN.TXT",
	"ISTRUZIONI.TXT"
};
const char **text_container[] =
{
	text_mainmenu, text_newgame, text_loadgame, text_settings, text_topten, text_istruzioni, text_exit, text_defaults, text_files
};

char *GetGameText(int state, int index)
{
	return (char*)text_container[state][index];
}
