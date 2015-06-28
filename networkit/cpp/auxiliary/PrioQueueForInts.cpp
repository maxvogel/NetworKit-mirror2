/*
 * BucketPQ.cpp
 *
 *  Created on: 26.06.2015
 *      Author: Henning
 */

#include "PrioQueueForInts.h"

namespace Aux {


PrioQueueForInts::PrioQueueForInts(std::vector<index>& elems, index maxPrio):
		buckets(maxPrio+1), nodePtr(elems.size()), myBucket(elems.size(), NetworKit::none),
		minNotEmpty(maxPrio+1), maxNotEmpty(-1), maxPrio(maxPrio)
{
	for (index i = 0; i < elems.size(); ++i) {
		insert(i, elems[i]);
	}
}

void PrioQueueForInts::changePrio(index elem, index prio) {
	remove(elem);
	insert(elem, prio);
}


void PrioQueueForInts::insert(index elem, index prio) {
	assert(0 <= prio && prio <= maxPrio);
	assert(0 <= elem && elem < nodePtr.size());

	buckets[prio].push_front(elem);
	nodePtr[elem] = buckets[prio].begin();
	myBucket[elem] = prio;

	// bookkeeping
	if (prio < minNotEmpty || minNotEmpty > maxPrio) {
		minNotEmpty = prio;
	}
	if (maxNotEmpty < 0 || prio > (unsigned int) maxNotEmpty) {
		maxNotEmpty = prio;
	}
}

index PrioQueueForInts::extractMin() {
	if (minNotEmpty > maxPrio) {
		return NetworKit::none;
	}
	else {
		assert(! buckets[minNotEmpty].empty());
		index result = buckets[minNotEmpty].front();
		remove(result);
		return result;
	}
}

index PrioQueueForInts::extractMax() {
	if (maxNotEmpty < 0) {
		return NetworKit::none;
	}
	else {
		assert(! buckets[maxNotEmpty].empty());
		index result = buckets[maxNotEmpty].front();
		remove(result);
		return result;
	}
}

void PrioQueueForInts::remove(index elem) {
	assert(0 <= elem && elem < nodePtr.size());

	if (myBucket[elem] != NetworKit::none) {
		// remove from appropriate bucket
		index prio = myBucket[elem];
		buckets[prio].erase(nodePtr[elem]);
		myBucket[elem] = NetworKit::none;

		// adjust max pointer if necessary
		while (buckets[maxNotEmpty].empty() && maxNotEmpty >= 0) {
			--maxNotEmpty;
		}

		// adjust min pointer if necessary
		while (buckets[minNotEmpty].empty() && minNotEmpty <= maxPrio) {
			++minNotEmpty;
		}
	}
}

index PrioQueueForInts::extractAt(index prio) {
	assert(0 <= prio && prio <= maxPrio);
	if (buckets[prio].empty()) {
		return NetworKit::none;
	}
	else {
		index result = buckets[prio].front();
		myBucket[result] = NetworKit::none;
		buckets[prio].pop_front();
		return result;
	}
}

index PrioQueueForInts::priority(index elem) {
	return myBucket[elem];
}

} /* namespace Aux */
