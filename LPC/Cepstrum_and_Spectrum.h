#ifndef _Cepstrum_and_Spectrum_h_
#define _Cepstrum_and_Spectrum_h_
/* Cepstrum_and_Spectrum.h
 *
 * Copyright (C) 1994-2012, 2015 David Weenink
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "Spectrum.h"
#include "Cepstrum.h"

autoCepstrum Spectrum_to_Cepstrum (Spectrum me);

autoSpectrum Cepstrum_to_Spectrum (Cepstrum me);

autoPowerCepstrum Spectrum_to_PowerCepstrum (Spectrum me);

#endif /* _Cepstrum_and_Spectrum_h_ */
