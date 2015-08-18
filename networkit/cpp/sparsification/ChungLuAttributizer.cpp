/*
 * ChungLuAttributizer.cpp
 *
 *  Created on: 20.11.2014
 *      Author: Michael Hamann
 */

#include "ChungLuAttributizer.h"

namespace NetworKit {

ChungLuAttributizer::ChungLuAttributizer(const Graph& graph) : graph(graph) {}

std::vector< double > ChungLuAttributizer::getAttribute() {
	if (!graph.hasEdgeIds()) {
		throw std::runtime_error("edges have not been indexed - call indexEdges first");
	}

	std::vector< double > result(graph.upperEdgeIdBound());
	
	graph.parallelForEdges([&](node u, node v, edgeid eid) {
		result[eid] = 1.0 / (graph.degree(u) * graph.degree(v));
	});
	
	return result;
}

} /* namespace NetworKit */