/* HMM_def.h
 *
 * Copyright (C) 2010-2011, 2015 David Weenink
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

/*
 djmw 20100929 Initial definition.
 djmw 20110329 oo_STRINGW -> oo_STRING
 */


#define ooSTRUCT HMMState
oo_DEFINE_CLASS (HMMState, Daata)

	oo_STRING(label)

oo_END_CLASS(HMMState)
#undef ooSTRUCT


#define ooSTRUCT HMMObservation
oo_DEFINE_CLASS (HMMObservation, Daata)

	oo_STRING(label)
	oo_AUTO_OBJECT (GaussianMixture, 1, gm)

oo_END_CLASS(HMMObservation)
#undef ooSTRUCT


#define ooSTRUCT HMM
oo_DEFINE_CLASS (HMM, Daata)

	oo_INT (notHidden) // to model a Markov model instead of HMM
	oo_INT (leftToRight)
	oo_LONG (numberOfStates)
	oo_LONG (numberOfObservationSymbols)
	oo_LONG (numberOfMixtureComponents)
	oo_LONG (componentDimension)
	oo_INT (componentStorage)
	oo_DOUBLE_MATRIX_FROM (transitionProbs, 0, numberOfStates, 1, numberOfStates + 1) // row 0: initial probabilities
	oo_DOUBLE_MATRIX (emissionProbs, numberOfStates, numberOfObservationSymbols)
	oo_AUTO_OBJECT (Ordered, 1, states)
	oo_AUTO_OBJECT (Ordered, 1, observationSymbols)

	#if oo_DECLARING
		void v_info ()
			override;
	#endif

oo_END_CLASS(HMM)
#undef ooSTRUCT


#define ooSTRUCT HMMViterbi
oo_DEFINE_CLASS (HMMViterbi, Daata)
	oo_LONG (numberOfTimes)
	oo_LONG (numberOfStates)
	oo_DOUBLE (prob)
	oo_DOUBLE_MATRIX (viterbi, numberOfStates, numberOfTimes)
	oo_LONG_MATRIX (bp, numberOfStates, numberOfTimes)
	oo_LONG_VECTOR (path, numberOfTimes)
oo_END_CLASS(HMMViterbi)
#undef ooSTRUCT


/* End of file HMM_def.h */
