/*
 * MultiscaleAttributizer.cpp
 *
 *  Created on: 20.06.2014
 *      Author: Gerd Lindner
 */

#include "MultiscaleAttributizer.h"

namespace NetworKit {

MultiscaleAttributizer::MultiscaleAttributizer(const Graph& graph, const std::vector<double>& attribute) : graph(graph), attribute(attribute) {}

std::vector<double> MultiscaleAttributizer::getAttribute() {
	if (!graph.hasEdgeIds()) {
		throw std::runtime_error("edges have not been indexed - call indexEdges first");
	}

	//The following vector is used for the _local_ normalization of edgeweights.
	//We use a global vector for performance reasons.
	std::vector<edgeweight> normalizedWeights(graph.upperNodeIdBound());

	std::vector<double> multiscaleAttribute(graph.upperEdgeIdBound(), 0.0);

	graph.forNodes([&](node u) {
		count k = graph.degree(u);

		//Normalize edgeweights of N(u)
		edgeweight sum = 0.0;
		graph.forNeighborsOf(u, [&](node _u, node v, edgeid eid) {
			sum += attribute[eid];
		});
		graph.forNeighborsOf(u, [&](node _u, node v, edgeid eid) {
			normalizedWeights[v] = attribute[eid] / sum;
		});

		//Filter edges by probability
		graph.forNeighborsOf(u, [&](node _u, node v, edgeid eid) {
			//In case d(u) == 1 and d(v) > 1: ignore u
			//if (k > 1 || graph.degree(v) == 1) {
				edgeweight p = normalizedWeights[v];
				double probability = getProbability(k, p);

				multiscaleAttribute[eid] = std::max(multiscaleAttribute[eid], probability);
			//}
		});
	});

	return multiscaleAttribute;
}

/**
 * Returns the probability that a node of the given
 * degree has an edge of the given weight.
 *
 * The null hypothesis is the following: the normalized weights of the
 * edges connected to a node of degree k are uniformly distributed.
 */
double MultiscaleAttributizer::getProbability(count degree, edgeweight normalizedWeight) {
	return 1 - pow(1 - normalizedWeight, degree - 1);
}

} /* namespace NetworKit */