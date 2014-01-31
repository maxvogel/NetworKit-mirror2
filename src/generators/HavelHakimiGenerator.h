/*
 * HavelHakimiGenerator.h
 *
 *  Created on: Dec 10, 2013
 *      Author: Henning
 */

#ifndef HAVELHAKIMIGENERATOR_H_
#define HAVELHAKIMIGENERATOR_H_

#include <vector>
#include <stack>

#include "../graph/Graph.h"
#include "../auxiliary/ShellList.h"
#include "StaticGraphGenerator.h"

namespace NetworKit {

/**
 * 	Havel-Hakimi algorithm for generating a graph according to a given degree sequence.
 * 	The sequence, if it is realizable, is reconstructed exactly.
 *  The resulting graph usually has a high clustering coefficient.
 *  Construction runs in linear time O(m).
 */
class HavelHakimiGenerator: public NetworKit::StaticGraphGenerator  {
protected:
	std::vector<count> seq;
	bool realizable;

public:
	/**
	 * @param sequence Degree sequence to realize. Must be non-increasing.
	 */
	HavelHakimiGenerator(const std::vector<count>& sequence);
	virtual ~HavelHakimiGenerator() = default;

	/**
	 * Erdoes-Gallai test if degree sequence seq is realizable.
	 */
	virtual bool isRealizable();

	virtual bool getRealizable() const;

	/**
	 * Generates degree sequence seq (if it is realizable).
	 * @return Empty graph if graph is not realizable, otherwise graph with degree sequence seq.
	 */
	virtual Graph generate() override;
};


} /* namespace NetworKit */
#endif /* HAVELHAKIMIGENERATOR_H_ */
