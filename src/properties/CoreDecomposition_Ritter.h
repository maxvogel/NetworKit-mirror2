/*
 * CoreDecomposition_Ritter.h
 */

#ifndef COREDECOMPOSITION_RITTER_H_
#define COREDECOMPOSITION_RITTER_H_

#include <vector>
#include "../graph/Graph.h"

namespace NetworKit {

/**
 * Computes k-core decomposition of a graph.
 */
class CoreDecomposition_Ritter {
public:
	CoreDecomposition_Ritter();
	virtual ~CoreDecomposition_Ritter();

	/**
	 * @return k-core decomposition of graph @a G.
	 */
	std::vector<count> run(const Graph& G);
};

} /* namespace NetworKit */
#endif /* COREDECOMPOSITION_RITTER_H_ */
