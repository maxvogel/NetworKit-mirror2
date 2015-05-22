/*
 * Globals.cpp
 *
 *  Created on: 06.02.2013
 *      Author: Christian Staudt (christian.staudt@kit.edu)
 */

#include "Globals.h"
#include "auxiliary/Log.h"

bool PRINT_PROGRESS = true;
bool RAND_ORDER = false; 	///< don't randomize LabelPropagation node order by default, since this seems to be faster and slightly better
uint64_t INACTIVE_SEEDS = 0;		///< number of seed nodes which are set inactive for first iteration
bool NORMALIZE_VOTES = false; ///< if set, normalize votes of LP by dividing edge weight by weighted degree


double SCALE_STRENGTH = 0.0; ///< if set, scale cluster strengths in LP


uint64_t MIN_NUM_COMMUNITIES = 2; ///< minimum number of communities, so far only used by agglomerative clustering
double REL_REPEAT_THRSH = 5e-3; ///< threshold for minimum number of matching edges relative to number of vertices to proceed agglomeration

bool CALC_DISSIMILARITY = false; ///< if set, calculate and print base clustering dissimilarity for ensemble (expensive!)

int MAX_LOUVAIN_ITERATIONS = 32; ///< maximum number of iterations within contractions in Louvain algorithm

#ifndef _OPENMP
int omp_get_thread_num() {
	ERROR("OpenMP is not available");
	return 0;
}
int omp_get_max_threads() {
	ERROR("OpenMP is not available");
	return 1;
}
#endif