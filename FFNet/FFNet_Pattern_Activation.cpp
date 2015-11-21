/* FFNet_Pattern_Activation.cpp
 *
 * Copyright (C) 1994-2011,2015 David Weenink, 2015 Paul Boersma
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
 djmw 19960826
 djmw 20020712 GPL header
 djmw 20030701 Removed non-GPL minimizations
 djmw 20040416 More precise error messages.
 djmw 20041118 Added FFNet_Pattern_Categories_getCosts.
*/

#include "Graphics.h"
#include "FFNet_Pattern_Activation.h"

static double func (Daata object, const double p[]) {
	FFNet me = (FFNet) object;
	Minimizer thee = my minimizer.peek();
	double fp = 0.0;

	for (long j = 1, k = 1; k <= my nWeights; k++) {
		my dw[k] = 0.0;
		if (my wSelected[k]) {
			my w[k] = p[j++];
		}
	}
	for (long i = 1; i <= my nPatterns; i++) {
		FFNet_propagate (me, my inputPattern[i], nullptr);
		fp += FFNet_computeError (me, my targetActivation[i]);
		FFNet_computeDerivative (me);
		/* derivative (cumulative) */
		for (long k = 1; k <= my nWeights; k++) {
			my dw[k] += my dwi[k];
		}
	}
	thy funcCalls++;
	return fp;
}

static void dfunc_optimized (Daata object, const double p[], double dp[]) {
	FFNet me = (FFNet) object;
	(void) p;

	long j = 1;
	for (long k = 1; k <= my nWeights; k++) {
		if (my wSelected[k]) {
			dp[j++] = my dw[k];
		}
	}
}

static void _FFNet_Pattern_Activation_checkDimensions (FFNet me, Pattern p, Activation a) {
	if (my nInputs != p -> nx) {
		Melder_throw (U"The Pattern and the FFNet do not match.\nThe number of columns in the Pattern must equal the number of inputs in the FFNet.");
	}
	if (my nOutputs != a -> nx) {
		Melder_throw (U"The Activation and the FFNet do not match.\nThe number of columns in the Activation must equal the number of outputs in the FFNet.");
	}
	if (p -> ny != a -> ny) {
		Melder_throw (U"The Pattern and the Activation do not match.\nThe number of rows in the Pattern must equal the number of rows in the Activation.");
	}
	if (! _Pattern_checkElements (p)) {
		Melder_throw (U"All Pattern elements must be in the interval [0, 1].\nYou could use \"Formula...\" to scale the Pattern values first.");	}
	if (! _Activation_checkElements (a)) {
		Melder_throw (U"All Activation elements must be in the interval [0, 1].\nYou could use \"Formula...\" to scale the Activation values first.");
	}
}

static void _FFNet_Pattern_Activation_learn (FFNet me, Pattern pattern, Activation activation, long maxNumOfEpochs, double tolerance, int costFunctionType, bool reset) {
	try {
		_FFNet_Pattern_Activation_checkDimensions (me, pattern, activation);

		// Link the things to be learned

		my nPatterns = pattern -> ny;
		my inputPattern = pattern -> z;
		my targetActivation = activation -> z;
		FFNet_setCostFunction (me, costFunctionType);

		if (reset) {
			autoNUMvector<double> wbuf (1, my dimension);
			long k = 1;
			for (long i = 1; i <= my nWeights; i++) {
				if (my wSelected[i]) {
					wbuf[k++] = my w[i];
				}
			}
			Minimizer_reset (my minimizer.peek(), wbuf.peek());
		}

		Minimizer_minimize (my minimizer.peek(), maxNumOfEpochs, tolerance, 1);

		// Unlink

		my nPatterns = 0;
		my inputPattern = nullptr;
		my targetActivation = nullptr;
	} catch (MelderError) {
		my nPatterns = 0;
		my inputPattern = nullptr;
		my targetActivation = nullptr;
	}
}


void FFNet_Pattern_Activation_learnSD (FFNet me, Pattern p, Activation a, long maxNumOfEpochs, double tolerance, double learningRate, double momentum, int costFunctionType) {
	int resetMinimizer = 0;
	/* Did we choose another minimizer */
	if (my minimizer && ! Thing_isa (my minimizer.peek(), classSteepestDescentMinimizer)) {
		my minimizer.reset();
		resetMinimizer = 1;
	}
	/* create the minimizer if it doesn't exist */
	if (! my minimizer) {
		resetMinimizer = 1;
		my minimizer = SteepestDescentMinimizer_create (my dimension, me, func, dfunc_optimized);
	}
	((SteepestDescentMinimizer) my minimizer.get()) -> eta = learningRate;
	((SteepestDescentMinimizer) my minimizer.get()) -> momentum = momentum;
	_FFNet_Pattern_Activation_learn (me, p, a, maxNumOfEpochs, tolerance, costFunctionType, resetMinimizer);
}

void FFNet_Pattern_Activation_learnSM (FFNet me, Pattern p, Activation a, long maxNumOfEpochs, double tolerance, int costFunctionType) {
	int resetMinimizer = 0;

	// Did we choose another minimizer

	if (my minimizer.peek() && ! Thing_isa (my minimizer.peek(), classVDSmagtMinimizer)) {
		my minimizer.reset();
		resetMinimizer = 1;
	}
	// create the minimizer if it doesn't exist
	if (! my minimizer.peek()) {
		resetMinimizer = 1;
		my minimizer = VDSmagtMinimizer_create (my dimension, me, func, dfunc_optimized);
	}
	_FFNet_Pattern_Activation_learn (me, p, a, maxNumOfEpochs, tolerance, costFunctionType, resetMinimizer);
}

double FFNet_Pattern_Activation_getCosts_total (FFNet me, Pattern p, Activation a, int costFunctionType) {
	try {
		_FFNet_Pattern_Activation_checkDimensions (me, p, a);
		FFNet_setCostFunction (me, costFunctionType);

		double cost = 0.0;
		for (long i = 1; i <= p -> ny; i++) {
			FFNet_propagate (me, p -> z[i], nullptr);
			cost += FFNet_computeError (me, a -> z[i]);
		}
		return cost;
	} catch (MelderError) {
		return NUMundefined;
	}
}

double FFNet_Pattern_Activation_getCosts_average (FFNet me, Pattern p, Activation a, int costFunctionType) {
	double costs = FFNet_Pattern_Activation_getCosts_total (me, p, a, costFunctionType);
	return costs == NUMundefined ? NUMundefined : costs / p -> ny;
}

autoActivation FFNet_Pattern_to_Activation (FFNet me, Pattern p, long layer) {
	try {
		if (layer < 1 || layer > my nLayers) {
			layer = my nLayers;
		}
		if (my nInputs != p -> nx) {
			Melder_throw (U"The Pattern and the FFNet do not match. The number of colums in the Pattern (", p -> nx, U") should equal the number of inputs in the FFNet (", my nInputs, U").");
		}
		if (! _Pattern_checkElements (p)) {
			Melder_throw (U"All Pattern elements must be in the interval [0, 1].\nYou could use \"Formula...\" to scale the Pattern values first.");
		}
		long nPatterns = p -> ny;
		autoActivation thee = Activation_create (nPatterns, my nUnitsInLayer[layer]);

		for (long i = 1; i <= nPatterns; i++) {
			FFNet_propagateToLayer (me, p -> z[i], thy z[i], layer);
		}
		return thee;
	} catch (MelderError) {
		Melder_throw (me, U": no Activation created.");
	}
}

/* End of file FFNet_Pattern_Activation.cpp */
