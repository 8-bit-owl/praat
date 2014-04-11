/* main_Praat.c
 *
 * Copyright (C) 1992-2005 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * pb 2005/02/27
 */

#include "praat.h"
#include "praat_version.h"

static void logo (Graphics g) {
	Graphics_setWindow (g, 0, 1, -0.14, 0.80);
	Graphics_setTextAlignment (g, Graphics_CENTRE, Graphics_HALF);
	Graphics_setFont (g, Graphics_TIMES);
	Graphics_setFontSize (g, 45);
	Graphics_setColour (g, Graphics_MAROON);
	#if defined (macintosh)
		Graphics_text (g, 0.375, 0.66, "P");
		Graphics_text (g, 0.447, 0.66, "\\s{R}");
		Graphics_text (g, 0.515, 0.66, "\\s{A}");
		Graphics_text (g, 0.580, 0.66, "\\s{A}");
		Graphics_text (g, 0.635, 0.66, "\\s{T}");
	#else
		Graphics_text (g, 0.5, 0.66, "P\\s{RAAT}");
	#endif
	Graphics_setFontSize (g, 15);
	Graphics_text (g, 0.5, 0.55, "%%doing phonetics by computer");
	#define xstr(s) str(s)
	#define str(s) #s
	Graphics_text (g, 0.5, 0.45, "version " xstr(PRAAT_VERSION));
	Graphics_setColour (g, Graphics_BLACK);
	Graphics_setFontSize (g, 14);
	Graphics_text (g, 0.5, 0.33, "www.praat.org");
	Graphics_setFont (g, Graphics_HELVETICA);
	Graphics_setFontSize (g, 10);
	Graphics_text (g, 0.5, 0.16, "Copyright  \\co 1992-" xstr(PRAAT_YEAR) " by Paul Boersma and David Weenink");
	Graphics_text (g, 0.5, 0.04, "PostScript phonetic font:  \\co 2005-2006 Fukui Rei & Rafael Laboissi\\e`re");
	Graphics_text (g, 0.5, -0.02, "GNU Scientific Library:  \\co 1996-2001 Gerard Jungman & Brian Gough");
	Graphics_text (g, 0.5, -0.08, "PortAudio:  \\co 1999-2006 Ross Bencina, Phil Burk, Bjorn Roche");
}

int main (int argc, char *argv []) {
	praat_setLogo (130, 130*0.70, logo);
	praat_init ("Praat", argc, argv);
	INCLUDE_LIBRARY (praat_uvafon_init)
	praat_run ();
	return 0;
}

/* End of file main_Praat.c */
